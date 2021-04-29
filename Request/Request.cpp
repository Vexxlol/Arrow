#include<iostream>
#include<string.h>
#include<fstream>
#include<string>

#include<vector>
#include<sstream>
#include<map>
#include<iterator>
#include<regex>

#include "../include/Request/Request.hpp"

Request::Request(std::string request) {
  std::vector<std::string> lines;

  std::istringstream buffer(request);
  std::string line;

  while(getline(buffer, line)) {
    lines.push_back(line);
  }

  std::vector<std::string> requestLine;
  std::string reqL = std::string(lines[0]);
  std::string tmp = "";

  for (int i = 0; i <= reqL.length(); i++) {
    if (reqL[i] == ' ') {
      requestLine.push_back(tmp);
      tmp = "";
    } else {
      tmp += reqL[i];
    }
  }

  this->headers["method"] = requestLine[0];
  this->headers["route"] = requestLine[1];

  tmp = this->headers["route"];
  tmp = std::regex_replace(tmp, std::regex("\\%20"), " ");
  this->headers["route"].replace(0, 1, "");

  if (this->headers["route"] == "") {
    this->headers["route"] = "index.html";
  }

  tmp = this->headers["route"];
  int ext;
  for (int i = 0; i < tmp.length(); i++) {
      if (tmp[i] == '.') {
        this->headers["fileExtension"] = tmp.replace(0, i, "");
      }
  }

  /* 
  if (this->headers.find("fileExtension") == this->headers.end()) { } else { std::cout << this->headers["fileExtension"] << std::endl; }
  */
}