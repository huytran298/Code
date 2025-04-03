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
    ll k;
    string s, t;
    cin >> k >> s >> t;
    ll n = s.size(), m = t.size();
    ll pos = 0;
    ll cnt = 0;
    if(abs(n - m) > k)return void (cout << "No");
    for(int i = 0; i < s.size(); i ++){
        if(pos > m){
            cnt += n - i + 1;
            break;
        }
        if(s[i] == t[pos])pos ++;
        else {
            if(n < m){ //insert
                n ++;
                cnt ++;
                pos ++;
                i --;
            }else if(n == m){ //replace
                cnt ++;
                pos ++;
            }else { //delete
                cnt ++;
            }
        }
    }
    if(cnt <= k)cout << "Yes";
    else cout << "No";
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