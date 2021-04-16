//@ts-ignore
import api from '../../nwinuser.node';

export interface RECT {
  left: number;
  top: number;
  right: number;
  bottom: number;
}
export const GWL = {
  EXSTYLE: -20,
  HINSTANCE: -6,
  HWNDPARENT: -8,
  ID: -12,
  STYLE: -16,
  USERDATA: -21
}
export const SWP = {
  ASYNCWINDOWPOS: 0x4000,
  DEFERERASE: 0x2000,
  DRAWFRAME: 0x0020,
  FRAMECHANGED: 0x0020,
  HIDEWINDOW: 0x0080,
  NOACTIVATE: 0x0010,
  NOCOPYBITS: 0x0100,
  NOMOVE: 0x0002,
  NOOWNERZORDER: 0x0200,
  NOREDRAW: 0x0008,
  NOSENDCHANGING: 0x0400,
  NOSIZE: 0x0001,
  NOZORDER: 0x0004,
  SHOWWINDOW: 0x0040,
}

/**
 * @function 获取窗口DPI
 */
export function GetDpiForWindow(hWnd: number) {
  //test:ok
  return api.GetDpiForWindow(hWnd)
}

/**
 * @function 获取系统DPI
 */
export function GetDpiForSystem() {
  //test:ok
  return api.GetDpiForSystem()
}

/**
 * @function 寻找窗口
 * @param className 窗口类名,为空则返回第一个与类名匹配的窗口
 * @param className "" returns the first window that matches the className
 * @param windowName 窗口标题,为空则返回第一个与标题匹配的窗口
 * @param windowName "" returns the first window that matches the windowName
 * @returns hWnd 窗口句柄
 */
export function FindWindowA(className = "", windowName: string = "") {
  //test:ok
  return api.FindWindowA(className.trim(), windowName.trim())
}


/**
 * @function 寻找窗口
 * @param hWndParent 为0等同于C++null
 * @param hWndParent 0 equals C++ NULL
 * @param hWndChildAfter 为0等同于C++null
 * @param hWndChildAfter 0 equals C++ NULL
 * @param className 窗口类名,为空则返回第一个与类名匹配的窗口
 * @param className "" returns the first window that matches the className
 * @param windowName 窗口标题,为空则返回第一个与标题匹配的窗口
 * @param windowName "" returns the first window that matches the windowName
 * @returns hWnd 窗口句柄
 */
export function FindWindowExA(hWndParent: number,
  hWndChildAfter: number,
  className: string,
  WindowName: string)
  : number {
  //test:ok
  return api.FindWindowExA(hWndParent, hWndChildAfter, className.trim(), WindowName.trim())
}

/**
 * @function 获取客户区矩形
 * @param hWnd 
 * @returns 返回矩形，失败返回null
 * @returns Returns a rectangle. Failure returns null
 */
export function GetClientRect(hWnd: number)
  : RECT | null {
  //test:ok
  return api.GetClientRect(hWnd)
}

/**
 * @function 获取窗口矩形
 * @param hWnd 
 * @returns 返回矩形，失败返回null
 * @returns Returns a rectangle. Failure returns null
 */
export function GetWindowRect(hWnd: number)
  : RECT | null {
  //test:ok
  return api.GetWindowRect(hWnd)
}

/**
 * @function 更新窗口,成功返回真，反之。
 * @param hWnd 
 */
export function UpdateWindow(hWnd: number) {
  // test:ok
  return api.UpdateWindow(hWnd)
}

/**
 * 
 * @param hWnd 
 * @param gaFlags The ancestor to be retrieved. 
 * @param gaFlags 要检索的祖先。
 */
export function GetAncestor(hWnd: number, gaFlags: number)
  : number {
  //test:ok
  return api.GetAncestor(hWnd, gaFlags);
}

/**
 * @function Limit mouse area
 * @function 限制鼠标区域
 * @param Rect null为解除
 */
