# README

## 简述

项目的内容

- 南开大学古力老师的密码学上机作业；
- 作业的内容是分别用 C++ 实现了 `Classical`、`DES`、`AES`、`RSA`、`MD5` 这五个算法。

本项目的优势：

- 老师布置的作业是造轮子的工作，造的还是很标准的轮子，为什么不直接抄呢？
- 关于同学的代码：
  1. 往届流传的部分代码质量太低了，看得太难受了；
  2. 往届的代码是各个网络搜集的结果，代码风格不一致，看得也很难受；
- 关于标准库的代码：比如 `C++` 的 `openssl`、`python` 的 `hashlib`；标准库里面考虑的事情太多了，命名以及软件架构都太复杂了，不适合作为一个简单、为了阐述流程的作业；

## 文件结构

每个 LAB 都有四个子文件夹：

- `include`：动态链接库、静态链接库等对外暴露的接口头文件；

- `src`：不对外暴露结构的源文件；

- `lib`：编译结果的动态、静态链接库所在的文件夹；

- `bin`：项目的可执行二进制文件，**作业在这里**；

## 运行

### MAC OS

作者开发所用的操作系统，需要安装依赖：

```bash
# cmake 编译套件
$ brew install cmake

# 如果是 lab4 要需要安装大整数库
$ brew install gmp
```

直接编译即可：

```bash
$ cmake CMakeLists.txt

$ make
```

### Ubuntu

安装相关的编译组件：

```bash
$ sudo apt-get install cmake make clang
```

然后直接使用 cmake 编译即可：

```bash
$ cmake
```

对于 lab4，还需要额外安装大整数库：

```bash
$ apt-get install libgmp-dev
```

### Windows

如果在 Windows 上有 Mingw 的 bash 环境，可以直接使用 g++ 编译：

```bash
# lab2
$ g++ main.cpp src/Des.cpp -o ./bin/lab2

# lab3
$ g++ main.cpp src/Aes.cpp -o ./bin/lab3

# lab4
# 需要现在 mingw 的 GUI 内选择安装 gmp 大整数库
$ g++ main.cpp src/Rsa.cpp -lgmp -o ./bin/lab4

# lab5
$ g++ main.cpp src/Md5Hash.cpp -p ./bin/lab5
```

如果配置了 VisualStudio 的命令行工具 `cl`，也可以直接下载 Windows 的 cmake 然后直接编译：

```bash
$ cmake
```

