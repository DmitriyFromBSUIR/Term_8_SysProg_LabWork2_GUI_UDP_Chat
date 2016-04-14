#ifndef __UDPSOCKET_HPP__
#define __UDPSOCKET_HPP__

//#include "Sockets.hpp"

#define PORT "38000"

#define pcPort 38000

struct NodeInternetAddress
{// represents an Internet Protocol (IP) address.

private:

    // port
    std::string _port;
    // IP
    std::string _IP;
    // universal struct for addr
    addrinfo _hints;
    // the list of network interfaces
    addrinfo* _resultServicesInfoList;
    // port
    unsigned short int _Port;

public:
    NodeInternetAddress(string& IP, unsigned short int port)
    {
        this->_IP = IP;
        this->_port = toString(port);
        this->_Port = port;
    }
    NodeInternetAddress(string& IP, string& port)
    {
        this->_IP = IP;
        this->_port = port;
    }

    NodeInternetAddress(string& IP, unsigned short int port, addrinfo& ai)
    {
        this->_IP = IP;
        this->_port = port;
        this->_hints = ai;
    }

    ~NodeInternetAddress() { freeAddrInfo();  }

    //----------------------------- обёртки для вызовов функций -----------------------------//
    bool _getAddrInfo(int family, int socktype, int protocol, int flags)
    {
        _hints.ai_family = family;
        _hints.ai_socktype = socktype;
        _hints.ai_protocol = protocol;
        _hints.ai_flags = flags;	//The socket address will be used in a call to the bind function.
                                    /*
                                    !!!!!!!!!! If the pIP parameter contains an empty string, all registered addresses on the local computer are returned.
                                    */
                                    //The getaddrinfo function provides protocol-independent translation
                                    //from an ANSI host name to an address.
        int retValue = getaddrinfo(_IP.c_str(),	//a host (node) name or a numeric host address string.
            _port.c_str(), //A pointer to a NULL-terminated ANSI string that contains
                                       //either a service name or port number represented as a string.
            &_hints,					//A pointer to an addrinfo structure that provides hints about the type of socket the caller supports.
            &_resultServicesInfoList	//A pointer to a linked list of one or more addrinfo structures that contains response information about the host.
            );
        //Success returns zero.
        return retValue == 0;
    }

    void getAddrInfo(int family, int socktype, int protocol, int flags)
    {
        if (!_getAddrInfo(family, socktype, protocol, flags))
            throw runtime_error("Error! Fail to get addrinfo struct");
    }

    //NodeInternetAddress(string& IP, unsigned short int port, int family, int socktype, int protocol, string canonname="", int flags=0)
    NodeInternetAddress(string& IP, string& port, int family, int socktype, int protocol, string canonname="", int flags=0)
    {
        memset(&_hints, 0, sizeof(_hints));
        this->_IP = IP;
        //this->_port = toString(port);
        this->_port = port;
        _hints.ai_family = family;
        _hints.ai_socktype = socktype;
        _hints.ai_flags = flags;
        _hints.ai_protocol = protocol;
        _hints.ai_canonname = const_cast<char*>(canonname.c_str());
        _hints.ai_addr = nullptr;
        _hints.ai_next = nullptr;
        getAddrInfo(family, socktype, protocol, flags);
    }



    NodeInternetAddress(sockaddr_in& addr, string IP, string port)
    {
        getNameInfo((sockaddr*)&addr, IP, port);
    }

