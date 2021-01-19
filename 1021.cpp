#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

int G[105][105];
int n, m;
map<string, int> mp;
string s1[105], s2[105];
string name[105];
int val[105];

//建图过程
void init() {
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) {
        cin >> s1[i] >> s2[i];
    }
    for(int i = 1; i <= m; ++i) {
        string s; cin >> s;
        mp[s] = i;
        name[i] = s;
        cin >> val[i];
    }
    for(int i = 1; i <= m; ++i) {
        for(int j = 1; j <= m; ++j) G[i][j] = 1;
    }
    for(int i = 1; i <= n; ++i) {
        int x = mp[s1[i]], y = mp[s2[i]];
        G[x][y] = G[y][x] = 0;
    }
}

int tab[105], cur, cost;
int max_tab[105], max_tab_cur, lowest_cost;
int nums[105];


void dfs(int u) {
    tab[++ cur] = u;
    cost += val[u];
    for(int v = u + 1; v <= m; ++v) {
        if(cur + nums[v] < max_tab_cur) break; //剪枝1 :当前往后最大的加上 tab里的如果还要小，剪掉。
        if(cur + nums[v] == max_tab_cur && cost >= lowest_cost) break; //同理
        int flag = 1;
        for(int i = 1; i <= cur; ++i) {
            if(!G[v][tab[i]]) {
                flag = 0;
                break;
            }
        }
        if(flag) {
            dfs(v);
        }
    }
    if(cur > max_tab_cur || (cur == max_tab_cur && cost < lowest_cost)) {
        max_tab_cur = cur;
        lowest_cost = cost;
        for(int i = 1; i <= cur; ++i) {
            max_tab[i] = tab[i];
        }
    }
    cost -= val[u];
    cur --;
}


int main() {
    init();
    //从后往前遍历
    for(int i = m; i >= 1; --i) {
        dfs(i);
        nums[i] = max_tab_cur;
    }
    vector<string > ans;
    ans.clear();
    for(int i = 1; i <= max_tab_cur; ++i) {
        ans.push_back(name[max_tab[i]]);
    }
    sort(ans.begin(), ans.end());
    cout << max_tab_cur << endl;
    cout << ans[0];
    for(int i = 1; i < max_tab_cur; ++i) {
        cout << " " <<ans[i];
    }
    cout << endl;
    cout << lowest_cost << endl;
    return 0;
}