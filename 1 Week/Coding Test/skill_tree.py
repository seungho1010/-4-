# 스킬트리

def solution(skill, skill_trees):
    answer = 0
    
    is_correct_skill_tree = [-1] * len(skill)
    for skill_tree in skill_trees:

        for i in range(len(skill)):
            if skill[i] in skill_tree:
                is_correct_skill_tree[i] = skill_tree.index(skill[i])
        
        if is_correct(is_correct_skill_tree) == True:
            answer += 1
        
        is_correct_skill_tree = [-1] * len(skill)
    return answer

def is_correct(is_correct_skill_tree):

    for i in range(len(is_correct_skill_tree) - 1):
        # 선행 스킬을 배우지 않고 나중 스킬을 배운 경우
        if is_correct_skill_tree[i] == -1:
            if is_correct_skill_tree[i+1] > -1:
                return False
        
        # 선행 스킬보다 빨리 배운 경우
        elif is_correct_skill_tree[i] >  is_correct_skill_tree[i+1]:
            if is_correct_skill_tree[i+1] == -1:
                continue
            else:
                return False

    return True
    

# Example
skill = "CBD"
skill_trees = ["BACDE", "CBADF", "AECB", "BDA"]
# "BACDE", "BDA" -> False
# "CBADF", "AECB" -> True
# return -> 2

print(solution(skill, skill_trees))
