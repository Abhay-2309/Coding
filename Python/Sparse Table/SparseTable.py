import sys
from math import log2
from typing import List
input = sys.stdin.readline
class SparseTable:
    def __init__(self, n: int):
        self.n = n
        k = int(log2(n)) + 1
        self.table = [[0] * n for _ in range(k + 1)]

    def build(self, arr: List[int]) -> None:
        n = len(arr)
        self.table[0] = arr[:]
        for j in range(1, int(log2(n)) + 1):
            i = 0
            while i + (1 << j) - 1 < n:
                self.table[j][i] = min(self.table[j - 1][i], self.table[j - 1][i + (1 << (j - 1))])
                i += 1

    def query(self, L: int, R: int) -> int:
        j = int(log2(R - L + 1))
        return min(self.table[j][L], self.table[j][R - (1 << j) + 1])
