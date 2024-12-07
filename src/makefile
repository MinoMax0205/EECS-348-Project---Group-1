# Target executable
evaluator: Main.o Input.o InToPost.o Evaluator.o
	g++ -std=c++17 -Wall -Wextra -o evaluator Main.o Input.o InToPost.o Evaluator.o

# Compile Main.cpp
Main.o: Main.cpp Evaluator.hpp Input.hpp InToPost.hpp
	g++ -std=c++17 -Wall -Wextra -c Main.cpp -o Main.o

# Compile Input.cpp
Input.o: Input.cpp Input.hpp
	g++ -std=c++17 -Wall -Wextra -c Input.cpp -o Input.o

#Compile InToPost.cpp
InToPost.o: InToPost.cpp InToPost.hpp
	g++ -std=c++17 -Wall -Wextra -c InToPost.cpp -o InToPost.o

#Compile Evaluator.cpp
Evaluator.o: Evaluator.cpp Evaluator.hpp
	g++ -std=c++17 -Wall -Wextra -c Evaluator.cpp -o Evaluator.o

# Clean up build files
clean:
	rm -f evaluator Main.o Input.o InToPost.o Evaluator.o
