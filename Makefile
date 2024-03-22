CXX=g++
CLINK=$(CXX)
CXXFLAGS=-Wall -g -std=c++11
EXEC=firewall.exe
OBJS=main.o
LOBJS=string.o ip.o port.o
RM=rm -rf *.o *firewall.so 

$(EXEC):$(OBJS)
	$(CLINK) $(OBJS) -o $(EXEC) -linput -lfirewall -L.

$(OBJS): libfirewall.so main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp
	
libfirewall.so: $(LOBJS)
	$(CLINK) -shared $(LOBJS) -o libfirewall.so

ip.o: ip.cpp ip.h string.h string-array.h
	$(CXX) $(CXXFLAGS) -c -fpic ip.cpp
	
port.o: port.cpp port.h string.h string-array.h
	$(CXX) $(CXXFLAGS) -c -fpic port.cpp
	
string.o: string.cpp string.h string-array.h
	$(CXX) $(CXXFLAGS) -c -fpic string.cpp
	
string-array.o: string-array.cpp string-array.h string.h
	$(CXX) $(CXXFLAGS) -c string-array.cpp

clean:
	$(RM)
