[中文版](README_cn.md)
# FluxStore
## A small distributed file system    
FluxStore is a lightweight distributed file system designed for technical validation, experiments, and practice.   

## Development Progress
- [x] Stage1: Implement local file storage    
* - [x] Local file storage - Sequential Read   
* - [x] Local file storage - Overwrite Write  
* - [x] Local file storage - Delete  
* - [x] Local file indexing (in-memory and persisted to a JSON file)    
- [ ] Stage2: Client-Server Architecture  
- [ ] Stage3: Multi-node Distribution with Control Node  
- [ ] Stage4: Data Redundancy and Fault Tolerance  

## Build Instructions
```shell
mkdir cmake-build
cd cmake-build
cmake ..
make
```
## Using the Configuration File  
The configuration file path is `src/conf/FluxStore.conf`, When running the program, include the `--flagfile=src/conf/FluxStore.conf` option, as shown below:
```shell
[root@localhost cmake-build]# ./FluxStore upload Makefile --flagfile=src/conf/FluxStore.conf 
```

## Usage - Uploading Files
```shell
# Upload a file. This uploads the local Makefile to the specified FluxStore storage path, which defaults to /flux_store_data.
[root@localhost cmake-build]# ./FluxStore upload Makefile
Hello FluxStore
Uploading file: Makefile
# At this point, the Makefile has been written to /flux_store_data.
[root@localhost cmake-build]# ls -rlt /flux_store_data/
total 12
-rw-r--r--. 1 root root 11803 Sep 29 10:55 Makefile
```
The persistent file index now records the metadata for the Makefile:  
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

## Usage - Downloading Files
Note that Makefile is the filename in FluxStore, and ./Makefile_bak is the downloaded local filename.
```shell
[root@localhost cmake-build]# ./FluxStore download Makefile ./Makefile_bak
Hello FluxStore
Downloading file: Makefile to ./Makefile_bak
```

## Usage - Deleting Files
After deleting the Makefile from FluxStore, both /flux_store_data and file_index.json are cleaned up correctly, removing the file data and metadata.
```shell
[root@localhost cmake-build]# ./FluxStore delete Makefile
Hello FluxStore
Deleting file: Makefile
[root@localhost cmake-build]# ls -rlt /flux_store_data/
total 0
[root@localhost cmake-build]# cat file_index.json
null[root@localhost cmake-build]#
```