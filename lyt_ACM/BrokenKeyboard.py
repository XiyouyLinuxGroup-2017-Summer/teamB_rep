#!/usr/bin/env python3
# coding=utf-8
import re

pattern = re.compile(r'\[[^\[\]]*|\]')
while(True):
    try:
        a = input()
    except:
        break;
    start = pattern.findall(a)
    for i in start[::-1]:
        print(i[1:],end='')
    start = pattern.sub('',a)
    print(start)

