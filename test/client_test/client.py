import socket

SERVER_HOST = '127.0.0.1'
SERVER_PORT = 8080       

def main():
    try:
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        
        client_socket.connect((SERVER_HOST, SERVER_PORT))
        print(f"[info] Conectado ao servidor em {SERVER_HOST}:{SERVER_PORT}")
        
        message = "PING"
        client_socket.sendall(message.encode())
        print(f"[info] Mensagem enviada: {message}")
        
        response = client_socket.recv(1024).decode()
        print(f"[info] Resposta recebida: {response}")
        
        client_socket.close()
        print("[info] Conexão encerrada")
    except Exception as e:
        print(f"[error] Ocorreu um erro: {e}")

if __name__ == "__main__":
    main()
