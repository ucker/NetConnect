all: NetConnect

NetConnect: main.o BitBuffer.o get_ssl_svg.o convert_qrcode.o get_information.o QrCode.o QrSegment.o
	$(CXX) $(LDFLAGS) main.o BitBuffer.o get_ssl_svg.o convert_qrcode.o get_information.o QrCode.o QrSegment.o -o NetConnect -std=c++11 $(LIBS) -lssl -lcrypto

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -std=c++11

BitBuffer.o: BitBuffer.cpp
	$(CXX) $(CXXFLAGS) -c BitBuffer.cpp -std=c++11

get_ssl_svg.o: get_ssl_svg.cpp
	$(CXX) $(CXXFLAGS) -c get_ssl_svg.cpp -std=c++11

convert_qrcode.o: convert_qrcode.cpp
	$(CXX) $(CXXFLAGS) -c convert_qrcode.cpp -std=c++11

get_information.o: get_information.cpp
	$(CXX) $(CXXFLAGS) -c get_information.cpp -std=c++11

QrCode.o: QrCode.cpp
	$(CXX) $(CXXFLAGS) -c QrCode.cpp -std=c++11

QrSegment.o: QrSegment.cpp
	$(CXX) $(CXXFLAGS) -c QrSegment.cpp -std=c++11

clean:
	rm *.o NetConnect 
