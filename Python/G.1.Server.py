#!/usr/bin/env python
# -*- coding: utf-8 -*-
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# 導入socket lib, json lib
import socket

import json
from time import gmtime, strftime

import requests


import re
#-----------------------------------------------------------------------------
# 一個奇怪的函數，編碼轉換
#-----------------------------------------------------------------------------
def process_data(d):
    # 傳遞內容
    
    return d

    
#-----------------------------------------------------------------------------
# 主程序
#-----------------------------------------------------------------------------



#-----------------------------------------------------------------------------
# 正則表達式
#
m1Regex = re.compile(r'[0123456789.]+ [0123456789:]+ ([EW0123456789.]+) ([NS0123456789.]+)')

# 創建socket，決定Client IP及Server Listening 端口
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# 允許所有對3333的訪問接入
host = '0.0.0.0'
port = 3333

IIS_host = 'http://survfu.cn/temp/in.php'
IIS_port = 3333
#IIS = 'http://'+IIS_host+':'+str(IIS_port)
IIS = IIS_host
# 申請端口。如果端口已被佔用，則會拋出異常……
sock.bind((host,port))

# 讓socket 開始Listen。僅允許一個連接。
print("Listening...")
sock.listen(1)

# 服務器等待連接
while True:
    # Accept connection and data from cilent. M1
    Plate_Recognition_Server, address = sock.accept()  # 注意，這裡Plate_Recognition_Server是一個類
    print("來訪者的位址是: %s"% address[0])
    raw_data = Plate_Recognition_Server.recv(1024)
    data=raw_data.decode('utf-8')
    print("收到的訊息是:\n**********BEGIN**********\n")
    print("%s\n***********END***********"% data)
    m1r = m1Regex.match(data)
    Long = m1r.group(1) #經度
    Lat = m1r.group(2) #緯度
    
    Plate_Recognition_Server.close()
    
    # Accept connection and data from cilent. M2
    Plate_Recognition_Server, address = sock.accept()  # 注意，這裡Plate_Recognition_Server是一個類
    print("來訪者的位址是: %s"% address[0])
    raw_data = Plate_Recognition_Server.recv(1024)
    data=raw_data.decode('utf-8')
    print("收到的訊息是:\n**********BEGIN**********\n")
    print("%s\n***********END***********"% data)


    Plate_Recognition_Server.close()
    
    # Accept connection and data from cilent. M3
    Plate_Recognition_Server, address = sock.accept()  # 注意，這裡Plate_Recognition_Server是一個類
    print("來訪者的位址是: %s"% address[0])
    raw_data = Plate_Recognition_Server.recv(1024)
    data=raw_data.decode('utf-8')
    print("收到的訊息是:\n**********BEGIN**********\n")
    print("%s\n***********END***********"% data)


    Plate_Recognition_Server.close()

    
    # Accept connection and data from cilent. M4
    Plate_Recognition_Server, address = sock.accept()  # 注意，這裡Plate_Recognition_Server是一個類
    print("來訪者的位址是: %s"% address[0])
    raw_data = Plate_Recognition_Server.recv(1024)
    data=raw_data.decode('gbk')
    print("收到的訊息是:\n**********BEGIN**********\n")
    print("%s\n***********END***********"% data)
    
#-----------------------------------------------------------------------------
# FOR TEST
    data='苏000002'
#-----------------------------------------------------------------------------

    Plate_Recognition_Server.close()
    # print("Long=%s, Lati=%s"%(Long,Lat))
    data_post='a='+data+'&b='+Long+'&c='+Lat
    print(data_post+'\n')
    # "a=%Plate&b=%Longitude&c=%Latitude"
    r = requests.post(IIS, data=data_post.encode())
