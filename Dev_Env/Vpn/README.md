<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 0.0.0
 * @Date: 2022-04-07 11:35:54
 * @LastEditTime: 2022-04-07 11:40:12
-->
# VPN

## LUG

## [panda vpn](https://pandavpnpro.com/zh-cn/)

## ssr

1. 安装elctron-ssr.deb
2. 小飞机添加订阅地址 : 配置-> 选项设置-> 订阅管理 -> https://sockboom.me/link/0HfPneNWtNKK0ql8?mu=1
   - （ssr 机场搜索， 如https://sockboom.art/）
3. 系统设置 网络： socks主机 127.0.0.1  1080
4. 系统代理模式 PAC 
5. 浏览器 SwitchyOmega 情景模式： 网址协议 SOCKS: 127.0.0.1  1080
6. atuo swtich设置规则列表 https://github.com/FelisCatus/SwitchyOmega/wiki/GFWList （最下面）


终端：
1. 安装 sudo apt-get install proxychains
2. sudo vim /etc/proxychains.conf
  - 最后一行 socks5 127.0.0.1 1080
3. proxychains wget --no-cookie --no-check-certificate  https://www.google.com 



手机：
切换`App Store`账号-ID: `yis_ubai1@163.com` 密码: `Aa112211` 注意特殊符号与大小写,如果显示需要解锁账号，请刷新本页面，会随机到其他共享ID。**（千万不要试图登陆iCloud，会上传您的照片与通讯录到这个账户上）**

looks_two 已购项目搜索`Quantumult`下载安装

looks_3 安装完成后切换回您自己的账号。（请务必切换回您自己的账户）

looks_4 打开软件后，选择下方的设置，选择订阅，点击右上角add符号，选择服务器，此时将下方订阅地址粘贴在链接栏（名称栏随便填），保存后订阅会自动更新。

looks_5 回到主页面点击底栏最中间的节点列表按钮，此时就可以进行节点的选择了，选择完成后只需打开右上角开关即可连上我们的网络！

looks_6 注意：第一次连接可能不能用，导入后程序退出并重新打开程序后连接即可！


## google-access-helper-2.3.0