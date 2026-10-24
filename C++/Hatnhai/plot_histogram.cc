#include <iostream>
#include <fstream>
#include <TH1.h>
using namespace std;

int plot_histogram(){
ifstream file ("runlinear.dat");
double x;
TH1* h1 = new TH1F("h1","ve histogram",2000,-10,10); //Khai bao histogram

/// Doc du lieu tu file va fill vao histogram
x=0;
while (1){
 if(!file.good()) break;
 file >> x;               //Doc du lieu tu file vao bien x
 h1->Fill(x);             // Du lieu x duoc fill histogram h1
}

/// Ve histogram
TCanvas* c1 = new TCanvas();
h1->Draw();
file.close();
return 0;
}



