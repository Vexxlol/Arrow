#include<iostream>

#include "./include/Server/Server.hpp"

int main(int argc, const char *argv[]) {
    Server server;
    server.start(argc, argv);
    return 0;
}