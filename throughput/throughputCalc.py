import numpy as np
import matplotlib.pyplot as plt

T = 1000

def simulate_throughput(N, k, T=1000):
    requests = []
    for _ in range(N):
        chosen_slots = np.random.choice(T, k, replace=False)
        requests.extend(chosen_slots)
    requests = np.array(requests)
    
    unique, counts = np.unique(requests, return_counts=True)
    successful_requests = np.sum(counts == 1)
    return successful_requests

k_values = list(range(1, 11))
N_values = range(10, 300, 10)
plt.figure(figsize=(10,6))

for k in k_values:
    print(f"Processing throughput vs N for k={k}")
    throughputs = []
    for N in N_values:
        trials = [simulate_throughput(N, k, T) for _ in range(10)]
        avg_throughput = np.mean(trials)
        throughputs.append(avg_throughput)
    plt.plot(N_values, throughputs, label=f'k={k}')

plt.xlabel('Number of Nodes (N)')
plt.ylabel('Throughput (Number of Successful Requests)')
plt.title('Throughput vs Number of Nodes (for different k)')
plt.legend()
plt.grid(True)
plt.show()

N_values_fixed = [50, 100, 200]
k_values = list(range(1, 11))
plt.figure(figsize=(10,6))

for N in N_values_fixed:
    print(f"Processing throughput vs k for N={N}")
    throughputs = []
    for k in k_values:
        trials = [simulate_throughput(N, k, T) for _ in range(10)]
        avg_throughput = np.mean(trials)
        throughputs.append(avg_throughput)
    plt.plot(k_values, throughputs, label=f'N={N}')

plt.xlabel('Number of Slots Requested per Node (k)')
plt.ylabel('Throughput (Number of Successful Requests)')
plt.title('Throughput vs k (for different N)')
plt.legend()
plt.grid(True)
plt.show()
