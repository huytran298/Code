#include <iostream>
#include <math.h>
using namespace std;

int main(){
  srand(time(NULL));
  freopen("run02.dat", "w", stdout);
  double r1, r2;
  int i = 0;
  int Nevent = 500000;
  double mu = 2, sigma = 3;
  while (i < Nevent){
    r1 = (double)rand()/RAND_MAX;
    r2 = (double)rand()/RAND_MAX;
    double x2, x1 = sqrt((-2) * log(r1));
    x2 = sin(2. * M_PI * r2);
    double gauss = mu + sigma * x1 * x2;
    double newGass = 1 / (sigma * sqrt(2 * M_PI)) * exp(-pow(r1 - mu, 2)/(2 * sigma * sigma));
    cout << gauss << endl;
    i ++;
  }
   
  return 0;
}
