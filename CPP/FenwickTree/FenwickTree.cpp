#include <bits/stdc++.h>
using namespace std;

/*
You should use a Fenwick Tree anytime your problem involves an associative and reversible operation (like addition, subtraction, or XOR) alongside frequent updates. Common use cases include:
1. Dynamic Prefix Sums / Range Queries: The most direct application. When an array is constantly being updated and you need the sum of subarrays efficiently.
2. Counting Inversions: Used extensively in algorithms to count the number of strict inversions in an array (how many pairs i, j exist such that i < j and A[i] > A[j]).
3. Frequency Arrays / Order Statistic Trees: If you compress coordinate values, a Fenwick Tree can keep track of how many times elements appear. You can then use binary lifting on the Fenwick Tree to find the $K$-th smallest element dynamically.
4. Data Stream Processing: Maintaining a running median, or answering questions like "How many numbers smaller than X have I seen so far in the stream?"
*/
class FenwickTree {
private:
    vector<int> tree;
    int n;
public:
    FenwickTree(const vector<int>& arr) {
        n = arr.size();
        tree.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            tree[i] += arr[i - 1];
            
            int parent = i + (i & -i);
            if (parent <= n) {
                tree[parent] += tree[i];
            }
        }
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
int main() {
    vector<int> arr = {1, 3, 4, 8, 6, 1, 4, 2};
    FenwickTree fenwick(arr);
    cout << "Range sum (1 to 5): " << fenwick.query(1, 5) << "\n";
    fenwick.update(3, 2);
    cout << "Range sum (1 to 5) after update: " << fenwick.query(1, 5) << "\n";
    return 0;
}