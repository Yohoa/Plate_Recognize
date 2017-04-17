#!/usr/bin/env python
# -*- coding: utf-8 -*-
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# 導入socket lib, json lib
import socket

import json
from time import gmtime, strftime


#-----------------------------------------------------------------------------
# 一個奇怪的函數，編碼轉換
#-----------------------------------------------------------------------------
def process_data(d):
    # 傳遞內容
    
    return d

    
#-----------------------------------------------------------------------------
# 主程序
#-----------------------------------------------------------------------------
    
# 創建socket，決定Client IP及Server Listening 端口
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# 允許所有對3333的訪問接入
host = '0.0.0.0'
port = 3333

# 申請端口。如果端口已被佔用，則會拋出異常……
sock.bind((host,port))

# 讓socket 開始Listen。僅允許一個連接。
print("Listening...")
sock.listen(1)

# 服務器等待連接
while True:
    # Accept connection and data from cilent.
    Plate_Recognition_Server, address = sock.accept()  # 注意，這裡Plate_Recognition_Server是一個類
    print("來訪者的位址是: %s"% address[0])
    raw_data = Plate_Recognition_Server.recv(1024)
    data=raw_data.decode('utf-8')
    print("收到的訊息是：\n")
    print("%s\n"% data)
	
    data_json = {
        'Time':strftime("%Y-%m-%d %H:%M:%S",gmtime()),
        'Plate':data
        }
    with open('data.json', 'w') as outfile:
	    json.dump(data_json, outfile)

    #print("Received <- %s")% (data)
    #if data:
    
        # # 收到數據，再把它們送回去……
        # send = process_data(data)
    #print("請您輸入訊息\n")
    #send = input()
    #print("Sent ->: %s"% send)
    #Plate_Recognition_Server.send(send.encode())
    
    # 關閉連接
    Plate_Recognition_Server.close()
