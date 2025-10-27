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
void solve(){
    ll n;
    cin >> n;
    vector<ll> lines(n + 2, 0), arr, ladder;
    
    set<ll> fil;
    ll a = 0, b = 0;
    for(int i = 1; i <= n; i ++){
        cin >> lines[i];
        a = max(a, lines[i]);
        if(i > 1)b = max(b, abs(lines[i] - lines[i - 1]));
    }
    
    ll mid;
    ll hi = max(a, b), lo = 0;
    while(lo < hi){
        mid = (lo + hi) / 2LL;

        ll stop = 1;
        ll tmp = lines[1];
        for(int i = 2; i <= n; i ++){
            if(abs(lines[i] - lines[i - 1]) <= mid){
                tmp = min(tmp, lines[i]);
            }else {
                if(tmp > mid){
                    stop = 0;
                    lo = mid + 1;
                    break;
                }
                tmp = lines[i];
            }
        }
        if(!stop)continue;
        if(tmp <= mid)hi = mid;
        else lo = mid + 1;
    }
    cout << lo;
    cout << endl;
}
signed main(){
    fast; 
    string filename = "";
    freopen("snake_scales_chapter_2_input.txt", "r", stdin);
    freopen("snake_scales_chapter_2_output.txt", "w", stdout);
    ll t;
    cin >> t;
    for(int i = 1; i <= t; i ++){
        cout << "Case #" << i << ": ";
        solve();
    }
}