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

void solve()
{
    ll n;
    cin >> n;
    string s;
    cin >> s;
    string q = "";
    char last = s[0];
    ll cntChar = 1;
    vector<ll> cnt;

    for (int i = 1; i < n; i++)
    {
        if (s[i] != last)
        {
            q += last;
            last = s[i];
            cnt.pb(cntChar);
            cntChar = 1;
        }
        else
            cntChar++;
    }
    q += last;
    cnt.pb(cntChar);

    vector<ll> rightS(cnt.size() + 1, 0), midS(cnt.size(), 0), leftS(cnt.size(), 0);
    for (int i = cnt.size() - 1; i >= 0; i--)
    {
        if (q[i] == '1')
            rightS[i] = cnt[i] + rightS[i + 1];
        else
            rightS[i] = rightS[i + 1];
        // cout << i << ' ';
    }
    // return ;
    if (q[0] == '0')
        cnt[0];
    ll before = 0;
    for (int i = 0; i < cnt.size(); i++)
    {
        if (q[i] == '1')
        {
            if (i == 0)
            {
                leftS[i] = cnt[i];
                midS[i] = 0;
            }
            else
            {
                leftS[i] = cnt[i] + leftS[i - 1];
                midS[i] = midS[i - 1];
            }
        }
        else
        {
            if (i == 0)
            {
                midS[i] = cnt[i];
                leftS[i] = 0;
            }
            else
            {
                midS[i] = cnt[i] + midS[i - 1];
                leftS[i] = leftS[i - 1];
            }
        }
    }
    ll ans = infi;
    for (int i = 1; i < cnt.size() - 1; i++)
    {
        // cout << i << ' ';
        if (q[i] == '0')
        {
            ll case1 = (i - 2 >= 0) ? leftS[i - 2] : infi, case2 = (i + 2 < cnt.size()) ? rightS[i + 2] : infi;
            ll case3 = leftS[i], case4 = rightS[i];
            ans = min(ans, min(case1, min(case2, min(case3, case4))));
        }
    }

    if (ans == infi)
        ans = 0;
    // ans = min(midS.back(), ans);
    // cout << endl;
    cout << ans;
    cout << endl;
}

signed main()
{
    fast;
    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}