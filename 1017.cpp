#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
const int maxn = 1e5 + 10;
int a[maxn], a_rev[maxn];
int len_a[maxn], len_a_rev[maxn];
int n;
void init() {
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> a[i];
        a_rev[n + 1 - i] = a[i];
    }
}
int que[maxn], top;
void solve(int f[], int len[]){
    que[1] = f[1];
    len[1] = 1;
    top = 1;
    for(int i = 2; i <= n; ++i) {
        int x = f[i];
        if(que[top] < x) {
            que[++ top] = x;
            len[i] = top;
            continue;
        }
        int l = 1, r = top;
        while (l < r) {
            int mid = (l + r) >> 1;
            if(que[mid] >= x) r = mid;
            else l = mid + 1;
        }
        que[l] = x;
        len[i] = l;
    }
}


int main() {
    freopen("test.in", "r", stdin);
    init();
    solve(a, len_a);
    solve(a_rev, len_a_rev);
    int ans = 0, h = 0, sym = 0;
    for(int i = 1; i <= n; ++i) {
        int l = len_a[i] - 1, r = len_a_rev[n - i + 1] - 1;
        if(l == 0 || r == 0) continue;
        if(l + r + 1 > ans || (l + r + 1 == ans && sym < l * r) ){
            ans = l + r + 1;
            sym = l * r;
            h = i;
        }
    }
    if(ans == 0) {
        cout << "No peak shape";
    }
    else {
        cout << ans << " " << h << " " << a[h];
    }
    return 0;
}