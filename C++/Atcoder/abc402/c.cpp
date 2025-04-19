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
    vector<vector<ll>> dishs(m);
    for(int i = 0; i < m; i ++){
        ll k;
        cin >> k;
        vector<ll> ingre(k);
        for(int j = 1; j <= k; j ++){
            cin >> ingre[j - 1];
        }
        dishs[i] = ingre;
    }
    vector<ll> b(n + 1);
    for(int i = 1; i <= n; i ++){
        ll x;
        cin >> x;
        b[x] = i;
    }
    vector<ll> traced(n + 1, 0);
    for(int i = 0; i < m; i ++){
        ll days = 0;
        for(auto x : dishs[i]){
            days = max(days, b[x]);
        }
        traced[days] ++;
    }
    ll sum = 0;
    for(int i = 1; i <= n; i ++){
        sum += traced[i];
        cout << sum << endl;
    }
}