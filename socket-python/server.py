import socket
import sys

BUFFER_SIZE = 1500

# 引数の確認
if len(sys.argv)<2:
    print("usage: %s port" % sys.argv[0])
    exit(0)
port = int(sys.argv[1])
server = ('', port)

# ソケットの作成
w = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# ウィンドウを識別するため、メッセージを表示
print("I'm a TCP server waiting at port %d" % port)

# ポート番号に接続
w.bind(server)

# 接続要求を待機
w.listen(0)

# 接続要求を受理して接続開始
s, address = w.accept()

# 接続待ち用のソケットは先に閉じておく
w.close()

# パケットを受信して表示
buffer = s.recv(BUFFER_SIZE)
buffer = buffer.decode(encoding='utf-8')
print("%d:%s" % (len(buffer), buffer))

# 送信メッセージをキーボードから取得
print("Input a message:")
buffer = input()
buffer = buffer.encode('utf-8')

# パケットを送信
s.send(buffer)

# ソケットを閉じる
s.close()

exit(0)
