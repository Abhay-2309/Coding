#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long

class SegmentTree {
private:
    int n;
    vector<int> tree;
    vector<int> lazy;

public:
    SegmentTree(const int n) {
        this->n = n;
        tree.assign((n << 2) + 1, 0);
        lazy.assign((n << 2) + 1, 0);
    }

    void build(int index, int low, int high, const vector<int>& arr) {
        if (low == high) {
            tree[index] = arr[low];
            return;
        }
        int mid = low + ((high - low) >> 1);
        build(index << 1, low, mid, arr);
        build((index << 1) + 1, mid + 1, high, arr);
        tree[index] = tree[index << 1] + tree[(index << 1) + 1];
    }

    void rangeupdate(int index, int low, int high, const int L, const int R, const int val) {
        if (lazy[index]) {
            tree[index] += (high - low + 1) * lazy[index];
            if (low != high) {
                lazy[(index << 1)] += lazy[index];
                lazy[(index << 1) + 1] += lazy[index];
            }
            lazy[index] = 0;
        }
        if (low > R || high < L || L > R) return;
        if (low >= L && high <= R) {
            tree[index] += (high - low + 1) * val;
            if (low != high) {
                lazy[(index << 1)] += val;
                lazy[(index << 1) + 1] += val;
            }
            return;
        }
        int mid = low + ((high - low) >> 1);
        rangeupdate(index << 1, low, mid, L, R, val);
        rangeupdate((index << 1) + 1, mid + 1, high, L, R, val);
        tree[index] = tree[index << 1] + tree[(index << 1) + 1];
    }

    int query(int index, int low, int high, const int L, const int R) {
        if (lazy[index]) {
            tree[index] += (high - low + 1) * lazy[index];
            if (low != high) {
                lazy[(index << 1)] += lazy[index];
                lazy[(index << 1) + 1] += lazy[index];
            }
            lazy[index] = 0;
        }

        if (high < L || low > R || L > R) return 0;
        
        if (low >= L && high <= R) return tree[index];
        
        int mid = low + ((high - low) >> 1);
        return query(index << 1, low, mid, L, R) + query((index << 1) + 1, mid + 1, high, L, R);
    }
};