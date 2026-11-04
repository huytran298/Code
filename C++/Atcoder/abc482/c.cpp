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
bool s_R(pair<ll, ll> a, pair<ll, ll> b){
    return a.first < b.first;
}

bool s_C(pair<ll, ll> a, pair<ll, ll> b){
    return a.second < b.second;
}
signed main(){
    fast; 
    ll h, w, n, q;
    cin >> h >> w >> n >> q;
    
    vector<ll> placed_R;
    vector<ll> placed_C;
    for(int i = 0; i < n; i ++){
        ll u, v;
        cin >> u >> v;
        placed_R.pb(u);
        placed_C.pb(v);
    }
    sort(bend(placed_C));
    sort(bend(placed_R));
    while(q --){
        ll t, l, r;
        cin >> t >> l >> r;
        if(t == 1){
            ll L = lower_bound(bend(placed_R), l) - placed_R.begin();
            ll R = upper_bound(bend(placed_R), r) - placed_R.begin();
            R --;
            if(L == -1)L = 0;
            if(R == -1 || L == placed_R.size())cout << 0;
            else cout << (R - L + 1);
        }
        else{
            ll L = lower_bound(bend(placed_C), l) - placed_C.begin();
            ll R = upper_bound(bend(placed_C), r) - placed_C.begin();
            R --;
            if(L == -1)L = 0;
            if(R == -1 || L == placed_C.size())cout << 0;
            else cout << (R - L + 1);
        }
        cout << endl;
    }
}

/*

*/
