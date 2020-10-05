#include <iostream>
#include <fstream>
#include <map>
#include "avlbst.h"

using namespace std;


typedef AVLTree<char, int> ANSWER_MAP_T;
// void printSolution(ANSWER_MAP_T& answer, std::ostream& ostr);
void printSolution(std::map<char, int>& answer, std::ostream& ostr);
bool search(int num, char** map, std::map<char, int>& answer, int& row, int& col, int& countries);
bool check(char c, char** map, std::map<char, int>& answer, int& row, int& col);


int main(int argc, char* argv[])
{
    if(argc < 3) {
        cout << "Please supply a map input file and output filename" << endl;
        return 1;
    }
    // COMPLETE main()
    int countries, row, col;
    ifstream ifile(argv[1]);
    ofstream ofile(argv[2]);
    map<char, int> answer;

    ifile >> countries >> row >> col;
    char** map = new char*[row];
    for(int i=0; i < row; i++){
        map[i] = new char[col];
    }

    for(int i=0; i < row; i++){
        for(int j=0; j < col; j++){
            ifile >> map[i][j];
        }   
    }

    for(int i=0; i< countries; i++){
        answer['A'+i] = 1; 
    }

    // Call printSolution to output the answers to the output file
    if(search(0, map, answer, row, col, countries)){
        printSolution(answer, ofile);
    }else{
        cout << "no solution" << endl;
    }

    return 0;
}

bool search(int num, char** map, std::map<char, int>& answer, int& row, int& col, int& countries){
    if(num == countries){
        return true;
    }else{
        for(answer['A' + num] = 1; answer['A' + num] < 5; answer['A' + num] ++){
            if(check('A' + num, map, answer, row, col)){
                if(search(num+1, map, answer, row, col, countries)){
                    return true;
                }
            }
            printSolution(answer, std::cout);
            cout << endl;
        }
    }
    return false;
}

bool check(char c, char** map, std::map<char, int>& answer, int& row, int& col){
    for(int i=0; i < row; i++){
        for(int j=0; j < col; j++){
            if(map[i][j] == c){
                if(i+1 < row){
                    if(map[i+1][j] != c && answer.find(map[i+1][j]) -> second == answer.find(c) -> second){
                        return false;
                    }
                }
                if(i-1 >= 0){
                    if(map[i-1][j] != c && answer.find(map[i-1][j]) -> second == answer.find(c) -> second){
                        return false;
                    }
                }
                if(j+1 < col){
                    if(map[i][j+1] != c && answer.find(map[i][j+1]) -> second == answer.find(c) -> second){
                        return false;
                    }
                }
                if(j-1 >=0){
                    if(map[i][j-1] != c && answer.find(map[i][j-1]) -> second == answer.find(c) -> second){
                        return false;
                    }
                }
            }
        }   
    }
    return true;
}

// void printSolution(ANSWER_MAP_T& answer, std::ostream& os)
// {
//     for(ANSWER_MAP_T::iterator it = answer.begin();
//             it!= answer.end();
//             ++it) {
//         os << it->first << " " << it->second << endl;
//     }
// }

void printSolution(map<char, int>& answer, std::ostream& os)
{
    for(map<char, int>::iterator it = answer.begin();
            it!= answer.end();
            ++it) {
        os << it->first << " " << it->second << endl;
    }
}

