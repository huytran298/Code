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
    
    int N, Q;
    cin >> N >> Q;
    
    // Store coordinates
    vector<pair<ll, ll>> monsters(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> monsters[i].fi >> monsters[i].se;
    }
    
    // Normalize direction vectors and compute angle for sorting
    struct Direction {
        ll x, y;
        long double angle;
        bool operator<(const Direction& other) const {
            return angle < other.angle;
        }
    };
    
    vector<Direction> dirs(N + 1);
    for (int i = 1; i <= N; i++) {
        ll x = monsters[i].fi;
        ll y = monsters[i].se;
        ll g = gcd(abs(x), abs(y));
        dirs[i].x = x / g;
        dirs[i].y = y / g;
        dirs[i].angle = atan2((long double)y, (long double)x);
        if (dirs[i].angle < 0) dirs[i].angle += 2 * M_PI;
    }
    
    // Group monsters by normalized direction
    map<pair<ll, ll>, int> dirCount;
    for (int i = 1; i <= N; i++) {
        dirCount[{dirs[i].x, dirs[i].y}]++;
    }
    
    // Extract unique directions with their angles and counts
    vector<pair<long double, pair<ll, ll>>> uniqueDirs;
    for (auto& p : dirCount) {
        long double angle = atan2((long double)p.fi.se, (long double)p.fi.fi);
        if (angle < 0) angle += 2 * M_PI;
        uniqueDirs.pb({angle, p.fi});
    }
    
    // Sort by angle
    sort(uniqueDirs.begin(), uniqueDirs.end());
    
    // Build prefix sum for counts
    int m = uniqueDirs.size();
    vector<int> prefixSum(m + 1, 0);
    for (int i = 0; i < m; i++) {
        prefixSum[i + 1] = prefixSum[i] + dirCount[uniqueDirs[i].se];
    }
    
    // Map each monster to its index in uniqueDirs
    vector<int> monsterIdx(N + 1);
    for (int i = 1; i <= N; i++) {
        pair<ll, ll> normDir = {dirs[i].x, dirs[i].y};
        for (int j = 0; j < m; j++) {
            if (uniqueDirs[j].se == normDir) {
                monsterIdx[i] = j;
                break;
            }
        }
    }
    
    // Process queries
    for (int j = 0; j < Q; j++) {
        int A, B;
        cin >> A >> B;
        
        int idxA = monsterIdx[A];
        int idxB = monsterIdx[B];
        
        if (idxA == idxB) {
            // Same direction, no rotation
            cout << dirCount[uniqueDirs[idxA].se] << endl;
            continue;
        }
        
        int total = 0;
        
        if (idxA < idxB) {
            // Clockwise from A to B: [A, B]
            total = prefixSum[idxB + 1] - prefixSum[idxA];
        } else {
            // Clockwise from A to B: [A, end) + [0, B]
            total = prefixSum[m] - prefixSum[idxA] + prefixSum[idxB + 1];
        }
        
        cout << total << endl;
    }
    
    return 0;
}
