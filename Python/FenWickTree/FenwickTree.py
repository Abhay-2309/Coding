from typing import List
class FenwickTree:
    def __init__(self, arr: List[int]):
        """
        Initializes the Fenwick Tree in O(N) time.
        """
        self.n = len(arr)
        # 1-based indexing requires an array of size n + 1
        self.tree = [0] * (self.n + 1)
        
        # O(N) Construction workflow
        for i in range(1, self.n + 1):
            self.tree[i] += arr[i - 1]
            
            # Determine the parent node using the Least Significant Bit (LSB)
            parent = i + (i & -i)
            if parent <= self.n:
                self.tree[parent] += self.tree[i]

    def update(self, index: int, val: int) -> None:
        """
        Adds 'val' to the element at 'index' (1-based indexing) in O(log N) time.
        """
        while index <= self.n:
            self.tree[index] += val
            index += (index & -index)

    def query_prefix(self, index: int) -> int:
        """
        Computes the prefix sum from index 1 to 'index' in O(log N) time.
        """
        total_sum = 0
        while index > 0:
            total_sum += self.tree[index]
            index -= (index & -index)
        return total_sum

    def query_range(self, left: int, right: int) -> int:
        """
        Computes the range sum between 'left' and 'right' (inclusive).
        """
        if left > right:
            return 0
        return self.query_prefix(right) - self.query_prefix(left - 1)


if __name__ == "__main__":
    # Test array
    arr = [1, 3, 4, 8, 6, 1, 4, 2]
    
    # Instantiate the tree
    fenwick = FenwickTree(arr)
    
    # Initial range query
    print(f"Range sum (1 to 5): {fenwick.query_range(1, 5)}")
    
    # Point update: Add 2 to the element at index 3
    fenwick.update(3, 2)
    
    # Range query post-update
    print(f"Range sum (1 to 5) after update: {fenwick.query_range(1, 5)}")