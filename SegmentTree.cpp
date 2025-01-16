struct Info{

};

Info operator +(Info a, Info b){
    
}

struct Node{
    int l, r;
    Info info;
}tr[N << 2];
 
void build(int u,int l,int r){
    tr[u] = {l, r};
    if (l == r){
        tr[u].info = Info(a[l]);
        return;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    tr[u].info = tr[u << 1].info + tr[u << 1 | 1].info;
}
 
void modify(int u,int x){
    if (tr[u].l == tr[u].r){
        tr[u].info = Info(a[x]);
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