#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"

vector<int> ans;

int f(vector<vector<int>>& graph, int curr_node, int parent_node){
    int total = 0;
    for(auto child : graph[curr_node]){
        if(child == parent_node) continue;  
        total += f(graph, child, curr_node);
    }
    // Store only the subordinates, but return the whole subtree size (subordinates + 1)
    ans[curr_node] = total; 
    return 1 + total;
}

void solve(vector<vector<int>>& graph, int nodes){
    ans.assign(nodes, 0);
    f(graph, 0, -1); 
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;                                   
    
    // Read n - 1 elements
    vector<int> arr(n - 1);
    for(int i = 0; i < n - 1; i++) cin >> arr[i];

    // Standard way to declare an adjacency list of size n
    vector<vector<int>> graph(n);
    
    // Loop only up to n - 1
    for(int i = 0; i < n - 1; i++){
        int u = i + 1;         // Employee index (2 to n in 1-based is 1 to n-1 in 0-based)
        int v = arr[i] - 1;    // Boss index (convert 1-based to 0-based)
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);           
    }

    solve(graph, n);   
    
    for(const auto& itr: ans) cout << itr << " ";
    cout << endl;
    
    return 0;
}
