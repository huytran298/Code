#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define maxN (long long)1e6 + 5
#define endl '\n'
#define fi first
#define se second
#define infi (int)(1e18)
#define bend(a) (a).begin(), (a).end()
#define rbend(a) (a).rbegin(), (a).rend()
#define gcd(a, b) __gcd(a, b)
#define lcm(a, b) ((a / gcd(a, b)) * b)
#define fast                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
#define LIMIT (long long)1e18
#define maxSelf(a, b) a = max(a, b)
#define minSelf(a, b) a = min(a, b)
#define elif else if
#define FORi(a, b, c) for (int i = a; i <= b; i += c)
#define FORj(a, b, c) for (int j = a; j <= b; j += c)
#define foreach(a) for (auto x : a)
#define pb push_back
#define mod 1000000007
int nxt()
{
    int n;
    cin >> n;
    return n;
}
/*
 _  _             _____
| || |_  _ _  _  |_   _| _ __ _ _ _
| __ | || | || |   | || '_/ _` | ' \
|_||_|\_,_|\_, |   |_||_| \__,_|_||_|
           |__/
*/

signed main()
{
    fast;
    ll t;
    cin >> t;
    while (t--)
    {
        string p, s;
        cin >> p >> s;
        vector<ll> a, b;
        a.pb(1);
        b.pb(1);
        string tp = "", ts ="";
        tp += p[0];
        ts += s[0];
        for(int i = 1; i < p.size(); i ++){
            if(p[i] != p[i - 1]){
                a.pb(1);
                tp += p[i];
            }else a.back() ++;
        }

        for(int i = 1; i < s.size(); i ++){
            if(s[i] != s[i - 1]){
                b.pb(1);
                ts += s[i];
            }else b.back() ++;
        }
        if(tp != ts || a.size() != b.size()){
            cout << "NO\n";

            continue;
        }
        bool found = true;
        for(int i = 0; i < a.size(); i ++){
            if(b[i] < a[i] || b[i] > a[i] * 2){
                found = false;
                break;
            }
        }
        if(found)cout << "YES\n";
        else cout << "NO\n";

        //cout << tp << ' ' << ts;
    }
}