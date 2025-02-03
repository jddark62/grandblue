import socket
import sys

def start_client(server_address, port):
    """Start the TCP client."""
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        client_socket.connect((server_address, port))
        print(f"Connected to server at {server_address}:{port}")
        username = input("Enter username: ").strip()
        client_socket.sendall(username.encode('utf-8'))
        response = client_socket.recv(1024).decode('utf-8')
        print(f"Server response: {response}")
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        client_socket.close()

if __name__ == "__main__":
    default_server_address = 'localhost'
    default_port = 8080  
    if len(sys.argv) > 1:
        server_address = sys.argv[1]
    else:
        server_address = default_server_address

    if len(sys.argv) > 2:
        try:
            port_number = int(sys.argv[2])
        except ValueError:
            print("Invalid port number. Using default port 8080.")
            port_number = default_port
    else:
        port_number = default_port

    start_client(server_address, port_number)
