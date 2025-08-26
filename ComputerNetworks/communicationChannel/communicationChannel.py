import random

def generateParityBit(payload):
    count = payload.count('1')
    return '0' if count % 2 == 0 else '1'

def flipRandomBit(data):
    index = random.randint(0, len(data) - 1)
    corrupted = list(data)
    corrupted[index] = '1' if corrupted[index] == '0' else '0'
    return ''.join(corrupted)

def checkParity(received_message):
    count = received_message.count('1')
    return count % 2 == 0

def insertParityBits(data_bits):
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

def correctHamming(hamming_code):
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

originalPayload = ''.join(random.choice('01') for _ in range(25))

parityBit = generateParityBit(originalPayload)
messageSent = originalPayload + parityBit

message_received = messageSent
message_received = flipRandomBit(messageSent)

with open("communicationChannel/File1.txt", "w") as f:
    f.write(f"Original bits: {originalPayload}\n")
    f.write(f"Extra bit(s) for detecting errors: {len(messageSent) - len(originalPayload)}\n")
    f.write(f"Message sent: {messageSent}\n")
    f.write(f"Message received: {message_received}\n")

isValid = checkParity(message_received)

with open("communicationChannel/File2.txt", "w") as f:
    f.write(f"Message received: {message_received}\n")
    f.write(f"Is message corrupted: {'No' if isValid else 'Yes'}\n")

hammingCode = insertParityBits(originalPayload)
messageSent = hammingCode

messageReceived = flipRandomBit(messageSent)

with open("communicationChannel/File3.txt", "w") as f:
    f.write(f"Original bits: {originalPayload}\n")
    f.write(f"Extra bit(s) for correcting errors: {messageSent[len(originalPayload):]}\n")
    f.write(f"Message sent: {messageSent}\n")
    f.write(f"Message received: {messageReceived}\n")

correctedMessage, wasError = correctHamming(messageReceived)

isCorrupted = 'Yes' if wasError else 'No'
isMatch = 'Yes' if correctedMessage == originalPayload else 'No'

with open("communicationChannel/File4.txt", "w") as f:
    f.write(f"Message received: {message_received}\n")
    f.write(f"Is message corrupted: {isCorrupted}\n")
    f.write(f"Rectified Message: {correctedMessage}\n")
    f.write(f"Original Message: {originalPayload}\n")
    f.write(f"Is there a match between rectified message and original message? {isMatch}\n")