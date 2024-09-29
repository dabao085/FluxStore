# FluxStore
A small distributed file system    
一个小型的分布式文件系统，用于技术验证和实验，以及练手。    

## 开发进度
- [x] Stage1: 实现单机文件存储    
* - [x] 单机文件存储-顺序读   
* - [x] 单机文件存储-覆盖写  
* - [x] 单机文件存储-删除  
* - [x] 单机文件索引(内存和持久化到Json文件)    
- [ ] Stage2: 客户端-服务器架构  
- [ ] Stage3: 多节点分布与控制节点  
- [ ] Stage4: 数据冗余与容错  

## 编译方法
```shell
mkdir cmake-build
cd cmake-build
cmake ..
make
```
## 使用方法-上传文件
```shell
# 上传文件，将本地Makefile文件上传到FluxStore指定的存储路径，默认是/flux_store_data
[root@localhost cmake-build]# ./FluxStore upload Makefile
Hello FluxStore
Uploading file: Makefile
# 此时Makefile文件已经写入到/flux_store_data
[root@localhost cmake-build]# ls -rlt /flux_store_data/
total 12
-rw-r--r--. 1 root root 11803 Sep 29 10:55 Makefile
```
可以看到持久化的文件索引已经记录了Makefile的元数据信息  
```shell
[root@localhost cmake-build]# cat file_index.json
{
    "Makefile": {
        "creation_time": 1727578519,
        "file_path": "Makefile",
        "file_path_flux": "/flux_store_data/Makefile",
        "file_size": 11803,
        "modification_time": 1727578519
    }
}
```

## 使用方法-下载文件
注意Makefile是FluxStore里的文件名，./Makefile_bak是下载到本地的文件名
```shell
[root@localhost cmake-build]# ./FluxStore download Makefile ./Makefile_bak
Hello FluxStore
Downloading file: Makefile to ./Makefile_bak
```

## 使用方法-删除文件
可见从FluxStore里删除Makefile文件后，/flux_store_data和file_index.json都正确清理了数据和元数据
```shell
[root@localhost cmake-build]# ./FluxStore delete Makefile
Hello FluxStore
Deleting file: Makefile
[root@localhost cmake-build]# ls -rlt /flux_store_data/
total 0
[root@localhost cmake-build]# cat file_index.json
null[root@localhost cmake-build]#
```