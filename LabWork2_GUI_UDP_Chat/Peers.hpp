#ifndef __PEERS_HPP__
#define __PEERS_HPP__

#include <udpSocket.hpp>
#include <multicastUDPsocket.hpp>
#include <UsefulDataPacket.hpp>

class Peer
{
private:
    UDP_Socket* _privateComUdpSock;
    MulticastUDPsocket* _mcUdpSock;
    string _currentMessage;
    string _buffer;
    usefulDataPacket* _packet;

public:
    //Peer(string IP, unsigned int port, string multicastAddress = MulticastAddress, unsigned int multicastPort = multicastPORT) {
    Peer(string IP, string port, string multicastAddress = "224.0.0.1", string multicastPort = "28000") {
        _privateComUdpSock = new UDP_Socket(IP, port);
        //_mcUdpSock = new MulticastUDPsocket(MulticastAddress, "28000");
        //_mcUdpSock = new MulticastUDPsocket(multicastAddress, multicastPort);
        _mcUdpSock = new MulticastUDPsocket(multicastAddress, multicastPort);
    }

    ~Peer() { delete _privateComUdpSock; delete _mcUdpSock;}

    string inputMessage(){
        string message;
        cin >> message;
        message += "\0";
        return message;
    }

    std::string readStdIn()
    {
        struct pollfd pfd = { STDIN_FILENO, POLLIN, 0 };

        std::string userInput;
        int ret = -1;
        //while(ret == 0) infinite wait for input
        while(ret == -1) // while poll return error
        {
            ret = poll(&pfd, 1, 5000);  // timeout of 5000ms
            if(ret == 1) // there is something to read
            {
                //std::getline(std::cin, line);
                userInput = inputMessage();
            }
            else if(ret == -1)
            {
                std::cout << "Error: " << strerror(errno) << std::endl;
            }
            else if(ret == 0)
            {
                cout << "[DEBUG]: Timed out for input"<< endl;
            }
        }
        return userInput;
    }

    string userInputMessage(){
        string msg = readStdIn();
        cout << "Sended Message: " << msg << endl;
        return msg;
    }

    bool Select(int connectionTimeOut = 10)
    {
        /*
        The select function returns the total number of socket handles
        that are ready and contained in the fd_set structures,
        zero if the time limit expired, or SOCKET_ERROR if an error occurred.
        */

        timeval timeOut;
        timeOut.tv_usec = 0;
        timeOut.tv_sec = connectionTimeOut;

        fd_set readset;

        FD_ZERO(&readset);
        FD_SET(_privateComUdpSock->getSocket(), &readset);
        FD_SET(_mcUdpSock->getSocket(), &readset);
        int retVal = 0;

        while(true) {

            retVal = ::select(2 + 1,	//Ignored. The nfds parameter is included only for compatibility with Berkeley sockets.
                &readset,//An optional pointer to a set of sockets to be checked for readability.
                NULL,//An optional pointer to a set of sockets to be checked for writability.
                NULL,//An optional pointer to a set of sockets to be checked for errors.
                &timeOut	//The maximum time for select to wait (TIMEVAL structure)
                );
            if(retVal <= 0) { //if timed out for select
                cout << endl << "[DEBUG]: timed out for receivng message" << endl;
                string message = userInputMessage();
                usefulDataPacket buffer(message);

                //MulticastUDPsocket mUdpSock(MulticastAddress, "28000");
                _mcUdpSock->Send<usefulDataPacket>(MulticastAddress, 28000, buffer);

                //UDP_Socket udpSock("192.168.0.12", "37000");
                //UDP_Socket udpSock("127.0.0.1", "37000");

                //bool funcResult = udpSock.Send<usefulDataPacket>("192.168.0.12", 38000, buffer);
                bool funcResult = _privateComUdpSock->Send<usefulDataPacket>("127.0.0.1", 38000, buffer);
            }
            else if(retVal > 0){
                if(FD_ISSET(_privateComUdpSock->getSocket(), &readset)) // if private socket
                {
                    cout << endl << "[DEBUG]: Private Socket is ready" << endl;

                    string msg;
                    msg.reserve(256);

                    usefulDataPacket buffer(msg);

                    //UDP_Socket udpSock("192.168.0.12", PORT);
                    //UDP_Socket udpSock("127.0.0.1", PORT);
                    //bool funcResult = udpSock.Receive<usefulDataPacket>("192.168.0.12", 37000, buffer);
                    bool funcResult = _privateComUdpSock->Receive<usefulDataPacket>("127.0.0.1", 37000, buffer);
                }
                if(FD_ISSET(_mcUdpSock->getSocket(), &readset)) // if multicast socket
                {
                    cout << endl << "[DEBUG]: Multicast Socket is ready" << endl;

                    string msg;
                    msg.reserve(256);

                    usefulDataPacket buffer(msg);

                    //MulticastUDPsocket mUdpSock(MulticastAddress, "28000");
                    _mcUdpSock->Receive<usefulDataPacket>(MulticastAddress, 28000, buffer);
                }
            }
        }
    }

    void run()
    {
        cout << "Peer is running" << endl;
        while(true) {
            Select(10);
        }
    }
};

#endif // __PEERS_HPP__

