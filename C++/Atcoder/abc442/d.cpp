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

ll tree[maxN], A[maxN], lazy[maxN];
void build(int node, int start, int end)
{
    if(start == end)
    {
        
        tree[node] = A[start];
    }
    else
    {
        int mid = (start + end) / 2;

        build(2*node, start, mid);

        build(2*node+1, mid+1, end);

        tree[node] = tree[2*node] + tree[2*node+1];
    }
}
void updateRange(int node, int start, int end, int l, int r, int val)
{
    if(lazy[node] != 0)
    { 

        tree[node] += (end - start + 1) * lazy[node];    
        if(start != end)
        {
            lazy[node*2] += lazy[node];                  
            lazy[node*2+1] += lazy[node];                
        }
        lazy[node] = 0;                                  
    }
    if(start > end || start > r || end < l)              
        return;
    if(start >= l && end <= r)
    {
        // Segment is fully within range
        tree[node] += (end - start + 1) * val;
        if(start != end)
        {
            // Not leaf node
            lazy[node*2] += val;
            lazy[node*2+1] += val;
        }
        return;
    }
    int mid = (start + end) / 2;
    updateRange(node*2, start, mid, l, r, val);        
    updateRange(node*2 + 1, mid + 1, end, l, r, val);  
    tree[node] = tree[node*2] + tree[node*2+1];        
}

int queryRange(int node, int start, int end, int l, int r)
{
    if(start > end || start > r || end < l)
        return 0;         
    if(lazy[node] != 0)
    {
        tree[node] += (end - start + 1) * lazy[node];           
        if(start != end)
        {
            lazy[node*2] += lazy[node];         
            lazy[node*2+1] += lazy[node];    
        }
        lazy[node] = 0;                 
    }
    if(start >= l && end <= r)             
        return tree[node];
    int mid = (start + end) / 2;
    int p1 = queryRange(node*2, start, mid, l, r);         
    int p2 = queryRange(node*2 + 1, mid + 1, end, l, r); 
    return (p1 + p2);
}
signed main(){
    fast; 
    ll n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; i ++)cin >> A[i];
    build(1, 1, n);
    while(q --){
        ll t;
        cin >> t;
        if(t == 1){
            ll x;
            cin >> x;
            ll diff = abs(A[x] - A[x + 1]);
            if(A[x] > A[x + 1]){
                updateRange(1, 1, n, x, x, - diff);
                updateRange(1, 1, n, x + 1, x + 1, diff);
                
            }else {
                updateRange(1, 1, n, x, x, diff);
                updateRange(1, 1, n, x + 1, x + 1, - diff);
            }
            swap(A[x], A[x + 1]);
        }else {
            ll l, r;
            cin >> l >> r;
            cout << queryRange(1, 1, n, l, r) << endl;
        }
    }

}