<p align="center">
<a href="https://www.npmjs.com/package/easywin"><img src="https://img.shields.io/npm/v/easywin.svg" alt="npm package"></a>
</p>

[English](./README.md)

# easyWin

## 安装使用


```javascript
npm install easywin 
//or
yarn add easywin

//取QQ句柄演示
let {winuser}=require('easywin')
let hQQ = winuser._findWindowFuzzy("QQ");

//进程树获取演示
let {process} = require('easywin')
let tree = process._processTree();
//结构展示
{
  ExeFile: '[System Process]',
  Id: 0,
  children: {
    '4': { ExeFile: 'System', ParentId: 0, Id: 4, children: [Object] },
    '564': { ExeFile: 'csrss.exe', ParentId: 544, Id: 564 },
    '648': {
      ExeFile: 'wininit.exe',
      ParentId: 544,
      Id: 648,
      children: [Object]
    },
    '3824': {
      ExeFile: 'winlogon.exe',
      ParentId: 10952,
      Id: 3824,
      children: [Object]
    },
    '6360': { ExeFile: 'csrss.exe', ParentId: 10952, Id: 6360 },
    '10584': { ExeFile: 'jusched.exe', ParentId: 6764, Id: 10584 },
    '10856': {
      ExeFile: 'explorer.exe',
      ParentId: 9148,
      Id: 10856,
      children: [Object]
    }
  }
}
 */
```

模块内大写开头方法为原生调用，为适应JS部分函数做了返回调整。

'_'开头方法为包装完善功能后的方法。

当出现和C++调用歧义的地方，例如C++填写null.那么相应的在JS中要做出数值参数赋值0，字符串赋值""的操作

## 介绍
提供了node在windows环境下的窗口，进程相关的API。

>winuser下包含了常用的User32下的API。

>process提供了进程列表，进程树(由于进程操作依赖权限),进程操作可以使用windows下提供的命令行工具,tasklist或者wmic或者ps。

>draw提供了有关gdi的方法。主要为了实现spy++所开发。

>file提供了有关文件的方法。

## electron使用相关

暂无

## 方法总览
```javascript
{
  winuser: {
    GetDpiForWindow
    GetDpiForSystem
    FindWindowA
    FindWindowExA
    GetClientRect
    GetWindowRect
    UpdateWindow
    GetAncestor
    ClipCursor
    GetClipCursor
    GetCursorInfo
    ShowCursor
    SetWindowLongPtrA
    GetWindowLongPtrA
    SetLayeredWindowAttributes
    SetWindowPos
    GetLayeredWindowAttributes
    ShowWindow
    PostMessageA
    SendMessageA
    GetWindowText
    SetForegroundWindow
    WindowFromPoint
    IsWindow
    GetWindowInfo
    EnumWindows
    GetDesktopWindow
    GetLastError
    GetForegroundWindow
    EnumDesktopWindows
    GetWindowThreadProcessId
    IsWindowEnabled
    IsWindowVisible
    IsWindowUnicode
    IsZoomed
    GetClassName
    GetClassLongPtrA
    SetClassLongPtrA
    GetWindowHicon
    GetWindow
    EnableWindow
    EnumChildWindows
    _modifyStyle//修改样式
    _modifyStyleEx//修改扩展样式 
    _findWindowFuzzy//模糊寻找窗口
    _setWindowTransparency//设置窗口透明度
    _cancelWindowTransparency//取消窗口透明度
    _getWindowTransparency//获取窗口透明度
    _setWindowTopmost//置顶窗口
    _windowFromCursorPoint//取鼠标当前位置窗口
    _isTopMost//窗口是否置顶
    _isTransparency//窗口是否透明
  },
  file: { OpenFolderAndSelect//资源管理器中定位文件
  draw: {
    drawBorder//窗口画边框
    hIconSave//图标句柄保存
    hIconToBuffer//图标句柄取BUFFER
  },
  process: {
    QueryFullProcessImageName
    DriveToDosDevice
    GetDrives
    ProcessSnapshot
    ProcessSnapshot_cb//回调形式快照进程列表
    EnumProcesses
    GetCurrentProcessId
    _filePathFromProcessId//进程ID取运行路径
    _processTree//生成进程树
  },
  util: {
    buildArrTree//生成数组树
    buildObjTree//生成进程树
  }
}
```

## 闲聊

并不会C/C++，功能更新也是按照自己意愿进行添加。有两个功能更是写了两天。

不过自身也获得很多。功能都经过调试，调试平台 WIN10 20H2。部分新API在WIN8以下平台不可用。
