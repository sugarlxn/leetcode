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



if __name__ == "__main__":
    main()