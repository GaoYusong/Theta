#include <cstdio>
#include <cstring>

usingnamespace std;

constint MAXN =10000*50+100; //模式串个数 * 长度
constint ABC =26; //字母表大小

int g[MAXN][ABC];
int fail[MAXN];
intout[MAXN];
int tot;
int q[MAXN], f, r;
int to[128]; //字母表映射

void init()
{
    tot =0;
    memset(g[0], 0, sizeof(g[0]));
    out[tot] =0;
}

void btrie(char*ss, int len)
{
    int x =0;
    int id;
    for (int i =0; i < len; i++) {
        id = to[ss[i]];
        if (!g[x][id]) {
            g[x][id] =++tot;
            memset(g[tot], 0, sizeof(g[tot]));
            out[tot] =0;
        }
        x = g[x][id];
    }
    out[x]++;
}

void AC()
{
    f = r =0;
    for (int i =0; i < ABC; i++) {
        if (g[0][i]) {
            q[r++] = g[0][i];
            fail[g[0][i]] =0;
        }
    }
    while (f < r) {
        int s = q[f++];
        for (int i =0; i < ABC; i++) {
            if (g[s][i]) {
                int u = g[s][i];
                q[r++] = u;
                fail[u] = g[fail[s]][i];
                //此处根据out[fail[u]],更新out[u]
            } else {
                g[s][i] = g[fail[s]][i];
            }
        }
    }
}

//根据需要匹配，返回答案
int search(char*ss, int len)
{
    int x =0;
    int ans =0;
    for (int i =0; i < len; i++) {
        x = g[x][to[ss[i]]];
        int tmp = x;
        while (tmp !=0&&out[tmp] !=-1) {
            ans +=out[tmp];
            out[tmp] =-1;
            tmp = fail[tmp];
        }
    }
    return ans;
}

int main()
{
    int cn, cns;
    char str[110];
    char ss[1000100];

    //freopen("input.txt", "r", stdin);

    for (int i =0; i < ABC; i++) {
        to[i +'a'] = i;
    }

    scanf("%d", &cns);
    for (cn =0; cn < cns; cn++) {
        int n;
        scanf("%d", &n);
        init();
        for (int i =0; i < n; i++) {
            scanf("%s", str);
            btrie(str, strlen(str));
        }
        AC();
        scanf("%s", ss);
        printf("%d\n", search(ss, strlen(ss)));
    }
    return0;
}
