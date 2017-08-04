#!/usr/bin/env python
# coding=utf-8
a = input()
a = int(a)
for i in range(a):
    input()
    c = input()
    l = len(c)
    for j in range(1,l+1):
        if (l % j != 0):
            continue;
        else:
            z = l // j
            if(c[0:j]*z == c):
                print(j)
                break
    if(i != a - 1):
        print('')
