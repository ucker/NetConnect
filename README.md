# NetConnect
>连:smile:接江:cn:苏:blush:电:blush:信
>>校:blush:园:cn:宽:blush:带
## 安装
>仅以openwrt为例

1. 下载包 [下载地址](http://104.143.38.103/NetConnect.ipk)
2. 安装包，需要openssl支持。[如何安装openssl](#install_openssl)  
```bash
opkg install NetConnect.ipk
```

## 编译
* Ubuntu 14.04
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
        ```bash
        git clone https://github.com/ucker/NetConnect.git package
        #选择NetConnect
        make menuconfig
        make V=99
        ```
    4. 运行  
        用ssh连接openwrt，输入`NetConnect`, 之后在浏览器中输入`路由器ip:8888`即可出现二维码

## <p id="install_openssl">安装openssl</p>

Ubuntu直接`apt-get`安装即可，openwrt需要编译openssl的包。只需在`make menuconfig`时选择openssl即可。编译完之后在目录中就会出现openssl的包。

这里提供小米路由器青春版(R1CL)的[包](http://104.143.38.103/openssl.ipk)

## 注意
保证你的路由器内存至少为64M，否则可能无法运行
    
#### **联系方式：netsimpler@163.com**
