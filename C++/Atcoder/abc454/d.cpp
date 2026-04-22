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
string convert(string a){
    ll v = a.size();
    for(int i = 1; i < v - 1; i ++){
        if(a[i] == a[i + 1] && a[i] == 'x' && i < v - 2){
            if(a[i - 1] == '(' && a[i + 2] == ')'){
                string b = a;
                b.erase(i + 2, 1);
                b.erase(i - 1, 1);
                a = b;
                i -= 2;
                v -= 2;
            }
        }
    }
    return a;
}
void solve(){
    string a, b;
    cin >> a >> b;
    // if(convert(a) == convert(b)){
    //     cout << "Yes";
    // }else {
    //     cout << "No";
    // }
    // cout << endl;
    cout << convert(a);
}
signed main(){
    fast; 
    string s;
    cin >> s;
    ll v = s.size();
    for(int i = 1; i < v - 1; i ++){
        if(s[i] == s[i + 1] && s[i] == 'x' && i < v - 2){
            if(s[i - 1] == '(' && s[i + 2] == ')'){
                s.erase(i + 2, 1);
                string b = s;
                b.erase(i - 1, 1);
                s = b;
                i -= 2;
                v -= 2;
            }
        }
    }
    cout << s;
    
}