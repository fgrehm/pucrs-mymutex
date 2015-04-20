#!/usr/bin/env python

if __name__ == "__main__":
    lastnum = -1
    curnum = -1
    BOUND=299
    with open("out.txt") as f:
        while (True):
            line = f.readline()
            if line == '':
                break
            curnum = int(line)

            if lastnum == -1:
                lastnum = curnum
                continue

            if lastnum + 1 != curnum:
                print("FAIL")
                print(lastnum)
                print(curnum)
                break
            else:
                lastnum = curnum

            if lastnum == BOUND:
                lastnum = -1

