all: predictors

predictors: main.o getBinary.o bimodalOneBit.o bimodalTwoBit.o
	g++ main.o getBinary.o bimodalOneBit.o bimodalTwoBit.o -o predictors

main.o: main.cpp getBinary.h bimodalOneBit.h 
	g++ -c main.cpp getBinary.h bimodalOneBit.h 
# .h files would go here as well

getBinary.o: getBinary.h getBinary.cpp 
	g++ -c getBinary.h getBinary.cpp

bimodalOneBit.o: bimodalOneBit.h bimodalOneBit.cpp
	g++ -c bimodalOneBit.h bimodalOneBit.cpp

bimodalTwoBit.o: bimodalTwoBit.h bimodalTwoBit.cpp
	g++ -c bimodalTwoBit.h bimodalTwoBit.cpp

clean:
	rm -f *.o predictors a.out *.gch