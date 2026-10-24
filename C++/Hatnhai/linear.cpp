#include <iostream>
#include <cmath>
using namespace std;

int main () {
  double x, y, Y;
  freopen("runlinear.dat","w", stdout);
  srand(time(NULL));
  int length = 10E5, i = 1;
  while(i <= length){
    x = rand()/RAND_MAX;
    x = x * 5 - 2;
    y = rand()/RAND_MAX;
    y = y * 8 - 1;
    Y = 2 * x + 1;
    if(y < Y){
      cout << x << endl;
      i ++;
    }
  }
  return 0;
}
