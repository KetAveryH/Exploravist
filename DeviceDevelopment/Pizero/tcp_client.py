import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

raspberry_pi_ip = 'IP_ADDRESS_OF_RASBERRY_PI'
port = 8000

client_socket.connect((raspberry_pi_ip, port))

# Send data to the server
message = "Hello, Raspberry Pi!"
client_socket.send(message.encode())

# Receive data from the server
data = client_socket.recv(1024).decode()
print(f"Received from server: {data}")

client_socket.close()