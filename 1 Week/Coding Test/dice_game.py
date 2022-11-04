# 주사위 게임
from itertools import product

def solution(monster, S1, S2, S3):
    count_monster = 0
    total = 0

    dice_1 = [i for i in range(1, S1+1)]
    dice_2 = [i for i in range(1, S2+1)]
    dice_3 = [i for i in range(1, S3+1)]

    for j in product(dice_1, dice_2, dice_3):
        total += 1
        if sum(j) + 1 in monster:
            count_monster += 1
    
    answer = int((1 - (count_monster / total)) * 1000)

    return answer

# Example
# 1.
monster = [4, 9, 5, 8]
S1 = 2; S2 = 3; S3 = 4
# result = 500
print(solution(monster, S1, S2, S3))
