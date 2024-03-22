# Network_educ
西研究室の新人教育用資料です。西研での新人教育目的以外での他者への共有を禁じます。
ローカル内で通信する時はターミナルを二つ開き、IPアドレス```127.0.0.1```を指定します

## socket-python
pythonで記述されたソケット通信プログラムです

#### 使い方
port番号はウェルノウンポートではない好きな値を指定する

例：11111

server

```
python server [port番号]
```

client
```
python clint.py [宛先IPアドレス] [port番号]
```

## socket-c
C言語で記述されたソケット通信プログラムです

#### 使い方
```
make
```
server
```
cd server
./server-tcp 
```
client
```
cd client
./client-tcp [IPアドレス]
```

## wolfssl
wolfsslライブラリを使用したTLS通信プログラムです

#### 使い方
```
make
```
server
```
cd server
./server-tls
```
client
```
cd client
./client-tls [IPアドレス]
```