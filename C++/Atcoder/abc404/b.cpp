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
    ll n; 
    cin >> n;
    vector< vector <char>> tbl1(n, vector<char> (n)),  tbl2(n, vector<char> (n)); 
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){
            cin >> tbl1[i][j];
        }
    }
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){
            cin >> tbl2[i][j];
        }
    }
    ll cnt[4] = {0};
    ll tmp = n - 1;
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){
            if(tbl2[i][j] != tbl1[i][j])cnt[0] ++;
            if(tbl2[j][tmp - i] != tbl1[i][j]){
                cnt[1] ++;
               // cout << j << ' ' << tmp - i << ' ' << i << endl;
            }
            if(tbl2[tmp - i][tmp - j] != tbl1[i][j])cnt[2] ++;
            if(tbl2[tmp - j][i] != tbl1[i][j])cnt[3] ++;
        }
    }
    ll ans = infi;
    for(int i = 0; i < 4; i ++){
        ans = min(ans, cnt[i] + i);
    }
    cout << ans;
    cout << endl;

}