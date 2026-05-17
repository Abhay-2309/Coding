import sys
from typing import List
input = sys.stdin.readline

class SegmentTree:
    def __init__(self, n: int):
        self.n = n
        self.tree = [0] * ((n << 2) + 1)
        self.lazy = [0] * ((n << 2) + 1)

    def build(self, index: int, low: int, high: int, arr: List[int]) -> None:
        if low == high:
            self.tree[index] = arr[low]
            return
        mid = low + ((high - low) >> 1)
        self.build(index << 1, low, mid, arr)
        self.build((index << 1) + 1, mid + 1, high, arr)
        self.tree[index] = self.tree[index << 1] + self.tree[(index << 1) + 1]

    def range_update(self, index: int, low: int, high: int, L: int, R: int, val: int) -> None:
        if self.lazy[index]:
            self.tree[index] += (high - low + 1) * self.lazy[index]
            if low != high:
                self.lazy[index << 1] += self.lazy[index]
                self.lazy[(index << 1) + 1] += self.lazy[index]
            self.lazy[index] = 0

        if low > R or high < L or L > R:
            return

        if low >= L and high <= R:
            self.tree[index] += (high - low + 1) * val
            if low != high:
                self.lazy[index << 1] += val
                self.lazy[(index << 1) + 1] += val
            return

        mid = low + ((high - low) >> 1)
        self.range_update(index << 1, low, mid, L, R, val)
        self.range_update((index << 1) + 1, mid + 1, high, L, R, val)
        self.tree[index] = self.tree[index << 1] + self.tree[(index << 1) + 1]

    def query(self, index: int, low: int, high: int, L: int, R: int) -> int:
        if self.lazy[index]:
            self.tree[index] += (high - low + 1) * self.lazy[index]
            if low != high:
                self.lazy[index << 1] += self.lazy[index]
                self.lazy[(index << 1) + 1] += self.lazy[index]
            self.lazy[index] = 0

        if high < L or low > R or L > R:
            return 0

        if low >= L and high <= R:
            return self.tree[index]

        mid = low + ((high - low) >> 1)
        return self.query(index << 1, low, mid, L, R) + self.query((index << 1) + 1, mid + 1, high, L, R)
