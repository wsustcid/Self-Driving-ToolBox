- [Git 与 GitHub 简明教程](#git-与-github-简明教程)
  - [1. 安装与配置](#1-安装与配置)
    - [1.1 安装Git并注册Github账号](#11-安装git并注册github账号)
    - [1.2 创建本地秘钥并添加至GitHub](#12-创建本地秘钥并添加至github)
  - [2. 常用命令](#2-常用命令)
  - [3. 高级用法](#3-高级用法)
    - [3.1 github上传大文件](#31-github上传大文件)
    - [3.2 使用Github进行多人合作](#32-使用github进行多人合作)


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
