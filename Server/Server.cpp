#include<iostream>

#include "../include/Server/Server.hpp"
#include "../include/Request/Request.hpp"
#include "../include/Response/Response.hpp"

#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<netinet/in.h>
#include<string.h>
#include<fstream>
#include<string>

#include<vector>
#include<sstream>
#include<map>
#include<iterator>
#include<regex>

#define PORT 80

void Server::start(int argc, char const* argv[]) {

    std::string green = "\u001b[1;32m";
    std::string red = "\u001b[1;31m";
    std::string yellow = "\u001b[1;33m";
    std::string purple = "\u001b[1;35m";

    std::string reset = "\u001b[0m";

    std::string line;
    /*std::fstream configTarget;
    configTarget.open("./config.arrow", std::ios::in);
    if (configTarget) {
        while (std::getline(configTarget, line)) {
            std::string tmp;
            std::string key;
            bool value = false;
            for (int i = 0; i < line.length(); i++) {
                if (!value) {
                    if (line[i] == '=') {
                        value = true;
                        key = tmp;
                        tmp = "";
                    } else {
                        tmp += line[i];
                    }
                } else {
                    if (key == "dir") {
                        dir += line[i];
                    } else if (key == "ssr") {
                        ssr += line[i];
                    } else if (key == "loglevel") {
                        logLevel += line[i];
                    }
                }
            }
        }
    }

    std::cout << dir << " " << ssr << " " << logLevel << std::endl;
*/
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    
    int opt = 1;
    int addrlen = sizeof(address);
    
    char buffer[1024] = {0};
    std::string message = "MenuDocs";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed!");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
            perror("bind failed!");
            exit(EXIT_FAILURE);
    }

    std::cout << green << "Arrow" << purple << " -> " << reset << "Application started on " << PORT << std::endl;

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    

    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        valread = read( new_socket, buffer, 3000);
        std::string request = buffer;

        Request req(request);

        std::cout << std::string(green + "Arrow " + purple + "->" + reset + " Request made to " +  yellow + req.headers["route"] + reset) << std::endl;
        Response resp(new_socket, req);
    }
}