    NodeInternetAddress() { _resultServicesInfoList = nullptr; }
    bool operator==(NodeInternetAddress& inetAddress)
    {//сравнение адресов
        return (_IP == inetAddress.getIP()) && (_port == inetAddress.getPort());
    }
    static bool getNameInfo(sockaddr* pSockAddr, string& hostName, string& port)
    {
        //protocol - independent name resolution from an address to an ANSI host name and from a port number to the ANSI service name.
        //NI_MAXHOST - 1025
        char nodeBuffer[NI_MAXHOST] = "";
        //NI_MAXSERV - 32
        char serviceBuffer[NI_MAXSERV] = "";
        //NI_NUMERICHOST flag returns the numeric form of the host name instead of its name.
        //NI_NUMERICSERV flag returns the port number of the service instead of its name.
        int retVal = getnameinfo(pSockAddr, sizeof(sockaddr), nodeBuffer, NI_MAXHOST, serviceBuffer, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

        hostName = nodeBuffer;
        port = serviceBuffer;

        //On success, getnameinfo returns zero
        return (retVal == 0) ? true : false;
    }

    addrinfo getCurrentAddrInfo() const
    {
        return _hints;
    }

    addrinfo* getResultAddrInfo() const
    {
        return _resultServicesInfoList;
    }

    sockaddr* getResultAddrStructInfo() const
    {
        return _resultServicesInfoList->ai_addr;
    }

    void setCurrentAddrInfo(addrinfo hints)
    {
        //_hints = hints;
        //_hints.ai_addr->sa_data   = hints.ai_addr->sa_data;
        _hints.ai_addr            = hints.ai_addr;
        _hints.ai_addrlen         = hints.ai_addrlen;
        _hints.ai_family          = hints.ai_family;
        _hints.ai_socktype        = hints.ai_socktype;
        _hints.ai_flags           = hints.ai_flags;
        _hints.ai_protocol        = hints.ai_protocol;
        _hints.ai_canonname       = hints.ai_canonname;
        _hints.ai_addr = nullptr;
        _hints.ai_next = nullptr;
    }

    void setAddrInfoHints(addrinfo& hints)
    {
        _hints = hints;
    }
    addrinfo getAddIinfoHints() const
    {
        return _hints;
    }

    void setAddrInfoResultList(addrinfo* resultList)
    {
        _resultServicesInfoList = resultList;
    }
    addrinfo* getAddrInfoResultList() const
    {
        return _resultServicesInfoList;
    }

    string getIP()
    {
        return _IP;
    }
    void setIP(string& IP)
    {
        _IP = IP;
    }

    unsigned short int getNumValPort() const
    {
        return _Port;
    }
    void setNumValPort(unsigned short int port)
    {
        _Port = port;
    }

    string getPort() const
    {
        return _port;
    }
    void setPort(string& port)
    {
        _port = port;
    }

    //------------------------ закрытие объекта--------------------------------------//
    void freeAddrInfo()
    {
        //The freeaddrinfo function frees address information that the getaddrinfo
        //function dynamically allocates in addrinfo structures.
        //освобождаем список из структур addrinfo
        if (_resultServicesInfoList != nullptr)
            freeaddrinfo(_resultServicesInfoList);
    }
} typedef NodeInetAddress;



class UDP_Socket
{
private:
    SOCKET _fsdHandle;
    NodeInetAddress* _nodeInetAddr;
    NodeInetAddress* _toPeerAddr;
    //sockaddr_in* _toPeerAddr;
    int _protocolFamily;
    int _addressFamily;
    unsigned int _messageMaxSize;

public:
    enum class Selection { ReadCheck, WriteCheck, ExceptCheck };

    UDP_Socket() { _nodeInetAddr = new NodeInetAddress(); _toPeerAddr = new NodeInetAddress(); resetHande(); _protocolFamily = 0; _addressFamily = 0; _messageMaxSize = 0; }

    //UDP_Socket(char* IP = "", char* port = "", int domain = AF_UNSPEC, int socktype = SOCK_DGRAM, int protocol = IPPROTO_UDP, SOCKET handle = INVALID_SOCKET, size_t messageMaxSize = 256)
    UDP_Socket(string IP = "", string port = "", int domain = AF_UNSPEC, int socktype = SOCK_DGRAM, int protocol = IPPROTO_UDP, SOCKET handle = INVALID_SOCKET, size_t messageMaxSize = 256)
    {
        socketSettings(IP, toString(port), domain, socktype, protocol, handle, messageMaxSize);
        Socket(this->_nodeInetAddr->getAddrInfoResultList());
        Bind(this->_nodeInetAddr->getAddrInfoResultList());
        //Connect()
        //start to fill up the peeer addr that will be get packets
        /*
        _toPeerAddr = new sockaddr_in();
        _toPeerAddr->sin_family = domain;
        */
        //_toPeerAddr.sin_port = const_cast<char*>(port.c_str());
    }

    ~UDP_Socket() { shutDown(); closeSocket(); delete _nodeInetAddr; delete _toPeerAddr; resetHande(); _protocolFamily = 0; _addressFamily = 0; _messageMaxSize = 0; }

    SOCKET getSocket() const
    {
        return _fsdHandle;
    }
    void setSocket(SOCKET sock)
    {
        _fsdHandle = sock;
    }

    void resetHande() { _fsdHandle = INVALID_SOCKET; }

