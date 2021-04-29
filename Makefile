compile:
	g++ \
	Main.cpp \
	Server/Server.cpp \
  Request/Request.cpp \
	 -o web

run: 
	sudo ./web