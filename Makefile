compile:
	 g++ \
	 Main.cpp \
	 Server/Server.cpp \
  	 Request/Request.cpp \
	 Response/Response.cpp \
	 -o Arrow

run: 
	sudo ./Arrow