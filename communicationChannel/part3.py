import random

def insert_parity_bits(data_bits):
    data = list(data_bits)
    data.reverse()
    h = []
    j = 0
    r = 0

    while (len(data) + r + 1) > (2 ** r):
        r += 1

    for i in range(r + len(data)):
        if (i + 1) == 2 ** j:
            h.append(0)
            j += 1
        else:
            h.append(int(data.pop(0)))

    for i in range(r):
        idx = (2 ** i) - 1
        val = 0
        for j in range(idx, len(h), 2 ** (i + 1)):
            val ^= sum(h[j:j + 2 ** i])
        h[idx] = val % 2

    h.reverse()
    return ''.join(map(str, h))

def flip_random_bit(data):
    index = random.randint(0, len(data) - 1)
    corrupted = list(data)
    corrupted[index] = '1' if corrupted[index] == '0' else '0'
    return ''.join(corrupted)

original_payload = ''.join(random.choice('01') for _ in range(25))
hamming_code = insert_parity_bits(original_payload)
message_sent = hamming_code

message_received = message_sent
if random.random() < len(message_sent) / 1000:
    message_received = flip_random_bit(message_sent)

with open("File3.txt", "w") as f:
    f.write(f"Original 25 bits payload: {original_payload}\n")
    f.write(f"Extra bit(s) for correcting errors: {message_sent[25:]}\n")
    f.write(f"Message sent: {message_sent}\n")
    f.write(f"Message received: {message_received}\n")
