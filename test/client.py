import socket
import struct

serverAddr = ("127.0.0.1",1234)

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
sock.connect(serverAddr)

message = "hey there!"
metaData = (0x0000,len(message))

s = struct.Struct("I I")
print(s)
packed_metaData = s.pack(*metaData)

sock.sendall(packed_metaData)
sock.send(message.encode("utf-8"))

print(sock.recv(64))

sock.close()
