int n, m, son[N], fa[N], siz[N], top[N], dfn[N], rnk[N], stamp, dep[N];
vector<int>adj[N];
void dfs1(int u, int p){
    son[u] = -1;
    siz[u] = 1;
    for (auto v : adj[u]){
        if (v != p){
            dep[v] = dep[u] + 1;
            fa[v] = u;
            dfs1(v, u);
            siz[u] += siz[v];
            if (son[u] == -1 || siz[v] > siz[son[u]]){
                son[u] = v;
            }
        }
    }
}

void dfs2(int u, int root){
    top[u] = root;
    dfn[u] = ++ stamp;
    rnk[stamp] = u;

    if (son[u] == -1){
        return;
    }
    dfs2(son[u], root);
    for (auto v : adj[u]){
        if (v != fa[u] && v != son[u]){
            dfs2(v, v);
        }
    }
}

int lca(int a,int b){
    while (top[a] != top[b]){
        if (dep[top[a]] < dep[top[b]]){
            swap(a, b);
        }
        a = fa[top[a]];
    }
    return dep[a] < dep[b] ? a : b;
}

vector<int>H[N];
vector<int>a;
void build(){
    int n = a.size();
    sort(a.begin(), a.end(), [&](int p1, int p2){return dfn[p1] < dfn[p2];});
    for (int i = 0;i < n - 1;i ++) a.push_back(lca(a[i], a[i + 1]));
    a.push_back(1);
    sort(a.begin(), a.end(), [&](int p1, int p2){return dfn[p1] < dfn[p2];});
    a.erase(unique(a.begin(), a.end()), a.end());
    n = a.size();
    for (int i = 0;i < n - 1;i ++)H[lca(a[i], a[i + 1])].push_back(a[i + 1]);
}