//
// Created by Administrator on 2019/7/16.
//

template<class Ty_>
class BinayIndexedTree {
public:
    BinayIndexedTree(long long size = 0) :size(size) {
        BIT.resize(size + 1);
    }
    void add_point(long long p, Ty_ value) {
        while (p <= size) {
            BIT[p] += value;
            p += lowbit(p);
        }
    }
    Ty_ query_prefix(long long x) {
        x = min(x, size);
        Ty_ rtn = 0;
        while (x > 0) {
            rtn += BIT[x];
            x -= lowbit(x);
        }
        return rtn;
    }
    Ty_ query_seg(int l, int r) {
        if (l > r)return 0LL;
        return query_prefix(r) - query_prefix(l - 1);
    }
    static long long lowbit(long long x) {
        return x & (-x);
    }
private:
    long long size;
    vector<Ty_>BIT;
};
