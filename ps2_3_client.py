import socket

def start_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_address = ('localhost', 5000)  
    while True:
        message = input("Enter message (or type 'exit' to quit): ")
        if message.lower() == 'exit':
            print("Exiting client.")
            break
        client_socket.sendto(message.encode('utf-8'), server_address)
        print(f"Sent: {message}")
        data, _ = client_socket.recvfrom(1024)  # Buffer size of 1024 bytes
        print(f"Received echo: {data.decode('utf-8')}")
    client_socket.close()

if __name__ == "__main__":
    start_client()
