Radio
=====

Radio是一个用来多播Firmware的程序，配合U-boot可以实现一对多的开机。

Radio由三部分构成：
1. 打包程序——radiomaker
打包程序用来把一个普通的Firmware做成一个Radio支持的文件。它所做的事为Firmware加四字节头部信息，格式如下：
|---- ----|---- ----|---- ----|---- ----|

2. 将生成文件多播出去的部分--radioplayer
首先看radioplayer的配置档：
# Channel | File  | Bandwidth
         0       *         5
         1  test.o        10   
		 2   dbg.o        10
说明：
Channel 0是用来播送文件信息的，包括文件名，文件大小和校验和(CRC32)

3. 运行在U-boot上能够接受多播的patch代码——radioreceiver
#待定
