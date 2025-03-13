// time-limit: 3000
/*
**********************************
 Author : Akkotsu / huyhuyne         
**********************************
*/
#include<bits/stdc++.h>
using namespace std; 

#define ll long long
#define int long long
#define maxN (ll) 1e6 + 5
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
    ll r, c, n, p;
    cin >> r >> c >> n >> p;
    // gọi lst là tập hợp các điểm có giá trị từ 1 -> p (có thể sử dụng 2 vector để lưu giá trị của các điểm)
    vector<pair<ll, ll>> lst;

    ll tbl[r + 1][c + 1];
    for(int i = 1; i <= r; i ++){
        for(int j = 1; j <= c; j ++){
            ll x;
            cin >> x;
            tbl[i][j] = x;
            // lấy vị trí các điểm có giá trị từ 1 -> p
            if(x > 0 && x <= p)lst.pb({i, j});
        }
    }
    // gọi meet là tập hợp các giá trị mà có thể gặp được 
    set<ll> meet;
    ll dx[] = {1,0 , -1, 0};
    ll dy[] = {0, 1, 0, -1};
    for(auto [u, v] : lst){
        // delta là sự chênh lệch giữa giá trị của điểm hiện tại và giá trị của p
        ll delta = p - tbl[u][v];
        //duyệt qua 4 cạnh liền kề của điểm hiện tại
        for(int i = 0; i < 4; i ++){
            ll x = u + dx[i];
            ll y = v + dy[i];
            // nếu điểm đó nằm trong bảng và giá trị của điểm đó + delta <= n và giá trị của điểm đó > 0 thì thêm giá trị đó vào tập hợp meet
            if(x > 0 && x <= r && y > 0 && y <= c){
                if(tbl[x][y] + delta <= n && tbl[x][y] > 0)meet.insert(tbl[x][y] + delta);
            }
        }
    }
    // in ra kết quả
    cout << meet.size() << '/' << n - 1;
}

signed main(){
    fast; 
    ll t = 1;
   // cin >> t;
    while(t --) {
        solve();
        //cout << endl;
    }
}