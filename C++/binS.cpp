#include<bits/stdc++.h>
using namespace std; 

#define ll long long
#define maxN (long long) 1e5 + 5
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

ll sol1(priority_queue<ll> q, ll k, ll n, ll mid){
    vector<ll> sm(k + 1, 0);
     ll minz = 0, maxz = 0;
    while(!q.empty()){
        ll x = q.top();
        q.pop();
        ll had = 0;
        ll minCheck = 0;
        ll diff = 0, pos, diff1 = infi, pos1 = 0;
        for(int i = 1; i <= k; i ++){
            if(sm[i] == 0){
                sm[i] += x;
                had = 1;
                break;
            }else if(mid == sm[i] + x){
                sm[i] += x;
                had = 1;
                break;
            }else if(mid > sm[i] + x && mid - (sm[i] + x)  > diff){
                diff = mid - (sm[i] + x);
                minCheck = 1;
                pos = i;
            }else if(abs(mid - (sm[i] + x))  < diff1){
                diff1 = abs(mid - (sm[i] + x));
                pos1 = i;
            }

        }
        if(!had){
            if(minCheck)sm[pos] += x;
            else sm[pos1] += x;
        }

    }
    ll ans = 0;
    for(int i = 1; i <= k; i ++)ans = max(ans, sm[i]);
    return ans;
}
ll sol2(priority_queue<ll> q, ll k, ll n, ll mid){
    vector<ll> sm(k + 1, 0);
     ll minz = 0, maxz = 0;
    while(!q.empty()){
        ll x = q.top();
        q.pop();
        ll had = 0;
        ll minCheck = 0;
        ll diff = infi, pos, diff1 = infi, pos1 = 0;
        for(int i = 1; i <= k; i ++){
            if(sm[i] == 0){
                sm[i] += x;
                had = 1;
                break;
            }else if(mid == sm[i] + x){
                sm[i] += x;
                had = 1;
                break;
            }else if(mid > sm[i] + x && mid - (sm[i] + x)  < diff){
                diff = mid - (sm[i] + x);
                minCheck = 1;
                pos = i;
            }else if(abs(mid - (sm[i] + x))  < diff1){
                diff1 = abs(mid - (sm[i] + x));
                pos1 = i;
            }

        }
        if(!had){
            if(minCheck)sm[pos] += x;
            else sm[pos1] += x;
        }
    }
    ll ans = 0;
    for(int i = 1; i <= k; i ++)ans = max(ans, sm[i]);
    return ans;
}
signed main(){
    fast; 
    ll n;
    cin >> n;
    vector<ll> a(n);
    for(auto &q : a)cin >> q;
    ll x;
    cin >> x;
    ll mid = 0, l = 0, r = n;
    while(l < r){
        mid = l + (r - l) / 2LL;
        //cout << l << " " << r << ' ' << mid << ' ' << a[mid] << '\n';
        if(a[mid] >= x)r = mid;
        else l = mid + 1; 
    }
    if(l < n && a[l] < x)l ++;
    cout << l;
}
