# weights 중에 적절히 골라, m의 무게를 맞추는 경우의 수 구하기

answer = [0]
def solution(m, weights):
    # weights를 작은 순으로 정렬
    weights.sort()
    
    find_weight(m, weights)
    
    return answer[0]

# 재귀적으로 문제 해결
def find_weight(m, weights):
    if m == 0:
        answer[0] += 1
    elif len(weights) == 0:
        return
    elif weights[0] > m:
        return
    else:
        find_weight(m-weights[0], weights[1:])
        find_weight(m,weights[1:])


## Example
m = 3000
weights = [500, 1500, 2500, 1000, 2000]

print(solution(m, weights))
