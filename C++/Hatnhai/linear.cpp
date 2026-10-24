#include <iostream>
#include <cmath>
#include<fstream>
using namespace std;

int main () {
  double x, y, Y;
  ofstream myFile("data1.dat");
  srand(time(NULL));
  int length = 5 * 10E4;
  while(length > 1){
    x = double(rand())/RAND_MAX;
    y = double(rand())/RAND_MAX;
    x = x * 8 - 4;
    y = y * 20;
    Y = x * x + 4;
    if(y < Y){
      myFile << x << endl;
      length --;
    }
  }
  return 0;
}
