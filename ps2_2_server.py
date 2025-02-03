import socket

def start_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_address = ('', 5000) 
    server_socket.bind(server_address)
    print("Server is listening on UDP port 5000...")
    while True:
        data, addr = server_socket.recvfrom(1024)  
        print(f"Received message: {data.decode('utf-8')} from {addr}")

if __name__ == "__main__":
    start_server()
