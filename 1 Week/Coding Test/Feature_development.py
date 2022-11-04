# 기능 개발
import math

def solution(progresses, speeds):
    answer = []
    end_date = [0] * (len(progresses) + 1)

    for i  in range(len(progresses)):
        end_date[i] = math.ceil((100 - progresses[i]) / speeds[i])
    
    point_ = 0
    max_date = 0; num = 0
    while point_ < len(end_date):
        if max_date >= end_date[point_]:
            if point_ == len(end_date)-1:
                answer.append(num)
            else:
                num += 1
        else:
            if point_ == 0:
                num += 1
                max_date = end_date[point_]
            else:
                answer.append(num)
                num = 1
                max_date = end_date[point_]
        point_ += 1
    return answer

# Example
# 1
progresses = [93, 30, 55]
speeds = [1, 30, 5]
# return = [2, 1]
print(solution(progresses, speeds))

# 2
progresses = [95, 90, 90, 99, 99, 80, 99]	
speeds = [1, 1, 1, 1, 1, 1, 1]
# return = [1, 3, 2]
print(solution(progresses, speeds))
