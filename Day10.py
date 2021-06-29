#!/usr/bin/env python3

import sys

if __name__ == '__main__':
    adapters = list(sorted(map(int, sys.stdin.read().strip().split('\n'))))
    adapters = [0] + adapters
    valid_arrangements = [1] * len(adapters)
    for index in range(1, len(adapters)):
        valid_arrangements[index] = sum(
            valid_arrangements[src_index]
            for src_index in range(max(0, index - 3), index)
            if adapters[index] - adapters[src_index] <= 3
        )
    print(valid_arrangements[-1])
