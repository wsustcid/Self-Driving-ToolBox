- [Git 与 GitHub 简明教程](#git-与-github-简明教程)
  - [1. 安装与配置](#1-安装与配置)
    - [1.1 安装Git并注册Github账号](#11-安装git并注册github账号)
    - [1.2 创建本地秘钥并添加至GitHub](#12-创建本地秘钥并添加至github)
  - [2. 常用命令](#2-常用命令)
  - [3. 高级用法](#3-高级用法)
    - [3.1 github上传大文件](#31-github上传大文件)
    - [3.2 使用Github进行多人合作](#32-使用github进行多人合作)
  - [附录:](#附录)
    - [版本控制规范](#版本控制规范)


# Git 与 GitHub 简明教程
## 1. 安装与配置
### 1.1 安装Git并注册Github账号
首先根据自己的系统情况安装git
  - Linux 自带git，因此不用安装
  - MacOs 在terminal中输入`git --version`查看是否已经安装，如果未安装，按照提示进行安装即可

然后需要注册GitHub账户以及创建仓库
  - github官网地址：https://github.com
  - 按照提示创建账户后，点集Create a New Repository，填好名称后Create，就创建了一个属于自己的github仓库

### 1.2 创建本地秘钥并添加至GitHub
Github提供了两种协议用于将本地仓库与远程仓库建立连接，分别是https和ssh。

1. 若使用https协议建立本地仓库与远程仓库的联系，创建过程较为简单，按照下面的命令即可，但每次pull, push都要输入密码
   ```bash
     # create a new repository on the command line
     echo "# CarSim" >> README.md
     git init
     git add README.md
     git commit -m "first commit"
     git remote add origin https://github.com/wsustcid/CarSim.git
     git push -u origin master
     # or push an existing repository from the command line
     git remote add origin https://github.com/wsustcid/CarSim.git
     git push -u origin master
     ```

2. 更为推荐的方式是使用ssh协议，通过配置公钥和私钥来实现绑定。
   - 使用ssh密钥, 创建时稍微麻烦一些，但省去每次都输密码
   - 公钥我们一般是给服务器的, 当我使用`git clone 别人的或自己的项目的时候，虽然都可以clone, 但push时那个服务器通过他绑定的公钥来匹配我的私钥，这个时候,如果匹配,则就可以正常push,如果不匹配,则失败，因此我们无法向别人的仓库push
  
   ```bash
   # 首先在本地创建`ssh key；`
   ssh-keygen -t rsa -C "your_email@youremail.com" # 你注册github账户使用的邮箱
   # 之后使用默认一路回车, 成功的话会在`~/`下生成`.ssh`文件夹 以及id_rsa.pub
   cd ~/.ssh
   cat id_rsa.pub # 复制里面的`key`
   # 回到github上，进入 Account Settings，选择SSH Keys，Add SSH Key,title随便填
   # 粘贴在你电脑上生成的key。
   # 为了验证是否成功，在git bash下输入：
   ssh -T git@github.com
   # 接下来设置username和email，免得每次commit时输入
   git config --global user.name "your name"
   git config --global user.email "your_email@youremail.com"
   # 此时在本地创建仓库并与远程仓库建立连接的方式为
   git init
   git add README.md
   git commit -m "first commit"
   git remote add origin git@github.com:wsustcid/CarSim.git
   git push -u origin master
   ```


## 2. 常用命令

```python
# 帮助命令
git help 
git add help

# 仓库初始化
git init
git init projectname

# 文件基本操作
git add filename
git add -u   # 编辑或删除的文件
git add -A   # 所有文件
git add -A . # 所有改变的文件
git add .    # 新文件和编辑文件（无删除文件）
git commit -m "message"

# 查看文件修改
git status
git diff <source_branch> <target_branch>

# 查看提交log
git log

# 忽略文件
touch .gitignore   # 创建文件
vim .gitignore     # 添加要忽略的文件

# 在本地目录与远程repository的关联与取消：
git remote add origin git@github.com:git_username/repository_name.git
git push -u origin master # master 可以是你想要推送的任何分支
git remote remove origin

# 分支操作
git clone -b devel https://github.com/xxx # 克隆指定分支到本地(默认克隆Head 指向的branch)

git branch branchname   # 创建分支
git checkout branchname # 切换分支
git push origin branchname # 推送本地更改至远程分支

git checkout master
git merge brancename # 合并branchname分支到目前所在的分支（本地已合并，但github并未合并）
git push  # 将本地合并推送到github master主分支（亦可手动操作 pull request）

git branch -d branchname # 删除分支-已合并的（github 未删除）
git branch -D branchname # 删除分支-未合并的 (github 未删除)

git branch -a # 查看所有分支
git push origin --delete brancename # 删除远程分支

git checkout commitID -b brancename # 从当前分支某个commit开始创建新分支
git push origin branchname

##  版本回退
# 0. 没有add,简单的想撤销已经做出的改动
git checkout -- <filename> # 会使用 HEAD 中的最新内容替换掉你的工作目录中的文件
# 1. 本地代码（或文件）已经add但是还未commit
git reset <file> # 或git reset 取消所有更改 
# 2. 本地已经commit了，但还未push
git reset HEAD # 如果后面什么都不跟的话 就是上一次add 里面的全部撤销了 
git reset HEAD XXX/XXX/XXX.java # 就是对某个文件进行撤销了
git reset id # 仅仅撤销刚才的commit,历史id之后所做的更改将会保留，你可以重新选择commit的文件
git reset --hard id # 这样会丢弃刚才commit时做的更改，真正回到历史id，工作区将没有要commit的文件
# 3. 要回退的commit的代码已经push到远程的个人分支，但还未merge到公共的repository 
git reset [commitID] # 回退
git push -f [commitID] # 强制更新你的远程库
# 4. 要回退的commit的代码已被merge到公共的repository
#对于最后一种情况，考虑到其他人的版本历史，使用git reset [commit]是不建议的，此时我们应该使用git revert [commit]改命令不会修改之前的提交历史，相当于对数据做了一次逆操作，然后再执行add，commit等命令。git revert与reset的区别是git revert会生成一个新的提交来撤销某次提交，此次提交之前的commit都会被保留，也就是说对于项目的版本历史来说是往前走的。而git reset 则是回到某次提交，类似于穿越时空。
```

## 3. 高级用法
### 3.1 github上传大文件

### 3.2 使用Github进行多人合作
当我们多人合作一个项目时，因为每个人的本地都会有一个项目，如果A在自己的本地做了修改并传至github，如果B也要修改的话，就要先把项目的最新版本从github上pull下来，然后在最新版本之上修改；但经常发生的情况是B不知道A做了修改，直接在自己的本地在老版本上修改，这样自己本地的版本与github版本就会发生冲突，一般需要手动合并冲突，比较麻烦
  - 我们这里使用分支来确保每人的修改都是独立进行的，这样可以在自己的分支上进行任意修改，修改完成后只需要将自己的分支合并到主分支上就可以了，一般不会发生冲突
  - 其实分支更广泛的用途是自己基于主分支开发出和多个完全不同的版本，主分支相当于自己的一个原始备份，自己开发失败后可以推导重来且不影响主分支，同时还能保证自己能接收主分支的更新，最后可以把在自己分支的测试成功的功能合并到主分支上
  - 比如我们比赛的代码首先有了一个基础版本的功能，但需要添加更多的模块，每人负责一个模块，如果大家都在主分支上修改，这样就乱套了，在大家测试成功之前基础功能也用不了，所以需要每人创建一个分支，各自干各自的，自己测试成功了，再往主分支上合并，这样保证主分支永远都是安全的

```python
## 1. 将想要参与的项目clone到本地
git clone git@github.com:USTC-LAB-411/Group-Meeting.git

## 2. 创建参与者分支
# 每个参与者独占一个分支，可以自由修改，不影响主分支文件
# 最后根据需求合并到主分支(master)
git branch ws
# 查看当前已经存在的分支
# 带*号的表示你当前处于的分支
git branch

## 3. 切换到自己的分支下，并进行相应文件修改
git checkout ws

## 4. 提交自己的修改
git add -u
git commit -m "ws test"
# 将自己的分支也push到github上，以便下次使用
git push orgin ws

## 5. 切换到master分支，并合并自己分支
git checkout master
git merge --no-ff -m "merge by ws" ws
# 推送到github
git push origin master

# 现在去github 项目页，可以看到branch下有了两个分支，且两个分支都是最新的内容；

## 6. 合并提交完成后及时切换回自己的分支，防止不小心在主分支上做改动
git branch ws

## 7.1 再次在自己的分支上进行文件修改操作
git add 
git commit 
git push origin ws
## 7.2 此时whz也在自己的分支上进行了修改操作，并推送到了主分支

## 8. 拉取最新的主分支，合并自己新的修改并推送
git checkout master
git pull # 更新了whz的修改
git merge --no-ff -m "merge test" ws
git push orgin master

## 返回步骤6，重复操作
```



## 附录:

### 版本控制规范
**软件版本阶段说明**
  - `Alpha版`: 此版本表示该软件在此阶段主要是以实现软件功能为主，通常只在软件开发者内部交流，一般而言，该版本软件的Bug较多，需要继续修改。
  - `Beta版`: 该版本相对于α版已有了很大的改进，消除了严重的错误，但还是存在着一些缺陷，需要经过多次测试来进一步消除，此版本主要的修改对像是软件的UI
  - `RC版`: 该版本已经相当成熟了，基本上不存在导致错误的BUG，与即将发行的正式版相差无几
  - `Release版`: 该版本意味“最终版本”，在前面版本的一系列测试版之后，终归会有一个正式版本，是最终交付用户使用的一个版本。该版本有时也称为标准版。一般情况下，`Release` 不会以单词形式出现在软件封面上，取而代之的是符号(R)。

**版本命名规范**  
软件版本号由四部分组成：第一个1为主版本号；第二个1为子版本号；第三个1为阶段版本号；第四部分为日期版本号加希腊字母版本号：希腊字母版本号共有5种，分别为：`base`、`alpha`、`beta`、`RC`、`release`。
  - 例如：1.1.1.051021_beta
  - 常规：完全的版本号定义，分三项：：<主版本号>.<次版本号>.<修订版本号>，如 1.0.0

**版本号定修改规则**  
   - `主版本号(1)`：当功能模块有较大的变动，比如增加多个模块或者整体架构发生变化。此版本号由项目决定是否修改。
   - `子版本号(1)`：当功能有一定的增加或变化，比如增加了对权限控制、增加自定义视图等功能。此版本号由项目决定是否修改。
   - `阶段版本号(1)`：一般是 Bug 修复或是一些小的变动，要经常发布修订版，时间间隔不限，修复一个严重的bug即可发布一个修订版。此版本号由项目经理决定是否修改。
   - `日期版本号(051021)`: 用于记录修改项目的当前日期，每天对项目的修改都需要更改日期版本号。此版本号由开发人员决定是否修改。
   - `希腊字母版本号(beta)`: 此版本号用于标注当前版本的软件处于哪个开发阶段，当软件进入到另一个阶段时需要修改此版本号。此版本号由项目决定是否修改。

**文件命名规范**  
文件名称由四部分组成：第一部分为项目名称，第二部分为文件的描述，第三部分为当前软件的版本号，第四部分为文件阶段标识加文件后缀，例如：项目外 包平台测试报告 `1.1.1.051021_beta_b.xls`，此文件为项目外包平台的测试报告文档，版本号为：`1.1.1.051021_beta`。

如果是同一版本同一阶段的文件修改过两次以上，则在阶段标识后面加以数字标识，每次修改数字加1，项目外包平台测试报告 `1.1.1.051021_beta_b1.xls`。

当有多人同时提交同一份文件时，可以在阶段标识的后面加入人名或缩写来区别，例如：项目外包平台测试报告 `1.1.1.051021_beta_b_LiuQi.xls`。当此文件再次提交时也可以在人名或人名缩写的后面加入序号来区别，例如：项目外包平台测试 报告 `1.1.1.051021_beta_b_LiuQi2.xls`。

**版本号的阶段标识**  
软件的每个版本中包括11个阶段，详细阶段描述如下：

| 阶段名称     | 阶段标识 |
| ------------ | -------- |
| 需求控制     | a        |
| 设计阶段     | b        |
| 编码阶段     | c        |
| 单元测试     | d        |
| 单元测试修改 | e        |
| 集成测试     | f        |
| 集成测试修改 | g        |
| 系统测试     | h        |
| 系统测试修改 | i        |
| 验收测试     | j        |
| 验收测试修改 | k        |

