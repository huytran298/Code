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
    ll t = 1;
    while(t --){
        ll q;
        cin >> q;
        while(q --){
            deque<ll> a;
            bool rev = false;
            ll sum = 0, sumrev = 0;
            ll s;
            cin >> s;
            if(s == 1){
                sum -= (a.size() - 1);
                sumrev += a.size() - 1;
                if(!rev){
                    ll tmp = a.back();
                    a.pop_back();
                    a.push_front(tmp);
                }else {
                    ll tmp = a.front();
                    a.pop_front();
                    a.push_back(tmp);
                }
            }else if(s == 2){
                rev = !rev;
            }else {
                ll k;
                cin >> k;
                sum += (a.size() + 1) * k;
                sumrev += k;
                if(!rev){
                    a.push_back(k);
                }else {
                    a.push_front(k);
                }
            }
            if(rev)cout << sum << endl;
            else cout << sumrev << endl;
        }
    }
}