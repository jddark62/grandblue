import socket
import sys

USER_DATA = {
    "Akila": "Akila_08",
    "Ram": "Ram@123",
    "James": "James_james"
}

def load_user_data(filename):
    """Load user data from a specified file."""
    user_data = {}
    try:
        with open(filename, 'r') as file:
            for line in file:
                username, full_name = line.strip().split(',')
                user_data[username] = full_name
    except FileNotFoundError:
        print(f"Error: The file {filename} was not found.")
    return user_data

def start_server(port):
    """Start the TCP server."""
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = ('', port)
    server_socket.bind(server_address)
    server_socket.listen(1)
    print(f"Server listening on port {port}...")

    while True:
        connection, client_address = server_socket.accept()
        try:
            print(f"Connection from {client_address}")
            username = connection.recv(1024).decode('utf-8').strip()
            print(f"Received username: {username}")
            if username in USER_DATA:
                response = f"Login Name: {username}, Full Name: {USER_DATA[username]}"
            else:
                response = "Sorry, no match to your query!"
            connection.sendall(response.encode('utf-8'))
        finally:
            connection.close()

if __name__ == "__main__":
    default_port = 8080
    if len(sys.argv) > 1:
        try:
            port_number = int(sys.argv[1])
        except ValueError:
            print("Invalid port number. Using default port 79.")
            port_number = default_port
    else:
        port_number = default_port

    start_server(port_number)
