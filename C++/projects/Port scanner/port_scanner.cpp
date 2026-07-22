#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

bool is_port_open(const std::string &webname, int timeout = 2)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        return false;
    }

    struct hostent *server = gethostbyname(webname.c_str());
    if (server == nullptr)
    {
        close(sockfd);
        return false;
    }

    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;

    memcpy(&addr.sin_addr, server->h_addr, server->h_length);

    for (int port = 1; port < 1024; port++)
    {
        addr.sin_port = htons(port);
        int result = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));

        if (result == 0)
        {
            close(sockfd);
            return true;
        }

        if (errno == EINPROGRESS)
        {
            fd_set fdset;
            FD_ZERO(&fdset);
            FD_SET(sockfd, &fdset);

            struct timeval tv;
            tv.tv_sec = timeout;
            tv.tv_usec = 0;

            if (select(sockfd + 1, nullptr, &fdset, nullptr, &tv) > 0)
            {
                int so_error;
                socklen_t len = sizeof(so_error);
                getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &so_error, &len);
                if (so_error == 0)
                {
                    close(sockfd);
                    return true;
                }
            }
        }
    }
    close(sockfd);
    return false;
}

int main()
{
    std::vector<std::thread> threads;
    for (int i = 1; i < 255; i++)
    {
        std::string target = "192.168.1." + std::to_string(i);
        threads.emplace_back(is_port_open, target);
    }

    for (const auto &t : threads)
    {
        t.join();
    }

    return 0;
}
