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
double out(ll a, ll b){
    ll tmp = b;
    while(tmp > 0){
        a *= 10LL;
        tmp /= 10LL;
    }
    return a + b;
}
signed main(){
    fast; 
    ll q;
    cin >> q;
    while(q --){
        ll a, b;
        cin >> a >> b;
        ll cnt = 0;
        ll st = ceil(sqrt(out(a, a))), end = floor(sqrt(out(a, a + b)));
        for(ll i = st; i <= end; i ++){
            ll tmp = i * i;
            while(tmp > a){
                tmp /= 10;
            }
            if(tmp == a)cnt ++;
        }
        cout << cnt << endl;
    }
}