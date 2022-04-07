<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 0.0.0
 * @Date: 2022-04-06 20:36:53
 * @LastEditTime: 2022-04-06 22:05:42
-->
- [Linux Usage](#linux-usage)
  - [1. 基本概念](#1-基本概念)
    - [1.1 文件系统](#11-文件系统)
    - [1.2 环境变量](#12-环境变量)
  - [2. 基本操作](#2-基本操作)
    - [2.1 常用命令](#21-常用命令)
    - [2.2 文件相关](#22-文件相关)
    - [2.3 压缩解压](#23-压缩解压)
    - [2.4 系统与软件(Ubuntu)](#24-系统与软件ubuntu)
  - [3. Ubuntu 安装](#3-ubuntu-安装)
    - [3.1 Win & Ubuntu 双系统](#31-win--ubuntu-双系统)
    - [3.2 Mac & Ubuntu 虚拟机](#32-mac--ubuntu-虚拟机)


# Linux Usage

## 1. 基本概念
### 1.1 文件系统
Linux是一种自由和开放源码的类UNIX操作系统，在Linux中所有的文件都是基于目录的方式存储的，一切都是目录，一切都是文件。通常接触任何一种类UNIX系统的第一步都是打开终端，查看其文件目录分布。
  - 终端打开后，每行的命令提示符$之前都会出现：`用户名@主机名：当前所在目录`。注意主机名只有一个，因为我们只有一个主机，但用户名可以有多个，因为我们一台主机我们可以建立多个账户，各根目录下的文件夹会根据其自身属性为各个用户根据用户名创建不同的文件夹（有的文件是所有用户共享的，则不会创建）。比如终端打开后默认`home`目录~，其实是当前用户的home目录，其绝对路径为`/home/usename/`
  - `/` : 是一切目录的起点，如大树的主干。其它的所有目录都是基于树干的枝条或者枝叶。ubuntu中硬件设备如光驱、软驱、usb设备都将挂载到这颗繁茂的枝干之下，作为文件来管理。
  - `/home`: 用户的主目录，在Linux中，每个用户都有一个自己的目录，一般该目录名是以用户的账号命名的。
  - `/media`: ubuntu系统挂载的硬盘、usb设备，存放临时读入的文件。
  - `/tmp`: 这个目录是用来存放一些临时文件的，所有用户对此目录都有读写权限。
  - `/bin`: bin是Binary的缩写。存放系统中最常用的可执行文件（二进制）。
  - `/boot`: 这里存放的是Linux内核和系统启动文件，包括Grub、lilo启动器程序。
  - `/dev`: dev是Device(设备)的缩写。该目录存放的是linux的外部设备，如硬盘、分区、键盘、鼠标、usb等。
  - `/etc`: 这个目录用来存放所有的系统管理所需要的配置文件和子目录，如passwd、hostname等。
  - `/lib`: 存放共享的库文件，包含许多被/bin和/sbin中程序使用的库文件。
  - `/mnt`: 作为被挂载的文件系统得挂载点。
  - `/opt`: 作为可选文件和程序的存放目录，主要被第三方开发者用来简易安装和卸载他们的软件
  - `/usr`: 存放与系统用户有关的文件和目录。
  - `/var`: 长度可变的文件，尤其是些记录数据，如日志文件和打印机文件。

### 1.2 环境变量
所谓 “变量” 可简单理解成编程中定义的Variable. bash shell用一个叫作`环境变量`的特性来存储有关shell会话和工作环境的信息(这也是它们被称作环境变量的原因)。这项特性允许你在内存中存储数据，以便程序或shell中运行的脚本能够轻松访问到它们。这也是存储持久数据的一种方法。
```sh
# 查看已定义好的变量 
printenv
# 查看变量值
echo $变量名
echo $PWD
echo $USER=ubuntu16
echo $PATH
# 编程中可直接使用这些定义好的变量，不用每次定义
```

**Linux环境变量分类**
1. 按照生命周期来分：
   - 永久的：需要用户修改相关的配置文件，变量永久生效
   - 临时的：用户利用export命令，在当前终端下声明环境变量，关闭Shell终端失效
2. 按照作用域来分：
   - 系统环境变量：系统环境变量对该系统中所有用户都有效
   - 用户环境变量：顾名思义，这种类型的环境变量只对特定的用户有效。


**Linux设置环境变量的方法**
  1. 对所有用户有效：在`/etc/profile`文件中添加变量。修改文件后要想马上生效还要运行`source /etc/profile`不然只能在下次重进此用户时生效
  2. 对单一用户生效：在用户目录下的`.bash_profile`文件中增加变量。如ubuntu下修改`～/.bashrc`文件: 这种方法更为安全，它可以把使用这些环境变量的权限控制到用户级别,这里是针对某一个特定的用户，如果需要给某个用户权限使用这些环境变量，只需要修改其个人用户主目录下的.bashrc文件就可以了。
  3. 临时生效；直接运行export命令定义变量，只对当前shell（BASH）临时有效，在shell的命令行下直接使用`export 变量名=变量值`

注意：如果要`用到`变量，使用`$`；如果要`操作`变量，`不`使用`$`。这条规则的一个例外是使用`printenv`显示某个变量的值。


**设置PATH环境变量**
当你在shell命令行界面中输入一个外部命令时，shell必须搜索系统来找到对应的程序，而PATH环境变量定义了：用于进行命令和程序查找的目录。
- PATH中的目录使用冒号分隔。
- 如果命令或者程序的位置没有包括在`PATH`变量中，那么如果不使用绝对路径的话，shell是没法找到的。如果shell找不到指定的命令或程序，它会产生`command not found`的错误信息。
```sh
# 现在假设你新安装了一个命令在/usr/locar/new/bin下面
# 而你又想像ls一样在任何地方都使用这个命令，就需要修改环境变量PATH了
export PATH=$PATH:/usr/locar/new/bin
# 通常的做法是把这行bash命令写到/root/.bashrc的末尾,然后source该文件即可
```


## 2. 基本操作
无需特别记忆，使用时通过 --help 查看参数用法

### 2.1 常用命令
```bash
# 1. check kernel version
uname -a
uname -v
uname -r
# 2.check ip address
ifconfig
ip addr show eth0
# 3. check free disk space
df -ah
# 4. mange services on a system
service udev status
service udev start
# 5. check the size of a directory's contents on disk
ls -s filename
du -sh filename
# 6. check for open ports
netstart -tulpn
# 7. check cup usage for a process
ps aux | grep nginx
top
htop
# 8. dealing with mounts
ls /mnt
mount /dev/sda2 /mnt
mount
# 9. look up something you don't know
man <command> 
man ps
# 10 when you can't find an answer in a man page
google
```

### 2.2 文件相关
```sh
## 文件夹创建
mkdir temp
mkdir -p temp/tem

## 文件操作
mv filename.txt temp # 移动
cp # 复制
rm -rf xxx/xx # 删除

## 文件查看 
head -n 10 filename # 查看文件前几行
tail -n 5 filename  # 查看文件后几行
cat filename # 查看所有内容

# 统计文件夹下文件个数
ls count_folder | wc -l
#统计当前目录下文件的个数（不包括目录）
ls -l | grep "^-" | wc -l
#统计当前目录下文件的个数（包括子目录）
ls -lR| grep "^-" | wc -l
#查看某目录下文件夹(目录)的个数（包括子目录）
ls -lR | grep "^d" | wc -l
```


### 2.3 压缩解压
```sh
## zip 压缩
zip -r file.zip file 
zip -P password file.zip file
# zip 解压
unzip -d file.zip folder/

# 解压分卷压缩文件
cat test.z* > testall.zip # 先合并文件
unzip testall.zip # 然后解压

# 查看.zip 文件的内容
unzip -v file.zip
```

### 2.4 系统与软件(Ubuntu)
```sh
# 添加 源并更新
sudo add-apt-repository ppa:user/ppa-name
sudo apt-get update
# 删除 源
然后进入 /etc/apt/sources.list.d 目录，将相应 ppa 源的保存文件删除。然后更新一下
# 如果之前添加了错误的源，新添加源之前需要移除
sudo add-apt-repository --remove ppa:jonathonf/python-3.6

# 建立软连接
sudo ln -s python3.5 /usr/bin/python3

# 修复新加卷
sudo ntfsfix /dev/sdb8

# 通过apt-get安装指定版本
apt-get install package_name=version
# 查询指定软件有多少个版本
apt-cache madison package_name

# 删除软件及其配置文件
apt-get --purge remove <package>
# 删除没用的依赖包
apt-get autoremove <package>
# 此时dpkg的列表中有“rc”状态的软件包，可以执行如下命令做最后清理：
dpkg -l |grep ^rc|awk '{print $2}' |sudo xargs dpkg -P

# 无法打开锁文件 /var/lib/dpkg/lock-frontend - open (13: 权限不够)

```

## 3. Ubuntu 安装
### 3.1 Win & Ubuntu 双系统
参考官网链接，制作启动盘，确定引导，按步骤安装即可

### 3.2 Mac & Ubuntu 虚拟机
使用Parallels Desktop安装
