all: predictors

predictors: main.o getBinary.o bimodalOneBit.o bimodalTwoBit.o gShare.o Tournament.o
	g++ main.o getBinary.o bimodalOneBit.o bimodalTwoBit.o gShare.o Tournament.o -o predictors

main.o: main.cpp getBinary.h bimodalOneBit.h gShare.h 
	g++ -c main.cpp getBinary.h bimodalOneBit.h gShare.h 
# .h files would go here as well

getBinary.o: getBinary.h getBinary.cpp 
	g++ -c getBinary.h getBinary.cpp

bimodalOneBit.o: bimodalOneBit.h bimodalOneBit.cpp
	g++ -c bimodalOneBit.h bimodalOneBit.cpp

bimodalTwoBit.o: bimodalTwoBit.h bimodalTwoBit.cpp
	g++ -c bimodalTwoBit.h bimodalTwoBit.cpp

gShare.o: gShare.h gShare.cpp
	g++ -c gShare.h gShare.cpp

Tournament.o: bimodalTwoBit.h bimodalTwoBit.cpp gShare.h gShare.cpp Tournament.h Tournament.cpp
	g++ -c bimodalTwoBit.h bimodalTwoBit.cpp gShare.h gShare.cpp Tournament.h Tournament.cpp

clean:
	rm -f *.o predictors a.out *.gch