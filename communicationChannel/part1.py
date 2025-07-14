import random

def generate_parity_bit(payload):
    count = payload.count('1')
    return '0' if count % 2 == 0 else '1'

def flip_random_bit(data):
    index = random.randint(0, len(data) - 1)
    corrupted = list(data)
    corrupted[index] = '1' if corrupted[index] == '0' else '0'
    return ''.join(corrupted)

original_payload = ''.join(random.choice('01') for _ in range(25))
parity_bit = generate_parity_bit(original_payload)
message_sent = original_payload + parity_bit

message_received = message_sent
if random.random() < len(message_sent) / 1000:
    message_received = flip_random_bit(message_sent)

with open("File1.txt", "w") as f:
    f.write(f"Original 25 bits payload: {original_payload}\n")
    f.write(f"Extra bit(s) for detecting errors: {parity_bit}\n")
    f.write(f"Message sent: {message_sent}\n")
    f.write(f"Message received: {message_received}\n")
