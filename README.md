Radio
=====

Radio是一个用来多播Firmware的程序，配合U-boot可以实现一对多的开机。

Radio由三部分构成：
1. 打包程序——radiomaker
打包程序用来把一个普通的Firmware做成一个Radio支持的文件。它所做的事为Firmware加20字节头部信息，格式如下：
|----16 bytes file name----|
|4 bytes size|4 bytes CRC32|
|------Firmware Data-------|

typedef struct radio_header {
	char fname[16];
	int fsize;
	int crc32;
}radio_header;

2. 将生成文件多播出去的部分--radioplayer
首先看radioplayer的配置档：
# Channel | File  | Bandwidth | Destination
         0       *         5    224.0.0.1:1234
         1  test.o        10    224.0.0.1:1235
说明：
Channel 0是用来播送文件信息的，即文件头的。包括文件名，文件大小和校验和(CRC32)
	Channel 0的文件名是*。

Channel 1用来播送实际的文件内容。Channel 1发送的每个包为：
|--4 bytes index--|--1024 bytes data--|
index从0开始，Ethernet的MTU为1500，1024是一个很合适的大小。

typedef radio_unit{
	int index;
	char data[1024];
}radio_unit;
	
Bandwidth用来控制发送速率，这里可采用简单的sleep实现。

typedef struct radio_config{
	int channel;
	char fname[16];
	int bandwidth;
	int ip;
	short port;
}radio_config;

默认把Channel 0发送到UDP 224.0.0.1:1234，
Channel 1发送到UDP 224.0.0.1:1235


3. 运行在U-boot上能够接受多播的patch代码——radioreceiver
a. 首先从224.0.0.1:1234的位置读取文件的大小和CRC32信息
b. 从224.0.0.1:1235读取文件内容
c. 将文件内容排序整理，拷贝到U-boot的boot位置
d. 跳转到该位置，启动系统！

