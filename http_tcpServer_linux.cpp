#include <http_tcpServer_linux.h>
#include <iostream>

namespace
{
    void log(const std::string &message)
    {
        std::cout << message << std::endl;
    }
    void exitWithError(const std::string &errorMessage)
    {
        log("ERROR: " + errorMessage);
        exit(1);
    }
}

namespace http
{
    TcpServer::TcpServer(std::string ip_address, int port)
        : m_ip_address(ip_address), m_port(port), m_socket(),
          m_new_socket(), m_incomingMessage(), m_socketAddress(),
          m_socketAddress_len(sizeof(m_socketAddress)),
          m_serverMessage(buildResponse())
    {
        m_socketAddress.sin_family = AF_INET;
        m_socketAddress.sin_port = htons(m_port);
        m_socketAddress.sin_addr.s_addr = inet_addr(m_ip_address.c_str());
        startServer();
    }
    int TcpServer::startServer()
    {
        // Create a socket
        // 1st parameter: use IPv4 Internet protocols defined by the AF_INET domain / protocol family the socket will belong to
        // 2nd parameter: for this protocol family, we use the SOCK_STREAM type of communication structure to allow for
        // reliable, full-duplex byte streams.
        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_socket < 0)
        {
            exitWithError("Cannot create socket");
            return 1;
        }

        if (bind(m_socket, (sockaddr *)&m_socketAddress, m_socketAddress_len) < 0)
        {
            exitWithError("Cannot connect socket to address");
            return 1;
        }
        return 0;
    }

    void TcpServer::closeServer()
    {
        close(m_socket);
        close(m_new_socket);
        exit(0);
    }
    TcpServer::~TcpServer()
    {
        // Close a socket in the destructor
        closeServer();
    }
} // namespace http