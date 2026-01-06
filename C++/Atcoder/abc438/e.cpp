#include <iostream>
#include <vector>

using namespace std;


const int MAXN = 200005;
const int LOG = 32; 


int up[LOG][MAXN];
long long weight[LOG][MAXN];
int A[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    int Q;
    cin >> Q; 

    for (int i = 1; i <= n; ++i) {
        cin >> A[i];
    }
    for (int i = 1; i <= n; ++i) {
        up[0][i] = A[i];
        weight[0][i] = i;
    }


    for (int k = 1; k < LOG; ++k) {
        for (int i = 1; i <= n; ++i) {
            int mid = up[k - 1][i];
            up[k][i] = up[k - 1][mid];
            weight[k][i] = weight[k - 1][i] + weight[k - 1][mid];
        }
    }


    while (Q--) {
        long long T;
        int B;
        cin >> T >> B;

        long long total_water = 0;
        int curr = B;

        for (int k = 0; k < LOG; ++k) {
            if ((T >> k) & 1) {
                total_water += weight[k][curr];
                curr = up[k][curr];
            }
        }

        cout << total_water << endl;
    }

    return 0;
}