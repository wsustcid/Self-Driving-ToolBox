<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-11-19 20:45:40
 * @LastEditTime: 2022-01-05 16:54:36
-->
- [1. 安装说明](#1-安装说明)
  - [1.1 必备软件安装](#11-必备软件安装)
    - [1.1.1 安装 Ubuntu Linux](#111-安装-ubuntu-linux)
    - [1.1.2 安装 NVIDIA GPU 驱动（可选）](#112-安装-nvidia-gpu-驱动可选)
    - [1.1.3 安装 Docker Engine](#113-安装-docker-engine)
    - [1.1.4 安装 NVIDIA Container Toolkit](#114-安装-nvidia-container-toolkit)
  - [1.2 通过安装包安装Apollo](#12-通过安装包安装apollo)
    - [1.2.1 下载安装包](#121-下载安装包)
    - [1.2.2 安装](#122-安装)
  - [1.3 通过源码编译安装Apollo](#13-通过源码编译安装apollo)
  - [参考资源](#参考资源)

# 1. 安装说明
## 1.1 必备软件安装
### 1.1.1 安装 Ubuntu Linux
推荐安装纯净版本的 Ubuntu 18.04.5 LTS 或者之后的版本，具体安装教程参考[官方安装指南](https://ubuntu.com/tutorials/install-ubuntu-desktop).

安装完成后最好执行一下软件更新
```bash
sudo apt-get update
sudo apt-get upgrade
```

### 1.1.2 安装 NVIDIA GPU 驱动（可选）
自动驾驶汽车上的Apollo运行环境需要依赖NVIDIA GPU驱动，但如果不运行感知模块，只是通过播放数据包体验Apollo，则不安装NVIDIA1驱动也是可以的。

对于Ubuntu系统，有两种安装驱动的方式：[apt-get安装](https://github.com/NVIDIA/nvidia-docker/wiki/Frequently-Asked-Questions#how-do-i-install-the-nvidia-driver)和[runfile安装]((https://www.nvidia.com/en-us/drivers/unix/))

**apt-get安装驱动(推荐)**
```bash
sudo apt-get update
sudo apt-add-repository multiverse
sudo apt-get update
sudo apt-get install nvidia-driver-455
# 查看是否已经安装成功（一般需要重启）
nvidia-smi
```

### 1.1.3 [安装 Docker Engine](https://docs.docker.com/engine/install/ubuntu/)
Apollo 6.0 要求Docker 19.03+版本，安装配置步骤如下
```bash
# installation
curl https://get.docker.com | sh
sudo systemctl start docker && sudo systemctl enable docker
# 使用非root权限运行docker，一般docker相关命令会要求在root user权限下运行
sudo groupadd docker # Create the docker group
sudo usermod -aG docker $USER # Add your user to the docker group -> 重启电脑
docker run hello-world # Verify that you can run docker commands without sudo
# 设置开机自动启动
sudo systemctl enable docker.service
sudo systemctl enable containerd.service
```

### 1.1.4 安装 NVIDIA Container Toolkit
为了在docker镜像内使用cuda，我们还需要安装[NVIDIA Container Toolkit](https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/install-guide.html)：
```bash
distribution=$(. /etc/os-release;echo $ID$VERSION_ID)
curl -s -L https://nvidia.github.io/nvidia-docker/gpgkey | sudo apt-key add -
curl -s -L https://nvidia.github.io/nvidia-docker/$distribution/nvidia-docker.list | sudo tee /etc/apt/sources.list.d/nvidia-docker.list
sudo apt-get -y update
sudo apt-get install -y nvidia-docker2
# 安装完成后，重启docker使配置生效
sudo systemctl restart docker
```

## 1.2 通过安装包安装Apollo
本章节主要介绍在Ubuntu 18.04 (和Apollo 6.0相匹配的Ubuntu版本)安装Apollo软件的相关步骤，在进行正式安装之前，首先我们要确保：
  - 确保已经完成1.1章节中【必备软件安装】
  - 确保docker正在运行：执行`systemctl status docker` 查看Docker的运行状态；如果没有运行，通过`systemctl start docker`启动Docker

### 1.2.1 下载安装包
首先在[官网首页](https://apollo.auto/developer_cn.html)下载安装包，然后选择合适的路径进行解压，解压后的文件夹将作为Apollo的根目录
```bash
tar -xvf apollo_v6.0_edu_amd64.tar.gz
```

### 1.2.2 安装
在Apollo根目录下执行
```bash
# cd ~/apollo_edu
./apollo.sh
```
第一次执行该脚本时，会自动在同级目录下创建一些文件夹用于在容器中挂载，目录结构如下：
```bash
.
├── apollo.sh
├── data
│   ├── bag
│   ├── core
│   └── log
├── modules
│   ├── calibration
│   │   └── data # 用于保存车辆数据
│   └── map
│       └── data # 用于保存地图数据，用户可将自己的车辆和地图文件拷贝到这两个文件夹使用
└── scripts
    ├── apollo_base.sh
    ├── apollo.bashrc
    ├── docker_base.sh
    ├── runtime_into.sh
    └── runtime_start.sh
```

脚本执行成功后，将显示如下信息，表示已经进入了Apollo的运行容器
```bash
[ubuntu18@in-runtime-docker:/apollo]$ 
```
至此，我们就可以在容器内直接使用Apollo的各项功能，而无需手动build

## 1.3 通过源码编译安装Apollo
```bash
## 下载Apollo源码并切换至要安装的版本
git clone git@github.com:ApolloAuto/apollo.git # https://github.com/ApolloAuto/apollo/blob/master/docs/howto/how_to_clone_apollo_repo_from_china.md
cd apollo
git checkout master
# (Optional) For convenience, you can set up environment variable APOLLO_ROOT_DIR to refer to Apollo root directory by running
echo "export APOLLO_ROOT_DIR=$(pwd)" >> ~/.bashrc  && source ~/.bashrc

## 确保docker 已经启动并运行
systemctl status docker # 若未启动： systemctl start docker
# 启动Docker容器内的Apollo 开发环境
bash docker/scripts/dev_start.sh # !! From the ${APOLLO_ROOT_DIR} directory
# If successful, you will see [ OK ] Enjoy!

## 进入容器
bash docker/scripts/dev_into.sh
# 在容器内编译Apollo源码
./apollo.sh build # ！From the /apollo directory inside Apollo Docker container
# for an optimized build, Or type
./apollo.sh build_opt
# 
```

## 参考资源
  - [Ubuntu 18.04](https://old-releases.ubuntu.com/releases/18.04.5/)
  - NVIDIA driver version 455.32.00 and above ([Web link](https://www.nvidia.com/Download/index.aspx?lang=en-us))
  - Docker-CE version 19.03 and above ([Docker Install](https://docs.docker.com/engine/install/ubuntu/))
  - [Docker配置参考](https://docs.docker.com/engine/install/linux-postinstall/)
  - NVIDIA Container Toolkit ([Official doc](https://github.com/NVIDIA/nvidia-docker))