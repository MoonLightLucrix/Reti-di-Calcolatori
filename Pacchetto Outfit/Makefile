CXX = g++
CXXFLAGS = -std=c++2a

all: CreateBinFolder CopyFile bin/Outfit bin/Client

CreateBinFolder:
	mkdir -p bin

CopyFile:
	cp tableAbito.txt /tmp

bin/Outfit: bin/Outfit.o
	$(CXX) $< -o $@
	rm $<

bin/Client: bin/Client.o
	$(CXX) $< -o $@
	rm $<

bin/Outfit.o: src/Outfit.cpp
	$(CXX) -c $< -o $@

bin/Client.o: src/Client.cpp
	$(CXX) -c $< -o $@

clean:
	rm /tmp/tableAbito.txt
	rm -rf bin