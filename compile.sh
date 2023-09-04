#!/bin/bash

# 检查参数数量
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <source_file>"
    exit 1
fi

# 获取文件的绝对路径
file_path=$(realpath "$1")

# 获取目录路径
dir_path=$(dirname "$file_path")

# 获取文件名，不包括扩展名
filename=$(basename -- "$file_path")
base_name="${filename%.*}"

# 使用nvcc进行编译，将输出放在与输入相同的目录下
nvcc "$file_path" -o "$dir_path/$base_name" -lnvidia-ml