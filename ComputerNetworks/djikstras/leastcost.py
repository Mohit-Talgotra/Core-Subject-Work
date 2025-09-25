import heapq

graph = {
    1: {2: 5, 3: float('inf'), 4: 10, 5: float('inf'), 6: 2, 7: 1},
    2: {1: 5, 3: 7, 4: 5, 5: 1, 6: 3, 7: float('inf')},
    3: {1: float('inf'), 2: 7, 4: 1, 5: 15, 6: 3, 7: 2},
    4: {1: 10, 2: 5, 3: 1, 5: 7, 6: 8, 7: 2},
    5: {1: float('inf'), 2: 1, 3: 15, 4: 7, 6: 3, 7: 1},
    6: {1: 2, 2: 3, 3: 3, 4: 8, 5: 3, 7: 4},
    7: {1: 1, 2: float('inf'), 3: 2, 4: 2, 5: 1, 6: 4}
}

def dijkstra(source, target):
    dist = {node: float('inf') for node in graph}
    dist[source] = 0
    prev = {node: None for node in graph}
    pq = [(0, source)]
    while pq:
        current_dist, current = heapq.heappop(pq)
        if current == target:
            break
        for neighbor, weight in graph[current].items():
            if weight == float('inf'):
                continue
            new_dist = current_dist + weight
            if new_dist < dist[neighbor]:
                dist[neighbor] = new_dist
                prev[neighbor] = current
                heapq.heappush(pq, (new_dist, neighbor))
    path = []
    node = target
    while node is not None:
        path.insert(0, node)
        node = prev[node]
    return dist[target], path

s = int(input("Enter start node (1-7): "))
t = int(input("Enter end node (1-7): "))
c, p = dijkstra(s, t)
print("Least cost:", c)
print("Path:", p)