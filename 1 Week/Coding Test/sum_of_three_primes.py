# 세 소수의 합

import math
from itertools import combinations

def solution(n):
    result = 0
    is_prime = [False, False] + [True]*(n-1)

    for i in range(2, math.ceil(n**0.5)):
        for j in range(i*2, n+1, i):
            is_prime[j] = False

    primes = []
    for i in range(2, n):
        if is_prime[i] == True:
            primes.append(i)

    comb = combinations(primes, 3)

    for c in comb:
        if sum(c) == n:
            result+= 1

    return result


# Example
# 1.
n = 33
# result = 4 -> (3+7+23), (3+11+19), (3+13+17), (5+11+17)
print(solution(n))
