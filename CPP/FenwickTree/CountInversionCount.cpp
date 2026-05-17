#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

class FenwickTree {
private:
    vector<int> tree;
    int n;
public:
    FenwickTree(int n) {
        this->n = n;
        tree.assign(n + 1, 0);
    }
    void update(int index, int val) {
        while (index <= n) {
            tree[index] += val;
            index += (index & -index);
        }
    }
    int query(int index) {
        int sum = 0;
        while (index > 0) {
            sum += tree[index];
            index -= (index & -index);
        }
        return sum;
    }
    int query(int left, int right) {
        if (left > right) return 0;
        return query(right) - query(left - 1);
    }
};

int CountInversion(const vector<int>& arr) {
    int n = arr.size();
    map<int, int> mp;
    for (int x : arr) {
        mp[x] = 0;
    }
    
    int rank = 1;
    for (auto& itr : mp) {
        itr.second = rank++;
    }
    
    int size = mp.size();
    FenwickTree Ftree(size);
    int inversioncount = 0;
    
    for (int i = 0; i < n; i++) {
        int index = mp[arr[i]];
        int previousdata = Ftree.query(index + 1, size);
        Ftree.update(index, 1);
        inversioncount += previousdata;
    }
    
    return inversioncount;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        cout << CountInversion(arr) << endl;
    }
    return 0;
}