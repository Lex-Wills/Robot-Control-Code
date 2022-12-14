
#include <iostream>
#include <boost/asio.hpp>
#include <boost/program_options.hpp>


#include "tcp/tcp_server.h"

#include "../detail/serial/RX150SerialInterface.h"
#include "../detail/tcp/RobotServerComm.h"

namespace po = boost::program_options;
using namespace std;

int main(int argc, char* argv[]){

    int serialPort = 0;

    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "produce help message")
            ("serialPort,s", po::value<int>(&serialPort)->default_value(serialPort), "Serial port number")
            ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << "\n";
        return 1;
    }

    if (vm.count("compression")) {
        cout << "Compression level was set to "
             << vm["compression"].as<int>() << ".\n";
    } else {
        cout << "Compression level was not set.\n";
    }


    try
    {
        boost::asio::io_service io_service;
        tcp_server server(io_service, ROBOT_SERVER_PORT, RX150SerialInterface::create(serialPort));
        io_service.run();
//        cout << AX18ASerialInterface::create(serialPort)->getCurrentJointAngles() << endl;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
