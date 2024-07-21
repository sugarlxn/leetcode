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
def mfu(mb,t,gb=64):
    print(f"mfu{mb,t,gb}",end=" ")
    f = 38.7
    n = 4
    return(function(gb,1024,12,512,50257)/(f*n*(t/1000)*(10**12)*2))

def samplepersecond(samples, time):
    return (samples/time)

def count(gb,t,samples):
    mfus = mfu(gb,t,gb)
    sameper = samplepersecond(samples,t/1000)
    return (mfus,sameper)

if __name__ == "__main__":
    # main()
    # print(mfu(64,0.704));print(samplepersecond(64,0.704))
    # print(mfu(32,0.731))
    # print(mfu(16,0.753))
    # print(mfu(8,1.116))
    # print(mfu(4,1.997))
    # print(mfu(2,3.745))
    # print(mfu(1,7.029))
    print("============114==================")
    print(count(2,214.08,200))
    print(count(4,228.8,400))
    print(count(8,325.3,800))
    print(count(16,452.8,1600))
    print(count(32,835.1,3200))
    print(count(64,1701.5,6400))
    print("============122==================")
    print(count(2,279.3,200))
    print(count(4,283.1,400))
    print(count(8,287.7,800))
    print(count(16,333.2,1600))
    print(count(32,454.8,3200))
    print(count(64,706.4,6400))
    print("============141==================")
    print(count(2,366.7,200))
    print(count(4,349.9,400))
    print(count(8,408.2,800))
    print(count(16,453.5,1600))
    print(count(32,595.3,3200))
    print(count(64,902.9,6400))
    print("============212==================")
    print(count(4,232.4,400))
    print(count(8,225.8,800))
    print(count(16,233.6,1600))
    print(count(32,277.9,3200))
    print(count(64,422.1,6400))
    print("============221==================")
    print(count(4,280.8,400))
    print(count(8,282.0,800))
    print(count(16,292.2,1600))
    print(count(32,360.1,3200))
    print(count(64,521.0,6400))
    print("============411==================")
    print(count(8,158.4,800))
    print(count(16,277.1,1600))
    print(count(32,262.5,3200))
    print(count(64,314.4,6400))
    print(count(128,467.9,12800))
