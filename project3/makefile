CXX = g++
CXXFLAGS = -Wall

driver: cqueue.o driver.cpp
	$(CXX) $(CXXFLAGS) cqueue.o driver.cpp -o driver

cqueue.o: cqueue.h cqueue.cpp
	$(CXX) $(CXXFLAGS) -c cqueue.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./driver

val:
	valgrind ./driver