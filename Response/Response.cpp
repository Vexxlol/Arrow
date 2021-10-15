#include<iostream>

#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<netinet/in.h>
#include<string.h>
#include<fstream>
#include<string>

#include "../include/Request/Request.hpp"
#include "../Config.hpp"
#include "../include/Response/Response.hpp"

Response::Response(int socket, Request& req) {
    this->socket = socket;

    std::string tmp = dir + req.headers["route"];
    std::string line;
    std::string fileExt = "text/html";

    std::fstream target;
    target.open(tmp, std::ios::in);
    tmp = "";
    if (!target) { this->response = "HTTP/1.1 404 BAD\nContent-Type: text/html\n\n404"; }
    else {
          while (std::getline(target, line)) {
              tmp += line + "\n";
          }
          target.close();
          this->response = "HTTP/1.1 200 OK\nServer: Arrow/" + arrowBuildVersion + "\nAccept-Ranges: bytes\nConnection: close";
          if (req.headers["fileExtension"] == ".css") fileExt = "text/css";
          if (req.headers["fileExtension"] == ".js") fileExt = "text/javascript";
          if (req.headers["fileExtension"] == ".png") fileExt = "image/png";
          this->response += "\nContent-Type: " + fileExt;
          this->response += "\nContent-Length: " + std::to_string(tmp.length());
          this->response += "\n\n" + tmp;
    }

    write(this->socket, this->response.c_str(), strlen(this->response.c_str()));
    close(this->socket);
}
