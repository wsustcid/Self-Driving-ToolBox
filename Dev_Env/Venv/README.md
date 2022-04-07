<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 0.0.0
 * @Date: 2022-04-07 10:54:10
 * @LastEditTime: 2022-04-07 10:54:10
-->
# Virtual Environment
相比于conda，比较轻量，适用于临时使用

## 1. 常用命令
```python
# 首先为需要使用的python版本安装对应的pip
#sudo apt-get install python-pip  #为python2 安装对应的pip
sudo apt-get install python3-pip #为python3 安装对应的pip
# 查看对应的pip是否已经安装正确，注意查看输出结果是否指向正确的python版本位置
python3 -m pip --version
# 使用pip安装相关包
pip3 install xxx # 注意，如果要给python2 安装，就使用 pip install; 二者是独立的
# 查看pip已经安装的包
pip3 list

# 安装virtualenv
#sudo apt-get install python-dev python-virtualenv   # for Python 2.7
sudo apt-get install python3-dev python-virtualenv # for Python 3.n

# 创建虚拟环境（以python3为例）
virtualenv --no-site-packages -p python3 venv
# 激活虚拟环境
source venv/bin/activate
# 退出虚拟环境
deactivate
```



