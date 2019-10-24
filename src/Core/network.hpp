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
#include <filesystem>
#include <csignal>
#include <Poco/StreamCopier.h>
#include <Poco/FileStream.h>
#include <Poco/Timespan.h>
#include <Poco/Timestamp.h>
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

/*
 * WARNING
 *
 * DEPRECATED:
 * THIS WAS A MISTAKE
 * NETWORKING SHOULD BE HANDLED BY THE UI
 * ONCE I BUILD A GUI THIS ALL GOES AWAY
 */

bool dist = false;

void sigHandleDistribute(int /*signal*/) {
    std::cout << "Signal activated!" << std::endl << std::flush;
    dist = true;
}

class server : public Poco::Net::TCPServerConnection {
public:
    explicit server(const Poco::Net::StreamSocket& s) : TCPServerConnection(s) {}

    int sendFile(const std::string& file) {
        std::string message;
        unsigned char mess[5] = "File";
        socket().sendBytes(mess, sizeof(mess));

        unsigned char inBuff[5];
        socket().receiveBytes(inBuff, sizeof(inBuff));

        message = std::string(reinterpret_cast<char const*>(inBuff));
        message.erase(remove_if(message.begin(), message.end(), [](char c){ return (isspace(c) || !isalpha(c)) && c != '!';} ), message.end());
        message = message.substr(0, 4);

        if(message == "Ack!") {
            Poco::Net::SocketStream ostr(socket());

            Poco::FileInputStream istr(file, std::ios::binary);
            Poco::StreamCopier::copyStream(istr, ostr);

            return 1;
        } else {
            return 0;
        }
    }

    void recieveFile(const std::string& file) {
        unsigned char mess[5] = "Ack!";
        socket().sendBytes(mess, sizeof(mess));

        Poco::Net::SocketStream istr(socket());

        Poco::FileOutputStream ostr(file, std::ios::binary);

        Poco::StreamCopier::copyStream(istr, ostr);
    }

    int act(const std::string& action) {
        unsigned char mess[4] = "Act"; std::string message;
        socket().sendBytes(mess, sizeof(mess));

        unsigned char inBuff[5];
        socket().receiveBytes(inBuff, sizeof(inBuff));

        message = reinterpret_cast<const char*>(inBuff);
        message.erase(std::remove_if(message.begin(), message.end(), [](char c){ return !isspace(c) && !isalnum(c); }), message.end());
        message = message.substr(0, 4);

        if (message == "Ack!") {
            unsigned char act[action.size() + 1];
            std::copy(action.begin(), action.end(), act);

            socket().sendBytes(act, sizeof(act));
            return 1;
        } else {
            return 0;
        }
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

    int distribute(const std::string& dir) {
        int ret = 1;

        unsigned char dbeg[5] = "Dbeg";
        socket().sendBytes(dbeg, sizeof(dbeg));

        for(auto &i : std::filesystem::recursive_directory_iterator(dir)) {
            ret = sendFile(dir + i.path().filename().string());

            if(!ret) {
                return 0;
            }
        }

        unsigned char dfin[5] = "Dfin";
        socket().sendBytes(dfin, sizeof(dfin));

        dist = false;
        return ret;
    }

    void run() final {
        std::clog << "New connection from: " << socket().peerAddress().host().toString() << std::endl << std::flush;
        bool isOpen = true;
        Poco::Timespan timeOut(10, 0);
        unsigned char inBuff[1000];
        std::string message;

        signal(SIGINT, sigHandleDistribute);

        while (isOpen) {
            if (!socket().poll(timeOut, Poco::Net::Socket::SELECT_READ)) {
                std::cerr << "TIMEOUT!" << std::endl << std::flush;
            } else {
                std::clog << "RX EVENT!!! ---> " << std::flush;
                int nBytes = -1;

                if (dist) {
                    std::string dir;
                    std::cout << "Enter the directory to send: ";
                    std::cin >> dir;

                    distribute(dir);
                }

                try {
                    nBytes = socket().receiveBytes(inBuff, sizeof(inBuff));
                    message = std::string(reinterpret_cast<char const *>(inBuff));
                    message.erase(
                            remove_if(message.begin(), message.end(), [](char c) { return isspace(c) || !isalpha(c); }),
                            message.end());
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

                    if (message == "File") {
                        std::string file;
                        std::cout << "Enter filename: ";
                        std::cin >> file;
                        recieveFile(file);
                    } else if (message == "Act") {
                        std::clog << action() << std::endl << std::flush;
                    } else if (message == "Ping") {
                        unsigned char mess[5] = "Pong";
                        socket().sendBytes(mess, sizeof(mess));
                    } else if (message == "Test") {
                        sendFile("data/fred.ezdc");
                    }
                }
            }
        }

        std::cout << "Connection closed" << std::endl << std::flush;
    }
};

///TODO: Actually test the client rather than assume it works
class client {
public:
    explicit client(const std::string& server) : ss(Poco::Net::SocketAddress(server, 42069)) {}

