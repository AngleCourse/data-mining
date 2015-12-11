
#FLAGS = -DDEBUG -DD_LOAD_LENGTH=100 
.phony: all 

all:
	g++ -g $(FLAGS) ./include/*.h ./include/*.cpp main.cpp

test_load:
	g++ -g $(FLAGS) -DDEBUG_STATISTICS ./include/*.h ./include/*.cpp test.cpp
	./a.out > ./dist/distribution
pack:
	rm ./dist/src.tar
	tar cvf ./dist/src.tar ./include ./main.cpp
clean:
	rm ./include/*.gch
	rm ./a.out
