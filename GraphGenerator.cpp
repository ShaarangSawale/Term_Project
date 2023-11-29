#include <stdio.h> 
#include <cstdlib>
#include <iostream> 
#include <fstream> 
#include <cmath> 
#include <limits>
using namespace std;

int main(int argc, char* argv[]){
    ofstream outputFile(argv[2]); 
    if(!outputFile){
        cout << "Error: Unable to open output file" << endl;
        return 1; 
    }
    int size = atoi(argv[1]); 
    int Graph[size][size];
    unsigned int limits = 30;
    int upperLimit = limits;
    int lowerLimit = -limits;
    srand((unsigned)time(NULL));
    cout << "starting the random graph generator" << endl;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            Graph[i][j] = (rand() % 201) - 100;
        }
    }

    outputFile << size << endl; 

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(Graph[i][j] > upperLimit || Graph[i][j] < lowerLimit){
                continue;
            }
            outputFile << i << " " << j << " " << Graph[i][j] << endl; 
        }
    }

    outputFile.close();
}