//
//  @course: CMPS 2143 - Object Oriented Programming
//  @assignment: Program 4
//  @filename: main.cpp
//  @author Thomas Bauer
//  @description: main source file for running Game of Life program
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define CELLSIZE 10				

using namespace std;				// uses standard template library
using namespace sf;				// uses sfml library

struct golCell : public Drawable {
	RectangleShape rect;
	bool isAlive;
	int neighborCount;

	golCell() {
		isAlive = 0;
		neighborCount = 0;
		rect.setSize(sf::Vector2f(CELLSIZE, CELLSIZE));
		rect.setFillColor(Color::Green);
		rect.setOutlineColor(Color::Black);
		rect.setOutlineThickness(1);
	}

	void setCellPos(int x, int y) {
		rect.setPosition(x*CELLSIZE, y*CELLSIZE);
	}

protected:
	void draw(RenderTarget& target, RenderStates state) const {
		target.draw(rect);
	}
};

class GameOfLife {
protected:
	golCell** gameBoard;
	int frameCount;
	int frameRate;
	int rows;
	int cols;
	int Width;
	int Height;
	string inputFilename;
	string line;
	int genCount;	
public:
	RenderWindow Window;

	// constructor for GameOfLife class that takes int dimensions
	// as parameters
	GameOfLife(int width, int height) {
		Width = width;					// sets width dimension for global use
		Height = height;				// sets height dimension for global use
		genCount = 0;					// sets count of generations for use in print()
		frameRate = 1;
		frameCount = 0;			
	}	

	// runs the program by setting up the event initialization for the sfml 
	// window that has been created in the init function
	// takes the number of generations to be run as a pa
	void runGolProgram(int generations) {
		genCount = generations;
		while (Window.isOpen()) {
			Event event;
			// close the window if the close button is clicked
			while (Window.pollEvent(event)) {
				if (event.type == Event::Closed)
					Window.close();
			}			
			
			// run the program for the specified number of generations and then
			// return to main
			for (int i = 1; i <= generations; i++) {
				frameCount++;
				printNewSet();
				printgameBoard();
				// kicks out to main so that print() will display the correct output
				if (frameCount == generations) {					
					return;
				}				
				for (int k = 0; k < rows; k++) {
					for (int j = 0; j < cols; j++) {
						countNeighbors(k, j);
					}
				}	
				checkRules();				
				if (frameCount % frameRate == 0) {
					printgameBoard();					
				}	
				resetBoard();				
			}
			return;
		}
	}

	// prints out the designated generation to a specified output file 
	// that is read in via the command line arguments
	void print(char* filename) {		
		ofstream outFile(filename);
		if (outFile.fail()) {
			cerr << "Error Opening File" << endl;
			exit(1);
		}
		// makes sure the gameboard generation is correct and prints the header
		if (frameCount == genCount) {
			outFile << "// \n"
				<< "// @course: CMPS 2143 - Object Oriented Programming\n"
				<< "// @assignment: Program 4\n"
				<< "// @filename: " << filename << endl
				<< "// @produced from input file: " << inputFilename << endl
				<< "// @author Thomas Bauer\n"
				<< "// @description: Output file used to print Game of Life program's designated (" 
				<< genCount << "th) generation\n"
				<< "// \n";
			// prints current generation of gameboard after header
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					outFile << gameBoard[i][j].isAlive;
				}
				outFile << endl;
			}
			outFile.close();
		}
	}
	
	// reads in file designated by command line argument and verifies that it can be opened
	// skips the header and reads in rows and columns used to create the 2D array of those
	// dimensions as well as the window they will be displayed in and closes the file when done
	void init(char* filename) {
		inputFilename = filename;
		ifstream inFile(filename);
		if (inFile.fail()) {
			cerr << "Error Opening File" << endl;
			exit(1);
		}		
		for (int i = 0; i < 9; i++)	{
			getline(inFile, line);
		}
		
		inFile >> rows >> cols;
		Window.create(VideoMode(cols*CELLSIZE, rows*CELLSIZE), "Game of Life");
		
		gameBoard = new golCell*[rows];
		for (int i = 0; i < rows; i++) {
			gameBoard[i] = new golCell[cols];			
		}
		for (int i = 0; i < rows; i++) {
			inFile >> line;
			for (int j = 0; j < cols; j++) {
				gameBoard[i][j].isAlive = line[j] - 48;
				gameBoard[i][j].rect.setSize(Vector2f(CELLSIZE, CELLSIZE));
				gameBoard[i][j].rect.setPosition((i*CELLSIZE), (j*CELLSIZE));
				gameBoard[i][j].rect.setOutlineColor(Color::Black);
				gameBoard[i][j].rect.setOutlineThickness(1);
			}		
		}
		inFile.close();
	}

	// verifies that the cell being checked is on the gameboard
	bool ongameBoard(int i, int j) {		
		return (i >= 0 && i < rows && j >= 0 && j < cols);
	}

	// counts the neighboring cells that are currently "alive"
	void countNeighbors(int r, int c) {
		for (int i = r - 1; i <= r + 1; i++) {
			for (int j = c - 1; j <= c + 1; j++) {
				if (i == r && c == j) {
					continue;
				}
				if (ongameBoard(i, j) && gameBoard[i][j].isAlive == 1) {
						gameBoard[r][c].neighborCount++;
				}				
			}
		}
	}

	//
	// Sets the following rules for the game and makes appropriate changes when called
	// 1.	Any live cell with fewer than two live neighbors dies, as if caused by under-population.
	// 2.	Any live cell with more than three live neighbors dies, as if by overcrowding.
	// 3.	Any live cell with two or three live neighbors lives on to the next generation.
	// 4.	Any dead cell with exactly three live neighbors becomes a live cell.
	//
	void checkRules() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {				
				if (gameBoard[i][j].isAlive == 1) {
					if (gameBoard[i][j].neighborCount < 2 || gameBoard[i][j].neighborCount > 3) {
						gameBoard[i][j].isAlive = 0;
						gameBoard[i][j].rect.setFillColor(Color::Black);
					}
					if (gameBoard[i][j].neighborCount == 2 || gameBoard[i][j].neighborCount == 3) {
					}
				}
				else if (gameBoard[i][j].neighborCount == 3) {
					gameBoard[i][j].isAlive = 1;
					gameBoard[i][j].rect.setFillColor(Color::Green);
				}
			}
		}
	}

	// prints out the state of the current generation to an sfml window
	void printgameBoard() {
		Window.clear();
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				gameBoard[i][j].setCellPos(j, i);
				if (gameBoard[i][j].isAlive) {
					Window.draw(gameBoard[i][j].rect);
				}
			}
		}
		Window.display();
	}

	// prints the output to command window to validate sfml window output
	void printNewSet() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cout << gameBoard[i][j].isAlive;
			}
			cout << endl;
		}
		cout << endl;
	}

	// resets the gameBoard and sets the neighbor count to 0
	void resetBoard() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				gameBoard[i][j].rect.setSize(Vector2f(CELLSIZE, CELLSIZE));
				gameBoard[i][j].neighborCount = 0;
				gameBoard[i][j].rect.setPosition((i)*CELLSIZE, (j)*CELLSIZE);				
			}
		}
	}		
};	



int main(int argc, char **argv) {

	GameOfLife GoLife(500, 500);				// create GameOfLife object with parameterized constructor

	GoLife.init(argv[1]);					// initiate the program with input file									
	GoLife.runGolProgram(atoi(argv[2]));			// run for designated amount of generations
	GoLife.print(argv[3]);					// print last generation to output file

	system("pause");
	return 1;
}
