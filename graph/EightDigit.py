import heapq
import copy

class PriorityQueue:
    def __init__(self):
        self.elements = []
    def empty(self):
        return len(self.elements) == 0
    def put(self, item, priority):
        heapq.heappush(self.elements, (priority, item))
    def get(self):
        return heapq.heappop(self.elements)[1]

direction = (1,3,-1,-3)

def check(node, i):
    spac = node.index(0)
    if (i==0 and spac%3==2) or (i==1 and spac>5) or (i==2 and spac%3==0) or (i==3 and spac<3):
        return False
    return True

def Extend(node, i):
    node = list(node)
    spac = node.index(0)
    tmp = spac + direction[i]
    node[spac] = node[tmp]
    node[tmp] = 0
    result = tuple(node)
    return result

def heuristic(a, b):
    ret = 0
    for i in range(0, 9):
        if a[i] != b[i]:
            ret += 1
    return ret

def AStarSearch(start, target):
    frontier = PriorityQueue()
    frontier.put(start, 0)
    came_from = {}
    cost_so_far = {}
    came_from[start] = None
    cost_so_far[start] = 0
    while not frontier.empty():
        current = frontier.get()
        if current == target:
            break
        for i in range(0, 4):
            if check(current, i):
                next = copy.copy(current)
                next = Extend(next, i)
                new_cost = cost_so_far[current] + 1
                if next not in cost_so_far or new_cost < cost_so_far[next]:
                    cost_so_far[next] = new_cost
                    priority = new_cost + heuristic(next, target)
                    frontier.put(next, priority)
                    came_from[next] = current

    return came_from, cost_so_far

def reconstruct_path(came_from, start, target):
    current = target
    path = [current]
    while current != start:
        current = came_from[current]
        path.append(current)
    path.reverse()
    return path


if __name__ == '__main__':
    start = (1,2,5,7,6,4,0,8,3)
    target = (7,1,5,8,2,4,6,0,3)
    came, cost = AStarSearch(start, target)
    searchpath = reconstruct_path(came, start, target)
    for p in searchpath:
       for i in range(0, 9):
           print '%d ' % p[i],
           if (i+1)%3 == 0:
               print '\n'
       print '**********'