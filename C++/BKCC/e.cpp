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

/*
n = 1 : s = 1
n = 2 : s = 6
n = 3 : s = 12
n = 4 : s = 18 
s_i = s_{i - 1} + 6
s_i = (i - 1) * 6
sum = s_1 + s_2 + s_3 + s_4 + ... + s_n
    = 1 + 6 + 6 * 2 + 6 * 3 + ... + 6 * (n - 1)
    = 1 + 6 * (1 + 2 + 3 + ... + n - 1)
    = 1 + 6 * (n * (n - 1) / 2)
    = 
*/
/*


*/
void solve(){
    ll n;
    cin >> n;
    cout << 1 + 6 * (n * (n - 1) / 2) << endl;

}
signed main(){
    fast; 
    ll t;
    cin >> t;
    while(t --){
        solve();
    }
}