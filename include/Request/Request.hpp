#include<iostream>
#include<map>
#include<vector>

#pragma once

class Request {
  private:
    std::string route;
    

  public:
    Request(std::string request);
    std::map<std::string, std::string> headers;
};