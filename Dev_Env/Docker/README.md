<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-11-21 21:45:03
 * @LastEditTime: 2021-11-22 17:20:12
-->
- [Docker 简明教程](#docker-简明教程)
  - [1. 快速入门](#1-快速入门)
    - [1.1 Docker 安装](#11-docker-安装)
    - [1.2 常用指令](#12-常用指令)
  - [2. Docker 实践](#2-docker-实践)
    - [2.1 基础概念](#21-基础概念)
    - [2.2 使用 Docker 镜像](#22-使用-docker-镜像)
    - [2.3 利用 commit 理解镜像构成](#23-利用-commit-理解镜像构成)
    - [2.4 使用 Dockerfile 定制镜像](#24-使用-dockerfile-定制镜像)
    - [2.5 操作 Docker 容器](#25-操作-docker-容器)
    - [2.6 访问仓库](#26-访问仓库)
    - [2.7 Docker 数据管理](#27-docker-数据管理)
  - [3. Nvidia-Docker](#3-nvidia-docker)
    - [3.1 快速入门](#31-快速入门)
  - [4. Docker ROS](#4-docker-ros)
  - [参考资料](#参考资料)

# Docker 简明教程
## 1. 快速入门
### 1.1 Docker 安装
首先根据自己的系统类型，按照[官方教程](https://docs.docker.com/engine/install/ubuntu/)进行选择合适的版本进行安装
  - 有时并不是最新版就是适合自己的，有时需要和cuda版本兼容
  - 为了后续使用的方便，进行相关[安装后的配置](https://docs.docker.com/engine/install/linux-postinstall/)

```bash
# 选择对应版本安装
sudo apt-get install docker-ce=17.12.0-ce-0-ubuntu
# 设置docker开机自动启动
sudo systemctl enable docker
sudo systemctl start docker
# 建立 docker 用户组 (默认情况下，docker命令会使用Unix socket与Docker引擎通讯。而只有 `root` 用户和 `docker` 组的用户才可以访问 Docker 引擎的 Unix socket)
sudo groupadd docker # 建立 `docker` 组：
sudo usermod -aG docker $USER # 将当前用户加入 `docker` 组
# 退出当前终端并重新登录，测试安装是否成功
docker run hello-world
```

### 1.2 常用指令

```bash
## 1. 拉取镜像
docker images # 显示本地已下载镜像
docker search [] # 搜索可用镜像
docker pull [imagename:tag] # 拉取镜像

## 2. 创建容器
docker ps # 显示正在运行的容器
docker ps -a # 显示所有创建过的容器
docker run -it [image:tag] /bin/bash # 运行一次自动关闭
docker run --name [cname] -it [image:tag] /bin/bash # 创建指定名称的容器(方便下次进入)
# 现在打开另一个终端 docker ps 发现有一个容器在运行, 
docker inspect ws # 不关闭，查看容器信息
# 使用 ctrl-pq 或 exit 退出容器，但不会关闭

## 3. 再次启动并进入容器
docker exec -it ws /bin/bash # 可以再次回到正在运行的容器
docker container start [cname] # 如果已经关闭，将一个已经终止的容器启动运行

## 4. 容器相关操作
docker cp orders.txt [containername]:/order.txt
docker cp [containername]:/oreders.txt order.txt

## 5. 容器镜像、关闭移除
docker container stop ws # 关闭正在运行的容器
docker rm [containername] # 移除容器
docker stop $(docker ps -a -q) # ！停止所有容器
docker rm $(docker ps -a -q) # !! 移除所有容器 ！！
docker rmi [image] # !!! 移除镜像 !!!

## 资源使用监控
 docker stats
```

**注意事项：**
  - 容器不是镜像，多次退出后即使使用一样的命令，你会创建多个容器（进程），即使已经关闭也会存在，可用 docker ps -a 查看所有创建过的容器
  - 因此为了避免重复创建，创建是要指定名字，并且退出后用exec再次进入容器

**docker run Options**
  - --name: container name
  - -d: run container in background mode
  - --rm: remove when it exits
  - -v: volume mount
  - -p: port forwarding (-P: open all)
  - -e: set environment in container
  - -t: terminal
  - -i: STDIN open (-ti: -t -i)
  - -u: set user UID
  - -w: working directory in container
  - -m: memory limit
  - --cpuset-cpus: limit cpus to run
  - --add-host: custom host:ip setting
  - --privileged: open kernel functions

## 2. Docker 实践
**实践准则：**
  1. 首先要明确镜像的概念，镜像是一个安装了必备软件的操作系统，仅提供最基础的服务，不要老想着去怎么去修改镜像，只需要使用镜像即可
     - 比如使用tensorflow镜像，每次我只需要使用此镜像创建一个容器（进程），就有了一个新的tensorflow环境
     - 容器也不是随意创建的，创建了一个只要不换电脑（不删除此容器）就可以一直使用
     - 对于文件的创建和修改，我可以挂载本地目录，这样文件在本地，容器虚拟，镜像始终不变
  2. 对于ROS类的任务，容器用作调试环境，我需要的其他任务可以写到本地，然后拷贝/挂载本地目录到容器，然后在容器内运行
     - 只要不删除此容器，你的调试环境将始终存在
     - 这里我们使用的原始镜像对应于我们之前拿到新电脑后安装的Ubuntu和ROS，然后我们的容器就对应于我们在新系统内进行创建包，新安装配置等操作
  3. 如果为了保险起见，防止对原始镜像的修改，可以使用容器的导出与导入来生成新的测试镜像，然后推送到仓库保存
  4. 如果基础镜像实在不好，有问题或不符合自己的使用要求，那就把可以在之前调试的基础上，从零开始重新用 dockerfile 构建基础镜像
     - 确保只包含最基础的服务，不要执行特定任务--比如CMD 指令）

### 2.1 基础概念
Docker 包括三个基本概念 镜像（`Image`）、容器（`Container`）以及仓库（`Repository`），理解了这三个概念，就理解了 Docker 的整个生命周期。

**Docker 镜像**   
我们都知道，操作系统分为内核和用户空间。对于 Linux 而言，内核启动后，会挂载 `root` 文件系统为其提供用户空间支持
  - Docker 镜像（Image），就相当于是一个 `root` 文件系统。比如官方镜像 `ubuntu:18.04` 就包含了完整的一套 Ubuntu 18.04 最小系统的 `root` 文件系统。
  - Docker 镜像是一个特殊的文件系统，除了提供容器运行时所需的程序、库、资源、配置等文件外，还包含了一些为运行时准备的一些配置参数（如匿名卷、环境变量、用户等）
  - 镜像不包含任何动态数据，其内容在构建之后也不会被改变

**Docker 容器**  
镜像（`Image`）和容器（`Container`）的关系，就像是面向对象程序设计中的 `类` 和 `实例` 一样，镜像是静态的定义，容器是镜像运行时的实体。容器可以被创建、启动、停止、删除、暂停等
  - 容器的实质是进程，但与直接在宿主执行的进程不同，容器进程运行于属于自己的独立的 [命名空间](https://en.wikipedia.org/wiki/Linux_namespaces)
  - 因此容器可以拥有自己的 `root` 文件系统、自己的网络配置、自己的进程空间，甚至自己的用户 ID 空间
  - 容器内的进程是运行在一个隔离的环境里，使用起来，就好像是在一个独立于宿主的系统下操作一样。这种特性使得容器封装的应用比直接在宿主运行更加安全。也因为这种隔离的特性，很多人初学 Docker 时常常会混淆容器和虚拟机。

镜像使用的是分层存储，容器也是如此。每一个容器运行时，是以镜像为基础层，在其上创建一个当前容器的存储层，我们可以称这个为容器运行时读写而准备的存储层为 容器存储层
  - 容器存储层的生存周期和容器一样，容器消亡时，容器存储层也随之消亡。因此，任何保存于容器存储层的信息都会随容器删除而丢失
  - 因此，容器不应该向其存储层内写入任何数据，容器存储层要保持无状态化
  - 所有的文件写入操作，都应该使用 [数据卷（Volume）](https://yeasy.gitbooks.io/docker_practice/content/data_management/volume.html)、或者绑定宿主目录，在这些位置的读写会跳过容器存储层，直接对宿主（或网络存储）发生读写，其性能和稳定性更高

数据卷的生存周期独立于容器，容器消亡，数据卷不会消亡。因此，使用数据卷后，容器删除或者重新运行之后，数据却不会丢失。

**Docker Registry**  
镜像构建完成后，可以很容易的在当前宿主机上运行，但是，如果需要在其它服务器上使用这个镜像，我们就需要一个集中的存储、分发镜像的服务，[Docker Registry](https://yeasy.gitbooks.io/docker_practice/content/repository/registry.html) 就是这样的服务
  - 一个 Docker Registry 中可以包含多个 仓库（`Repository`），每个仓库可以包含多个标签（`Tag`），每个标签对应一个镜像
  - 通常，一个仓库会包含同一个软件不同版本的镜像，而标签就常用于对应该软件的各个版本。我们可以通过 `<仓库名>:<标签>` 的格式来指定具体是这个软件哪个版本的镜像。如果不给出标签，将以 `latest` 作为默认标签。
  - 以 [Ubuntu 镜像](https://hub.docker.com/_/ubuntu) 为例，`ubuntu` 是仓库的名字，其内包含有不同的版本标签，如，`16.04`, `18.04`。我们可以通过 `ubuntu:14.04`，或者 `ubuntu:18.04` 来具体指定所需哪个版本的镜像。如果忽略了标签，比如 `ubuntu`，那将视为 `ubuntu:latest`
  - 仓库名经常以 *两段式路径* 形式出现，比如 `jwilder/nginx-proxy`，前者往往意味着 Docker Registry 多用户环境下的用户名，后者则往往是对应的软件名

Docker Registry 公开服务是开放给用户使用、允许用户管理镜像的 Registry 服务。一般这类公开服务允许用户免费上传、下载公开的镜像，并可能提供收费服务供用户管理私有镜像。
  - 最常使用的 Registry 公开服务是官方的 [Docker Hub](https://hub.docker.com/)，这也是默认的 Registry，并拥有大量的高质量的官方镜像。

### 2.2 使用 Docker 镜像
在之前的介绍中，我们知道镜像是 Docker 的三大组件之一。Docker 运行容器前需要本地存在对应的镜像，如果本地不存在该镜像，Docker 会从镜像仓库下载该镜像
  - [Docker Hub](https://hub.docker.com/explore/) 上有大量的高质量的镜像可以用，从 Docker 镜像仓库获取镜像的命令是 `docker pull`
  - 具体的选项可以通过 `docker pull --help` 命令看到
  - Docker 镜像仓库地址：地址的格式一般是 `<域名/IP>[:端口号]`，默认地址是 Docker Hub。
  - 仓库名：如之前所说，这里的仓库名是两段式名称，即 `<用户名>/<软件名>`。对于 Docker Hub，如果不给出用户名，则默认为 `library`，也就是官方镜像

```bash
# 拉取镜像 docker pull [选项] [Docker Registry 地址[:端口号]/]仓库名[:标签]
docker pull ubuntu:18.04 
# 显示镜像
docker image ls # 列出已经下载下来的镜像
docker image ls ubuntu # 列出指定仓库的镜像
docker image ls -f since=mongo:3.2 # 版本过滤
docker image ls -f label=com.example.version=0.1
# 查看镜像、容器、数据卷所占用的空间
docker system df
# 删除本地镜像：docker image rm [选项] <镜像1> [<镜像2> ...]
docker image rm $(docker image ls -q redis) # 删除所有仓库名为 redis 的镜像
docker image rm $(docker image ls -q -f before=mongo:3.2) # 删除所有在mongo:3.2之前的镜像
```

### 2.3 利用 commit 理解镜像构成
回顾一下之前我们学到的知识，镜像是多层存储，每一层是在前一层的基础上进行的修改；而容器同样也是多层存储，是在以镜像为基础层，在其基础上加一层作为容器运行时的存储层
  - 因此，镜像是容器的基础，每次执行 `docker run` 的时候都会指定哪个镜像作为容器运行的基础
  - 在之前的例子中，我们所使用的都是来自于 Docker Hub 的镜像，直接使用这些镜像是可以满足一定的需求，而当这些镜像无法直接满足需求时，我们就需要定制这些镜像

现在让我们以定制一个 Web 服务器为例子，来讲解镜像是如何构建的：

1. 首先我们用 `nginx` 镜像启动一个容器，命名为 `webserver`，并且映射 80 端口，这样我们可以用浏览器去访问这个 `nginx` 服务器
   ```bash
   docker run --name webserver -d -p 80:80 nginx
   ```
   - 如果是在 Linux 本机运行的 Docker，或者如果使用的是 Docker for Mac、Docker for Windows，那么可以直接访问：http://localhost
   - 如果使用的是 Docker Toolbox，或者是在虚拟机、云服务器上安装的 Docker，则需要将 `localhost` 换为虚拟机地址或者实际云服务器地址
   - 直接用浏览器访问的话，我们会看到默认的 Nginx 欢迎页面。

2. 现在，假设我们非常不喜欢这个欢迎页面，我们希望改成欢迎 Docker 的文字，我们可以使用 `docker exec` 命令进入容器，修改其内容
   ```bash
   $ docker exec -it webserver bash
   root@3729b97e8226:/# echo '<h1>Hello, Docker!</h1>' > /usr/share/nginx/html/index.html
   root@3729b97e8226:/# exit
   exit
   ```
   - 我们以交互式终端方式进入 `webserver` 容器，并执行了 `bash` 命令，也就是获得一个可操作的 Shell
   - 然后，我们用 `<h1>Hello, Docker!</h1>` 覆盖了 `/usr/share/nginx/html/index.html` 的内容
   - 现在我们再刷新浏览器的话，会发现内容被改变了。
   - 在上述操作中，我们修改了容器的文件，也就是改动了容器的存储层，我们可以通过 `docker diff webserver` 命令看到具体的改动

3. 现在我们定制好了变化，我们希望能将其保存下来形成镜像：
   - 当我们运行一个容器的时候（如果不使用卷的话），我们做的任何文件修改都会被记录于容器存储层里
   - 而 Docker 提供了一个 `docker commit` 命令，可以将容器的存储层保存下来成为镜像
   - 换句话说，就是在原有镜像的基础上，再叠加上容器的存储层，并构成新的镜像。以后我们运行这个新镜像的时候，就会拥有原有容器最后的文件变化
   ```bash
    # docker commit 的语法格式: docker commit [选项] <容器ID或容器名> [<仓库名>[:<标签>]]
    # 将当前容器内容保存下来成为镜像：
    docker commit \
    --author "Tao Wang <twang2218@gmail.com>" \
    --message "修改了默认网页" \
    webserver \
    nginx:v2
    # 查看新定制的镜像
    docker image ls
    # 查看镜像内的历史记录
    docker history nginx:v2
   ```

4. 新的镜像定制好后，我们可以来运行这个镜像
   ```bash
   docker run --name web2 -d -p 81:80 nginx:v2
   ```
   - 这里我们命名为新的服务为 `web2`，并且映射到 `81` 端口
   - 如果是 Docker for Mac/Windows 或 Linux 桌面的话，我们就可以直接访问 http://localhost:81看到结果，其内容应该和之前修改后的 `webserver` 一样。

5. 至此，我们第一次完成了定制镜像，使用的是 `docker commit` 命令，手动操作给旧的镜像添加了新的一层，形成新的镜像，对镜像多层存储应该有了更直观的感觉

**！！！慎用 docker commit！！！**  
注意，使用 `docker commit` 命令虽然可以比较直观的帮助理解镜像分层存储的概念，但是实际环境中并不会这样使用：
  - 首先，如果仔细观察之前的 `docker diff webserver` 的结果，你会发现除了真正想要修改的 `/usr/share/nginx/html/index.html` 文件外，由于命令的执行，还有很多文件被改动或添加了
  - 这还仅仅是最简单的操作，如果是安装软件包、编译构建，那会有大量的无关内容被添加进来，如果不小心清理，将会导致镜像极为臃肿
  - 此外，使用 `docker commit` 意味着所有对镜像的操作都是黑箱操作，生成的镜像也被称为黑箱镜像，换句话说，就是除了制作镜像的人知道执行过什么命令、怎么生成的镜像，别人根本无从得知。而且，即使是这个制作镜像的人，过一段时间后也无法记清具体在操作的
  - 虽然 `docker diff` 或许可以告诉得到一些线索，但是远远不到可以确保生成一致镜像的地步。这种黑箱镜像的维护工作是非常痛苦的。
  - 而且，回顾之前提及的镜像所使用的分层存储的概念，除当前层外，之前的每一层都是不会发生改变的，换句话说，任何修改的结果仅仅是在当前层进行标记、添加、修改，而不会改动上一层。如果使用 `docker commit` 制作镜像，以及后期修改的话，每一次修改都会让镜像更加臃肿一次，所删除的上一层的东西并不会丢失，会一直如影随形的跟着这个镜像，即使根本无法访问到，这会让镜像更加臃肿。

总的来讲，`docker commit` 命令除了学习之外，还有一些特殊的应用场合，比如被入侵后保存现场等。但是，不要使用 `docker commit` 定制镜像，定制镜像应该使用 `Dockerfile` 来完成

### 2.4 使用 Dockerfile 定制镜像
从刚才的 `docker commit` 的学习中，我们可以了解到，镜像的定制实际上就是定制每一层所添加的配置、文件。如果我们可以把每一层修改、安装、构建、操作的命令都写入一个脚本，用这个脚本来构建、定制镜像，那么之前提及的无法重复的问题、镜像构建透明性的问题、体积的问题就都会解决。这个脚本就是 Dockerfile。

Dockerfile 是一个文本文件，其内包含了一条条的 指令(Instruction)，每一条指令构建一层，因此每一条指令的内容，就是描述该层应当如何构建。

还以之前定制 `nginx` 镜像为例，这次我们使用 Dockerfile 来定制:

1. 首先在一个空白目录中，建立一个文本文件，并命名为 `Dockerfile`，这个 Dockerfile 很简单，一共就两行。涉及到了两条指令，`FROM` 和 `RUN`，其内容为：
   ```dockerfile
   FROM nginx
   RUN echo '<h1>Hello, Docker!</h1>' > /usr/share/nginx/html/index.html
   ```

**FROM 指定基础镜像**  
所谓定制镜像，那一定是以一个镜像为基础，在其上进行定制。就像我们之前运行了一个 `nginx` 镜像的容器，再进行修改一样，基础镜像是必须指定的。而 `FROM` 就是指定基础镜像
  - 因此一个 `Dockerfile` 中 `FROM` 是必备的指令，并且必须是第一条指令
  - 如果没有找到对应服务的镜像，官方镜像中还提供了一些更为基础的操作系统镜像，如 [`ubuntu`](https://hub.docker.com/_/ubuntu/)、[`debian`](https://hub.docker.com/_/debian/)、[`centos`](https://hub.docker.com/_/centos/)、[`fedora`](https://hub.docker.com/_/fedora/)、[`alpine`](https://hub.docker.com/_/alpine/) 等，这些操作系统的软件库为我们提供了更广阔的扩展空间
  - 除了选择现有镜像为基础镜像外，Docker 还存在一个特殊的镜像，名为 `scratch`。这个镜像是虚拟的概念，并不实际存在，它表示一个空白的镜像。如果你以 `scratch` 为基础镜像的话，意味着你不以任何镜像为基础，接下来所写的指令将作为镜像第一层开始存在。

**RUN 执行命令**  
`RUN` 指令是用来执行命令行命令的。由于命令行的强大能力，`RUN` 指令在定制镜像时是最常用的指令之一。其格式有两种：
  - *shell* 格式：`RUN <命令>`，就像直接在命令行中输入的命令一样。刚才写的 Dockerfile 中的 `RUN` 指令就是这种格式
  - *exec* 格式：`RUN ["可执行文件", "参数1", "参数2"]`，这更像是函数调用中的格式。

既然 `RUN` 就像 Shell 脚本一样可以执行命令，那么我们是否就可以像 Shell 脚本一样把每个命令对应一个 RUN 呢？比如这样：
   ```dockerfile
   FROM debian:stretch

   RUN apt-get update
   RUN apt-get install -y gcc libc6-dev make wget
   RUN wget -O redis.tar.gz "http://download.redis.io/releases/redis-5.0.3.tar.gz"
   RUN mkdir -p /usr/src/redis
   RUN tar -xzf redis.tar.gz -C /usr/src/redis --strip-components=1
   RUN make -C /usr/src/redis
   RUN make -C /usr/src/redis install
   ```

  - 之前说过，Dockerfile 中每一个指令都会建立一层，`RUN` 也不例外。每一个 `RUN` 的行为，就和刚才我们手工建立镜像的过程一样：新建立一层，在其上执行这些命令，执行结束后，`commit` 这一层的修改，构成新的镜像
  - 而上面的这种写法，创建了 7 层镜像。这是完全没有意义的，而且很多运行时不需要的东西，都被装进了镜像里，比如编译环境、更新的软件包等等。结果就是产生非常臃肿、非常多层的镜像，不仅仅增加了构建部署的时间，也很容易出错。 这是很多初学 Docker 的人常犯的一个错误
  - Union FS 是有最大层数限制的，比如 AUFS，曾经是最大不得超过 42 层，现在是不得超过 127 层

上面的 `Dockerfile` 正确的写法应该是这样：
   ```dockerfile
   FROM debian:stretch

   RUN buildDeps='gcc libc6-dev make wget' \
       && apt-get update \
       && apt-get install -y $buildDeps \
       && wget -O redis.tar.gz "http://download.redis.io/releases/redis-5.0.3.tar.gz" \
       && mkdir -p /usr/src/redis \
       && tar -xzf redis.tar.gz -C /usr/src/redis --strip-components=1 \
       && make -C /usr/src/redis \
       && make -C /usr/src/redis install \
       && rm -rf /var/lib/apt/lists/* \
       && rm redis.tar.gz \
       && rm -r /usr/src/redis \
       && apt-get purge -y --auto-remove $buildDeps
   ```

  - 首先，之前所有的命令只有一个目的，就是编译、安装 redis 可执行文件。因此没有必要建立很多层，这只是一层的事情。
  - 因此，这里没有使用很多个 `RUN` 对一一对应不同的命令，而是仅仅使用一个 `RUN` 指令，并使用 `&&` 将各个所需命令串联起来。将之前的 7 层，简化为了 1 层。
  - 在撰写 Dockerfile 的时候，要经常提醒自己，这并不是在写 Shell 脚本，而是在定义每一层该如何构建。
  - 并且，这里为了格式化还进行了换行。Dockerfile 支持 Shell 类的行尾添加 `\` 的命令换行方式，以及行首 `#` 进行注释的格式。良好的格式，比如换行、缩进、注释等，会让维护、排障更为容易，这是一个比较好的习惯。
  - 此外，还可以看到这一组命令的最后添加了清理工作的命令，删除了为了编译构建所需要的软件，清理了所有下载、展开的文件，并且还清理了 `apt` 缓存文件。这是很重要的一步，我们之前说过，镜像是多层存储，每一层的东西并不会在下一层被删除，会一直跟随着镜像。因此镜像构建时，一定要确保每一层只添加真正需要添加的东西，任何无关的东西都应该清理掉。

很多人初学 Docker 制作出了很臃肿的镜像的原因之一，就是忘记了每一层构建的最后一定要清理掉无关文件。

**构建镜像**  

2. 我们再回到之前定制的 nginx 镜像的 Dockerfile 来。现在我们明白了这个 Dockerfile 的内容，那么让我们来构建这个镜像吧。在 `Dockerfile` 文件所在目录执行：
   ```bash
   docker build -t nginx:v3 .
   # Sending build context to Docker daemon 2.048 kB
   # Step 1 : FROM nginx
   #  ---> e43d811ce2f4
   # Step 2 : RUN echo '<h1>Hello, Docker!</h1>' > /usr/share/nginx/html/index.html
   #  ---> Running in 9cdc27646c7b
   #  ---> 44aa4490ce2c
   # Removing intermediate container 9cdc27646c7b
   # Successfully built 44aa4490ce2c
   ```
   - 从命令的输出结果中，我们可以清晰的看到镜像的构建过程。在 `Step 2` 中，如同我们之前所说的那样，`RUN` 指令启动了一个容器 `9cdc27646c7b`，执行了所要求的命令，并最后提交了这一层 `44aa4490ce2c`，随后删除了所用到的这个容器 `9cdc27646c7b`。

这里我们使用了 `docker build` 命令进行镜像构建。其格式为：`docker build [选项] <上下文路径/URL/->`
   - 在这里我们指定了最终镜像的名称 `-t nginx:v3`，构建成功后，我们可以像之前运行 `nginx:v2` 那样来运行这个镜像，其结果会和 `nginx:v2` 一样。

**镜像构建上下文（Context）**  
如果注意，会看到 `docker build` 命令最后有一个 `.`, `.` 表示当前目录，而 `Dockerfile` 就在当前目录，因此不少初学者以为这个路径是在指定 `Dockerfile` 所在路径，这么理解其实是不准确的。如果对应上面的命令格式，你可能会发现，这是在指定**上下文路径**。那么什么是上下文呢？
  - 首先我们要理解 `docker build` 的工作原理。Docker 在运行时分为 Docker 引擎（也就是服务端守护进程）和客户端工具。Docker 的引擎提供了一组 REST API，被称为 [Docker Remote API](https://docs.docker.com/develop/sdk/)，而如 `docker` 命令这样的客户端工具，则是通过这组 API 与 Docker 引擎交互，从而完成各种功能。因此，虽然表面上我们好像是在本机执行各种 `docker` 功能，但实际上，一切都是使用的远程调用形式在服务端（Docker 引擎）完成。也因为这种 C/S 设计，让我们操作远程服务器的 Docker 引擎变得轻而易举
  - 当我们进行镜像构建的时候，并非所有定制都会通过 `RUN` 指令完成，经常会需要将一些本地文件复制进镜像，比如通过 `COPY` 指令、`ADD` 指令等。而 `docker build` 命令构建镜像，其实并非在本地构建，而是在服务端，也就是 Docker 引擎中构建的。那么在这种客户端/服务端的架构中，如何才能让服务端获得本地文件呢？
  - 这就引入了上下文的概念。当构建的时候，用户会指定构建镜像上下文的路径，`docker build` 命令得知这个路径后，会将路径下的所有内容打包，然后上传给 Docker 引擎。这样 Docker 引擎收到这个上下文包后，展开就会获得构建镜像所需的一切文件。

如果在 `Dockerfile` 中这么写：
   ```Dockerfile
   COPY ./package.json /app/
   ```

这并不是要复制执行 `docker build` 命令所在的目录下的 `package.json`，也不是复制 `Dockerfile` 所在目录下的 `package.json`，而是复制 **上下文（context）** 目录下的 `package.json`
  - 因此，`COPY` 这类指令中的源文件的路径都是*相对路径*。这也是初学者经常会问的为什么 `COPY ../package.json /app` 或者 `COPY /opt/xxxx /app` 无法工作的原因，因为这些路径已经超出了上下文的范围，Docker 引擎无法获得这些位置的文件。如果真的需要那些文件，应该将它们复制到上下文目录中去。
  - 现在就可以理解刚才的命令 `docker build -t nginx:v3 .` 中的这个 `.`，实际上是在指定上下文的目录，`docker build` 命令会将该目录下的内容打包交给 Docker 引擎以帮助构建镜像。
  - 如果观察 `docker build` 输出，我们其实已经看到了这个发送上下文的过程：`Sending build context to Docker daemon 2.048 kB`

理解构建上下文对于镜像构建是很重要的，避免犯一些不应该的错误。比如有些初学者在发现 `COPY /opt/xxxx /app` 不工作后，于是干脆将 `Dockerfile` 放到了硬盘根目录去构建，结果发现 `docker build` 执行后，在发送一个几十 GB 的东西，极为缓慢而且很容易构建失败。那是因为这种做法是在让 `docker build` 打包整个硬盘，这显然是使用错误
  - 一般来说，应该会将 `Dockerfile` 置于一个空目录下，或者项目根目录下。如果该目录下没有所需文件，那么应该把所需文件复制一份过来
  - 如果目录下有些东西确实不希望构建时传给 Docker 引擎，那么可以用 `.gitignore` 一样的语法写一个 `.dockerignore`，该文件是用于剔除不需要作为上下文传递给 Docker 引擎的
  - 那么为什么会有人误以为 `.` 是指定 `Dockerfile` 所在目录呢？这是因为在默认情况下，如果不额外指定 `Dockerfile` 的话，会将上下文目录下的名为 `Dockerfile` 的文件作为 Dockerfile。
  - 这只是默认行为，实际上 `Dockerfile` 的文件名并不要求必须为 `Dockerfile`，而且并不要求必须位于上下文目录中，比如可以用 `-f ../Dockerfile.php` 参数指定某个文件作为 `Dockerfile`。

当然，一般大家习惯性的会使用默认的文件名 `Dockerfile`，以及会将其置于镜像构建上下文目录中。

**COPY 复制文件**  
和 `RUN` 指令一样，也有两种格式，一种类似于命令行，一种类似于函数调用：
  - `COPY [--chown=<user>:<group>] <源路径>... <目标路径>`
  - `COPY [--chown=<user>:<group>] ["<源路径1>",... "<目标路径>"]`

`COPY` 指令将从构建上下文目录中 `<源路径>` 的文件/目录复制到新的一层的镜像内的 `<目标路径>` 位置。比如：
   ```Dockerfile
   COPY package.json /usr/src/app/
   ```

`<源路径>` 可以是多个，甚至可以是通配符，其通配符规则要满足 Go 的 [`filepath.Match`](https://golang.org/pkg/path/filepath/#Match) 规则，如：

```Dockerfile
COPY hom* /mydir/
COPY hom?.txt /mydir/
```

`<目标路径>` 可以是容器内的绝对路径，也可以是相对于工作目录的相对路径（工作目录可以用 `WORKDIR`指令来指定）。目标路径不需要事先创建，如果目录不存在会在复制文件前先行创建缺失目录
  - 此外，还需要注意一点，使用 `COPY` 指令，源文件的各种元数据都会保留。比如读、写、执行权限、文件变更时间等。这个特性对于镜像定制很有用。特别是构建相关文件都在使用 Git 进行管理的时候。
  - 在使用该指令的时候还可以加上 `--chown=<user>:<group>` 选项来改变文件的所属用户及所属组。

```Dockerfile
COPY --chown=55:mygroup files* /mydir/
COPY --chown=bin files* /mydir/
COPY --chown=1 files* /mydir/
COPY --chown=10:11 files* /mydir/
```

**ENV 设置环境变量**  
这个指令很简单，就是设置环境变量而已，无论是后面的其它指令，如 `RUN`，还是运行时的应用，都可以直接使用这里定义的环境变量。格式有两种：
  - `ENV <key> <value>`
  - `ENV <key1>=<value1> <key2>=<value2>...`
  - 
定义了环境变量，那么在后续的指令中，就可以使用这个环境变量。比如在官方 `node` 镜像 `Dockerfile`中，就有类似这样的代码：
```Dockerfile
ENV NODE_VERSION 7.2.0

RUN curl -SLO "https://nodejs.org/dist/v$NODE_VERSION/node-v$NODE_VERSION-linux-x64.tar.xz" \
  && curl -SLO "https://nodejs.org/dist/v$NODE_VERSION/SHASUMS256.txt.asc" \
  && gpg --batch --decrypt --output SHASUMS256.txt SHASUMS256.txt.asc \
  && grep " node-v$NODE_VERSION-linux-x64.tar.xz\$" SHASUMS256.txt | sha256sum -c - \
  && tar -xJf "node-v$NODE_VERSION-linux-x64.tar.xz" -C /usr/local --strip-components=1 \
  && rm "node-v$NODE_VERSION-linux-x64.tar.xz" SHASUMS256.txt.asc SHASUMS256.txt \
  && ln -s /usr/local/bin/node /usr/local/bin/nodejs
```
  - 在这里先定义了环境变量 `NODE_VERSION`，其后的 `RUN` 这层里，多次使用 `$NODE_VERSION` 来进行操作定制。可以看到，将来升级镜像构建版本的时候，只需要更新 `7.2.0` 即可，`Dockerfile` 构建维护变得更轻松了。
  - 下列指令可以支持环境变量展开： `ADD`、`COPY`、`ENV`、`EXPOSE`、`LABEL`、`USER`、`WORKDIR`、`VOLUME`、`STOPSIGNAL`、`ONBUILD`。

可以从这个指令列表里感觉到，环境变量可以使用的地方很多，很强大。通过环境变量，我们可以让一份 `Dockerfile` 制作更多的镜像，只需使用不同的环境变量即可。

**WORKDIR 指定工作目录**  
使用 `WORKDIR` 指令可以来指定工作目录（或者称为当前目录），以后各层的当前目录就被改为指定的目录，如该目录不存在，`WORKDIR` 会帮你建立目录。格式为 `WORKDIR <工作目录路径>`。

之前提到一些初学者常犯的错误是把 `Dockerfile` 等同于 Shell 脚本来书写，这种错误的理解还可能会导致出现下面这样的错误：
   ```docker
   RUN cd /app
   RUN echo "hello" > world.txt
  ```
   - 如果将这个 `Dockerfile` 进行构建镜像运行后，会发现找不到 `/app/world.txt` 文件，或者其内容不是 `hello`。原因其实很简单，在 Shell 中，连续两行是同一个进程执行环境，因此前一个命令修改的内存状态，会直接影响后一个命令
   - 而在 `Dockerfile` 中，这两行 `RUN` 命令的执行环境根本不同，是两个完全不同的容器。这就是对 `Dockerfile` 构建分层存储的概念不了解所导致的错误。

之前说过每一个 `RUN` 都是启动一个容器、执行命令、然后提交存储层文件变更。第一层 `RUN cd /app` 的执行仅仅是当前进程的工作目录变更，一个内存上的变化而已，其结果不会造成任何文件变更。而到第二层的时候，启动的是一个全新的容器，跟第一层的容器更完全没关系，自然不可能继承前一层构建过程中的内存变化。

因此如果需要改变以后各层的工作目录的位置，那么应该使用 `WORKDIR` 指令。


### 2.5 操作 Docker 容器
简单的说，容器是独立运行的一个或一组应用，以及它们的运行态环境。对应的，虚拟机可以理解为模拟运行的一整套操作系统（提供了运行态环境和其他系统环境）和跑在上面的应用。

```bash
## 启动容器
# 可以基于镜像新建一个容器启动，亦可将终止状态的容器重新启动
docker run -it --rm ubuntu:18.04 /bin/bash # `-it`：这是两个参数，`-t` 选项让Docker分配一个伪终端（pseudo-tty）并绑定到容器的标准输入上， `-i` 则让容器的标准输入保持打开。`--rm`：这个参数是说容器退出后随之将其删除。默认情况下，为了排障需求，退出的容器并不会立即删除，除非手动 `docker rm`。我们这里只是随便执行个命令，看看结果，不需要排障和保留结果，因此使用 `--rm` 可以避免浪费空间

## 终止容器 
docker container stop # 来终止一个运行中的容器
# 当 Docker 容器中指定的应用终结时，容器也会自动终止
# 例如对于上一章节中只启动了一个终端的容器，用户通过 `exit` 命令或 `Ctrl+d` 来退出终端时，所创建的容器立刻终止
docker container ls -a # 查看终止状态的容器
docker ps -a
docker container start # 重新启动处于终止状态的容器
docker container restart # 将一个运行态的容器终止，然后再重新启动它。

## 进入容器：docker exec
# 在使用 `-d` 参数时，容器启动后会进入后台
# 只用 `-i` 参数时，由于没有分配伪终端，界面没有我们熟悉的 Linux 命令提示符，但命令执行结果仍然可以返回
# 当 `-i` `-t` 参数一起使用时，则可以看到我们熟悉的 Linux 命令提示符
docker run -dit ubuntu
docker container ls # 查看已经创建的容器
docker exec -it 69d1 bash # 根据容器id进入容器
# 如果从这个 stdin 中 exit，不会导致容器的停止
# 更多参数说明请使用 `docker exec --help` 查看

## 导出和导入容器
docker export 7691a814370e > ubuntu.tar # 导出容器快照到本地文件
cat ubuntu.tar | docker import - test/ubuntu:v1.0 # 从容器快照文件中再导入为镜像
docker import http://example.com/exampleimage.tgz example/imagerepo #也可以通过指定 URL 或者某个目录来导入

## 删除容器
docker container rm  trusting_newton # 如果要删除一个运行中的容器，可以添加 `-f` 参数。Docker 会发送 `SIGKILL` 信号给容器。

## 清理所有处于终止状态的容器
docker container prune # 用 `docker container ls -a` 命令可以查看所有已经创建的包括终止状态的容器，如果数量太多要一个个删除可能会很麻烦，用下面的命令可以清理掉所有处于终止状态的容器
```

### 2.6 访问仓库
仓库（`Repository`）是集中存放镜像的地方。一个容易混淆的概念是注册服务器（`Registry`）。实际上注册服务器是管理仓库的具体服务器，每个服务器上可以有多个仓库，而每个仓库下面有多个镜像。从这方面来说，仓库可以被认为是一个具体的项目或目录。例如对于仓库地址 `dl.dockerpool.com/ubuntu` 来说，`dl.dockerpool.com` 是注册服务器地址，`ubuntu` 是仓库名。大部分时候，并不需要严格区分这两者的概念。
  - 目前 Docker 官方维护了一个公共仓库 [Docker Hub](https://hub.docker.com/)，其中已经包括了数量超过 15,000 的镜像。大部分需求都可以通过在 Docker Hub 中直接下载镜像来实现。
  - 你可以在 [https://hub.docker.com](https://hub.docker.com/) 免费注册一个 Docker 账号。
  - 可以通过执行 `docker login` 命令交互式的输入用户名及密码来完成在命令行界面登录 Docker Hub。
  - 你可以通过 `docker logout` 退出登录。
  - 你可以通过 `docker search` 命令来查找官方仓库中的镜像，并利用 `docker pull` 命令来将它下载到本地
  - 用户也可以在登录后通过 `docker push` 命令来将自己的镜像推送到 Docker Hub。

```bash
docker tag ubuntu:18.04 username/ubuntu:18.04
docker image ls
docker push username/ubuntu:18.04
docker search username
```

**自动创建** 
自动创建（Automated Builds）功能对于需要经常升级镜像内程序来说，十分方便。有时候，用户创建了镜像，安装了某个软件，如果软件发布新版本则需要手动更新镜像。而自动创建允许用户通过 Docker Hub 指定跟踪一个目标网站（目前支持 [GitHub](https://github.com/) 或 [BitBucket](https://bitbucket.org/)）上的项目，一旦项目发生新的提交或者创建新的标签（tag），Docker Hub 会自动构建镜像并推送到 Docker Hub 中。要配置自动创建，包括如下的步骤：
   - 创建并登录 Docker Hub，以及目标网站；
   - 在目标网站中连接帐户到 Docker Hub；
   - 在 Docker Hub 中 [配置一个自动创建](https://registry.hub.docker.com/builds/add/)；
   - 选取一个目标网站中的项目（需要含 `Dockerfile`）和分支；
   - 指定 `Dockerfile` 的位置，并提交创建。

之后，可以在 Docker Hub 的 [自动创建页面](https://registry.hub.docker.com/builds/) 中跟踪每次创建的状态。


### 2.7 Docker 数据管理
这一章介绍如何在 Docker 内部以及容器之间管理数据，在容器中管理数据主要有两种方式：数据卷（Volumes）和 挂载主机目录 (Bind mounts)

**数据卷**  
数据卷是一个可供一个或多个容器使用的特殊目录，它绕过 UFS，可以提供很多有用的特性：
   - 数据卷可以在容器之间共享和重用
   - 对数据卷的修改会立马生效
   - 对数据卷的更新，不会影响镜像
   - 数据卷默认会一直存在，即使容器被删除

注意：数据卷的使用，类似于 Linux 下对目录或文件进行 mount，镜像中的被指定为挂载点的目录中的文件会隐藏掉，能显示看的是挂载的数据卷

```bash
## 创建一个数据卷
docker volume create my-vol

## 查看数据卷
docker volume inspect my-vol # 查看指定 `数据卷` 的信息
docker volume ls # 查看所有的 `数据卷`

## 启动一个挂载数据卷的容器
docker run -d -P \
    --name web \  # 创建一个名为 `web` 的容器
    # -v my-vol:/wepapp \
    --mount source=my-vol,target=/webapp \ # 加载一个 `数据卷` 到容器的 `/webapp` 目录
    training/webapp \
    python app.py
# 在一次 `docker run`中可以挂载多个 `数据卷`。
docker inspect web # 在主机里使用以下命令可以查看 `web` 容器的信息

## 删除数据卷
docker volume rm my-vol
docker volume prune # 无主的数据卷可能会占据很多空间，要清理请使用以下命令

## 挂载一个主机目录作为数据卷
#使用 `--mount` 标记可以指定挂载一个本地主机的目录到容器中去。
docker run -d -P \
    --name web \
    # -v /src/webapp:/opt/webapp \
    --mount type=bind,source=/src/webapp,target=/opt/webapp \
    training/webapp \
    python app.py
# 记录在容器输入过的命令
docker run --rm -it \
   # -v $HOME/.bash_history:/root/.bash_history \
   --mount type=bind,source=$HOME/.bash_history,target=/root/.bash_history \
   ubuntu:18.04 \
   bash
```


注意事项：
  - 数据卷是被设计用来持久化数据的，它的生命周期独立于容器，Docker 不会在容器被删除后自动删除数据卷，并且也不存在垃圾回收这样的机制来处理没有任何容器引用的数据卷。如果需要在删除容器的同时移除数据卷。可以在删除容器的时候使用 `docker rm -v` 这个命令。
  - mount命令加载主机的 `/src/webapp` 目录到容器的 `/opt/webapp`目录，这个功能在进行测试的时候十分方便，比如用户可以放置一些程序到本地目录中，来查看容器是否正常工作。本地目录的路径必须是绝对路径，以前使用 `-v` 参数时如果本地目录不存在 Docker 会自动为你创建一个文件夹，现在使用 `--mount`参数时如果本地目录不存在，Docker 会报错。
  - Docker 挂载主机目录的默认权限是 `读写`，用户也可以通过增加 `readonly` 指定为 `只读`。


## 3. Nvidia-Docker
docker一般都是使用基于CPU的应用，而如果是GPU的话，就需要安装特有的硬件环境，比如需要安装nvidia driver。所以docker容器并不直接支持Nvidia GPU。为了解决这个问题，最早的处理办法是在容器内部，全部重新安装nvidia driver，然后通过设置相应的设备参数来启动container，然而这种办法是很脆弱的。因为宿主机的driver的版本必须完全匹配容器内的driver版本，这样导致docker image无法共享，很可能本地机器的不一致导致每台机器都需要去重复操作，这很大的违背了docker的设计之初。
  - 为了使docker image能很便利的使用Nvidia GPU，从而产生了nvidia-docker，由它来制作nvidia driver的image，这就要求在目标机器上启动container时，确保字符设备以及驱动文件已经被挂载。
  - nvidia-docker是一个可以使用GPU的docker，nvidia-docker是在docker上做了一层封装，通过nvidia-docker-plugin，然后调用到docker上，其最终实现的还是在docker的启动命令上携带一些必要的参数。因此在安装nvidia-docker之前，还是需要安装docker的
  - nvidia-docker-plugin是一个docker plugin，被用来帮助我们轻松部署container到GPU混合的环境下。类似一个守护进程，发现宿主机驱动文件以及GPU 设备，并且将这些挂载到来自docker守护进程的请求中。以此来支持docker GPU的使用

### 3.1 快速入门
安装教程：
  - https://github.com/NVIDIA/nvidia-docker/wiki/Installation-(version-1.0)
  - https://github.com/NVIDIA/nvidia-docker


**常用指令**
```bash
# To use GPU, use once when launch container.
# Enables NVIDIA GPU use from containers
nvidia-docker run --rm nvidia/caffe nvidia-smi

# use once when container create initially
# Enables GPU selection (with NV_GPU option)
NV_GPU=1,3 nvidia-docker run --rm nvidia/caffe nvidia-smi

nvidia-docker run --rm nvidia/cuda:8.0-cudnn6-devel-ubuntu16.04 nvidia-smi topo -m

# CUDA
nvidia-docker run --rm -ti –u $(id –u):$(id –g) --name cuda \
nvcr.io/nvidia/cuda:8.0-cudnn6-devel-ubuntu16.04 nvidia-smi

#Caffe
nvidia-docker run --rm -ti –u $(id –u):$(id –g) --name caffe
-v $(pwd):/workspace
nvcr.io/nvidia/caffe:17.06 caffe train --solver=solver.prototxt

#Tensorflow
nvidia-docker run --rm -ti –u $(id –u):$(id –g) --name tensorflow \
-p 8888:8888 -p 6006:6006 -v $(pwd):/workspace \
nvcr.io/nvidia/tensorflow:17.06 python train.py

# Digits
nvidia-docker run -d –u $(id –u):$(id –g) --name digits \
--shm-size=1g --ulimit memlock=-1 --ulimit stack=67108864
-p 5000:5000 -v /mnt/dataset:/data -v /mnt/digit-work:/workspace \
nvcr.io/nvidia/digits:17.06

## Using tensorflofw with docker
docker run -it -p 8888:8888 tensorflow/tensorflow
docker run -it --rm --name tf -v ~/mywork:/notebooks -p 8888:8888 -p 6006:6006 tensorflow/tensorflow
# --rm 退出容器后即删除
# -v 和容器共享主机上的文件夹（~/mywork）
# 6006 tensorboard
# 本地文件夹如果不存在也会自动创建，你再容器内创建的文件也会保存在本地

# 不要关闭上面得容器，在另一个终端内查看tensorboard
docker exec -it tf tensorboard --logdir tf_logs/

## jupyter notebook for datascience-notebook
docker run -it --rm --name ds -p 8888:8888 jupyter/datascience-notebook
# 进入命令行交互界面 -- 等价于你在本地打开jupyter后再新开一个终端进行相关安装/查看本地文件等操作
docker exec -it ds /bin/bash

```
**相关资源** 
  - https://blog.csdn.net/u012465655/article/details/80485263
  - https://blog.csdn.net/ncloveqy/article/details/82944694
  - https://www.findhao.net/easycoding/2262
  - https://blog.csdn.net/qq_35254726/article/details/57083652
  - https://blog.csdn.net/sinat_26917383/article/details/78728215


## 4. Docker ROS

https://github.com/ruffsl/ros_docker_demos/tree/master/development
https://hub.docker.com/u/osrf


## 参考资料
  - [Book: Docker Practice](https://yeasy.gitbooks.io/docker_practice/content/)
  - [Video: Docker](https://space.bilibili.com/50902989/channel/detail?cid=119514)
  - [Video: Docker-ROS](https://space.bilibili.com/50902989/channel/detail?cid=119511)