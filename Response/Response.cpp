#include<iostream>

#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<netinet/in.h>
#include<string.h>
#include<fstream>
#include<string>

#include "../include/Response/Response.hpp"
#include "../include/Request/Request.hpp"


Response::Response(int socket, Request& req) {
    this->socket = socket;

    std::string tmp = "/var/www/html/" + req.headers["route"];
    std::string line;

    std::fstream target;
    target.open(tmp, std::ios::in);
    tmp = "";
    if (!target) { this->response = "HTTP/1.1 404 OK\nContent-Type: text/html\n\n404"; }
    else {
        while (std::getline(target, line)) {
            tmp += line + "\n";
        }
        target.close();
        this->response = "HTTP/1.1 200 OK\n\n";
        this->response += tmp;
    }

    write(this->socket, this->response.c_str(), strlen(this->response.c_str()));
    close(this->socket);
}
