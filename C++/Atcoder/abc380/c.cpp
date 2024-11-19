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
    ll n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    s += '0';
    ll poslast = 0, cnt = 0, posst = 0;
    ll state = 0;
    for(int i = 0; i <= n; i ++){
        if(s[i] == '0'){
            if(!state)continue;
            state = 0;
            cnt ++;
            if(cnt == k - 1){
                poslast = i;
            }else if(cnt == k){
                for(int j = 0; j < i - posst; j ++){
                    swap(s[j + poslast], s[j + posst]);
                }
                for(int j = 0; j < n; j ++)cout << s[j];
                
                return;
            }
        }else {
            if(state)continue;
            state = 1;
            if(cnt == k - 1){
                posst = i;
            }
        }
    }
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