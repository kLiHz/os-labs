#!/bin/bash

read_dir() # 递归输出目录下的所有文件
{
    for file in `ls $1`         # 遍历指定目录下的所有文件
    do
        if [ -d $1"/"$file ]    # 判断是目录
        then
            read_dir $1"/"$file
        else
            echo $1"/"$file
            # ./a.out  $1"/"$file   # 可自定义可执行程序
        fi
    done
}

read_dir $1
