all: compile run clean

compile: main.cpp Chess_Board.h Chess_Board.cpp Pieces.h Pieces.cpp Pointvalues.h
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -std=c++11 main.cpp Chess_Board.cpp Pieces.cpp -o ChessGame

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	
	@echo "==========================================="
	@./ChessGame
	@echo "==========================================="

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f ChessGame