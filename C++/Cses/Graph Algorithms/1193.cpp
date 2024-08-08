// time-limit: 3000
/*
**********************************
 Author : Akkotsu / huyhuyne         
**********************************
*/
#include<bits/stdc++.h>
using namespace std; 

#define ll long long
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
//hàm check tại vị trí x, y có phải là vị trí thỏa mãn điều kiện hay không
bool check(vector<vector<ll>> visited, ll n, ll m, ll x, ll y){
    return !visited[x][y] && x > 0 && x <= n && y > 0 && y <= m;
}
void solve(){
    //BFS - Breath First Search - Tìm kiếm theo chiều rộng - loan (loan nước)
    ll n, m, xs = 0, ys = 0, xe = 0, ye = 0;
    cin >> n >> m;
    char tbl[n + 10][m + 10];
    char ways[n + 10][m + 10];
    vector<vector<ll>> visited(n + 10, vector<ll>(m + 10, 0));
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            ways[i][j] = '!';
            cin >> tbl[i][j];
            if(tbl[i][j] == '#')visited[i][j] = 1;
            else if(tbl[i][j] == 'B'){
                xe = i;
                ye = j;
            }else if(tbl[i][j] == 'A'){
                xs = i;
                ys = j;
            }
        }
    }
    queue<pair<ll, ll>> step;
    visited[xs][ys] = 1;
    step.push({xs, ys});
    ways[xe][ye] = '0';
    while(!step.empty()){
        pair<ll, ll> st = step.front();
        //visited[st.first][st.second] = 1;
        step.pop();
        if(check(visited, n, m, st.first + 1, st.second)){
            step.push({st.first + 1, st.second});
            visited[st.first + 1][st.second] = 1;
            ways[st.first + 1][st.second] = 'D';
        }
        if(check(visited, n, m, st.first -1, st.second)){
            step.push({st.first - 1, st.second});
            visited[st.first - 1][st.second] = 1;
            ways[st.first - 1][st.second] = 'U';
        }
        if(check(visited, n, m, st.first, st.second + 1)){
            step.push({st.first, st.second + 1});
            visited[st.first][st.second + 1] = 1;
            ways[st.first][st.second + 1] = 'R';
        }
        if(check(visited, n, m, st.first, st.second - 1)){
            step.push({st.first, st.second - 1});
            visited[st.first][st.second - 1] = 1;
            ways[st.first][st.second - 1] = 'L';
        }
    }
    //  for(int i = 1; i <= n; i ++){
    //      for(int j = 1; j <= m; j ++)cout << ways[i][j];
    //      cout << endl;
    //  }
    //  return;
    if(ways[xe][ye] != '0'){
        string ans = "";
        while(xe != xs || ye != ys){
            char c = ways[xe][ye];
            ans += c;
            if(c == 'D')xe --;
            else if(c == 'U')xe ++;
            else if(c == 'L')ye ++;
            else ye --;
        }
        reverse(bend(ans));
        cout << "YES\n"<< ans.size() << '\n' << ans;
    }else cout << "NO";
}

signed main(){
    fast; 
    ll t = 1;
    //cin >> t;
    while(t --) {
        solve();
        cout << endl;
    }
}