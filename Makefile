compile:
	g++ \
	Main.cpp \
	Server/Server.cpp \
  Request/Request.cpp \
	 -o Arrow

run: 
	sudo ./Arrow