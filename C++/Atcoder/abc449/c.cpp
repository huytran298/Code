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
    ll n, l, r;
    cin >> n >> l >> r;
    ll ans = 0;
    vector<vector<ll>> flagChar('z' + 1, vector<ll>(n + 1, 0));
    string s;
    cin >> s;
    flagChar[s[0]][0] ++;
    for(int i = 1; i < n; i ++){
        for(int j = 'a'; j <= 'z'; j ++)flagChar[j][i] = flagChar[j][i - 1];
        flagChar[s[i]][i] ++;
        if(i - l >= 0){
            ll tmp = (i - r - 1 >= 0)? flagChar[s[i]][max(i - r - 1, 0LL)] : 0;
            ll cnt = flagChar[s[i]][i - l] - tmp;
            ans += cnt;
            //cout << i << ' ' << ans <<' ' <<flagChar[s[i]][i - l] << ' ' << flagChar[s[i]][max(i - r - 1, 0LL)] << '\n';
        }
    }
    cout << ans;
}