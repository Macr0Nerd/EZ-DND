#include <iostream>
#include <vector>
#include "Core/network.hpp"

using std::cout;
using std::cin;
using std::endl;

int main(){
    Poco::Net::ServerSocket svs(42069);

    //Configure some server params.
    auto* pParams = new Poco::Net::TCPServerParams();
    pParams->setMaxThreads(7);
    pParams->setMaxQueued(1);
    pParams->setThreadIdleTime(250000000);

    //Create your server
    Poco::Net::TCPServer myServer(new Poco::Net::TCPServerConnectionFactoryImpl<server>(), svs, pParams);
    myServer.start();

    while(1);

    return 0;
}