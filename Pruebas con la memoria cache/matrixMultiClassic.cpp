#include <iostream>
#include <chrono>
#include <fstream>
using namespace std::chrono;
using namespace std;

int MAX = 1000;
int A[1000][1000];
int B[1000][1000];
int C[1000][1000];

void llenar(int max){
    for(int i=0; i<max; i++){
        for(int j=0; j<max; j++){
            A[i][j] = (i)-(j);
            B[i][j] = (i)-(j);
        }
    }
}

void print(){
    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++){
            cout<<C[i][j]<<" ";
        }
        cout<<endl;
    }
}
void multiplicar(int max){
    for(int i=0; i<max; i++){
        for(int j=0; j<max; j++){
            for(int x=0; x<max; x++){
                C[i][j] += A[i][j] * B[j][i];
            }
        }
    }
}

void genFile(int min, int size){
    ofstream file;
    file.open("multiplicacionTest.txt");
    for(int i=min; i<=size; i+=min){
        llenar(i);
        auto start = high_resolution_clock::now(); 
        /* First pair of loops */
        multiplicar(i);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        file<< i <<" , " <<duration.count() << endl;
    }
}

int main(){
    /*llenar();
    auto start = high_resolution_clock::now();
    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++){
            int temp = 0;
            for(int x=0; x<MAX; x++){
                temp += A[i][j] * B[j][i];
            }
            C[i][j] = temp;
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() <<" microseconds"<< endl;
    //print();*/
    genFile(10,1000);
    return 0;
}
