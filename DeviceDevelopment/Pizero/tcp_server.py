import socket

# Server Setup:
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('0.0.0.0', 8000))
server_socket.listen(1)

print("Server is listening on port 8000...")

while True:
    connection, address = server_socket.accept()
    print(f"Connected to {address}!")
    
    # Receive data from the client (1024 bytes)
    data = connection.recv(1024).decode() 
    if not data:
        break
    
    print(f"Received data: {data}")
    
    # Send response back to the client
    connection.send("Data received on server!".encode())
    
    # Close the connection
    connection.close()

    # Run server in directory with: python3 tcp_server.py