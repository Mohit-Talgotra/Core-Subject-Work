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

def binary_to_string(binary_str):
    byte_chunks = [binary_str[i:i + 8] for i in range(0, len(binary_str), 8)]    
    ascii_characters = [chr(int(bv, 2)) for bv in byte_chunks]
    return ''.join(ascii_characters)


with open("communicationChannel/message.txt", "r") as f:
    message_received = f.read().strip()

corrected_message, was_error = correct_hamming(message_received)

print(f"Receiver: Received Hamming Code: {message_received}")
print(f"Receiver: Corrected Message: {binary_to_string(corrected_message)}")
print(f"Receiver: Was there an error? {'Yes' if was_error else 'No'}")
