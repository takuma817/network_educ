# Network_educ
西研究室の新人教育用資料です。西研での新人教育目的以外での他者への共有を禁じます。

## socket-c
c言語で記述されたソケット通信プログラムです

#### 使い方
server

```
python server [port番号]
```

client
```
python clint.py [宛先IPアドレス] [port番号]
```

## socket-python
pythonで記述されたソケット通信プログラムです

#### 使い方
```
make
```
server
``` 
./server-tcp 
```
client
```
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
./server-tls
```
client
```
./client-tls [IPアドレス]
```