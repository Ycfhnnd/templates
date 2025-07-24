int n, q, son[N], fa[N], siz[N], top[N], dfn[N], rnk[N], stamp, w[N], dep[N];
vector<int>adj[N];
void dfs1(int u){
    son[u] = -1;
    siz[u] = 1;
    for (auto v : adj[u]){
        if (dep[v] > dep[u] + 1){
            dep[v] = dep[u] + 1;
            fa[v] = u;
            dfs1(v);
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
int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] > dep[top[v]]) {
            u = fa[top[u]];
        } else {
            v = fa[top[v]];
        }
    }
    return dep[u] < dep[v] ? u : v;
}
struct Info{
    i64 a, b;
    Info() = default;
    Info(int x) {
        a = x == 1;
        b = x;
    }
};

Info operator +(Info a, Info b){
    Info c;
    c.a = a.a + b.a;
    c.b = a.b + b.b;
    return c;
}

struct Node{
    int l, r;
    Info info;
}tr[N << 2];
 
void build(int u,int l,int r){
    tr[u] = {l, r};
    if (l == r){
        tr[u].info = Info(w[rnk[l]]);
        return;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    tr[u].info = tr[u << 1].info + tr[u << 1 | 1].info;
}
 
//x是dfn[x]
void modify(int u,int x){
    if (tr[u].l == tr[u].r){
        tr[u].info = Info(w[rnk[x]]);
        return;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    if (x <= mid) modify(u << 1, x);
    else modify(u << 1 | 1, x);
    tr[u].info = tr[u << 1].info + tr[u << 1 | 1].info;  
}
 
Info query(int u,int l,int r){
    if (tr[u].l >= l and tr[u].r <= r){
        return tr[u].info;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    if (r <= mid) return query(u << 1, l, r);
    if (l > mid) return query(u << 1 | 1, l, r);
    return query(u << 1, l, r) + query(u << 1 | 1, l, r);
}

Info querySum(int a, int b) {
    Info ans;
    ans.a = ans.b = 0;
    while (top[a] != top[b]){
        if (dep[top[a]] < dep[top[b]]){
            swap(a, b);
        }
        ans = ans + query(1, dfn[top[a]], dfn[a]);
        a = fa[top[a]];
    }
    if (dep[a] > dep[b]){
        swap(a, b);
    }
    ans = ans + query(1, dfn[a], dfn[b]);
    return ans;
}

int main(){
    memset (dep, 0x3f, sizeof dep);
    dep[0] = 0, dep[1] = 1;
    dfs1(1);
    dfs2(1, 1);
    build(1, 1, n);

    //modify(1, dfn[x]);
}