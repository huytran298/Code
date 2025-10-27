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
    ll n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    map<string, ll> cnt;
    string tmp = "";
    for(int i = 0; i < k; i ++){
        tmp += s[i];
    }
    set<string> q;
    ll maxi = 0;
    for(int i = 0; i <= n - k; i ++){
        cnt[tmp] ++;
        maxi = max(maxi, cnt[tmp]);
        q.insert(tmp);
        if(i == n - k)continue;
        for(int j = 0; j < k - 1; j ++)tmp[j] = tmp[j + 1];
        tmp[k - 1] = s[i + k];
    }
    vector<string> ans;
    for(auto x : q){
        if(maxi == cnt[x])ans.pb(x);
    }
    sort(bend(ans));
    cout << maxi << endl;
    for(auto x : ans)cout << x << ' ';
}