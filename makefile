CXX = g++
CXXFLAGS = -Wall

mytest: show.o mytest.cpp
	$(CXX) $(CXXFLAGS) show.o mytest.cpp -o mytest

show.o: show.h show.cpp
	$(CXX) $(CXXFLAGS) -c show.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./mytest

val:
	valgrind ./mytest