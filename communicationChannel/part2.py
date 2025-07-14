def check_parity(received_message):
    count = received_message.count('1')
    return count % 2 == 0

with open("File1.txt", "r") as f:
    lines = f.readlines()
    message_received = lines[3].split(": ")[1].strip()

is_valid = check_parity(message_received)

with open("File2.txt", "w") as f:
    f.write(f"Message received: {message_received}\n")
    f.write(f"Is message corrupted: {'No' if is_valid else 'Yes'}\n")
