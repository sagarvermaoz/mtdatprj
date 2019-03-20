appname := MtdataApp

CXX := g++
CC := gcc
CXXFLAGS := -std=c++11 -pthread -Wl,--no-as-needed

cxxsrcfiles := $(shell find . -name "*.cpp")
cxxobjects  := $(patsubst %.cpp, %.o, $(cxxsrcfiles))

csrcfiles := $(shell find . -name "*.c")
cobjects  := $(patsubst %.c, %.o, $(csrcfiles))

all: $(appname)

$(appname): $(cxxobjects) $(cobjects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(cxxobjects) $(cobjects) $(LDLIBS)

depend: .depend

.depend: $(cxxsrcfiles) $(csrcfiles)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	rm -f $(cxxobjects)
	rm -f $(cobjects)
	rm -f $(appname)
	rm -f ./.depend
	rm -f *.o

dist-clean: clean
	rm -f *~ .depend

include .depend