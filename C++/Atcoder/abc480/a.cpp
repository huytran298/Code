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

signed main(){
    fast; 
    vector<string> tbl(2);
    for(int i = 0; i < 2; i ++){
        cin >> tbl[i];
    }    
    ll u = -1, v = -1;
    ll q = -1, p = -1;
    for(int i = 0; i < 2; i ++){
        for(int j = 0; j < 2; j ++){
            if(tbl[i][j] == 'A'){
                u = i;
                v = j;
            }
        }
    }
    for(int i = 0; i < 2; i ++){
        for(int j = 0; j < 2; j ++){
            if(tbl[i][j] == 'D'){
                q = i;
                p = j;
            }
        }
    }
    if(q == u || p == v)cout << "Yes";
    else cout << "No";
    //cout << q << ' ' << p << ' ' << u << ' ' << v;
}   