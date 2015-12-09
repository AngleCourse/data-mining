
DIR = ./include
OBJS = fields.o loadlogs.o

FLAGS = -g -Wall 

all: $(DIR)/fields.o $(DIR)/loadlog.o
	g++ $(FLAGS) $(DIR)/fields.o $(DIR)/loadlog.o test.cpp
fields.o: $(DIR)/fields.cpp $(DIR)/fields.h
	g++ $(FLAGS) $(DIR)/fields.cpp $(DIR)/fields.h
loadlog.o: $(DIR)/loadlog.cpp $(DIR)/loadlog.h
	g++ $(FALGS) $(DIR)/loadlog.cpp $(DIR)/loadlog.h

clean:
	rm a.out
	rm ./include/*.gch ./include/*.o

