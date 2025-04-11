#import socket module
import os
from datetime import datetime, timezone
from socket import *
import sys # In order to terminate the program
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('', 5000))
serverSocket.listen()
while True:
    #Establish the connection
    print('Ready to serve...')
    connectionSocket, addr = serverSocket.accept()
    try:
        message = connectionSocket.recv(1024).decode()
        filename = message.split()[1]
        filepath = f'./files{filename}'
        f = open(filepath)
        last_modified = os.path.getmtime(filepath)
        size_bytes = os.path.getsize(filepath)
        utc_datetime = datetime.fromtimestamp(last_modified, timezone.utc)
        formatted_date = utc_datetime.strftime("%a, %d %b %Y %H:%M:%S GMT")
        contents = f.read()
        outputdata = f'HTTP/1.1 200 OK\r\nDate: {formatted_date}\r\nContent-Length: {size_bytes}\r\nContent-Type: text/html; charset=UTF-8\r\nConnection: close\r\n\r\n{contents}\r\n\r\n'
        connectionSocket.sendall(outputdata.encode())
        connectionSocket.close()
    except IOError as err:
        error_resp = f'HTTP/1.1 400 Not Found\r\n\r\n'
        connectionSocket.sendall(error_resp.encode())
        connectionSocket.close()
serverSocket.close()
sys.exit()#Terminate the program after sending the corresponding data
