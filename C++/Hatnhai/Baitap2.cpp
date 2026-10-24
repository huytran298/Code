#include <iostream>
#include <math.h>
#include<fstream>
using namespace std;

int main(){
  srand(time(NULL));
  ofstream myFile("data2.dat");
  double r1, r2;
  int i = 0;
  int Nevent = 500000;
  double mu = 2, sigma = 2;
  while (i < Nevent){
    r1 = (double)rand()/RAND_MAX;
    r2 = (double)rand()/RAND_MAX;
    double x2, x1 = sqrt((-2) * log(r1));
    x2 = sin(2. * M_PI * r2);
    double gauss = mu + sigma * x1 * x2;  
    
    myFile << gauss << endl;                                          
    i ++;
  }
   
  return 0;
}
