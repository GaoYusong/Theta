#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

//MAXN为点数，MAXM为边数
//点的下标从0开始至n - 1
//并且要保证正向边的下标为偶数，反向边的下标为奇数

const int MAXN = 210;
const int MAXM = 210 * 210;

int head[MAXN], next[MAXM];
struct EE {
    int u, v;
    int c;
};
EE ee[MAXM];
int flow[MAXM];
int tot;

int gap[MAXN], cur[MAXN], d[MAXN];
int pre[MAXN];
const int INF = 1 << 30;

void init()
{
    tot = 0;
    memset(head, -1, sizeof(head));
}

void addedge(int u, int v, int c)
{
    ee[tot].u = u;
    ee[tot].v = v;
    ee[tot].c = c;
    next[tot] = head[u];
    head[u] = tot;
    tot++;

    ee[tot].u = v;
    ee[tot].v = u;
    ee[tot].c = 0;
    next[tot] = head[v];
    head[v] = tot;
    tot++;
}

void rbfs(int s, int n)
{
    queue<int> q;
    q.push(s);
    gap[d[s]]--;
    d[s] = 0;
    gap[d[s]]++;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int e = head[u]; e != -1; e = next[e]) {
            int v = ee[e].v;
            if (d[v] == n && (e & 1)) {
                gap[d[v]]--;
                d[v] = d[u] + 1;
                gap[d[v]]++;
                q.push(v);
            }
        }
    }

}

int sap(int s, int t, int n)
{
    memset(flow, 0, sizeof(flow));
    for (int i = 0; i < n; i++) {
        cur[i] = head[i];
        d[i] = n;
        gap[i] = 0;
    }
    gap[n] = n;
    rbfs(t, n);
    int u = s;
    pre[u] = -1;
    int f = 0;
    while (d[s] < n) {
        int v;
        bool ok = false;
        for (int e = cur[u]; e != -1; e = next[e]) {
            v = ee[e].v;
            if (ee[e].c > flow[e] && d[u] == d[v] + 1) {
                pre[v] = e;
                cur[u] = e;
                u = v;
                ok = true;
                break;
            }
        }
        if (ok) {
            if (u == t) {
                int minv = INF;
                for (int p = u; p != s; p = ee[pre[p]].u) {
                    int e = pre[p];
                    if (minv > ee[e].c - flow[e]) {
                        minv = ee[e].c - flow[e];
                    }
                }
                for (int p = u; p != s; p = ee[pre[p]].u) {
                    int e = pre[p];
                    flow[e] += minv;
                    flow[e ^ 1] -= minv;
                }
                f += minv;
                u = s;
            }
        } else {
            gap[d[u]]--;
            if (gap[d[u]] == 0)
                break;
            d[u] = n;
            for (int e = head[u]; e != -1; e = next[e]) {
                v = ee[e].v;
                if (ee[e].c > flow[e] && d[u] > d[v] + 1) {
                    d[u] = d[v] + 1;
                    cur[u] = e;
                }
            }
            gap[d[u]]++;
            if (u != s) {
                u = ee[pre[u]].u;
            }
        }


    }
    return f;
}

int main()
{
    int n, m;

    //freopen("input.txt", "r", stdin);

    while (scanf("%d%d", &m, &n) == 2) {
        init();
        for (int i = 0; i < m; i++) {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            u--;
            v--;
            addedge(u, v, c);
        }

        /*for (int i = 0; i < n; i++) {
            for (int e = head[i]; e != -1; e = next[e]) {
                printf("i %d j %d c %d\n", ee[e].u, ee[e].v, ee[e].c);
            }
        }*/

        int s = 0;
        int t = n - 1;
        int ret = sap(s, t, n);
        printf("%d\n", ret);
    }
    return 0;
}
