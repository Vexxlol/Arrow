compile:
	g++ \
	Main.cpp \
	Server/Server.cpp \
	 -o web

run: 
	sudo ./web