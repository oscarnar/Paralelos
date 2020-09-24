#include <iostream>
#include <chrono>
#include <ctime>
#include <time.h>
#include <fstream>
const int MAX = 1000;
double A[1000][1000], B[1000][1000], R[1000][1000];

using namespace std::chrono;
using namespace std;

void llenar(int max){
  srand (time(NULL));
  for (int i=0;i<max;i++){
    for (int j=0;j<max;j++){
      A[i][j]=rand()%10;
      B[i][j]=rand()%10;
      R[i][j]=0;
    }
  }
}

void bloques(int max,int B2){
  for (int ii = 0; ii < max; ii+=B2) {
    for (int jj = 0; jj < max; jj+=B2) {
      for (int kk = 0; kk < max; kk+=B2) {
        for (int i = ii; i < ii+B2; i++) {
          for (int j = jj; j < jj+B2; j++) {
            for (int k = kk; k < kk+B2; k++) {
              R[i][j] += A[i][k]*B[k][j];
            }
          }
        }
      }
    }
  }
}

void genFile(int min, int size){
    ofstream file;
    file.open("bloquesTest.txt");
    for(int i=min; i<=size; i+=min){
        llenar(i);
        int B2 = i/10;
        auto start = high_resolution_clock::now();
        bloques(i,B2);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        file<< i <<" , " <<duration.count() << endl;
    }
}

int main(){
  genFile(10,1000);
}
