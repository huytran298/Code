// Doc du lieu tu file va ve histogram
// Khai bao thu vien cho C++
#include <iostream>
#include <fstream>
// Khai bao thu vien ben Root
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>

using namespace std;
int AsciiToTTree(){
ifstream file ("run01.dat");
float x;

TFile *F=new TFile("data2.root","RECREATE");
TTree *T=new TTree("T","gia tri x");
T->Branch("x",&x,"x/F");

/// Doc du lieu tu file va fill vao TTree
x=0;
while (1){
 if(!file.good()) break;
 file >> x;               //Doc du lieu tu file vao bien x
 T->Fill();               // ghi x vao T
}
 F->Write();              // Write T vao F
 F->Close();

file.close();
return 0;
}



