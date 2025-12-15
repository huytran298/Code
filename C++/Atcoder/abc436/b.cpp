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
ll num(ll x, ll n){
    if(x < 0)return x + n;
    return x % n;
}
signed main(){
    fast; 
    ll n;
    cin >> n;
    vector<vector<ll>> table(n , vector<ll>(n, 0));
    table[0][(n - 1) / 2] = 1;
    ll k = 2, r = 0, c = (n - 1) / 2; 
    for(int i = 0; i < n * n - 1; i ++){
        //cout << r << ' ' << c << endl;
        if(table[num(r - 1, n)][(c + 1) % n] == 0){
            table[num(r - 1, n)][(c + 1) % n] = k;
            r = num(r - 1, n);
            c = (c + 1) % n;
        }else {
            table[(r + 1) % n][c] = k;
            r = (r + 1) % n;
        }
        k ++;
    }
    for(auto x : table){
        for(auto y : x){
            cout << y << ' ';
        }
        cout << endl;
    }
}