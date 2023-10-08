cmake_minimum_required(VERSION 3.0)

project(GMLib LANGUAGES C)

# 设置字符集
if(MSVC)
    # 在MSVC中添加编译参数，设置默认编码utf-8
    add_compile_options(/source-charset:utf-8)
endif()

