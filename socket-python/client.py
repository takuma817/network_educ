import socket
import sys

BUFFER_SIZE = 1500

# 引数の確認
if len(sys.argv)<3:
    print("usage: %s hostname port" % sys.argv[0])
    exit(0)
host = sys.argv[1]
port = int(sys.argv[2])
server = (host, port)

# ソケットの作成
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# ウィンドウを識別するため、メッセージを表示
print("I'm a TCP client connecting to %s port %d" % server)

# サーバへ接続要求を行う
s.connect(server)

# 送信メッセージをキーボードから取得
print("Enter a line to be sent.")
buffer = input()
buffer = buffer.encode('utf-8')

# パケットを送信
s.send(buffer)

# パケットを受信して表示
buffer = s.recv(BUFFER_SIZE)
buffer = buffer.decode(encoding='utf-8')
print("%d:%s" % (len(buffer), buffer))

# ソケットを閉じる
s.close()

exit(0)