    NodeInetAddress* getNodeInetAddr() const
    {
        return _nodeInetAddr;
    }
    void setNodeInetAddr(NodeInetAddress* nodeInetAddr)
    {
        _nodeInetAddr = nodeInetAddr;
    }

    int getProtocolFamily() const
    {
        return _protocolFamily;
    }
    void setProtocolFamily(int protocolFamily)
    {
        _protocolFamily = protocolFamily;
    }

    int getAddressFamily() const
    {
        return _addressFamily;
    }
    void setAddressFamily(int addressFamily)
    {
        _addressFamily = addressFamily;
    }

    static int errorCode()
    {
#if defined(WINDOWS)
        return GetLastError();
#elif defined(UNIX)
        return errno;
#endif
    }

    static int ioctlSocket(SOCKET handle, long command, unsigned long* pArg)
    {
#if defined(WINDOWS)
        return ioctlsocket(handle, command, pArg);
#elif defined(UNIX)
        return ioctl(handle, command, pArg);
#endif
    }

    //-------------------------обработка ошибок------------------------------------//
    static void socketError(const char* description)
    {

        string err_message = description + toString(errorCode());
        //The WSACleanup function terminates use of the Winsock 2 DLL (Ws2_32.dll).
        throw runtime_error(description);
    }

    //void socketSettings(char* IP, char* port, int domain, int socktype, int protocol, SOCKET handle, size_t messageMaxSize)
    void socketSettings(string IP, string port, int domain, int socktype, int protocol, SOCKET handle, size_t messageMaxSize)
    {//default socket parameters
        _fsdHandle = handle;

        _nodeInetAddr = new NodeInetAddress(IP, port, domain, socktype, protocol);

        _messageMaxSize = messageMaxSize;

        _addressFamily = domain;

        _protocolFamily = protocol;
    }

    bool Socket(addrinfo* ptrAddrInfo)
    {
        //создание сокета int socket (domain, type, protocol)
        _fsdHandle = ::socket(ptrAddrInfo->ai_family, //используемый для взаимодействия набор протоколов (для стека протоколов TCP/IP)
            ptrAddrInfo->ai_socktype, // с установлением соединения
            ptrAddrInfo->ai_protocol //протокол транспортного уровня
                                   //(из нескольких возможных в стеке протоколов).
                                   //Если этот аргумент задан равным 0,
                                   //то будет использован протокол "по умолчанию"
                                   //(TCP для SOCK_STREAM и UDP для SOCK_DGRAM
                                   //при использовании комплекта протоколов TCP/IP).
            );
        return _fsdHandle != INVALID_SOCKET;
    }

    bool Bind(addrinfo* ptrAddrInfo)
    {
        int retValue = ::bind(_fsdHandle,	//дескриптор сокета
            ptrAddrInfo->ai_addr, //структура, содержащуя локальный адрес, приписываемый socket'у
            ptrAddrInfo->ai_addrlen);
        return retValue != SOCKET_ERROR;
    }

    template<typename T>
    bool setSockOpt(int level, int optname, T optval)
    {
        return ::setsockopt(_fsdHandle, level, optname, &(*(char*)&optval), sizeof(optval)) == 0;
    }

    template<typename T>
    bool getSockOpt(int level, int optname, T &optval)
    {
        socklen_t optlen = sizeof(optval);
        return ::getsockopt(_fsdHandle, level, optname, &(*(char*)&optval), &optlen) == 0;
    }

    void closeSocket()
    {
        if (_fsdHandle != INVALID_SOCKET)
        {
#if defined(WINDOWS)
            closesocket(_fsdHandle);
#elif defined(UNIX)
            close(_fsdHandle);
#endif
            _fsdHandle = INVALID_SOCKET;
        }
    }
    bool shutDown()
    {
        //then not more send data
        return shutdown(_fsdHandle, SD_SEND) != SOCKET_ERROR;
    }
    static bool winsockStructInit()
    {
        int result = 0;
#if defined(WINDOWS)
        //The WSADATA structure contains information
        //about the Windows Sockets implementation.
        WSADATA wsaData;
        // initialize winsock library process wsock32.dll
        //If successful, the WSAStartup function returns zero. Otherwise,
        //it returns one of the error codes
        result = WSAStartup(SOCKET_V2, //The highest version of Windows Sockets specification that the caller can use
            &wsaData  //data structure that is to receive details of the Windows Sockets implementation.
            );
        if (result != 0)
            throw new runtime_error("WSAStartup failed");
#endif
        return result;
    }

    bool isValid()
    {//socket check
        return _fsdHandle != INVALID_SOCKET;
    }

