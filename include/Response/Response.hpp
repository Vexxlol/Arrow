#include<iostream>

#include "../Request/Request.hpp"

class Response {
  private:
    std::string contentType; // i.e. application/json
    int contentLength; // i.e. 35
    std::string statusCode; // i.e. 200 OK
  public:
    Response(int socket, Request req);
    void send();
};