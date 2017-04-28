all: NetConnect

NetConnect: main.o get_url.o get_information.o
	$(CXX) main.o get_url.o get_information.o -o main -std=c++11 -lssl -lcrypto

main.o: main.cpp
	$(CXX) -c main.cpp -std=c++11

get_url.o: get_url.cpp
	$(CXX) -c get_url.cpp -std=c++11

get_information.o: get_information.cpp
	$(CXX) -c get_information.cpp -std=c++11

clean:
	rm *.o main
