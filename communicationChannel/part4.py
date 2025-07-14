def correct_hamming(hamming_code):
    h = list(map(int, hamming_code))
    h.reverse()
    n = len(h)
    r = 0
    while (2 ** r) < n:
        r += 1

    error_pos = 0
    for i in range(r):
        idx = (2 ** i) - 1
        val = 0
        for j in range(idx, n, 2 ** (i + 1)):
            val ^= sum(h[j:j + 2 ** i])
        if val % 2 != 0:
            error_pos += 2 ** i

    if error_pos != 0:
        h[error_pos - 1] ^= 1

    corrected = []
    for i in range(len(h)):
        if (i + 1) & i:
            corrected.append(h[i])
    corrected.reverse()
    return ''.join(map(str, corrected)), error_pos != 0

with open("File3.txt", "r") as f:
    lines = f.readlines()
    original_message = lines[2].split(": ")[1].strip()
    message_received = lines[3].split(": ")[1].strip()

corrected_message, was_error = correct_hamming(message_received)
is_corrupted = 'Yes' if was_error else 'No'
is_match = 'Yes' if corrected_message == original_message[:25] else 'No'

with open("File4.txt", "w") as f:
    f.write(f"Message received: {message_received}\n")
    f.write(f"Is message corrupted: {is_corrupted}\n")
    f.write(f"Rectified Message: {corrected_message}\n")
    f.write(f"Original Message: {original_message}\n")
    f.write(f"Is there a match between rectified message and original message? {is_match}\n")
