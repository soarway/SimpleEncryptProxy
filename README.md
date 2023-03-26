# SimpleEncryptProxy
简单加密的透明代理，支持Windows和Linux

Windows下使用vs2019编译

linux下使用gcc编译




一、服务器安装

1、ssh登录linux服务器,  执行如下命令：
yum install  -y boost-devel 
yum install  -y gcc 
yum install  -y gcc-c++ 

2、上传服务器压缩包到/home目录
tar -zxvf  tcpproxy_server.tar.gz
cd  tcpproxy_server

3、获取池子IP地址
ping  ltc.f2pool.com

4、执行启动服务器端命令
nohup ./tcpproxy_server  8888    919.813.247.211    1800  &
其中 919.813.247.211    为ping命令获取的IP地址，根据ping的结果替换， 8888为端口号， 也可以根据自己的实际情况替换

5、查看服务器程序是否正在运行中
ps  -aux|grep  tcpproxy_server

如果找不到，代表服务器没有运行， 找到了代表正在运行

6、结束服务器
killall -9  tcpproxy_server


二、客户端安装
1、解压  “加密客户端.zip"  到 D:\proxy\  目录
2、打开CMD窗口，并进入到  D:\proxy\  目录
3、输入启动命令或者编写bat批处理文件
D:\\proxy\\proxy_client.exe  9338   919.813.247.211    8888    
其中  919.813.247.211    为你自己的VPS服务器的IP地址

4、启动后， 把矿机的池子地址配置为 本机的IP地址， 比如：stratum+tcp://192.168.1.201:9338
其中192.168.1.201就是windows电脑的IP地址，


查看IP地址可以用  ipconfig  /all   命令查看
