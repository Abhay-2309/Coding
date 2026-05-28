#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

void maximulset() {
    int nodes;
    cin >> nodes;
    
    vector<int> nums(nodes);
    for(int i = 0; i < nodes; i++) cin >> nums[i];
    vector<vector<int>> tree(nodes);
    for(int i = 0; i < nodes - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; 
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    auto f = [&](auto&& self, int currnode, int parentnode) -> pair<int,int> {
        int total_out_of_children = 0;
        int total_best_of_children = 0;
        
        for(int child : tree[currnode]){
            if(child == parentnode){
                continue; 
            }
            auto childscores = self(self, child, currnode); 
            int child_in = childscores.first;
            int child_out = childscores.second;
            
            total_out_of_children += child_out;
            total_best_of_children += max(child_in, child_out);
        }
        int current_in = nums[currnode] + total_out_of_children;
        int current_out = 0 + total_best_of_children;
        
        return {current_in, current_out};
    };
    auto ans = f(f, 0, -1);
    
    cout << max(ans.first, ans.second) << endl;
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    maximulset();
    
    return 0;
}
