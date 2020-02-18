/* 
mazeio.cpp

Author:

Short description of this file:
*/

#include <iostream>
#include <fstream>
#include "mazeio.h"

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from the given filename into a 
 *  2D dynamically  allocated array.
 * 
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem, 
 * opening the file or reading in the integer sizes.
 *
 * The first argument is the filename of the maze input.
 *  You should use an ifstream to open and read from this
 *  file.
 *
 * We also pass in two pointers to integers. These are
 * output parameters (i.e. declared by the caller and 
 * passed-by-reference for this function to fill in).
 * Fill the integers pointed to by these arguments
 * with the number of rows and columns 
 * read (the first two input values).
 *
 *************************************************/
char** read_maze(char* filename, int* rows, int* cols) 
{
    ifstream input (filename);
    
    if (input.fail()){
        return NULL;
    }    
    
    input >> *rows >> *cols; 
    
    if(input.fail()){
        return NULL;
    }
    
    char** arr = new char*[*rows];
    for(int i=0;i<*rows;i++)
    {
        arr[i] = new char[*cols];
    }
    
    for(int i=0; i<*rows; i++){
        for(int j=0; j< *cols; j++){
            input >> arr[i][j];
            if(arr[i][j] != 'S' && arr[i][j] != 'F'
              && arr[i][j] != '.' && arr[i][j] != '#'){
                return NULL;
            }
        } 
    }
    
    input.close();
    return arr;
}

/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols) 
{   
    cout << rows << " " << cols << endl;
    for(int i=0; i<rows; i++){
        for(int j=0; j< cols; j++){
            cout << maze[i][j];
        } 
        cout << endl;
    }
}

