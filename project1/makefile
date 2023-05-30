CXX = g++
CXXFLAGS = -Wall

mytest: checkers.o mytest.cpp
	$(CXX) $(CXXFLAGS) checkers.o mytest.cpp -o mytest

checkers.o: checkers.h checkers.cpp
	$(CXX) $(CXXFLAGS) -c checkers.cpp

clean:
	rm *.o*
	rm *~ 


run:
	./mytest

val:
	valgrind ./mytest