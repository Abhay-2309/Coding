#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
class SparseTable{
private:
    vector<vector<int>>table;
    int n;
public:
    SparseTable(const int n){
        this->n = n;
        int k = log2(n) + 1;
        table.resize(k + 1, vector<int>(n, 0));
    }
    void build(const vector<int>&arr){
        int n = arr.size();
        table[0] = arr;
        for(int j = 1; j <= log2(n); j++){
            for(int i = 0; i + (1 << j) - 1 < n; i++){
                table[j][i] = min(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
    int query(int L, int R){
        int j = log2(R - L + 1);
        return min(table[j][L], table[j][R - (1 << j) + 1]);
    }
};