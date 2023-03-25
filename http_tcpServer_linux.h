#ifndef INCLUDED_HTTP_TCPSERVER_LINUX
#define INCLUDED_HTTP_TCPSERVER_LINUX

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

namespace http
{
    class TcpServer
    {
    public:
        TcpServer();
        ~TcpServer();

    private:
        int m_socket;
        int m_new_socket;

        int startServer();
        void closeServer();
    };
} // namespace http
#endif