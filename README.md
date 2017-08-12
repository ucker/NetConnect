# NetConnect
>连接江苏电信校园宽带

## <p id="install">安装</p>

>仅以openwrt为例     


1. 下载二进制文件(请直接从Release页面下载)

2. 将二进制文件复制到`/www/cgi-bin`目录下。同时将文件js目录中的内容复制到`/www/luci-static`下。并配置合适的权限运行需要openssl支持。如何安装[openssl](#install_openssl)  
```bash
mv /root/netconnect /www/cgi-bin
chmod 755 /www/cgi-bin/netconnect
mkdir /www/luci-static/netconnect
mv /root/js/* /www/luci-static/netconnect
```
3. 在浏览器直接输入`http://路由器地址/cgi-bin/netconnect`，如果没有联网会出现二维码，扫码即可

## 编译
* <del>Ubuntu 14.04</del>
>>建议编译cgi版本，这个版本有缺陷
1. 安装openssl  
```bash
sudo apt-get install libssl-dev
```
2. 下载代码到本地  
```bash
git clone https://github.com/ucker/NetConnect.git
```
3. 编译  
```bash
cd NetConnect/src
make all
```
4. 运行
  1. 运行NetConnect  
  ```bash
  ./NetConnect
  ```
  2. 用浏览器打开`127.0.0.1:8888`
  3. 用手机扫码


* Openwrt
>>不使用原来的编译方式，采用cgi方法。一是节约内存；二是方便，不需要使用ssh连接路由器
1. 下载对应路由器的SDK，以小米路由器青春版为例，到[这里](https://downloads.openwrt.org/snapshots/trunk/ramips/mt7628/)下载  
```bash
#以小米路由器青春版(R1CL)为例
wget https://downloads.openwrt.org/snapshots/trunk/ramips/mt7628/OpenWrt-SDK-ramips-mt7628_gcc-5.3.0_musl-1.1.16.Linux-x86_64.tar.bz2
tar xjf OpenWrt-SDK-ramips-mt7628_gcc-5.3.0_musl-1.1.16.Linux-x86_64.tar.bz2
cd OpenWrt-SDK-ramips-mt7628_gcc*
```
2. 安装openssl  
```bash
./scripts/feeds update base packages
#下载项目所需的库openssl
./scripts/feeds install libopenssl
```
3. 编译  
	>>这里使用eclipse的跨平台编译，直接编译二进制文件，细节可以到网上搜
4. 运行  
       [见安装部分](#install)

## <p id="install_openssl">安装openssl</p>
Ubuntu直接`apt-get`安装即可，openwrt需要编译openssl的包。只需在 `make menuconfig`时选中openssl包，即可编译。


## 注意
<del>保证你的路由器内存至少为64M，否则可能无法运行。</del>cgi版本似乎可以运行
#### **联系方式：netsimpler\#163.com**
