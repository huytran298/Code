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
    ll l[n + 1];
    ll x[n + 1][101];
    vector<ll> juices(m + 1, 0);
    for(int i = 1; i <= n; i ++){
        cin >> l[i];
        for(int j = 1; j <= l[i]; j ++){
            cin >> x[i][j];
        }
    }
    bool checked = 0;
    for(int i = 1; i <= n; i ++){
        checked = 0;
        for(int j = 1; j <= l[i]; j ++){
            if(!juices[x[i][j]]){
                checked = 1;
                cout << x[i][j];
                juices[x[i][j]] = 1;
                break;
            }
        }
        if(!checked)cout << 0 ;
        cout << endl;
    }

}