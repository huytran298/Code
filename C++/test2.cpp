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
#define mod 998244353
int nxt(){ int n; cin >> n; return n;}
/*
 _  _             _____              
| || |_  _ _  _  |_   _| _ __ _ _ _  
| __ | || | || |   | || '_/ _` | ' \ 
|_||_|\_,_|\_, |   |_||_| \__,_|_||_|
           |__/                      
*/

double functionS(double x){
    return ((1 / (x * x)) + 4 * x);
}
void solve(){
    double begin, end, step;
    cin >> begin >> end >> step;
    double simpson13, simpson38;
    simpson13 = simpson38 =  functionS(begin);
    ll cnt = 1;
    while(begin < end){
        begin += step;
        double value = functionS(begin);
        simpson13 +=  (double)((cnt % 2)? 4 : 2) * value;
        simpson38 += 
        //cout << (double)((cnt % 2)? 4 : 2) << ' ' << begin << endl; 
        cnt ++;
    }
    //cout << simpson13 << endl;
    simpson13 = (step / 3 ) * simpson13;
    cout << fixed << setprecision(4) << simpson13;
}

signed main(){
    fast; 
    ll t = 1;
    //cin >> t;
    while(t --){
        solve();
        cout << endl;
    }
}