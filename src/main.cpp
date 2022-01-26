#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <windows.h>
#include <chrono>

#define BLACK "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
using namespace std;
using namespace std::chrono;

struct Letter{
    char alphabet;
    const char * color;
};

void createPuzzle(string fn, vector<vector<Letter>> &puzzle, vector<string> &query);
const char * generateColor();
bool HorizontalR(vector<vector<Letter>> &puzzle, string keyword, int x, int y, int &accessCounter);
bool HorizontalL(vector<vector<Letter>> &puzzle, string keyword, int x, int y, int &accessCounter);
bool VerticalU(vector<vector<Letter>> &puzzle, string keyword, int x, int y, int &accessCounter);
bool VerticalD(vector<vector<Letter>> &puzzle, string keyword, int x, int y, int &accessCounter);
bool DiagLRU(vector<vector<Letter>> &puzzle, string keyword, int x, int y, int &accessCounter);
bool DiagRLU(vector<vector<Letter>> &puzzle, string keyword, int x, int y, int &accessCounter);
bool DiagLRD(vector<vector<Letter>> &puzzle, string keyword, int x, int y, int &accessCounter);
bool DiagRLD(vector<vector<Letter>> &puzzle, string keyword, int x, int y, int &accessCounter);
void bruteSolution(vector<vector<Letter>> &puzzle, vector<string> query);
void printPuzzle(vector<vector<Letter>> puzzle);

int main(){

    vector<vector<Letter>> puzzle;
    vector<string> query;
    string filename;
    cout << "Input filename (<filename>.txt)\n>>";
    getline(cin, filename);
    createPuzzle("..\\test\\"+filename, puzzle, query);
    
    printPuzzle(puzzle);
    
    auto start = high_resolution_clock::now();
    bruteSolution(puzzle,query);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Waktu eksekusi fungsi: "<< duration.count() << " microseconds" << endl;
    cout << "\nSolusi :\n";
    printPuzzle(puzzle);
    
    return  0;
}

void createPuzzle(string fn, vector<vector<Letter>> &puzzle, vector<string> &query){
    char component = '-';
    bool isPuzzle = true;
    string myText;
    
    ifstream readFile(fn);
    while(isPuzzle){
        vector<Letter> line;
        Letter temp;
        getline(readFile, myText);
        myText = myText + " ";
        if(myText.length() == 1){
            isPuzzle = false;
        }else{
            int row = 0;
            for(auto x : myText){
                int col = 0;
                if (x != ' '){
                    component = x;
                    temp.alphabet = component;
                    temp.color = BLACK;
                    line.push_back(temp);
                }
            }
            puzzle.push_back(line);
        }
    }
    myText = "";
    while(getline(readFile, myText)){
        string readyText;
        //Cleaning data from space symbol
        for(auto x : myText){
            if (x != ' '){
                readyText = readyText + x;
            }
        }
        query.push_back(readyText);
    }
    readFile.close();
}

const char * generateColor(){
    static int x = -1;
    vector<const char *> color = {RED,GREEN,BLUE,YELLOW,MAGENTA,CYAN};
    x += 1;
    return color[(x%6)];
}

bool HorizontalR(vector<vector<Letter>> &puzzle, string keyword, int x, int y, int &accessCounter){
    bool comp = true;
    int i = 1;
    int tempy = y+1;
    while(i < keyword.length() && comp){
        accessCounter += 1;
        if(keyword[i] == puzzle[x][tempy].alphabet){
            i += 1;
            tempy += 1;
        }else{
            comp = false;
        }
    }
    if (comp){
        const char * color = generateColor();
        for(i = 0; i < keyword.length(); i++){
            puzzle[x][y+i].color = color;
        }
    }
    return comp;
}

bool HorizontalL(vector<vector<Letter>> &puzzle, string keyword, int x, int y, int &accessCounter){
    bool comp = true;
    int i = 1;
    int tempy = y-1;
    while(i < keyword.length() && comp){
        accessCounter += 1;
        if(keyword[i] == puzzle[x][tempy].alphabet){
            i += 1;
            tempy -= 1;
        }else{
            comp = false;
        }
    }
    if (comp){
        const char * color = generateColor();
        for(i = 0; i < keyword.length(); i++){
            puzzle[x][y-i].color = color;
        }
    }
    return comp;
}

bool VerticalU(vector<vector<Letter>> &puzzle, string keyword, int x, int y, int &accessCounter){
    bool comp = true;
    int i = 1;
    int tempx = x-1;
    while(i < keyword.length() && comp){
        accessCounter += 1;
        if(keyword[i] == puzzle[tempx][y].alphabet){
            i += 1;
            tempx -= 1;
        }else{
            comp = false;
        }
    }
    if (comp){
        const char * color = generateColor();
        for(i = 0; i < keyword.length(); i++){
            puzzle[x-i][y].color = color;
        }
    }
    return comp;
}

bool VerticalD(vector<vector<Letter>> &puzzle, string keyword, int x, int y, int &accessCounter){
    bool comp = true;
    int i = 1;
    int tempx = x+1;
    while(i < keyword.length() && comp){
        accessCounter += 1;
        if(keyword[i] == puzzle[tempx][y].alphabet){
            i += 1;
            tempx += 1;
        }else{
            comp = false;
        }
    }
    if (comp){
        const char * color = generateColor();
        for(i = 0; i < keyword.length(); i++){
            puzzle[x+i][y].color = color;
        }
    }
    return comp;
}

