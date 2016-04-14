#ifndef __MULTICASTUDPSOCKET_HPP__
#define __MULTICASTUDPSOCKET_HPP__

#include "udpSocket.hpp"

#define multicastPORT 28000

#define mcPort 27000

/*
What you need to know:
---------------------

When choosing a multicast address for use with nee167, you'll need to use
a group address within the following ranges:

       224.59.10.0 - 224.59.10.255
       224.59.11.0 - 224.59.11.255

For any other multicast address, you'll find that you can receive
multicast packets from that group address okay, but is unable to send to
that mulitcast group address.
*/

//#define MulticastAddress "224.59.10.10"
#define MulticastAddress "224.0.0.1"

class MulticastUDPsocket : public UDP_Socket
{
private:
    //SOCKET _fsdHandle;
    struct ip_mreq _mreq;

public:
    MulticastUDPsocket(string IP, string port) : UDP_Socket(IP, port)
    {
        bzero(&_mreq,sizeof(struct ip_mreq));
        //bcopy(this->getNodeInetAddr()->getResultAddrStructInfo(), _mreq, &_mreq->imr_multiaddr.s_addr, sizeof(sockaddr));

        // set multicast addr
        _mreq.imr_multiaddr.s_addr = inet_addr(MulticastAddress);
        // set interface
        _mreq.imr_interface.s_addr = htonl(INADDR_ANY);

        // do membership call
        setSockOpt(IPPROTO_IP, IP_ADD_MEMBERSHIP, _mreq);
    }

    template<typename T>
    bool setSockOpt(int level, int optname, T optval)
    {
        return ::setsockopt(this->getSocket(), level, optname, &(*(struct ip_mreq*)&optval), sizeof(struct ip_mreq)) == 0;
    }

    template<typename T>
    bool getSockOpt(int level, int optname, T &optval)
    {
        socklen_t optlen = sizeof(optval);
        return ::getsockopt(_fsdHandle, level, optname, &(*(struct ip_mreq*)&optval), &optlen) == 0;
    }
};

#endif // __MULTICASTUDPSOCKET_HPP__

