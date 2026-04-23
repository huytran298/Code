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

string result(string s){
    vector<char> res;
    for(int i = 0; i < s.size(); i ++){
        if(s[i] == ')' && res.size() >= 3){
            ll n = res.size();
            if(res[n - 1] == 'x' && res[n - 2] == 'x' && res[n - 3] == '('){
                for(int j = 1; j <= 3; j ++)res.pop_back();
                res.push_back('x');
                res.push_back('x');
            }else {
                res.pb(s[i]);
            }
        }else {
            res.pb(s[i]);
        }
    }
    string r = "";
    for(auto x : res){
        r += x;
    }
    return r;
}
void solve(){
    string a, b;
    cin >> a >> b;
    if(result(a) == result(b))cout << "Yes";
    else cout << "No";
    // cout << result(a) << " | " << result(b); 
    cout << endl;
}
signed main(){
    fast; 
    ll t;
    cin >> t;
    while(t --){
        solve();
    }
    
}