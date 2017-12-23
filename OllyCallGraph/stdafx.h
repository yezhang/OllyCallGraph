
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#include "targetver.h"

#ifndef _ATL_ALLOW_CHAR_UNSIGNED //由于ATL不支持/J编译选项，OllyDbg要求使用 /J 选项，所以使用该宏定义压制错误信息。
#define _ATL_ALLOW_CHAR_UNSIGNED
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持

#include <Plugin.h> //包含 OllyDbg v1.10 插件的头文件

#include <algorithm>
#include <list>
#include <stack>
#include <boost/property_tree/ptree.hpp>


#define OD_DELETE(x) {delete x; x = NULL;}






