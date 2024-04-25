n = int(input())
a = [[0 for i in range(n)] for i in range(n)]
dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]
def inbound(x, y):
    if (0 <= x < n and 0 <= y < n and a[x][y] == 0):
        return True
    else:
        return False
def process(x, y, dir, stp):
    a[x][y] = stp
    if (inbound(x + dx[dir], y + dy[dir])):
        process(x + dx[dir], y + dy[dir], dir, stp + 1)
    else:
        dir = (dir + 1) % 4
        if (inbound(x + dx[dir], y + dy[dir])):
            process(x + dx[dir], y + dy[dir], dir, stp + 1)
process(0, 0, 0, 1)
for i in range(n):
    for j in range(n):
        print("%d\t" % a[i][j], end = " \n"[j == n - 1])   
