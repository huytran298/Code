#include<iostream>
using namespace std;

int main(){
    int n = 100;
    cin >> n;
    
    int listPrime[n + 1];
    for(int i = 0; i <= n; i ++)listPrime[i] = 1;
    listPrime[0] = listPrime[1] = 0;
    for(int i = 2; i * i <= n; i ++){
        if(listPrime[i]){
            for(int j = i * i; j <= n; j += i){
                listPrime[j] = 0;
            }
        }
    }
    for(int i = 0; i <= n; i ++){
        if(listPrime[i]){
            cout << i << ' ';
        }
    }
}