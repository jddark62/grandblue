import socket
import time

def start_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_address = ('localhost', 5000) 
    try:
        start_message = "Client started"
        client_socket.sendto(start_message.encode('utf-8'), server_address)
        print(f"Sent: {start_message}")
        time.sleep(2)  
        stop_message = "Client stopped"
        client_socket.sendto(stop_message.encode('utf-8'), server_address)
        print(f"Sent: {stop_message}")

    finally:
        client_socket.close()

if __name__ == "__main__":
    start_client()
