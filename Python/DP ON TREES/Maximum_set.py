import sys

# Increase recursion depth for deep trees (default is usually 1000)
sys.setrecursionlimit(300000)

def maximulset():
    # Fast I/O: Read all inputs at once and split by whitespace
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    nodes = int(input_data[0])
    
    # Read node weights
    nums = [int(x) for x in input_data[1:nodes+1]]
    
    # Adjacency list for the tree
    tree = [[] for _ in range(nodes)]
    
    # Read edges (N-1 edges)
    idx = nodes + 1
    for _ in range(nodes - 1):
        u = int(input_data[idx]) - 1
        v = int(input_data[idx+1]) - 1
        tree[u].append(v)
        tree[v].append(u)
        idx += 2
        
    def dfs(currnode, parentnode):
        total_out_of_children = 0
        total_best_of_children = 0
        
        for child in tree[currnode]:
            if child == parentnode:
                continue
            
            child_in, child_out = dfs(child, currnode)
            
            total_out_of_children += child_out
            total_best_of_children += max(child_in, child_out)
            
        current_in = nums[currnode] + total_out_of_children
        current_out = total_best_of_children
        
        return current_in, current_out

    # Start DFS from node 0, with -1 as its parent
    ans_in, ans_out = dfs(0, -1)
    
    # Print the max of including or excluding the root
    print(max(ans_in, ans_out))

if __name__ == '__main__':
    maximulset()