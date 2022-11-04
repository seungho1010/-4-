# 문자열 압축

def solution(s):
    result = []

    if len(s) == 1:
        return 1

    for i in range(1, len(s)+1):
        compressed = ''
        cut_num = 1
        temp = s[:i]

        for j in range(i, len(s)+i, i):
            if temp == s[j:i+j]:
                cut_num += 1
            else:
                if cut_num != 1:
                    compressed = compressed + str(cut_num) + temp
                else:
                    compressed = compressed + temp
                    
                temp = s[j:j+i]
                cut_num = 1
      
        result.append(len(compressed))
        
    return min(result)

# Example
# 1. 
s = "aabbaccc"
# result = 7
# print(solution(s))

# 2.
s =  "ababcdcdababcdcd"
# result = 9
# print(solution(s))


# 3. 
s =  "abcabcdede"
# result = 8
print(solution(s))


# 4. 
s =  "abcabcabcabcdededededede"
# result = 14
# print(solution(s))


# 5. 
s =  "xababcdcdababcdcd"
# result = 17
# print(solution(s))
