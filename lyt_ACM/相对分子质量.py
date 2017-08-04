#!/usr/bin/env python
# coding=utf-8
import re
dirt = {
    'C':12.01,
    'H':1.008,
    'O':16.00,
    'N':14.01,
}
r = re.compile(r'[CHON]\d*')
for i in range(int(input())):
    s = input()
    num = {
        'C':0,
        'H':0,
        'O':0,
        'N':0,
    }
    for j in r.findall(s):
        if  j[1:]:
            num[j[0]] += int(j[1:])
        else:
            num[j[0]] += 1
    vv = 0
    for j in 'CHON':
        vv += num[j] * dirt[j]
    print('%.3f' % vv)



