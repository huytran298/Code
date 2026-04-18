#include<bits/stdc++.h>
using namespace std; 

#define ll long long
#define maxN (long long) 1e6 + 5
#define endl '\n'
#define fi first
#define se second
#define infi (int)(1e18)
#define bend(a) (a).begin(), (a).end()
#define rbend(a) (a).rbegin(), (a).rend()
#define gcd(a, b) __gcd(a, b)
#define lcm(a, b) ((a / gcd(a, b)) * b)
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define LIMIT (long long) 1e18
#define maxSelf(a, b) a = max(a, b)
#define minSelf(a, b) a = min(a, b)
#define elif else if
#define FORi(a, b, c) for(int i = a; i <= b; i += c)
#define FORj(a, b, c) for(int j = a; j <= b; j += c)
#define foreach(a) for(auto x : a)
#define pb push_back
#define mod 1000000007
int nxt(){ int n; cin >> n; return n;}
/*
 _  _             _____              
| || |_  _ _  _  |_   _| _ __ _ _ _  
| __ | || | || |   | || '_/ _` | ' \ 
|_||_|\_,_|\_, |   |_||_| \__,_|_||_|
           |__/                      
*/
double ExposureDose(double C, double T_half, double K_gamma, double length){
    return (K_gamma * T_half * C) / (length * length);
}
double C_t(double C, double T_half, double t){
    return C * exp(-0.693 / T_half * t);
}
signed main(){
    fast; 
    ofstream op;
    op.open("runs.txt");
    double C = 1; //mCi
    double T_half = 2; //h
    double K_gamma = 2; //(R*cm^2)/(h*mCi)
    double length = 200; //2m = 200 cm
    op << "C\tC_loss\tDose\n"; 
    for(int i = 0; i <= 100; i ++){
        double C_at = C_t(C, T_half, i);
        
        op << C_at << "\t" << C - C_at << "\t" << ExposureDose(C_at, T_half, K_gamma, length) << endl;
    }
}