export function ClipCursor(Rect: RECT | null): boolean {
  //test:ok
  return api.ClipCursor(Rect)
}

/**
 * @function 取限制区矩形
 */
export function GetClipCursor()
  : RECT | null {
  //test:ok
  return api.GetClipCursor()
}

/**
 * @function 获取鼠标详情(位置,是否隐藏,指针句柄)
 */
export function GetCursorInfo()
  : {
    ptScreenPos: { x: number, y: number },
    flags: number,
    hCursor: number
  } {
  //test:ok
  return api.GetCursorInfo()
}
/**
 *  @function 当前进程下窗口隐藏或显示鼠标(electron也可以cursor:none给元素设置)
 *  @function Hide or show mouse in current process window (electron can also be set to cursor:none for elements)
 */
export function ShowCursor(bShow: boolean)
  : number {
  return api.ShowCursor(bShow)
}

/**
 * 
 * @param hWnd 
 * @param nIndex GWL_常量
 * @param dwNewLong 
 * @return If the function succeeds, the return value is the requested value. And vice versa is zero.
 * @return 如果函数成功，返回值就是请求值。反之为零。
 */
export function SetWindowLongPtrA(hWnd: number, nIndex: number, dwNewLong: number)
  : number {
  //test:ok
  return api.SetWindowLongPtrA(hWnd, nIndex, dwNewLong)
}

export function GetWindowLongPtrA(hWnd: number, nIndex: number)
  : number {
  //test:ok
  return api.GetWindowLongPtrA(hWnd, nIndex)
}
/**
 * @function 设置窗口透明度，需要设置扩展样式WS_EX_LAYERED
 * @function The extension style WS EX LAYERED needs to be set
 * @param hWnd 
 * @param colorKey 颜色值
 * @param alpha  0 completely transparent,255 completely opaque
 * @param alpha  0完全透明,255完全不透明
 * @param flags 
 */
export function SetLayeredWindowAttributes(hWnd: number,
  colorKey: number, alpha: number, flags: number): boolean {
  //test:ok
  alpha = alpha > 255 ? 255 : alpha < 0 ? 0 : alpha;
  return api.SetLayeredWindowAttributes(hWnd, colorKey, alpha, flags)
}

/**
 * @function 更改窗口的大小,位置
 * @function Change window size, position
 * @param hWnd 窗口句柄
 * @param hWndInsertAfter 该窗口句柄之后或HWND_常量值
 * @param hWndInsertAfter After the window handle or HWND constant value
 * @param X 
 * @param Y 
 * @param cx 宽度 width
 * @param cy 高度 height
 * @param uFlags 窗口大小和定位标志。SWP_常量值可组合
 */
export function SetWindowPos(hWnd: number,
  hWndInsertAfter: number,
  X: number,
  Y: number,
  cx: number,
  cy: number,
  uFlags: number): boolean {
  //test:ok
  return api.SetWindowPos(hWnd,
    hWndInsertAfter,
    X,
    Y,
    cx,
    cy,
    uFlags)
}

/**
 * @function 获取分层窗口的不透明度和颜色值
 * @function Gets the opacity and color values of the layered window
 * @param hWnd 
 */
export function GetLayeredWindowAttributes(hWnd: number)
  : { colorKey: number, alpha: number, flags: number } | false {
  //test:ok
  return api.GetLayeredWindowAttributes(hWnd)
}

/**
 * @function 显示窗口
 * @param hWnd 
 * @param CmdShow 显示方式
 */
export function ShowWindow(hWnd: number, CmdShow: number)
  : number {
  //test:ok
  return api.ShowWindow(hWnd, CmdShow)
}

/**
 * @function 投递消息
 * @param hWnd 
 * @param msg 消息值
 * @param wParam 
 * @param lParam 
 */
export function PostMessageA(hWnd: number, msg: number, wParam: number, lParam: number)
  : number {
  //test:ok
  return api.PostMessageA(hWnd, msg, wParam, lParam)
}