bool DiagLRU(vector<vector<Letter>> &puzzle, string keyword, int x, int y, int &accessCounter){
    bool comp = true;
    int i = 1;
    int tempx = x-1;
    int tempy = y+1;
    while(i < keyword.length() && comp){
        accessCounter += 1;
        if(keyword[i] == puzzle[tempx][tempy].alphabet){
            i += 1;
            tempx -= 1;
            tempy += 1;
        }else{
            comp = false;
        }
    }
    if (comp){
        const char * color = generateColor();
        for(i = 0; i < keyword.length(); i++){
            puzzle[x-i][y+i].color = color;
        }
    }
    return comp;
}

bool DiagRLU(vector<vector<Letter>> &puzzle, string keyword, int x, int y, int &accessCounter){
    bool comp = true;
    int i = 1;
    int tempx = x-1;
    int tempy = y-1;
    while(i < keyword.length() && comp){
        accessCounter += 1;
        if(keyword[i] == puzzle[tempx][tempy].alphabet){
            i += 1;
            tempx -= 1;
            tempy -= 1;
        }else{
            comp = false;
        }
    }
    if (comp){
        const char * color = generateColor();
        for(i = 0; i < keyword.length(); i++){
            puzzle[x-i][y-i].color = color;
        }
    }
    return comp;
}

bool DiagLRD(vector<vector<Letter>> &puzzle, string keyword, int x, int y, int &accessCounter){
    bool comp = true;
    int i = 1;
    int tempx = x+1;
    int tempy = y+1;
    while(i < keyword.length() && comp){
        accessCounter += 1;
        if(keyword[i] == puzzle[tempx][tempy].alphabet){
            i += 1;
            tempx += 1;
            tempy += 1;
        }else{
            comp = false;
        }
    }
    if (comp){
        const char * color = generateColor();
        for(i = 0; i < keyword.length(); i++){
            puzzle[x+i][y+i].color = color;
        }
    }
    return comp;
}

bool DiagRLD(vector<vector<Letter>> &puzzle, string keyword, int x, int y, int &accessCounter){
    bool comp = true;
    int i = 1;
    int tempx = x+1;
    int tempy = y-1;
    while(i < keyword.length() && comp){
        accessCounter += 1;
        if(keyword[i] == puzzle[tempx][tempy].alphabet){
            i += 1;
            tempx += 1;
            tempy -= 1;
        }else{
            comp = false;
        }
    }
    if (comp){
        const char * color = generateColor();
        for(i = 0; i < keyword.length(); i++){
            puzzle[x+i][y-i].color = color;
        }
    }
    return comp;
}
void bruteSolution(vector<vector<Letter>> &puzzle, vector<string> query){
    int rowSize = puzzle.size();
    int colSize = puzzle[0].size();
    int totalAccess = 0;
    for (auto keyword : query){
        bool found = false;
        int len = keyword.length();
        int accessCounter = 0;
        int i = 0;
        while (i<rowSize && !found){
            int j = 0;
            while (j<colSize && !found){
                accessCounter += 1;
                if(keyword[0] == puzzle[i][j].alphabet){
                    if(j+len <= colSize && !found){
                        found = HorizontalR(puzzle,keyword,i,j,accessCounter);
                    }
                    if(j-len >= -1 && !found){
                        found = HorizontalL(puzzle,keyword,i,j,accessCounter);
                    }
                    if(i-len >= -1 && !found){
                        found = VerticalU(puzzle,keyword,i,j,accessCounter);
                    }
                    if(i+len <= rowSize && !found){
                        found = VerticalD(puzzle,keyword,i,j,accessCounter);
                    }
                    if(i-len >= -1 && j+len <= colSize && !found){
                        found = DiagLRU(puzzle,keyword,i,j,accessCounter);
                    }
                    if(i-len >= -1 && j-len >= -1 && !found){
                        found = DiagRLU(puzzle,keyword,i,j,accessCounter);
                    }
                    if(i+len <= rowSize && j+len <= colSize && !found){
                        found = DiagLRD(puzzle,keyword,i,j,accessCounter);
                    }
                    if(i+len <= rowSize && j-len >= -1 && !found){
                        found = DiagRLD(puzzle,keyword,i,j,accessCounter);
                    }
                }
            j+=1;
            }
        i+=1;
        }
        if (found){
            cout << "\"" << keyword << "\"" << "\x1B[32m" << " ditemukan\n" << "\x1B[0m";
        }else{
            cout << "\"" << keyword << "\"" << "\x1B[31m" << " tidak ditemukan\n" << "\x1B[0m";
        }
        cout << "\tJumlah perbandingan huruf : " << accessCounter << endl;
        totalAccess += accessCounter;
    }
    cout  << "\nJumlah perbandingan keseluruhan : " << totalAccess<< endl;
}

void printPuzzle(vector<vector<Letter>> puzzle){
    for(int i = 0; i<puzzle.size(); i++){
        for(int j = 0; j<puzzle[i].size(); j++){
            //cout << puzzle[i][j].color << puzzle[i][j].alphabet << " ";
            printf("%s%c ", puzzle[i][j].color,puzzle[i][j].alphabet);
        }
        cout << endl;
    }
    cout << endl;
}