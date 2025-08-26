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

def string_to_binary(input_string):
    return ''.join(format(ord(char), '08b') for char in input_string)

original_payload = string_to_binary(input("Enter a message: "))
hamming_code = insert_parity_bits(original_payload)

with open("communicationChannel/message.txt", "w") as f:
    f.write(hamming_code)

print("Sender: Message sent and written to file.")