/**
 * @function 发送消息
 * @param hWnd 
 * @param msg 消息值
 * @param wParam 
 * @param lParam 
 */
export function SendMessageA(hWnd: number, msg: number, wParam: number, lParam: number)
  : number {
  //test:ok
  return api.SendMessageA(hWnd, msg, wParam, lParam)
}

/**
 * 取窗口标题
 * @param hWnd 
 */
export function GetWindowText(hWnd: number): string {
  //test:ok
  return api.GetWindowText(hWnd)
}

/**
 * 聚焦窗口
 * @param hWnd 
 */
export function SetForegroundWindow(hWnd: number): boolean {
  //test:ok
  return api.SetForegroundWindow(hWnd)
}
/**
 * 取点位置窗口
 * @param x 
 * @param y 
 */
export function WindowFromPoint(x: number, y: number) {
  //test:ok
  return api.WindowFromPoint(x, y)
}
/**
 * @function 窗口是否有效
 * @param hWnd 
 */
export function IsWindow(hWnd: number): Boolean {
  //test:ok
  return api.IsWindow(hWnd);
}

export function GetWindowInfo(hWnd: number)
  : {
    cxWindowBorders: number,
    cyWindowBorders: number,
    atomWindowType: number,
    dwStyle: number,
    dwExStyle: number,
    dwWindowStatus: number,
    rcWindow: RECT,
    rcClient: RECT,
    wCreatorVersion: number
  } | false {
  return api.GetWindowInfo(hWnd)
}

/**
 * 具体查看文档EnumWindows，函数调用错误会设置Error。
 * @returns 返回所有顶级窗口。。
 */
export function EnumWindows()
  : number[] | false {
  return api.EnumWindows()
}

/**
 * 获取桌面句柄
 */
export function GetDesktopWindow(): number {
  //test:ok
  return api.GetDesktopWindow()
}


/**
 * 获取最后一条错误。
 */
export function GetLastError(): number {
  //test:ok
  return api.GetLastError()
}


/**
 * 获取聚焦窗口句柄
 */
export function GetForegroundWindow() {
  //test:ok
  return api.GetForegroundWindow()
}

/**
 * @function EnumDesktopWindows 基于桌面为根基进行枚举窗口
 * @param desktopHwnd 桌面句柄。如果没有提供desktopHwnd,默认为NULL。表示当前桌面。
 */
export function EnumDesktopWindows(desktopHwnd = 0): number[] | false {
  //test:ok
  return api.EnumDesktopWindows(desktopHwnd)
}

/**
 * 取窗口线程ID和进程ID
 * @param hWnd 
 */
export function GetWindowThreadProcessId(hWnd: number): {
  ProcessId: number,
  ThreadId: number
} {
  //test:ok
  return api.GetWindowThreadProcessId(hWnd)
}
/**
 * 窗口是否启用，窗口允许接受键盘或鼠标输入返回true，反之。
 * 子窗口只有在被允许并且可见时才可接受输入
 * @param hWnd 
 */
export function IsWindowEnabled(hWnd: number): boolean {
  //test:ok
  return api.IsWindowEnabled(hWnd)
}
/**
 * 窗口是否可见
 * @param hWnd 
 */
export function IsWindowVisible(hWnd: number): boolean {
  //test:ok
  return api.IsWindowVisible(hWnd)
}
/**
 * 窗口是否为Unicode窗口
 * @param hWnd 
 */
export function IsWindowUnicode(hWnd: number): boolean {
  //test:ok
  return api.IsWindowUnicode(hWnd)
}
/**
 * 窗口是否最大
 * @param hWnd 
 */
export function IsZoomed(hWnd: number): boolean {
  //test:ok
  return api.IsZoomed(hWnd)
}

/**
 * 获取窗口类名
 * @param hWnd 
 */
export function GetClassName(hWnd: number): string {
  //test:ok
  return api.GetClassName(hWnd);
}


