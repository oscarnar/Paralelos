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
    //duration<double> elapsed_seconds = end - start;
    auto duration = duration_cast<nanoseconds>(end - start);
    file<< len<<" , "<<duration.count() <<endl;
    // second
    time_point<system_clock> start2, end2; 
    start2 = system_clock::now(); 
    secondLoop(len);
    end2 = system_clock::now(); 
    //elapsed_seconds = end2 - start2;
    duration = duration_cast<nanoseconds>(end2 - start2);
    // write files
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
    /*int MAX = 1000;
    cout<<"Size "<<MAX<<endl;
    double A[MAX][MAX], x[MAX], y[MAX];
    auto start = high_resolution_clock::now();*/   
    /* First pair of loops */
    /*for(int i = 0; i < MAX ; i++)
        for(int j = 0; j < MAX ; j++)
            y[i] += A[i][j] * x[j];
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << duration.count() <<" nanoseconds 1ra"<< endl;

    auto start2 = high_resolution_clock::now();*/
    /* Second pair of loops */
    /*for(int j = 0; j < MAX ; j++)
        for(int i = 0; i < MAX ; i++)
            y[i] += A[i][j] * x[j];
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<nanoseconds>(stop2 - start2);
    cout << duration2.count() <<" nanoseconds 2da"<< endl;*/
    genFile(50,10000);
}
