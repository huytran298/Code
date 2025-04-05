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


bool check1(string s){
    ll n = s.size();
    string s1 = s.substr(0, (n - 1) / 2);
    ll end = n - 1;
    ll pos = 0;
    for(int i = (n - 1) / 2; i < end; i ++){
        if(s[i] != s1[pos])end = min(end + 1, n);
        else pos ++;
    }
    //cout << "pos : " << pos << endl;
    return pos == (n - 1) / 2;

}
void solve(){
    string s;
    ll n;
    cin >> n >> s;
    if(n < 3 && n % 2 == 0)return void (cout << "No Solution");
    vector cnt('Z' + 1, 0LL);
    for(auto x : s)cnt[x] ++;
    ll check = 0, tmp = 0;
    for(int i = 'A'; i <= 'Z'; i ++){
        if(cnt[i] == 0)continue;
        if(cnt[i] % 2 != 0){
            check ++;
            tmp = cnt[i];
        }
        
    }
    if(check == 1){
        //ll tmp = 0;
        string t = s;
        reverse(bend(t));
        bool t1 = check1(s), t2 = check1(t);
        //cout << t1 << ' ' << t2;
        string s1 = s.substr(0, (n - 1) / 2), s2 = s.substr(n - ((n - 1) / 2), (n - 1) / 2);
        if(t1 && t2 & (s1 != s2))cout << "Multiple Solutions";
        else if(t1){
            cout << s.substr(0, (n - 1) / 2);
        }else if(t2) cout << s.substr(n - ((n - 1) / 2), (n - 1) / 2);
        else cout << "No Solution";

    }
    else cout << "No Solution";
    
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