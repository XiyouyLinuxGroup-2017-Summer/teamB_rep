#!/usr/bin/env python
# coding=utf-8
import re

set = set()
while True:
    try:
        str = input()
    except:
        break
    for i in re.split(r'[^A-Za-z]+',str):
        if i:
            set.add(i.lower())
set = list(set)
set.sort()
for i in set:
    print(i)

