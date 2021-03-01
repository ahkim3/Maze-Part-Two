/*
Name: Andrew Kim
Date: March 1, 2021
Program: Even More A-Maze-ing

I hereby certify that this program represents my
work and that the design and logic was completed
without outside assistance.

Signature: Andrew Kim
*/

// TODO: MAKE STUFF CONSTANT

#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

enum class Direction { DOWN, RIGHT, UP, LEFT };

void mazeGenerator(char[12][12], int, int*, int*);
void fill(char[12][12], int, string);
void mazeTraverse(char[12][12], int, int&, int&, Direction, int, int);
bool validMove(char[12][12], int, int);
bool isSolved(int, int, int, int, int);
void printMaze(char[12][12], int);


int main()
{
    char maze[12][12];
    int xPos = 0, yPos = 2; // TODO: Define in generator instead

    fill(maze, 12, "Maze.txt");

    Direction direction = Direction::DOWN; // Initial direction attempt

    mazeTraverse(maze, 12, xPos, yPos, direction, xPos, yPos);
}


// Generated a new maze with a random starting and exit location
void mazeGenerator(char maze[12][12], int size, int* xPtr, int* yPtr)
{

}

// Fill array with maze from a file
void fill(char maze[12][12], int size, string inputFileName)
{
    string name;
    ifstream input;

    // Reads file and stores each character in an array element
    input.open(inputFileName, ios::in);
    if (input.is_open())
    {
        for (int j = 0; j < size; j++)
        {
            for (int i = 0; i < size; i++)
                input >> maze[i][j];
        }
        input.close();
    }
}


// Executes tasks for each step in maze
void mazeTraverse(char maze[12][12], int size, int& xCurrent, int& yCurrent,
    Direction direction, int xBegin, int yBegin)
{
    bool directionFound;
    Direction nextDirection;
    char previousChar = maze[xCurrent][yCurrent];

    // Enforces array boundaries
    if (xCurrent >= 0 && yCurrent >= 0 && xCurrent < size && yCurrent < size)
    {
        maze[xCurrent][yCurrent] = 'X'; // Places an X at current position

        // Briefly wait and print new step in maze
        Sleep(100);
        system("cls");
        printMaze(maze, size);

        maze[xCurrent][yCurrent] = previousChar; // Replace with original char

        // Continues onto next position if maze is not yet solved
        if (!(isSolved(size, xCurrent, yCurrent, xBegin, yBegin)))
        {
            directionFound = false;

            // Cycle through directions while a valid direction is not found
            while (!directionFound)
            {
                // Finds a valid direction to move
                switch (direction)
                {
                case Direction::DOWN:
                    if (validMove(maze, xCurrent, yCurrent + 1))
                        directionFound = true;
                    else
                        direction = Direction::RIGHT;
                    break;
                case Direction::RIGHT:
                    if (validMove(maze, xCurrent + 1, yCurrent))
                        directionFound = true;
                    else
                        direction = Direction::UP;
                    break;
                case Direction::UP:
                    if (validMove(maze, xCurrent, yCurrent - 1))
                        directionFound = true;
                    else
                        direction = Direction::LEFT;
                    break;
                case Direction::LEFT:
                    if (validMove(maze, xCurrent - 1, yCurrent))
                        directionFound = true;
                    else
                        direction = Direction::DOWN;
                    break;
                }
            }

            // Move onto next step in maze
            switch (direction)
            {
            case Direction::DOWN:
                nextDirection = Direction::LEFT;
                yCurrent++;
                break;
            case Direction::RIGHT:
                nextDirection = Direction::DOWN;
                xCurrent++;
                break;
            case Direction::UP:
                nextDirection = Direction::RIGHT;
                yCurrent--;
                break;
            case Direction::LEFT:
                nextDirection = Direction::UP;
                xCurrent--;
                break;
            }
            mazeTraverse(maze, size, xCurrent, yCurrent, nextDirection, xBegin, yBegin);
        }
    }
    // Check if maze is unsolvable (boundary is breached)
    else if ((xCurrent == xBegin - 1 && yCurrent == yBegin)
        || (xCurrent == xBegin && yCurrent == yBegin - 1))
        cout << endl << "Maze is unsolvable." << endl;
    else
        cout << endl << "Solved!" << endl;
}


// Determine if moving to a specified position in a maze is allowed
bool validMove(char maze[12][12], int xCoord, int yCoord)
{
    if (maze[xCoord][yCoord] == '#') // Specified position is a border
        return false;
    return true;
}


// Determines if exit of maze has been found
bool isSolved(int size, int xCurrent, int yCurrent, int xBegin, int yBegin)
{
    // Edge of array (exit) has been reached AND it's not the entrance
    if ((xCurrent != xBegin && yCurrent != yBegin)
        && (xCurrent == 0 || xCurrent == size
            || yCurrent == 0 || yCurrent == size))
        return true;
    return false;
}


// Prints the maze
void printMaze(char maze[12][12], int size)
{
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size; i++)
            cout << maze[i][j] << ' ';
        cout << endl;
    }
}
