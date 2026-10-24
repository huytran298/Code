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
    vector<string> store;
    set<string> cast;
    map<string, ll> t;
    for(int i = 0; i < n; i ++){
        string s;
        cin >> s;
        cast.insert(s);
        store.pb(s);
    }
    for(int i = 0; i < m; i ++){
        string s;
        cin >> s;
        if(cast.find(s) != cast.end()){
            t[s] ++;
        }else {
            ll c_can = 0;
            string s_can = "";
        
            for(auto x : cast){
                if(x.size() == s.size()){
                    ll c = 0;
                    for(int j = 0; j < x.size(); j ++){
                        if(s[j] != x[j])c ++;
                    }
                    if(c == 1){
                        s_can = x;
                        c_can ++;
                    }
                    if(c_can == 2)break;
                }
            }
            if(c_can == 1)t[s_can] ++;
        }
    }
    for(auto x : store){
        //cout << x << ": ";
        cout << t[x] << endl;
    }
}