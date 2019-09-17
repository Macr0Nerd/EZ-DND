#pragma once

#ifndef EZDND_NETWORK_HPP
#define EZDND_NETWORK_HPP

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <array>
#include <string>
#include <stdexcept>
#include <Poco/StreamCopier.h>
#include <Poco/FileStream.h>
#include <Poco/Timespan.h>
#include <Poco/Thread.h>
#include <Poco/Runnable.h>
#include <Poco/BinaryWriter.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/Socket.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/SocketStream.h>
#include <Poco/Net/NetException.h>
#include <Poco/Net/TCPServer.h>

/**
 * Because I, Gabriele Ron,
 * firmly believe in freeware,
 * open source, and proper attribution,
 * I need to correctly provide a source for the base of this code
 *
 * The base code (for the TCPServer) was built off of
 * https://stackoverflow.com/questions/16510205/multithread-tcp-server-with-poco-c-libraries
 * this SO post. This has been modified, but I believe that
 * I should be honest on the base stuff.
 *
 * :)
 */

class server : public Poco::Net::TCPServerConnection {
public:
    explicit server(const Poco::Net::StreamSocket& s) : TCPServerConnection(s) {}

    void sendFile(const std::string& file) {
        Poco::Net::SocketStream ostr(socket());

        Poco::FileInputStream istr(file, std::ios::binary);
        Poco::StreamCopier::copyStream(istr, ostr);
    }

    void recieveFile(const std::string& file) {
        unsigned char mess[5] = "Ack!";
        socket().sendBytes(mess, sizeof(mess));

        Poco::Net::SocketStream istr(socket());

        Poco::FileOutputStream ostr(file, std::ios::binary);

        Poco::StreamCopier::copyStream(istr, ostr);
    }

    std::string action() {
        unsigned char mess[5] = "Ack!"; std::string action;
        socket().sendBytes(mess, sizeof(mess));

        unsigned char inBuff[1000];
        socket().receiveBytes(inBuff, sizeof(inBuff));

        action = std::string(reinterpret_cast<char const*>(inBuff));
        action.erase(remove_if(action.begin(), action.end(), [](char c){ return c != ' ' && !isalnum(c) && c != ','; } ), action.end());

        return action;
    }

    void run() final {
        std::clog << "New connection from: " << socket().peerAddress().host().toString() << std::endl << std::flush;
        bool isOpen = true;
        Poco::Timespan timeOut(10, 0);
        unsigned char inBuff[1000];
        std::string message;

        while (isOpen) {
            if (!socket().poll(timeOut, Poco::Net::Socket::SELECT_READ)) {
                std::cerr << "TIMEOUT!" << std::endl << std::flush;
            } else {
                std::clog << "RX EVENT!!! ---> " << std::flush;
                int nBytes = -1;

                try {
                    nBytes = socket().receiveBytes(inBuff, sizeof(inBuff));
                    message = std::string(reinterpret_cast<char const*>(inBuff));
                    message.erase(remove_if(message.begin(), message.end(), [](char c){ return isspace(c) || !isalpha(c); } ), message.end());
                } catch (Poco::Exception &exc) {
                    //Handle your network errors.
                    std::cerr << "Network error: " << exc.displayText() << std::endl;
                    isOpen = false;
                }

                if (nBytes == 0) {
                    std::clog << "Client closes connection!" << std::endl << std::flush;
                    isOpen = false;
                } else {
                    std::clog << "Receiving data: " << message << std::endl << std::flush;

                    if(message == "File") {
                        std::string file;
                        std::cout << "Enter filename: "; std::cin >> file;
                        recieveFile(file);
                    } else if (message == "Act") {
                        std::clog << action() << std::endl << std::flush;
                    }
                }
            }
        }

        std::cout << "Connection closed" << std::endl << std::flush;
    }
};

class client : public Poco::Net::SocketStream {
public:
    client(Poco::Net::StreamSocket& ss) : SocketStream(ss){}

    void recieveFile(const std::string& f) {
        Poco::Net::SocketStream istr(socket());
        Poco::FileOutputStream ostr(f, std::ios::binary);
        Poco::StreamCopier::copyStream(istr, ostr);
    }

    void sendFile(const std::string& f) {
        unsigned char inBuff[1000];
        unsigned char mess[5] = "File";
        std::string message;
        socket().sendBytes(mess, sizeof(mess));

        int x = 0;
        while(true) {
            try {
                socket().receiveBytes(inBuff, sizeof(inBuff));
                message = std::string(reinterpret_cast<char const*>(inBuff));
                message.erase(message.length()-1);
                if (message == "Ack!") {
                    break;
                } else {
                    continue;
                }
            } catch (Poco::Exception& /*e*/){
                ++x;
                if(x > 5) {
                    throw std::out_of_range("No ack received");
                }
            }
        }

        Poco::Net::SocketStream ostr(socket());

        Poco::FileInputStream istr(f, std::ios::binary);
        Poco::StreamCopier::copyStream(istr, ostr);
    }
};

#endif /* EZDND_NETWORK_HPP */
