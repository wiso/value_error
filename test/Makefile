CC = g++
GTESTCFLAGS   := $(shell gtest-config --cppflags --cxxflags)
GTESTLIBS     := $(shell gtest-config --ldflags --libs)


test: test.o
	$(CC) $(GTESTLIBS) -lgtest_main -o test $^

test.o: test.cpp
	$(CC) -c $(GTESTCFLAGS) $^

clean:
	rm -f *.o test