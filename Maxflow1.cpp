const int N = 5010, M = 10010, INF = 0x3f3f3f3f;
int n, m, s, t;
int h[N], e[M], f[M], ne[M], idx;
int d[N], cur[N];

void add(int u,int v,int c, int d = 0){
    e[idx] = v, ne[idx] = h[u], f[idx] = c, h[u] = idx ++;
    e[idx] = u, ne[idx] = h[v], f[idx] = d, h[v] = idx ++;
}

bool bfs(){
    queue<int>q;
    memset(d, -1, sizeof d);
    q.push(s);
    d[s] = 0;
    cur[s] = h[s];
    while (!q.empty()){
        auto u = q.front();
        q.pop();
        for (int i = h[u]; ~i; i = ne[i]){
            int v = e[i];
            if (d[v] == -1 and f[i]){
                d[v] = d[u] + 1;
                cur[v] = h[v];
                if (v == t) return true;
                q.push(v);
            }
        }
    }
    return false;
}

int dfs(int u, int limit) {
    if (u == t) return limit;
    int flow = 0;
    for (int i = cur[u]; ~i && flow < limit; i = ne[i]) {
        cur[u] = i;
        int j = e[i];
        if (d[j] == d[u] + 1 && f[i]) {
            int t = dfs(j, min(f[i], limit - flow));
            if (!t) d[j] = -1;
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}

int dinic() {
    int r = 0, flow;
    while (bfs()) while (flow = dfs(s, INF)) r += flow;
    return r;
}