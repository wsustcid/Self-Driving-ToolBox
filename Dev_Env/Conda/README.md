<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 0.0.0
 * @Date: 2022-04-07 10:51:56
 * @LastEditTime: 2022-04-07 10:51:56
-->
# Conda
Conda 是开源包（packages）和虚拟环境（environment）的管理系统。
  - **packages 管理：** 可以使用 conda 来安装、更新 、卸载工具包 ，并且它更关注于数据科学相关的工具包。在安装 anaconda 时就预先集成了像 Numpy、Scipy、 pandas、Scikit-learn 这些在数据分析中常用的包。
  - **虚拟环境管理：** 在conda中可以建立多个虚拟环境，用于隔离不同项目所需的不同版本的工具包，以防止版本上的冲突。对纠结于 Python 版本的同学们，我们也可以建立 Python2 和 Python3 两个环境，来分别运行不同版本的 Python 代码。


## 1. 常用命令
```bash
# 包安装和管理
conda install package_name
conda install numpy scipy pandas # 同时安装多个
conda install numpy=1.10 # 指定版本
conda remove package_name # 卸载
conda update package_name # 升级
conda list # 查看所有包
conda search search_term # 包检索

## 环境管理
conda config --set auto_activate_base false # 关闭终端自动激活环境
conda create -n env_name python=2.7 #默认的环境是base，创建一个新环境：
conda activate env_name # 激活相关环境
conda deactivate # 退出当前环境
conda env remove -n env_name # 删除环境
conda env list
# 当分享代码的时候，同时也需要将运行环境分享给大家 
conda env export > environment.yaml # 存储当前环境下的package信息
# 用YAML 文件来创建一摸一样的运行环境
conda env create -f environment.yaml

## conda 删除
rm -rf ~/miniconda
# 2. OPTIONAL: Edit ~/.bash_profile to remove the Miniconda directory from your PATH environment variable.
# 3. OPTIONAL: Remove the following hidden file and folders that may have been created in the home directory: .condarc file .conda directory .continuum directory By running: 
rm -rf ~/.condarc ~/.conda ~/.continuum
```

## 2. conda on mac
```bash
## Step 1: Xcode Command Line Tools
xcode-select --install

## Step2: Install Miniforge
Install miniforge for arm64 (Apple Silicon) from https://github.com/conda-forge/miniforge
conda config --set auto_activate_base false

## Step3: Create a virtual environment with python3.8
conda create --name venv python=3.8 # conda env remove -n ENV_NAME
conda activate venv # conda deactivate

## Step4: Install Tensorflow 2.5 and its dependencies
conda install -c apple tensorflow-deps
pip install tensorflow-macos
pip install tensorflow-metal

## Step5: Install Jupyter Notebook, Pandas
conda install -c conda-forge -y pandas jupyter

## pytorch
conda install -c pytorch pytorch torchvision
```