    bool select(Selection selection = Selection::ReadCheck, int connectionTimeOut = 30)
    {
        /*
        The select function returns the total number of socket handles
        that are ready and contained in the fd_set structures,
        zero if the time limit expired, or SOCKET_ERROR if an error occurred.
        */

        timeval timeOut;
        timeOut.tv_usec = 0;
        timeOut.tv_sec = connectionTimeOut;

        fd_set set;

        FD_ZERO(&set);
        FD_SET(_fsdHandle, &set);
        int retVal = 0;

        if (selection == Selection::ReadCheck)
            retVal = ::select(_fsdHandle + 1,	//Ignored. The nfds parameter is included only for compatibility with Berkeley sockets.
                &set,//An optional pointer to a set of sockets to be checked for readability.
                NULL,//An optional pointer to a set of sockets to be checked for writability.
                NULL,//An optional pointer to a set of sockets to be checked for errors.
                &timeOut	//The maximum time for select to wait (TIMEVAL structure)
                );
        else if (selection == Selection::WriteCheck)
            retVal = ::select(_fsdHandle + 1, NULL, &set, NULL, &timeOut);

        else if (selection == Selection::ExceptCheck)
            retVal = ::select(_fsdHandle + 1, NULL, NULL, &set, &timeOut);

        return ((retVal != 0) && FD_ISSET(_fsdHandle, &set));
    }

    bool setBlocking(unsigned int blockMode)
    {//set/reset blocking mode of socket
     //(nonblockingIO) a nonzero value if the nonblocking mode should be enabled
     //or zero if the nonblocking mode should be disabled.
        unsigned long  arg = blockMode;
        int retVal = ioctlSocket(_fsdHandle,
            FIONBIO,	//set/clear nonblocking i/o
            &arg);
        return retVal != SOCKET_ERROR;
    }

    bool makeUnblocked()
    {//make socket unblocked
        return setBlocking(1);
    }

    bool makeBlocked()
    {//make socket blocked
        return setBlocking(0);
    }

    bool reuseAddr()
    {
        /*
        !!!!!!!!!!!!!!
        When using bind with the SO_REUSEADDR socket option,
        the socket option must be set prior to executing bind to have any affect.
        */
        //Allows the socket to be bound to an address that is already in use.
        //For more information, see bind. Not applicable on ATM sockets.
        return setSockOpt(SOL_SOCKET, SO_REUSEADDR, true);
    }

    static void closeWinsock()
    {
#if defined(WINDOWS)
        WSACleanup();
#endif
    }

    bool getRemotePeerAddr(SOCKET connectedSock) {
        socklen_t len;
        struct sockaddr_storage addr;
        char ipstr[INET6_ADDRSTRLEN];
        int port;

        len = sizeof(addr);
        if(getpeername(connectedSock, (struct sockaddr*)&addr, &len) == 0)
        {
            // deal with both IPv4 and IPv6:
            if (addr.ss_family == AF_INET) {
                struct sockaddr_in *sa = (struct sockaddr_in *)&addr;
                port = ntohs(sa->sin_port);
                inet_ntop(AF_INET, &sa->sin_addr, ipstr, sizeof ipstr);
            } else { // AF_INET6
                struct sockaddr_in6 *sa = (struct sockaddr_in6 *)&addr;
                port = ntohs(sa->sin6_port);
                inet_ntop(AF_INET6, &sa->sin6_addr, ipstr, sizeof ipstr);
            }

            printf("Peer IP address: %s\n", ipstr);
            printf("Peer port      : %d\n", port);
            return true;
        }
        else
        {
            cout << endl << "Error. Can't get the peer addr." << endl;
            return false;
        }
    }

