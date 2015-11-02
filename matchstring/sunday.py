__author__ = 'luoming'

#import string

def sunday(s, p):
    slen = len(s)
    plen = len(p)

    count = 0

    next = [0] * 256
    for i in range(0, 256):
        next[i] = plen+1

    for j in range(0, plen):
        next[ord(p[j])] = plen - j

    pos = 0
    flag = False
    while pos < (slen - plen + 1):
        k = 0
        while k < plen:
            if p[k] != s[pos+k]:
                if pos + plen >= slen:
                    flag = True
                    break
                pos = pos + next[ord(s[pos+plen])]
                break
            k = k + 1

        if k == plen:
            count += 1
            if pos + plen >= slen:
                flag = True
                break
            pos = pos + next[ord(s[pos+plen])]

        if flag:
            break

    return count

if __name__ == '__main__':
    s = 'aabb'
    p = 'a'
    n = sunday(s,p)
    print n
