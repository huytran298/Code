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
ll a[maxN], n;
vector<ll> c(maxN, 0);
ll cnt = 0;
void bt(ll q){
    if(q == n + 1 || q == n){
        bt(q + 1);
        return ;
    }
    for(int i = 2; i < 2 * n; i ++){
        if(!c[i]){
            a[q] = i;
            c[i] = 1;
            if(q == 2 * n){
                bool check = false;
                for(int j = 1; j <= n - 1; j ++){
                    if(a[j] > a[j + 1]){
                        check = true;
                        break;
                    }
                }
                
                for(int j = 1; j <= n - 1; j ++){
                    if(a[n + j] > a[n + j + 1]){
                        check = true;
                        break;
                    }
                }
                
                for(int j = 1; j <= n - 1; j ++){
                    if(a[j] < a[j + n]){
                        check = true;
                        break;
                    }
                }
                for(int j = 1; j <= n - 1; j ++){
                    if(a[j] > a[j + 1]){
                        check = true;
                        break;
                    }
                }
                
                if(!check){
                    cnt ++;
                    for(int j = 1; j <= n; j ++){
                        cout << a[j] << ' ';
                    }
                    cout << '\n';
                    for(int j = 1; j <= n; j ++){
                        cout << a[n + j] << ' ';
                    }
                    cout << "\n-------------------------\n";
                }
            }else {
                bt(q + 1);
            }
            c[i] = 0;
        }
    }
}
signed main(){
    fast; 
   
    cout << log(0)/log(2);

}

/*
    Chia 2 TH : 
    TH 1 : 2n và 2n - 1 chung cột. Số cách chọn sẽ là S_{n - 1}
    TH 2 : 2n và 2n - 1 cùng hàng. 
*/