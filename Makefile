FLAGS = -pedantic-errors -std=c++11

FileIO.o: FileIO.cpp FileIO.h
	g++ $(FLAGS) -c $<

Store.o: Store.cpp Store.h
	g++ $(FLAGS) -c $<

1340Gp_main.o: 1340Gp_main.cpp FileIO.h Store.h
	g++ $(FLAGS) -c $<

1340Gp_main: FileIO.o 1340Gp_main.o Store.o
	g++ $(FLAGS) $^ -o $@