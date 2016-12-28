#!/usr/bin/env python
"""
When this program is run, it outputs 1 Million random
permutations of 0..31 in the 'input.txt' file.
"""
import random

L = list(str(x) for x in range(32))
fp = open("input.txt", "w")#input.txt
for i in range(10**6):#10**6
    random.shuffle(L)
    fp.write(",".join(L)+"\n")
