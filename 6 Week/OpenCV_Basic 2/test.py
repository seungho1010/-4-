def solution(e, starts):
    divisor=[0 for i in range(e+1)]
    for i in range(2,e+1):
        for j in range(1,min(e//i+1,i)):
            print(i*j)
            divisor[i*j]+=2
    print("")
    for i in range(1,int(e**(1/2))+1):
        print(i**2)
        divisor[i**2]+=1
    print(divisor)

print(solution(8, [1, 3, 7]))