CXX=g++
#CXXFLAGS=-std=c++2a

all: createFolders copyFile bin/Server bin/Client

createFolders:
	mkdir -p bin obj

copyFile:
	cp tableDomanda.txt /tmp

bin/Server: obj/SocketService.o obj/Domanda.o obj/ConnectionHandler.o obj/Server.o
	$(CXX) $(CXXFLAGS) $^ -o $@

obj/Server.o: src/Server.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/ConnectionHandler.o: src/utils/ConnectionHandler.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/Domanda.o: src/utils/Domanda.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/SocketService.o: src/utils/SocketService.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin/Client: obj/SocketService.o obj/Client.o
	$(CXX) $(CXXFLAGS) $^ -o $@

obj/Client.o: src/Client.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm /tmp/tableDomanda.txt
	rm -r bin obj
