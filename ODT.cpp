struct node{
    i64 l, r;//区间左、右端点
    mutable int val;//权值
    bool operator < (const node &t) const{
        return l < t.l;
    }
};
set<node>s;
auto split(i64 pos){
    auto it = s.lower_bound(node({pos}));
    if(it != s.end() && it -> l == pos)
        return it;//只有不能空才能判断
    --it;
    i64 l = it -> l,r = it -> r,v = it -> val;
    s.erase(it);
    s.insert(node({l, pos - 1, v}));
    return s.insert(node({pos, r, v})).first;
}
void assign(i64 l,i64 r,i64 val){
    auto itr = split(r + 1),itl = split(l);
    s.erase(itl, itr);
    s.insert(node({l, r, val}));
}
void rever(i64 l,i64 r){
    auto itr = split(r + 1),itl = split(l);
    for(auto it = itl;it != itr;++ it)
        it->val=!it->val;
}
void add(i64 l,i64 r,i64 v){
    auto itr = split(r + 1),itl = split(l);
    for(auto it = itl;it != itr;++ it)
        it->val += v;
}