[中文](./README_CH.md)

# easyWin

## INSTALL

Modules are now compiled locally and are provided with compiled files (even without a build environment).

```javascript
npm install easywin 
//or
yarn add easywin

//Fuzzy keyword fetch hWnd
let {winuser}=require('easywin')
let hQQ = winuser._findWindowFuzzy("QQ");

//Get ProcessTree
let {process} = require('easywin')
let tree = process._processTree();
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

The uppercase method in the module is a native call, which is adjusted to the return of JS functions

The bottom line（_） beginning method is the method after packaging the complete function.

When there is ambiguity between C++ and the call, such as C++ filling in NULL, then corresponding in JS to make the numeric parameter 0, string assignment "" operation

## 介绍
Node Windows, process related API in Windows environment.

>winuser->The following contains the commonly used User32 API.。

>process->It provides a list of processes, a tree of processes, and because process operations depend on permissions, process operations can use the command line tools provided under Windows, Tasklist or WMIC or PS。

>draw->Provides methods for GDI.Mainly for the realization of Spy ++ developed.

>file->Add in the

## electron Related to the use

To add

## AllFunction

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
    _modifyStyle//Quickly add and delete window styles
    _modifyStyleEx//Quickly add and delete window styleEX 
    _findWindowFuzzy//Fuzzy search window
    _setWindowTransparency
    _cancelWindowTransparency
    _getWindowTransparency
    _setWindowTopmost
    _windowFromCursorPoint//Get the current mouse position window
    _isTopMost
    _isTransparency
  },
  file: { OpenFolderAndSelect//Locates the file in Explorer
  draw: {
    drawBorder//draw window border
    hIconSave
    hIconToBuffer
  },
  process: {
    QueryFullProcessImageName
    DriveToDosDevice
    GetDrives
    ProcessSnapshot
    ProcessSnapshot_cb//Snapshot process list in callback form
    EnumProcesses
    GetCurrentProcessId
    _filePathFromProcessId//The process ID takes the run path
    _processTree//buildProcessTree
  },
  util: {
    buildArrTree
    buildObjTree
  }
}
```

## AND

Functions have been debugged, debugging platform Win10 20H2.Some of the new APIs are not available on Windows 8 or below.

BUG fastest feedback channel: direct messages at 

B站:https://space.bilibili.com/7234113.

email:871782513@qq.com