all: clean compile run

compile: main.cpp file.cpp file.hpp directory.hpp directory.cpp regularfile.hpp regularfile.cpp linkedFile.hpp linkedFile.cpp MyShell.hpp MyShell.cpp
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -std=c++11 -o test main.cpp file.cpp directory.cpp regularfile.cpp linkedFile.cpp MyShell.cpp -lm

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "======================================================================="
	@./test
	@echo "======================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f test
