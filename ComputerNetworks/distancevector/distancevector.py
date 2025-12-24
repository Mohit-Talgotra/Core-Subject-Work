import numpy as np

def distance_vector_routing(cost):
    n = len(cost)
    dist = np.array(cost, dtype=float)
    
    next_hop = np.full((n, n), -1, dtype=int)
    for i in range(n):
        for j in range(n):
            if i != j and dist[i][j] != float('inf'):
                next_hop[i][j] = j
    
    updated = True
    iteration = 0
    while updated:
        updated = False
        iteration += 1
        for i in range(n):
            for j in range(n):
                if i != j:
                    for k in range(n):
                        if dist[i][k] != float('inf') and dist[k][j] != float('inf'):
                            new_dist = dist[i][k] + dist[k][j]
                            if new_dist < dist[i][j]:
                                dist[i][j] = new_dist
                                next_hop[i][j] = next_hop[i][k]
                                updated = True
    
    print(f"Algorithm converged in {iteration} iterations\n")
    return dist, next_hop

def print_distance_vector(node_num, dist, next_hop, n):
    print(f"\n{'='*60}")
    print(f"DISTANCE VECTOR FOR NODE N{node_num}")
    print(f"{'='*60}")
    print(f"{'Destination':<15} {'Distance':<15} {'Next Hop':<15}")
    print(f"{'-'*60}")
    
    for j in range(n):
        dest = f"N{j+1}"
        if node_num-1 == j:
            distance = "0"
            hop = "-"
        elif dist[node_num-1][j] == float('inf'):
            distance = "∞ (unreachable)"
            hop = "-"
        else:
            distance = str(int(dist[node_num-1][j]))
            hop = f"N{next_hop[node_num-1][j]+1}"
        
        print(f"{dest:<15} {distance:<15} {hop:<15}")

def print_all_distance_vectors(dist, next_hop, n):
    print("\n" + "="*60)
    print("DISTANCE VECTORS FOR ALL NODES")
    print("="*60)
    
    for i in range(n):
        print_distance_vector(i+1, dist, next_hop, n)

def print_matrices(dist, next_hop, n):
    print("\n" + "="*60)
    print("COMPLETE DISTANCE MATRIX (Shortest Paths)")
    print("="*60)
    print("        ", end="")
    for j in range(n):
        print(f"N{j+1}".rjust(5), end=" ")
    print()
    print("     " + "-"*42)
    
    for i in range(n):
        print(f"N{i+1} | ", end="")
        for j in range(n):
            if dist[i][j] == float('inf'):
                print("  ∞ ".rjust(5), end=" ")
            else:
                print(f"{int(dist[i][j])}".rjust(5), end=" ")
        print()
    
    print("\n" + "="*60)
    print("COMPLETE NEXT HOP MATRIX")
    print("="*60)
    print("        ", end="")
    for j in range(n):
        print(f"N{j+1}".rjust(5), end=" ")
    print()
    print("     " + "-"*42)
    
    for i in range(n):
        print(f"N{i+1} | ", end="")
        for j in range(n):
            if next_hop[i][j] == -1:
                print("  - ".rjust(5), end=" ")
            else:
                print(f"N{next_hop[i][j]+1}".rjust(5), end=" ")
        print()

def get_path(src, dest, next_hop):
    if next_hop[src][dest] == -1:
        return None
    
    path = [src]
    current = src
    while current != dest:
        current = next_hop[current][dest]
        path.append(current)
    return path

inf = float('inf')
cost = [
    [0,   5,   inf, 10,  inf, 2,   1  ],
    [5,   0,   7,   5,   1,   3,   inf],
    [inf, 7,   0,   1,   15,  3,   2  ],
    [10,  5,   1,   0,   7,   8,   2  ],
    [inf, 1,   15,  7,   0,   3,   1  ],
    [2,   3,   3,   8,   3,   0,   4  ],
    [1,   inf, 2,   2,   1,   4,   0  ]
]

print("="*60)
print("DISTANCE VECTOR ROUTING ALGORITHM")
print("Communication System with 7 Nodes (N1-N7)")
print("="*60)

n = len(cost)
dist, next_hop = distance_vector_routing(cost)
print_all_distance_vectors(dist, next_hop, n)
print_matrices(dist, next_hop, n)