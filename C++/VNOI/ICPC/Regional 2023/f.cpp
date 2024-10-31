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
bool check(string a, string b, int k){
    string s = "", s1 = "";
    for(; k < a.size(); k += 2){
        s += a[k];
        s1 += b[k];
    }
    sort(bend(s));
    sort(bend(s1));
    for(int i = 0; i < s.size(); i ++){
        if(s[i] != s1[i])return false;
    }
    return true;
}
void solve(){
    string a, b;
    cin >> a >> b;
    if(a.size() != b.size())return void (cout << "NO");
    ll n = a.size();
    vector<vector<ll>> p(2, vector<ll>(26, 0));
    for(int i = 0; i < n; i ++){
        p[i % 2][a[i] - 'a'] ++;
    }
    for(int i = 0; i < n; i ++){
        if(p[i % 2][b[i] - 'a'] == 0)return void (cout << "NO");
        p[i % 2][b[i] - 'a'] --;
    }
    for(int i = 0; i < 25; i ++){
        if(p[0][i] != 0 || p[1][i] != 0)return void (cout << "NO");
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