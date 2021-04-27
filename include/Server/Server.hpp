#include<iostream>

#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<netinet/in.h>
#include<string.h>

#pragma once

class Server {
    private:
        std::string response;
        std::string responseCode;
        std::string contentType;
    public:
        void start(int argc, const char* argv[]);
};