export function GetClassLongPtrA(hWnd: number, index: number) {
  return api.GetClassLongPtrA(hWnd, index)
}
export function SetClassLongPtrA(hWnd: number, index: number, newLong: number) {
  return api.SetClassLongPtrA(hWnd, index, newLong)
}
/**
 * 获取窗口图标句柄,使用SendMessageTimeout和GetClassLong,有如果失败会有40ms的延迟
 * 可自行更改获取方式例如单独的GetClassLong
 * @param hWnd 
 */
export function GetWindowHicon(hWnd: number): number {
  //test:ok
  return api.GetWindowHicon(hWnd)
}

/**
 * 获取窗口
 * GW_HWNDFIRST=0
 * GW_HWNDLAST=1
 * GW_HWNDNEXT=2
 * GW_HWNDPREV=3
 * GW_OWNER=4
 * GW_CHILD=5
 * GW_ENABLEDPOPUP=6
 * @param hWnd 
 * @param cmd 
 */
export function GetWindow(hWnd: number, cmd: number): number {
  return api.GetWindow(hWnd, cmd)
}

/**
 * 启用或禁用窗口
 * @param hWnd 
 * @param flag 
 */
export function EnableWindow(hWnd: number, flag: boolean) {
  //test:ok
  return api.EnableWindow(hWnd, flag)
}


/**
 * @function 枚举窗口的子窗口句柄
 * @function Enumerates the handle to a child window of a window
 * @param ParentHWnd 如果为0，则效果等同于EnumWindows
 * @param ParentHWnd If 0, the effect is equivalent to EnumWindows
 */
export function EnumChildWindows(ParentHWnd: number) {
  //test:ok
  return api.EnumChildWindows(ParentHWnd)
}



//-------------------------包装后方法

/**
 * @param flags If it is not zero, call SetWindowPos and redraw the preset flag。
 * SWP.NOSIZE | SWP.NOMOVE | SWP.NOZORDER | SWP.NOACTIVATE
 * @returns Returns true on success, or the window style value before the call
 */
export function _modifyStyle(hWnd: number,
  { addStyle = 0, removeStyle = 0 } = {},
  flags: boolean | number = true): true | number {
  let style = GetWindowLongPtrA(hWnd, GWL.STYLE)
  style = style & ~removeStyle
  style = style | addStyle
  let mod = SetWindowLongPtrA(hWnd, GWL.STYLE, style)
  let ok = mod === style, ok2 = true;
  if (flags === true) {
    ok2 = SetWindowPos(hWnd, 0, 0, 0, 0, 0,
      SWP.NOSIZE | SWP.NOMOVE | SWP.NOZORDER | SWP.NOACTIVATE)
  } else if (typeof flags == "number") {
    ok2 = SetWindowPos(hWnd, 0, 0, 0, 0, 0,
      SWP.NOSIZE | SWP.NOMOVE | SWP.NOZORDER | SWP.NOACTIVATE | flags)
  }
  if (!(ok && ok2)) {
    return true
  }
  return style
}
/**
 * @param flags If it is not zero, call SetWindowPos and redraw the preset flag。
 * SWP.NOSIZE | SWP.NOMOVE | SWP.NOZORDER | SWP.NOACTIVATE
 * @returns Returns true on success, or the window style value before the call
 */
