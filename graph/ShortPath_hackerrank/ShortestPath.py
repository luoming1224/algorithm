__author__ = 'luoming'
import heapq

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

adj = {}
text = ''

class PriorityQueue:
    def __init__(self):
        self.elements = []
    def empty(self):
        return len(self.elements) == 0
    def put(self, item, priority):
        heapq.heappush(self.elements, (priority, item))
    def get(self):
        return heapq.heappop(self.elements)[1]

def Dijkstra(start, target):
    frontier = PriorityQueue()
    frontier.put(start, 0)
    cost_so_far = {}
    tagstr = {}
    cost_so_far[start] = 0
    tagstr[start] = ''

    while not frontier.empty():
        current = frontier.get()
        if current == target:
            break

        for adjust in adj[current]:
            next = adjust[0]
            c = adjust[2]
            nextTag = tagstr[current] + c

            count = sunday(text, nextTag)
            if count == 0:
                continue

            value = int(adjust[1]) * count
            new_cost = cost_so_far[current] + value

            if next not in cost_so_far or new_cost < cost_so_far[next]:
                cost_so_far[next] = new_cost
                tagstr[next] = nextTag
                frontier.put(next, new_cost)

    print cost_so_far[target]



if __name__ == '__main__':
    s = raw_input()
    n,m = s.split(' ')
    for i in range(1, int(n)+1):
        adj[str(i)] = []
    for i in range(0, int(m)):
        t = raw_input()
        x,y,z,tag = t.split(' ')
        adj[x].append((y,z,tag))
        adj[y].append((x,z,tag))
    text = raw_input()

    Dijkstra(str(1), n)