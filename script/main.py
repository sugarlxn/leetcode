#!/bin/python3
import sys
import os


def test(num: float, flag : bool=True) -> float:
    print(f"nu= {num}")
    return num


def main():
    print("Hello World!")
    test(10)
    res = [1,10,2,3,4,11,5,7,12,8,9]
    print(sorted(res))
    res.sort()
    for i, num in enumerate(res):
        print(f"i={i}, num={num}")
    for j in range(len(res)):
        print(f"j={j}, num={res[j]}")

    # int 类 最大值 存储在 max 变量中
    max = sys.maxsize
    print(f"int max={max}") 
    # 以十六进制显示
    print(f"int max={hex(max)}")
    # max 的size大小
    print(f"int size={sys.getsizeof(max)}")
    temp = 0
    print(temp if temp  else "temp is 0")



def function(gb,s,l,h,v) -> float:
    return 96*gb*s*l*h*h*(1 + s/(6*h) + v/(16*l*h))

###计算MFU
def mfu(mb,t,gb):
    print(f"mfu{mb,t,gb}",end=" ")
    f = 38.7
    n = 8
    return(function(gb,1024,48,1608,50257)/(f*n*(t/1000)*(10**12)*2))

def samplepersecond(samples, time):
    return (samples/time)

###计算MFU和每秒采样数
###gb: global batch size
###t: time
###samples: number of samples
def count(gb,t,samples):
    mfus = mfu(gb,t,gb)
    sameper = samplepersecond(samples,t/1000)
    return (mfus,sameper)

if __name__ == "__main__":
    # main()
    print("====================================")
    print(count(24,2213.5,2400))
    print(count(16,1911.7,1600))
    print("====================================")
    print(count(18,6403.2,1800))
    print(count(16,5627.5,1600))
    print(count(24,8621.4,2400))
    print(count(24,3687.5,2400))
    print(count(24,5375.5,2400))
    print(count(24,2362.1,2400))
    print(count(24,2720.1,2400))
    print(count(24,4698.4,2400))






    




