#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;
const int maxn = 2005;
const int inf = 0x3f3f3f3f;
int statement[maxn], Lie[maxn], n, m, l;
int ans[maxn];
int temp[maxn], iswolf[maxn], mp[maxn];
bool cmp(int x, int y) {
    return x > y;
}
void init() {
    cin >> n >> m >> l;
    for(int i = 1; i <= n; ++i) {
        iswolf[i] = Lie[i] = -1;
        char c;
        int p;
        cin >> c >> p;
        if(c == '+') statement[i] = p;
        else statement[i] = -p;
    }
}

void get_werewolf() {
    int cnt = 0;
    for(int i = 1; i <= n; ++i) {
        mp[i] = 0;
        if(Lie[i] == 1 && iswolf[i] == 1) cnt ++;
    }
    if(cnt >= m) return;
    int cur = 0, lie_wolf = 0;
    for(int i = n; i >= 1; --i) {
        if(iswolf[i] == 1){
            temp[++ cur] = i;
            mp[i] = 1;
            if(Lie[i] == 1) lie_wolf ++;
        }
    }
    for(int i = n; i >= 1; --i) {
        if(cur == m) break;
        if(iswolf[i] == -1){
            if(Lie[i] == 1) {
                if(lie_wolf < m - 1) {
                    temp[++ cur] = i;
                    mp[i] = 1;
                    lie_wolf ++;
                }
            }
            else {
                mp[i] = 1;
                temp[++cur] = i;
            }
        }
    }
    if(cur < m) return;
    sort(temp + 1, temp + 1 + m, cmp);
    if(lie_wolf == 0) {
        int flag = 0;
        for(int i = n; i >= 1; --i) {
            if(mp[i] == 0 && Lie[i] == 1 && iswolf[i] == -1) {
                for(int j = m; j >= 1; --j) {
                    if(iswolf[temp[j]] == -1) {
                        temp[j] = i;
                        flag = 1;
                        break;
                    }
                }
                break;
            }
        }
        if(flag == 0) return;
    }
    for(int i = 1; i <= m; ++i) {
        if(temp[i] < ans[i]) break;
        if(temp[i] > ans[i]) {
            for(int j = 1; j <= m; ++j) {
                ans[j] = temp[j];
            }
            break;
        }
    }
}

void dfs(int i, int cnt, int wolf) {
    if(wolf > m) return;
    if(n - i + 1 + cnt < l) return;
    if(i == n + 1) {
        if(cnt == l){
            get_werewolf();
        }
        return;
    }
    int x = statement[i];
    if(x > 0) {
        if(iswolf[x] == 1) {
            if(cnt == l) return;
            Lie[i] = 1;
            dfs(i + 1, cnt + 1, wolf);
            Lie[i] = -1;
        }
        else if(iswolf[x] == 0){
            Lie[i] = 0;
            dfs(i + 1, cnt, wolf);
            Lie[i] = -1;
        }
        else {
            iswolf[x] = 0;
            Lie[i] = 0;
            dfs(i + 1, cnt, wolf);
            Lie[i] = -1;
            iswolf[x] = -1;
            if(cnt < l) {
                iswolf[x] = 1;
                Lie[i] = 1;
                dfs(i + 1, cnt + 1, wolf + 1);
                Lie[i] = -1;
                iswolf[x] = -1;
            }
        }
    }
    else {
        x = -x;
        if(iswolf[x] == 1) {
            Lie[i] = 0;
            dfs(i + 1, cnt, wolf);
            Lie[i] = -1;
        }
        else if(iswolf[x] == 0) {
            if(cnt == l) return;
            Lie[i] = 1;
            dfs(i + 1, cnt + 1, wolf);
            Lie[i] = -1;
        }
        else {
            iswolf[x] = 1;
            Lie[i] = 0;
            dfs(i + 1, cnt, wolf + 1);
            Lie[i] = -1;
            iswolf[x] = -1;
            if(cnt < l) {
                iswolf[x] = 0;
                Lie[i] = 1;
                dfs(i + 1, cnt + 1, wolf);
                Lie[i] = -1;
                iswolf[x] = -1;
            }
        }

    }
}
void print() {
    if(ans[1] == 0){
        cout << "No Solution";
        return;
    }
    cout << ans[1];
    for(int i = 2; i <= m; ++i) {
        cout <<" " << ans[i];
    }
}

int main() {
    freopen("test.in", "r", stdin);
    init();
    dfs(1, 0, 0);
    print();
    return 0;
}