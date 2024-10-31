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
bool check(string a, string b){
    sort(bend(a));
    sort(bend(b));
    for(int i = 0; i < a.size(); i ++){
        if(a[i] != b[i])return 0;
    }
    return 1;
}
void solve(){
    string a, b;
    cin >> a >> b;
    if(!check(a, b))return void (cout << "NO");
    vector<vector<ll>> pos(26);
    for(int i = a.size() - 1; i >= 0; i --){
        pos[a[i] - 'a'].pb(i);
    }
    for(int i = 0; i < b.size(); i ++){
        if(b[i] == a[i])continue;
        if(i == 1){
            if(b[i] == a[i + 1])return void(cout << "NO");
        }
        else if(i == b.size() - 1){
            if(b[i] == a[i - 1])return void (cout << "NO");
        }else {
            if(b[i] == a[i + 1] || b[i] == a[i - 1])return void (cout << "NO");
        }
    }
    cout << "YES";
}

signed main(){
    fast; 
    ll t = 1;
    cin >> t;
    while(t --) {
        solve();
        cout << endl;
    }
}