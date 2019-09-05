#include <iostream>
#include <utility>
#include <Poco/StreamCopier.h>
#include <Poco/FileStream.h>
#include <Poco/Timespan.h>
#include <Poco/Thread.h>
#include <Poco/Runnable.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/Socket.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/SocketStream.h>

using std::cout;
using std::cin;
using std::endl;

class Send : public Poco::Runnable {
public:
    Send(std::string  f, int p) : file(std::move(f)), port(p) {};

    virtual void run(){
        Poco::Net::ServerSocket srvs(Poco::Net::SocketAddress("localhost", port));
        Poco::Timespan span(250000);

        while(true) {
            if(srvs.poll(span, Poco::Net::Socket::SELECT_READ)) {
                Poco::Net::StreamSocket strs = srvs.acceptConnection();
                Poco::Net::SocketStream ostr(strs);

                Poco::FileInputStream istr(file, std::ios::binary);
                Poco::StreamCopier::copyStream(istr, ostr);
            } else {
                break;
            }
        }
    }

private:
    int port;
    std::string file;
};

class Reci : public Poco::Runnable {
public:
    Reci(std::string f, int p) : file(std::move(f)), port(p) {}

    virtual void run() {
        Poco::Net::StreamSocket ss;
        ss.connect(Poco::Net::SocketAddress("localhost", port));
        Poco::Net::SocketStream istr(ss);

        Poco::FileOutputStream ostr(file, std::ios::binary);
        Poco::StreamCopier::copyStream(istr, ostr);
    }

private:
    int port;
    std::string file;
};

int main(){
    Send send("data/fred.ezdc", 1560);
    Reci reci("test.ezdc", 1560);
    Poco::Thread threadSend, threadReci;

    threadSend.start(send);
    threadReci.start(reci);
    threadReci.join();
    threadSend.join();

    return 0;
}