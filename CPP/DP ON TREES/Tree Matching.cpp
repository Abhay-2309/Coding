// Approach 1: The Greedy Method (Bottom-Up DFS)
// This is the most intuitive and common approach. You start at the leaves (the bottom) of the tree and work your way up to the root.

// The Rule: If you are looking at a node and it is currently "unmatched" (not paired up), and its parent is also "unmatched", you pair them together.
// Why it works: In a tree, a leaf node has only one possible partner (its parent). If you don't match a leaf with its parent,
// that leaf is left isolated forever. Therefore, it is always optimal to aggressively pair nodes from the bottom up.code of this approhc?
#include <iostream>
#include <vector>

using namespace std;

// Maximum number of nodes based on typical constraints (e.g., CSES)
const int MAXN = 200005;
vector<int> graph[MAXN];
bool matched[MAXN]; // Keeps track of whether a node is already in a pair
int total_matches = 0;

void dfs(int curr_node, int parent_node) {
    // 1. Visit all children first (Post-order traversal / Bottom-up)
    for (int child : graph[curr_node]) {
        if (child == parent_node) continue;
        dfs(child, curr_node);
    }
    
    // 2. Greedy Choice: Apply the rule after returning from children
    // If we are not at the root (parent != 0), and neither the current node 
    // nor its parent are matched yet, we pair them up!
    if (parent_node != 0 && !matched[curr_node] && !matched[parent_node]) {
        matched[curr_node] = true;
        matched[parent_node] = true;
        total_matches++;
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // Read n-1 edges
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Initialize the matched array to false (0)
    // Global arrays are initialized to 0 by default in C++, but it is good practice to note.
    
    // Start DFS from node 1. We pass 0 as the parent since 1 has no parent.
    dfs(1, 0);

    // Print the maximum number of matches
    cout << total_matches << "\n";

    return 0;
}

// Approach 2: Tree Dynamic Programming (Tree DP)
// You can also solve this by defining states for each node and calculating the optimal choice recursively. For any node u, you maintain two values:

// DP[u][0] (Node u is NOT matched): This is the sum of the maximum matchings of all its children.
//   Since u isn't matched to any child, every child v is free to be matched or unmatched—we just take the maximum possible value for each subtree v.

// DP[u][1] (Node u IS matched): You choose exactly one child v to pair with u. For that specific child v, you must use its "not matched" state (DP[v][0]). 
//   For all other children, you take their maximum possible values. 
//   You test this for every child to find which pairing gives the maximum overall total.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
vector<int> graph[MAXN];

// dp[node][0] = max matching if 'node' is NOT matched with any of its children
// dp[node][1] = max matching if 'node' IS matched with exactly one of its children
int dp[MAXN][2];

void dfs(int u, int p) {
    // Base cases are implicitly 0 (global array initialization)
    dp[u][0] = 0;
    dp[u][1] = 0;

    // 1. Calculate DP for all children and build dp[u][0]
    for (int v : graph[u]) {
        if (v == p) continue;
        
        dfs(v, u);
        
        // If u is NOT matched, every child v is free to be matched or unmatched.
        // We greedily take the best possible outcome from the child's subtree.
        dp[u][0] += max(dp[v][0], dp[v][1]);
    }

    // 2. Build dp[u][1] by testing every child v as the chosen partner for u
    for (int v : graph[u]) {
        if (v == p) continue;
        
        // If u and v are paired:
        // - We gain 1 pair (+1).
        // - Child v cannot pair with its own children, so we MUST take dp[v][0].
        // - All other children (w != v) still contribute max(dp[w][0], dp[w][1]).
        
        // O(1) transition: Total sum (dp[u][0]) - old v contribution + new v contribution
        int match_with_v = dp[u][0] - max(dp[v][0], dp[v][1]) + dp[v][0] + 1;
        
        // Keep the maximum result among all possible child pairings
        dp[u][1] = max(dp[u][1], match_with_v);
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Start DP from root node 1, with parent 0
    dfs(1, 0);

    // The answer is the maximum possible matching at the root, 
    // whether the root itself ends up matched or unmatched.
    cout << max(dp[1][0], dp[1][1]) << "\n";

    return 0;
}
