struct Line{
    ll k, b;
    Line(ll k, ll b) : k(k), b(b) {}
    Line() : k(0), b(1e9) {}

    ll operator()(ll x){
        return k * x + b;
    }
};

const int N = 1e6 + 10;

struct LiChao{
    Line t[4 * N];
    void insertLine(int v, int tl, int tr, Line newLine){
        int tm = (tl + tr) / 2;
        bool dominateMid = (newLine(tm) < t[v](tm));
        bool dominateLeft = (newLine(tl) < t[v](tl));
        if(dominateMid)
            swap(newLine, t[v]);
        if(tl == tr)
            return;
        if(dominateLeft == dominateMid)
            insertLine(v * 2 + 1, tm + 1, tr, newLine);
        else
            insertLine(v * 2, tl, tm, newLine);
    }
    void insertLine(ll k, ll b){
        insertLine(1, 1, N, Line(k, b));
    }
    ll getmin(int v, int tl, int tr, int pos){
        ll ans = t[v](pos);
        if(tl != tr){
            int tm = (tl + tr) / 2;
            if(pos <= tm)
                ans = min(ans, getmin(v * 2, tl, tm, pos));
            else
                ans = min(ans, getmin(v * 2 + 1, tm + 1, tr, pos));
        }
        return ans;
    }
    ll getmin(int pos){
        return getmin(1, 1, N, pos);
    }
};
