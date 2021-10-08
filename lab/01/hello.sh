#!/bin/bash
ls
echo "ls 命令显示完毕"
pwd
echo "pwd 命令显示完毕"
echo "Welocme, $LOGNAME! It's now $(date +%T)."
echo ""
echo "c: View month calendar"
echo "e: View a file"
echo "q: Exit"

echo "Input your choice:"
read choice

case $choice in
    c|C) echo "Month:"
        read month
        echo "Year"
        read year
        cal $month $year # 调用 cal 命令打印月历
    ;;
    e|E) echo "Viewing a file. Input file name:"
        read file
        if  [ -f $file ] ;
        then
            more $file
        else
            echo "This file doesn't exist."
            exit 1
        fi
    ;;
    q|Q)  echo "Bye!"
        exit 0
    ;;
    *) echo "Illegal choice '$choice'."
        exit 1
    ;;
esac  # end of cases

echo "The end!"
