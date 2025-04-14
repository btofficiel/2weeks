from socket import *
import datetime

serverName = "127.0.0.1"
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_DGRAM)
clientSocket.settimeout(1)
try:
    start_time = datetime.datetime.now()
    clientSocket.sendto("bhaskar".encode(), (serverName, serverPort))
    message, addr = clientSocket.recvfrom(1024)
    end_time = datetime.datetime.now()
    delta = end_time-start_time
    print(f'Received from server: {message.decode()} in {delta.microseconds}ms') 
except TimeoutError:
    print("Lost UDP packet")
