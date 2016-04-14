#pragma once

#ifndef __INCLUDEDLIBS_H__
#define __INCLUDEDLIBS_H__

//#define WINDOWS
#define UNIX


#if defined(WINDOWS)
#define _CRT_SECURE_NO_WARNINGS	//ctime unsafe
#define NOMINMAX	//windows.h -> define min,max

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Mstcpip.h>	//keep_alive
#include <Windows.h>


#include <windows.h>
#include <winsock.h>         // For socket(), connect(), send(), and recv()
#include <winsock2.h>
#include <ws2tcpip.h>


#include "targetver.h"
#include <tchar.h>
#include <wchar.h>

#include <cstdlib>

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

//for server windows,to link
#pragma comment(lib, "Ws2_32.lib")
//for client
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#elif defined(UNIX)

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>	    // timeval structure
#include <unistd.h>         // For sleep() For close()
#include <sys/ioctl.h>
#include <netinet/tcp.h>    // SOL_TCP
#include <netdb.h>           // For gethostbyname()
#include <arpa/inet.h>       // For inet_addr()
#include <netinet/in.h>      // For sockaddr_in
#include <fcntl.h>
#include <cstdlib>          // For atoi()
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/select.h>
#include <poll.h>

#endif

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <sstream>	//std::stringstream
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include <exception>
#include <functional>
#include <algorithm>
#include <map>
#include <ctime>
#include <regex>
#include <cstring>
#include <fstream>
#include <queue>
#include <list>
#include <memory>
#include <time.h>
#include <ctime>
#include <random>
#include <memory>
#include <limits>
#include <math.h>
#include <cmath>



//boost libs

#include <boost/asio.hpp>
#include "boost/bind.hpp"
#include "boost/regex.hpp"
#include "boost/exception/all.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"
/*
#define BOOST_LOG_DYN_LINK
#include <boost/log/trivial.hpp>
*/
using namespace std;

#define SUCCESS_PROGRAM_EXIT 0
#define ERROR_PROGRAM_EXIT 1

using namespace boost;

#ifndef SOCKET_ERROR
#define SOCKET_ERROR (-1)
#endif

#ifndef INVALID_SOCKET
#define INVALID_SOCKET (-1)
#endif

const int MAXRCVSTRING = 255;     // Longest string to receive

#ifndef NI_MAXHOST
#define NI_MAXHOST 1024
#endif

#ifndef NI_MAXSERV
#define NI_MAXSERV 32
#endif

#if defined(UNIX)
#define SOCKET int
#define SD_SEND SHUT_WR
#endif

//using CommandMap = std::map< std::string, std::function<bool(string&)> >;
//template<typename T> using list_ptr_it = typename std::list< unique_ptr<T> >::iterator;

//versions of Winsock;
//the older, limited version
#define SOCKET_V1 0x0101
//the latest edition
#define SOCKET_V2 0x0202

template<typename T>
std::string toString(T number)
{
	ostringstream stringStream;
	stringStream << number;
	return stringStream.str();
}

template<typename T>
T toNumber(std::string& str)
{
	T number = 0;
	istringstream(str.c_str()) >> number;
	return number;
}

#endif //__INCLUDEDLIBS_H__
