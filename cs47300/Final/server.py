#!/usr/bin/python
import socket
import sys
from time import localtime, strftime

HOST = '139.102.14.201'
PORT = 2300

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)
while True:
  desc, addr = s.accept()
  addr = addr[0]
  saddr = addr.split('.')
  if (saddr[0] == '139' and saddr[1] == '102') or (saddr[0] == '10' and saddr[1] ==     '139'):
    msg = strftime("%H:%M:%S %a %b %d, %Y", localtime())+'\n'
    desc.send(msg)
    desc.close()
    sys.stderr.write(strftime("%H:%M:%S", localtime())+' '+addr+' '+msg) 
  else:
    msg = "ACCESS DENIED\n"
    desc.send(msg)
    desc.close()
    sys.stderr.write(strftime("%H:%M:%S", localtime())+' '+addr+' '+msg) 
