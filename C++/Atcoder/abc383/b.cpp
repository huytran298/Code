// time-limit: 3000
/*
**********************************
 Author : Akkotsu / huyhuyne         
**********************************
*/
#include<bits/stdc++.h>
using namespace std; 

#define ll long long
#define maxN (ll) 1e6 + 5
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
void solve(){
    ll h, w, d;
    cin >> h >> w >> d;
    char tbl[h + 1][w + 1];
    for(int i = 1; i <= h; i ++){
        for(int j = 1; j <= w; j ++){
            cin >> tbl[i][j];
        }
    }
    ll ans = 0;
    for(int i = 1; i <= h; i ++){
        for(int j = 1; j <= w; j ++){
            if(tbl[i][j] == '#')continue;
            vector<vector<ll>> ck(h + 1, vector<ll>(w + 1, 0));
            ll cnt1 = 0;
            for(int u = max(0LL, i - d); u <= min(h, i + d); u ++){
                for(int v = max(0LL, j - d); v <= min(w, j + d); v ++){
                    if(tbl[u][v] == '.' && abs(u - i) + abs(v - j) <= d){
                        cnt1 ++;
                        ck[u][v] = 1;
                    }
                }
            }

            for(int u = i; u <= h; u ++){
                for(int v = j; v <= w; v ++){
                    if(tbl[u][v] == '#')continue;
                    ll cnt2 = 0;
                    for(int q = max(0LL, u - d); q <= min(h, u + d); q ++){
                        for(int e = max(0LL, v - d); e <= min(w, v + d); e ++){
                            if(tbl[q][e] == '.' && abs(q - u) + abs(e - v) <= d && !ck[q][e]){
                                cnt2 ++;
                            }
                        }
                        ans = max(ans, cnt1 + cnt2);
                    }

                }
            }
        }
    }
    cout << ans;
}

signed main(){
    fast; 
    ll t = 1;
    //cin >> t;
    while(t --) {
        solve();
        cout << endl;
    }
}