# 올바른 괄호

def solution(s):
    answer = True
    
    bracket = 0
    for i in s:
        if i == "(":
            bracket += 1
        else:
            bracket -= 1
        
        if bracket < 0:
            answer = False
            break
    
    if bracket != 0:
        answer = False

    return answer


# Example
s = "(()("
print(solution(s))
