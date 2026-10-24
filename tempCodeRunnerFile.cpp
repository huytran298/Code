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
    ll n, m;
    cin >> n >> m;
    ll matrix[n][m];
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < m; j ++){
            cin >> matrix[i][j];
        }
    }
    ll minRow[n] = {LIMIT}, maxCol[m] = {0};
    // for(int i = 0; i < n; i ++){
    //     for(int j = 0; j < m; j ++)minRow[i] = min(minRow[i], matrix[i][j]);
    // }

    // for(int i = 0; i < m; i ++){
    //     for(int j = 0; j < n; j ++)maxCol[i] = max(maxCol[i], matrix[j][i]);
    // }
    for(int i = 0; i < n; i ++)cout << minRow[i] << ' ';
    cout << endl;
    
    // for(int i = 0; i < m; i ++)cout << maxCol[i] << ' ';
    // cout << endl;
    // for(int i = 0; i < n; i ++){
    //     for(int j = 0; j < m; j ++){
    //         if(minRow[i] == maxCol[j]){
    //             cout << matrix[i][j];
    //             return 0;
    //         }
    //     }
    // }
}