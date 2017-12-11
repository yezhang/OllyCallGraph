# 项目简介

## 配置 MFC 框架
1、使用官方指南配置好一个标准的 OllyDBG 插件。
2、移除 Dllmain 函数，使用MFC框架内置的函数。
3、在项目属性窗口后，配置如下宏定义。
WIN32
_WINDOWS
_DEBUG
_USRDLL
这四个编译宏定义，是从VS向导建立的 MFC DLL 项目属性中拷贝的。



