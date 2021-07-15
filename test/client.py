import socket

serverAddr = ("127.0.0.1",1234)

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
sock.connect(serverAddr)

sock.send("hey there!".encode("utf-8"))

print(sock.recv(64))

sock.close()
