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
bool st[maxN * 4];
ll minT = 0;
ll q;
string s, t;
void build(ll l, ll r, ll i){
    if(r - l + 1 < minT || l < 0 || r >= s.size()){
        st[i] = 0;
        return;
    }else if(r - l + 1 == minT){
        string tmp = "";
        for(int j = l; j <= r; j ++){
            tmp += s[j];
        }
        st[i] = (tmp == t);
    }else {
        ll mid = (l + r) / 2;
        build(l, mid, i * 2);
        build(mid + 1, r, i * 2 + 1);
        if(st[i * 2] || st[i * 2 + 1]){
            st[i] = true;
        }else {
            st[i] = false;
        }
    }
}
bool get(int id, int l, int r, int u, int v) {
    if (v < l || r < u) {
        // Đoạn [l, r] nằm ngoài đoạn [u, v]
        
        return 0;
    }
    if(abs(u - v) + 1 < t.size()){
        return 0;
    }
    if (u <= l && r <= v) {
        // Đoạn [l, r] nằm hoàn toàn trong đoạn [u, v]
        return st[id];
    }
    int mid = (l + r) / 2;
    return (get(id * 2, l, mid, u, v) || get(id * 2 + 1, mid + 1, r, u, v));
}
signed main(){
    fast; 
    
    cin >> q >> s >> t;
    minT = t.size();
    build(0, s.size() - 1, 1);
    while(q --){
        ll u, v;
        cin >> u >> v;
        bool p = get(1, 0, s.size() - 1, u - 1, v - 1);
        if(p)cout << "Yes";
        else cout << "No";
        cout << endl;
    }
}