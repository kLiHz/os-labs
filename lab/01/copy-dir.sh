#!/bin/bash

copy_dir() # 递归拷贝目录下的所有文件
{
    for file in `ls $1`         # 遍历指定目录下的所有文件
    do
        if [ -d $1"/"$file ]    # 判断是目录，则：
        then
            mkdir $2"/"$file    # 1. 在目标目录下创建同名目录
            copy_dir $1"/"$file # 2. 对这个目录执行递归的操作
        else
            # 如果不是目录，则拷贝该文件到对应目录下的同名文件
            cp $1"/"$file $2"/"$file
        fi
    done
}

copy_dir $1 $2
