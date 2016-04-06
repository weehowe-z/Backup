# Assignment3

#### Name: Wenhao Zhu

#### Student ID: 5130309717

---

## Introduction

由于客户端和服务端都是新开线程，因此，测试时可以选择：
- 一台机器打开一个GUI，可以同时作为服务端和客户端进行文件传输
- 一台机器打开两个GUI，各自作为服务端或客户端进行文件传输（需要使用不同端口）
- 两台机器各自打开GUI，各自作为服务端或客户端进行文件传输（需要在同一局域网内并指定地址）

## 1.Compile & Run

```shell
$ make
$ java FileShare.GUI
```

## 2.Use as Server Side

### Select file

点击 `Choose File` 按钮
> 由于采用的 java awt 很多控件是调用的系统自带的， 在 Linux 下可能出现错误，一般关闭重开即可解决。

### Run Server
点击 `Start Server` 按钮
> 需要指定端口，默认或不填为2680，如果端口被占用会自动退出

1. 启动服务后便可以通过浏览器直接访问地址获取文件， 如'0.0.0.0：2680'。 但是为了传输**文件名**，我的编码方式是，在文件之前第一个 byte 记录的是文件名的长度 l，接下来的 l 个 byte 保存文件名的 ASCII 编码， 再接下来才是文件内容， 因此如果是纯文本则可以明显在浏览器内看到前几个字节的变化，而其他类型文件下载后可能无法打开。
2. 由于服务端是线程，一开启后又是无限循环。为了支持更换发送的文件又不用更换端口，需要在主进程中关闭先前运行的线程，这里采用的方法是，为ServerSocket设置timeout时间，抛出超时异常跳回到主循环，从而避免在accept()处无限等待，同时，Server类添加一个volatile的成员变量flag，通过flag作为循环控制条件，从而可以通过主进程修改flag控制服务端线程的开关。

## 3.Use as Client Side

输入需要建立连接的服务端地址，如本机 '0.0.0.0:2680', 局域网内 '192.168.1.113:12345'等等。点击 `Start Download` 按钮即可开始下载，下载到的文件存放在 `Downloads` 文件夹下。

按`ESC`退出程序

## 4.Check the file integrity

不妨采用`md5`校验下载得到的文件完整性，`md5`应该是相同的

```shell
$ md5sum test.zip
$ md5sum Downloads/test.zip
```

## 5.Other


**The code and other related information can be also found on my [github](https://github.com/weehowe-z/backup/tree/master/CNetwork/Assignment3).**

**Any problem happens to my code(can't run.. etc), plz contact me at [weehowe.z@gmail.com](mailto:weehowe.z@gmail.com).**

目前在 `Ubuntu 15.10` 和 `Win10` 下做了测试，有问题的话可以联系我远程演示 = =
