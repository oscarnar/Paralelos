#include <iostream>
#include <chrono>
#include <fstream>
using namespace std::chrono;
using namespace std;

int MAXI = 1000;
double A[10000][10000], x[10000], y[10000];

void firstLoop(int MAX){
    for(int i = 0; i < MAX ; i++)
        for(int j = 0; j < MAX ; j++)
            y[i] += A[i][j] * x[j];
}

void secondLoop(int MAX){
    for(int j = 0; j < MAX ; j++)
        for(int i = 0; i < MAX ; i++)
            y[i] += A[i][j] * x[j];
}

void printTest(int len,ofstream &file,ofstream &file2){
    // first
    time_point<system_clock> start, end; 
    start = system_clock::now(); 
    firstLoop(len);
    end = system_clock::now(); 
    auto duration = duration_cast<nanoseconds>(end - start);
    file<< len<<" , "<<duration.count() <<endl;
    // second
    time_point<system_clock> start2, end2; 
    start2 = system_clock::now(); 
    secondLoop(len);
    end2 = system_clock::now();
    duration = duration_cast<nanoseconds>(end2 - start2);
    file2<<len<<" , "<<duration.count() <<endl;
}

void genFile(int min, int size){
    ofstream file;
    ofstream file2;
    file.open("primero.txt");
    file2.open("segundo.txt");
    for(int i=0; i<=size; i+=min){
        printTest(i,file,file2);
    }
}

int main(){
    genFile(50,10000);
}