    int sendFile(const std::string& file) {
        std::string message;
        unsigned char mess[5] = "File";
        ss.sendBytes(mess, sizeof(mess));

        unsigned char inBuff[5];
        ss.receiveBytes(inBuff, sizeof(inBuff));

        message = std::string(reinterpret_cast<char const*>(inBuff));
        message.erase(remove_if(message.begin(), message.end(), [](char c){ return isspace(c) || !isalpha(c); } ), message.end());
        message = message.substr(0, 4);

        if(message == "Ack!") {
            Poco::Net::SocketStream ostr(ss);

            Poco::FileInputStream istr(file, std::ios::binary);
            Poco::StreamCopier::copyStream(istr, ostr);

            return 1;
        } else {
            return 0;
        }
    }

    void recieveFile(const std::string& file) {
        unsigned char mess[5] = "Ack!";
        ss.sendBytes(mess, sizeof(mess));

        Poco::Net::SocketStream istr(ss);

        Poco::FileOutputStream ostr(file, std::ios::binary);

        Poco::StreamCopier::copyStream(istr, ostr);
    }

    int act(const std::string& action) {
        unsigned char mess[4] = "Act"; std::string message;
        ss.sendBytes(mess, sizeof(mess));

        unsigned char inBuff[5];
        ss.receiveBytes(inBuff, sizeof(inBuff));

        message = reinterpret_cast<const char*>(inBuff);
        message.erase(std::remove_if(message.begin(), message.end(), [](char c){ return !isspace(c) && !isalnum(c); }), message.end());
        message.substr(0, 4);

        if (message == "Ack!") {
            unsigned char act[action.size() + 1];
            std::copy(action.begin(), action.end(), act);

            ss.sendBytes(act, sizeof(act));
            return 1;
        } else {
            return 0;
        }
    }

    std::string action() {
        unsigned char mess[5] = "Ack!"; std::string action;
        ss.sendBytes(mess, sizeof(mess));

        unsigned char inBuff[1000];
        ss.receiveBytes(inBuff, sizeof(inBuff));

        action = std::string(reinterpret_cast<char const*>(inBuff));
        action.erase(remove_if(action.begin(), action.end(), [](char c){ return c != ' ' && !isalnum(c) && c != ','; } ), action.end());

        return action;
    }

    void run() {
        std::clog << "Connecting to " << ss.peerAddress().host().toString() << "" << std::endl << std::flush;
        bool isOpen = true;
        Poco::Timespan timeOut(10, 0);
        unsigned char inBuff[1000];
        std::string message, dir, charFile;
        Poco::Timestamp time;

        std::cout << "Enter the character to send: " << std::endl << std::flush;
        std::cin >> charFile;

        sendFile(charFile);

        while (isOpen) {
            if (!ss.poll(timeOut, Poco::Net::Socket::SELECT_READ)) {
                std::cerr << "TIMEOUT!" << std::endl << std::flush;
            } else {
                if (time.elapsed() >= 20000000) {
                    unsigned char ping[5] = "Ping";
                    ss.sendBytes(ping, sizeof(ping));

                    unsigned char pong[5];
                    ss.receiveBytes(pong, sizeof(pong));
                    std::string p = std::string(reinterpret_cast<char const*>(pong));
                    p.erase(remove_if(p.begin(), p.end(), [](char c){ return !isalnum(c); } ), p.end());

                    if(p != "Pong") {
                        throw Poco::Net::HostNotFoundException("The host did not respond to the ping");
                    }

                    time.update();
                }

                std::clog << "RX EVENT!!! ---> " << std::flush;
                int nBytes = -1;

                try {
                    nBytes = ss.receiveBytes(inBuff, sizeof(inBuff));
                    message = std::string(reinterpret_cast<char const*>(inBuff));
                    message.erase(remove_if(message.begin(), message.end(), [](char c){ return isspace(c) || !isalpha(c); } ), message.end());
                } catch (Poco::Exception &exc) {
                    //Handle your network errors.
                    std::cerr << "Network error: " << exc.displayText() << std::endl;
                    isOpen = false;
                }

                if (nBytes == 0) {
                    std::clog << "Server closed connection!" << std::endl << std::flush;
                    isOpen = false;
                } else {
                    std::clog << "Receiving data: " << message << std::endl << std::flush;

                    if(message == "File") {
                        std::string file;
                        std::cout << "Enter filename: "; std::cin >> file;

                        recieveFile(dir + file);
                    } else if (message == "Act") {
                        std::clog << action() << std::endl << std::flush;
                    } else if (message == "Dbeg") {
                        dir = "dat/";
                    } else if (message == "Dfin") {
                        dir.clear();
                    }
                }
            }
        }

        std::cout << "Connection closed" << std::endl << std::flush;
    }

private:
    Poco::Net::StreamSocket ss;
};

#endif /* EZDND_NETWORK_HPP */
