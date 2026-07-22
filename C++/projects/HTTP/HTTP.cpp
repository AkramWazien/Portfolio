#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sstream>

void parse_json(std::string data);
int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "Error creating socket\n";
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);

    struct hostent *server_ip = gethostbyname("httpbin.org");
    if (server_ip == nullptr)
    {
        std::cerr << "Error resolving hostname\n";
        return 1;
    }

    memcpy(&server_addr.sin_addr.s_addr, server_ip->h_addr, server_ip->h_length);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        std::cerr << "Error connecting\n";
        return 1;
    }

    std::string json_data = "{\"temp\": 23.5, \"humidity\": 90}";

    std::string request =
        "POST /post HTTP/1.1\r\n"
        "Host: httpbin.org\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: " +
        std::to_string(json_data.length()) + "\r\n"
                                             "Connection: close\r\n"
                                             "\r\n" +
        json_data;

    send(sockfd, request.c_str(), request.size(), 0);

    char buffer[4096];
    int bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    buffer[bytes_received] = '\0';
    std::cout << buffer;
    parse_json(buffer);

    return 0;
}

void parse_json(std::string data)
{
    std::istringstream stream(data);
    std::string line;
    std::string json_data;
    bool in_json = false;

    while (std::getline(stream, line))
    {
        if (!in_json && line.find("\"json\"") != std::string::npos)
        {
            in_json = true;
            json_data = line;
            continue;
        }

        if (in_json)
        {
            json_data += "\n" + line;
            if (line.find("}") != std::string::npos)
            {
                break;
            }
        }
    }
    std::cout << "Extracted data: \n"
              << json_data << "\n";
}