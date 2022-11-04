# 배상 비용 최소화

def solution(no, works):
    result = 0
    # 큰 작업부터 하나씩 빼면 됨.
    works.sort(reverse=True)

    for i in range(no):
        if works[0] == 0:
            break
        else:
            works[0] -= 1
            if works[0] < works[1]:
                works.sort(reverse=True)
    
    for i in works:
        result += i**2
    return result

# Example
# 1.
no = 4
works = [4, 3, 3]
# result =  2^2 + 2^2 + 2^2 = 12
print(solution(no, works))

# 2.
no = 2
works = [3, 3, 3]
# result =  2^2 + 2^2 + 3^2 = 17
print(solution(no, works))
