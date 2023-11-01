CXXFLAGS += -Iinclude

all: bin/dict
SRC := src/dict.cpp src/word.cpp src/main.cpp
bin/dict: $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

clean:
	rm -f bin/dict
	rm -rf bin
