/* 
maze.cpp

Author: Ethan Feng

Short description of this file:
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);
void deallocate(bool **visit, Location ** pre, int rows);

// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
   int rows, cols, result;
   char** mymaze;
   
   if(argc < 2)
   {
       cout << "Please provide a maze input file" << endl;
       return 1;
   }
   mymaze = read_maze(argv[1], &rows, &cols);
   
   if (mymaze == NULL) {
      cout << "Error, input format incorrect" << endl;
      return 1;
   }

   // when working on Checkpoint 3, you will call maze_search here.
   // here. but for Checkpoint 1, just assume we found the path.
    result = maze_search(mymaze, rows, cols);

   // examine value returned by maze_search and print appropriate output
   if (result == 1) { // path found!
      print_maze(mymaze, rows, cols);
   }
   else if (result == 0) { // no path :(
      cout << "No path could be found!" << endl;
   }else { // result == -1
      cout << "Invalid maze." << endl;
   }

   // ADD CODE HERE to delete all memory 
   // that read_maze allocated
    
   for(int i=0;i<rows;i++)
   {
        delete[]  mymaze[i];
   } 
   delete[] mymaze;

   return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 *************************************************/
int maze_search(char** maze, int rows, int cols) 
{
    
    Location start, finish; 
    bool **visit = new bool*[rows];
    Location **pre = new Location*[rows];
    
    for(int i=0;i<rows;i++)
    {
        visit[i] = new bool[cols];
    } 
    
    for(int i=0;i<rows;i++)
    {
        pre[i] = new Location[cols];    
    } 
     
    int s = 0, f = 0;
    
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            if(maze[i][j] == 'S'){
                s++;
                start.row = i;
                start.col = j;
                visit[i][j] = true;
            }
            else if(maze[i][j] == 'F'){
                f++;
                finish.row = i;
                finish.col = j;
            }
            
            Location loc;
            loc.row = -1;
            loc.col = -1;
            pre[i][j] = loc;
            visit[i][j] = false; 
        }
    }
    
    Queue q(rows*cols);
    
    if(s!=1 || f!=1){
        deallocate(visit, pre, rows);
        return -1;
    }
    q.add_to_back(start);
    
    while(!q.is_empty()){
       Location loc = q.remove_from_front();
       int r = loc.row;
       int c = loc.col;
        
       // North
        if((r+1) >= 0 && (r+1) < rows){ 
            if(maze[r+1][c] == '.' && visit[r+1][c]==false){
               Location add; 
               add.row = r+1;
               add.col = c;
               q.add_to_back(add);
               pre[r+1][c] = loc;
               visit[r+1][c] = true;
            }else if((r+1) == finish.row && c == finish.col){
                int tempR = r;
                int tempC = c;
                maze[r][c] = '*';

                while(pre[tempR][tempC].row != -1 && 
                                    pre[tempR][tempC].col != -1){
                    int temp = tempR;
                    tempR = pre[temp][tempC].row;
                    tempC = pre[temp][tempC].col;
                    maze[tempR][tempC] = '*';
                }
                maze[start.row][start.col] = 'S';
                deallocate(visit, pre, rows);
                return 1;
            }
        }
        
        
        //South 
        if((r-1) >= 0 && (r-1) < rows){ 
            if(maze[r-1][c] == '.' && visit[r-1][c]==false){
                Location add; 
                add.row = r-1;
                add.col = c;
                q.add_to_back(add);
                pre[r-1][c] = loc;
                visit[r-1][c] = true;
            }else if((r-1) == finish.row && c == finish.col){
                int tempR = r;
                int tempC = c;
                maze[r][c] = '*';
                while(pre[tempR][tempC].row != -1 && 
                                    pre[tempR][tempC].col != -1){
                    int temp = tempR;
                    tempR = pre[temp][tempC].row;
                    tempC = pre[temp][tempC].col;
                    maze[tempR][tempC] = '*';
                }
                maze[start.row][start.col] = 'S';
                deallocate(visit, pre, rows);
                return 1;
            }
        }
        
        
        // East
        if((c+1)>=0 && (c+1)<cols){ 
            if(maze[r][c+1] == '.' && visit[r][c+1]==false){
                Location add; 
                add.row = r;
                add.col = c+1;
                q.add_to_back(add);
                pre[r][c+1] = loc;
                visit[r][c+1] = true;
            }else if(r == finish.row && (c+1)== finish.col){
                int tempR = r;
                int tempC = c;
                maze[r][c] = '*';

                while(pre[tempR][tempC].row != -1 && 
                                  pre[tempR][tempC].col != -1){
                    int temp = tempR;
                    tempR = pre[temp][tempC].row;
                    tempC = pre[temp][tempC].col;
                    maze[tempR][tempC] = '*';
                }
                maze[start.row][start.col] = 'S';
                deallocate(visit, pre, rows);
                return 1;
            }
        }  
        
        
        //West
        if((c-1)>=0 && (c-1)<cols){ 
            if(maze[r][c-1] == '.' && visit[r][c-1]==false){
               Location add; 
               add.row = r;
               add.col = c-1;
               q.add_to_back(add);
               pre[r][c-1] = loc;
               visit[r][c-1] = true;
            }else if(r == finish.row && (c-1) == finish.col){
                int tempR = r;
                int tempC = c;
                maze[r][c] = '*';

                while(pre[tempR][tempC].row != -1 && 
                                  pre[tempR][tempC].col != -1){
                    int temp = tempR;
                    tempR = pre[temp][tempC].row;
                    tempC = pre[temp][tempC].col;
                    maze[tempR][tempC] = '*';
                }
                maze[start.row][start.col] = 'S';
                deallocate(visit, pre, rows);
                return 1;
            }
        }  
        
    }
    deallocate(visit, pre, rows);
    return 0; 
}


void deallocate(bool **visit, Location ** pre, int rows)
{
    for(int i=0;i<rows;i++)
    {
        delete[] visit[i];
        delete[] pre[i]; 
    }     
    
    delete[] visit; 
    delete[] pre;
}
