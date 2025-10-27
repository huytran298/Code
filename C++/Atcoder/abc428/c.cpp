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
    ll q;
    cin >> q;
    vector<char> sq;
    vector<ll> past;
    ll ans = 0;
    while(q --){
        ll t;
        cin >> t;
        if(t == 1){
            char c;
            cin >> c;
            ll delta = (c == '(')? 1 : -1;
            ans += delta;
            sq.pb(c);
            if(past.empty())past.pb((ans >= 0));
            else{
                if(past.back())past.pb((ans >= 0));
                else past.pb(false);
            }

        }else {
            ll delta = (sq.back() == '(')? 1 : -1;
            ans -= delta;
            sq.pop_back();
            past.pop_back();
        }
        bool state = (past.empty() || past.back());
        if(ans == 0 && state)cout << "Yes";
        else cout << "No";
        cout << endl;
    }
}