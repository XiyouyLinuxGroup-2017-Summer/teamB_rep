#coding=utf8

a = int(input())
while a:
    maxB = 98765 // a
    res = []
    for i in range(1234,maxB+1):

        sA = set(str(i*a))

        strB = str(i)
        if len(strB) == 4:
            strB = '0' + strB
        sB =set(strB)


        if len(sB) != 5 or len(sA) != 5:
            continue
        if sB&sA == set():
            res.append(strB)

    if not res:
        print('There are no solutions for %d.' % a)
    else:
        res.sort()
        for i in res:
            print('%d / %s = %d' % (int(i) * a, i, a))
    a = int(input())
    if a!= 0 :
        print('')