    static bool getNameInfo(sockaddr* pSockAddr, string& hostName, string& port)
    {
        //protocol - independent name resolution from an address to an ANSI host name and from a port number to the ANSI service name.
        //NI_MAXHOST - 1025
        char nodeBuffer[NI_MAXHOST] = "";
        //NI_MAXSERV - 32
        char serviceBuffer[NI_MAXSERV] = "";
        //NI_NUMERICHOST flag returns the numeric form of the host name instead of its name.
        //NI_NUMERICSERV flag returns the port number of the service instead of its name.
        int retVal = getnameinfo(pSockAddr, sizeof(sockaddr), nodeBuffer, NI_MAXHOST, serviceBuffer, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

        hostName = nodeBuffer;
        port = serviceBuffer;

        //On success, getnameinfo returns zero
        return (retVal == 0) ? true : false;
    }

    template<typename T>
    //int receiveData(T* buffer, size_t bufLength, int flags, sockaddr_storage& fromPeerAddr, int peerAddrStructSize)
    //int receiveData(T* buffer, size_t bufLength, int flags, sockaddr_in* fromPeerAddr, unsigned int peerAddrStructSize)
    int receiveData(T* buffer, size_t bufLength, int flags, sockaddr* fromPeerAddr, unsigned int peerAddrStructSize)
    {
        //return ::recvfrom(_fsdHandle, reinterpret_cast<char*>(buffer), bufLength, flags, (sockaddr*)&fromPeerAddr, (socklen_t*)&peerAddrStructSize) == bufLength;

        ssize_t recvBytes = ::recvfrom(_fsdHandle, (char*)buffer, bufLength, flags, fromPeerAddr, (socklen_t*)&peerAddrStructSize);

        string hostAddr, port;
        bool funcResult = getNameInfo(fromPeerAddr, hostAddr, port);
        cout << endl << "Massege: " << buffer->getMessage() << " from peer with IP: " << hostAddr << " and Port: " << port << endl;
        return recvBytes;
    }
/*
    template<typename T>
    char* serialize(T* buffer, size_t bufSize=10+256+32)
    {
        char* buf = NULL;
        buf = new char [bufSize];
        if(buf == NULL) throw runtime_error("Error! Can't allocate the memory");
        char * messageSize = new char[10];
        itoa(buffer->getMessageSize(), messageSize, 10);
    }
*/
    template<typename T>
    //int sendData(T* buffer, size_t bufLength, int flags, sockaddr_storage& toPeerAddr, int peerAddrStructSize)
    //int sendData(T* buffer, size_t bufLength, int flags, sockaddr_in* toPeerAddr, unsigned int peerAddrStructSize)
    int sendData(T* buffer, size_t bufLength, int flags, sockaddr* toPeerAddr, unsigned int peerAddrStructSize)
    {
        //return ::sendto(_fsdHandle, reinterpret_cast<char*>(buffer), bufLength, flags, (sockaddr*)&toPeerAddr, (socklen_t)&peerAddrStructSize) == bufLength;

        cout << endl << "Message for sending: " << (*buffer).getMessage() << endl;
        //serialization
        //char* buf = serialize(buffer);
        ssize_t sendBytes = ::sendto(_fsdHandle, (char*)buffer, bufLength, flags, toPeerAddr, (socklen_t)peerAddrStructSize);
        return sendBytes;
    }

    template<typename T>
    bool Send(string IP, unsigned short int port, T& obj)
    {
        int objectLength = sizeof(obj);

        string Port = toString(port);
        //_toPeerAddr = new NodeInetAddress(IP, Port, AF_UNSPEC, SOCK_DGRAM, IPPROTO_UDP);
        _toPeerAddr = new NodeInetAddress(IP, Port, AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        //return sendData<T>(&obj, objectLength*sizeof(T), 0, _toPeerAddr->getResultAddrStructInfo(), sizeof(_toPeerAddr->getResultAddrStructInfo())*sizeof(addrinfo*)) == objectLength;
        return sendData<T>(&obj, objectLength, 0, _toPeerAddr->getResultAddrStructInfo(), sizeof(_toPeerAddr->getResultAddrStructInfo())*sizeof(addrinfo*)) == objectLength;

    }
/*
    template<typename T>
    bool sendArray(T* arr,int size)
    {
        int length = size * sizeof(T);
        return send((char*)arr, length);
    }
*/
    template <typename T>
    bool Receive(string IP, unsigned short int port, T& obj)
    {
        int objectLength = sizeof(obj);

        string Port = toString(port);
        //_toPeerAddr = new NodeInetAddress(IP, Port, AF_UNSPEC, SOCK_DGRAM, IPPROTO_UDP);
        _toPeerAddr = new NodeInetAddress(IP, Port, AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        return receiveData<T>(&obj, objectLength, 0, _toPeerAddr->getResultAddrStructInfo(), sizeof(_toPeerAddr->getResultAddrStructInfo())*sizeof(addrinfo*)) == objectLength;
    }
/*
    template<typename T>
    bool receiveArray(T* arr, int size)
    {
        int length = size * sizeof(T);
        return receive((char*)arr, length);
    }
*/

};

#endif // __UDPSOCKET_HPP__