export function _modifyStyleEx(hWnd: number,
  { addStyle = 0, removeStyle = 0 } = {},
  flags: true | number = 0): true | number {
  let style = GetWindowLongPtrA(hWnd, GWL.EXSTYLE)
  style = style & ~removeStyle
  style = style | addStyle
  let mod = SetWindowLongPtrA(hWnd, GWL.EXSTYLE, style)
  let ok = mod === style, ok2 = true;
  if (flags === true) {
    ok2 = SetWindowPos(hWnd, 0, 0, 0, 0, 0,
      SWP.NOSIZE | SWP.NOMOVE | SWP.NOZORDER | SWP.NOACTIVATE)
  } else if (typeof flags == "number") {
    ok2 = SetWindowPos(hWnd, 0, 0, 0, 0, 0,
      SWP.NOSIZE | SWP.NOMOVE | SWP.NOZORDER | SWP.NOACTIVATE | flags)
  }
  if (!(ok && ok2)) {
    return true
  }
  return style
}
/**
 * @function Fuzzy search window
 * @param windowName Part of the window title to search, regardless of case
 * @param className The class name must be written in full, emptyString Ignore
 * @function 模糊搜索窗口
 * @param windowName 要搜索的窗口部分窗口标题,无视大小写
 * @param className 类名必须写明,空文本则忽略
 */
export function _findWindowFuzzy(windowName: string, className: string = "")
  : number {
  let _hWnd = 0;
  let _title = "";
  while (true) {
    _hWnd = FindWindowExA(0, _hWnd, className, '')
    if (_hWnd != 0) {
      _title = GetWindowText(_hWnd).toLocaleLowerCase();
      if (_title.includes(windowName)) {
        return _hWnd
      }
    } else {
      break;
    }
  }
  return 0;
}
//#region 透明相关
/**
 * @function 设置窗口透明度
 * @param hWnd 
 * @param alpha 不透明值,0完全透明,255完全不透明 
 * @param through 窗口是否可穿透
 * @param colorKey 
 */
export function _setWindowTransparency(hWnd: number, alpha: number,
  through = false, colorKey: number | false = false)
  : boolean {
  _modifyStyleEx(hWnd, { addStyle: through ? 524288 | 32 : 524288 })
  let method = 1
  if (colorKey === false) {
    method = 2
    colorKey = 0
  }
  return SetLayeredWindowAttributes(hWnd, colorKey as number, alpha, method)
}
/**
 * @function 取消窗口透明,返回真成功否则返回之前样式值.
 * @function Cancel window transparency, return true success otherwise return previous style value.
 * @param hWnd 
 */
export function _cancelWindowTransparency(hWnd: number) {
  return _modifyStyleEx(hWnd, { removeStyle: 524288 | 32 })
}
/**
 * 获取窗口不透明度,只有调用SetLayeredWindowAttributes后才会正确返回
 * 调用upLayeredWindowAttributes后失效
 * @param hWnd 
 */
export function _getWindowTransparency(hWnd: number)
  : number | false {
  let _r = GetLayeredWindowAttributes(hWnd)
  if (_r) {
    return _r.alpha
  }
  return false;
}
//#endregion


/**
 * @function 置顶窗口
 * @function topmost window
 * @param hWnd 
 * @param topmost 
 */
export function _setWindowTopmost(hWnd: number, topmost = true) {
  if (topmost) {
    SetForegroundWindow(hWnd)
    return SetWindowPos(hWnd, -1, 0, 0, 0, 0, SWP.NOMOVE | SWP.NOSIZE)
  } else {
    return SetWindowPos(hWnd, -2, 0, 0, 0, 0, SWP.NOMOVE | SWP.NOSIZE)
  }
}
/**
 * @function 取鼠标位置处窗口句柄
 * @function Gets the window handle at the mouse position
 */
export function _windowFromCursorPoint(): number {
  let c = GetCursorInfo()
  return WindowFromPoint(c.ptScreenPos.x, c.ptScreenPos.y);
}

/**
 * 取窗口是否顶置
 * @param hWnd 
 */
export function _isTopMost(hWnd: number) {
  let info = GetWindowInfo(hWnd)
  if (info) {
    return info.dwExStyle & 8
  }
  return false
}

/**
 * 窗口是否添加分层特效。
 */
export function _isTransparency(hWnd: number) {
  //test:ok
  let info = GetWindowInfo(hWnd)
  if (info) {
    return info.dwExStyle & 524288
  }
  return false
}

