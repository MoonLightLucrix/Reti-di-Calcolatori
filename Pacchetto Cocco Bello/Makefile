CXX=g++
CXXFLAGS=-std=c++2a -g

all: createFolders copyFile bin/Server bin/Client

createFolders:
	mkdir -p bin obj

copyFile:
	cp tableProdotto.txt /tmp
	cp tableUtente.txt /tmp

bin/Server: obj/Utente.o obj/SocketService.o obj/Prodotto.o obj/DatabaseManager.o obj/ConnectionHandler.o obj/Server.o
	$(CXX) $(CXXFLAGS) $^ -o $@ -lssl -lcrypto

obj/Server.o: src/Server.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/ConnectionHandler.o: src/utils/ConnectionHandler.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/DatabaseManager.o: src/utils/DatabaseManager.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/Prodotto.o: src/utils/Prodotto.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/SocketService.o: src/utils/SocketService.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/Utente.o: src/utils/Utente.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin/Client: obj/Utente.o obj/SocketService.o obj/Client.o
	$(CXX) $(CXXFLAGS) $^ -o $@ -lssl -lcrypto

obj/Client.o: src/Client.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm /tmp/tableProdotto.txt
	rm /tmp/tableUtente.txt
	rm -r bin obj