#include <Windows.h>
#include <iostream>
#include "nwinuser.h"
#include "util.cc"

#pragma region ClipCursor
Napi::Boolean nwinuser::Wrap_ClipCursor(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!(info[0].IsObject() || info[0].IsNull()))
  {
    error = Napi::Error::New(env, "Rect should be a RECT or Null.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, 0);
  }
  if (info[0].IsNull())
  {
    bool result = ClipCursor(NULL);
    return Napi::Boolean::New(env, result);
  }
  Napi::Object obj = info[0].As<Napi::Object>();
  RECT rect;
  rect.left = (int)obj.Get("left").ToNumber();
  rect.top = (int)obj.Get("top").ToNumber();
  rect.right = (int)obj.Get("right").ToNumber();
  rect.bottom = (int)obj.Get("bottom").ToNumber();
  bool result = ClipCursor(&rect);
  return Napi::Boolean::New(env, result);
}
#pragma endregion ClipCursor

#pragma region FindWindowA
Napi::Number nwinuser::Wrap_FindWindowA(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 2)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsString())
  {
    error = Napi::Error::New(env, "lpClassName should be a string.");
  }
  else if (!info[1].IsString())
  {
    error = Napi::Error::New(env, "lpWindowName should be a string.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Number::New(env, 0);
  }
  std::string arg0 = Utf8ToAnsi(info[0].As<Napi::String>());
  std::string arg1 = Utf8ToAnsi(info[1].As<Napi::String>());

  HWND result = FindWindowA(arg0 == "" ? NULL : arg0.c_str(),
                            arg1 == "" ? NULL : arg1.c_str());
  return Napi::Number::New(env, reinterpret_cast<size_t>(result));
}
#pragma endregion FindWindowA

#pragma region FindWindowExA
Napi::Number nwinuser::Wrap_FindWindowExA(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  /* (HWND hWndParent, HWND hWndChildAfter, LPCSTR lpszClass, LPCSTR lpszWindow) */
  if (info.Length() < 4)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWndParent should be a number.");
  }
  else if (!info[1].IsNumber())
  {
    error = Napi::Error::New(env, "hWndChildAfter should be a number.");
  }
  else if (!info[2].IsString())
  {
    error = Napi::Error::New(env, "lpszClass should be a string.");
  }
  else if (!info[3].IsString())
  {
    error = Napi::Error::New(env, "lpszWindow should be a string.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Number::New(env, 0);
  }
  HWND arg0 = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  HWND arg1 = (HWND) reinterpret_cast<size_t *>((int64_t)info[1].As<Napi::Number>());
  std::string arg2 = Utf8ToAnsi(info[2].As<Napi::String>());
  std::string arg3 = Utf8ToAnsi(info[3].As<Napi::String>());
  HWND result = FindWindowExA(arg0, arg1,
                              arg2 == "" ? NULL : arg2.c_str(),
                              arg3 == "" ? NULL : arg3.c_str());
  return Napi::Number::New(env, reinterpret_cast<size_t>(result));
}
#pragma endregion FindWindowExA

#pragma region GetDpiForWindow
Napi::Number nwinuser::Wrap_GetDpiForWindow(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "Hwnd should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Number::New(env, 0);
  }
  UINT result = GetDpiForWindow((HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>()));
  return Napi::Number::New(env, result);
}
#pragma endregion GetDpiForWindow

#pragma region GetDpiForSystem
Napi::Number nwinuser::Wrap_GetDpiForSystem(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() != 0)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Number::New(env, 0);
  }
  UINT result = GetDpiForSystem();
  return Napi::Number::New(env, result);
}
#pragma endregion GetDpiForSystem

#pragma region GetClientRect
Napi::Value nwinuser::Wrap_GetClientRect(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return env.Null();
  }
  RECT Rect;
  bool ok = GetClientRect((HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>()),
                          &Rect);

  if (!ok)
    return env.Null();
  Napi::Object result = Napi::Object::New(env);
  result.Set("left", Rect.left);
  result.Set("top", Rect.top);
  result.Set("right", Rect.right);
  result.Set("bottom", Rect.bottom);
  return result;
}
#pragma endregion GetClientRect

#pragma region GetClipCursor
Napi::Value nwinuser::Wrap_GetClipCursor(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() != 0)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return env.Null();
  }
  RECT rect;
  bool ok = GetClipCursor(&rect);
  if (ok)
  {
    Napi::Object obj = Napi::Object::New(env);
    obj.Set("left", rect.left);
    obj.Set("top", rect.top);
    obj.Set("right", rect.right);
    obj.Set("bottom", rect.bottom);
    return obj;
  }
  return env.Null();
}
#pragma endregion GetClipCursor

#pragma region GetWindowRect
Napi::Value nwinuser::Wrap_GetWindowRect(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return env.Null();
  }
  RECT Rect;
  bool ok = GetWindowRect((HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>()),
                          &Rect);
  if (!ok)
    return env.Null();
  Napi::Object result = Napi::Object::New(env);
  result.Set("left", Rect.left);
  result.Set("top", Rect.top);
  result.Set("right", Rect.right);
  result.Set("bottom", Rect.bottom);
  return result;
}
#pragma endregion GetWindowRect

#pragma region GetAncestor
Napi::Number nwinuser::Wrap_GetAncestor(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 2)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "Hwnd should be a number.");
  }
  else if (!info[1].IsNumber())
  {
    error = Napi::Error::New(env, "gaFlags should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Number::New(env, 0);
  }

  HWND result = GetAncestor((HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>()),
                            info[1].As<Napi::Number>());
  return Napi::Number::New(env, reinterpret_cast<size_t>(result));
}
#pragma endregion GetAncestor

#pragma region GetCursorInfo
Napi::Value nwinuser::Wrap_GetCursorInfo(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() != 0)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return env.Null();
  }
  CURSORINFO pci;
  pci.cbSize = sizeof(CURSORINFO);
  GetCursorInfo(&pci);
  Napi::Object result = Napi::Object::New(env);
  Napi::Object ptScreenPos = Napi::Object::New(env);
  ptScreenPos.Set("x", pci.ptScreenPos.x);
  ptScreenPos.Set("y", pci.ptScreenPos.y);
  result.Set("ptScreenPos", ptScreenPos);
  result.Set("flags", pci.flags);
  result.Set("hCursor", (int)reinterpret_cast<size_t>(pci.hCursor));
  return result;
}
#pragma endregion GetCursorInfo

#pragma region ShowCursor
Napi::Number nwinuser::Wrap_ShowCursor(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsBoolean())
  {
    error = Napi::Error::New(env, "bShow should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Number::New(env, 0);
  }
  int result = ShowCursor(info[0].ToBoolean());
  return Napi::Number::New(env, result);
}
#pragma endregion ShowCursor

#pragma region ShowWindow
Napi::Boolean nwinuser::Wrap_ShowWindow(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 2)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  HWND hWnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  int nCmdShow = info[1].ToNumber();
  return Napi::Boolean::New(env, ShowWindow(hWnd, nCmdShow));
}
#pragma endregion ShowWindow

#pragma region UpdateWindow
Napi::Boolean nwinuser::Wrap_UpdateWindow(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  bool result = UpdateWindow(hwnd);
  return Napi::Boolean::New(env, result);
}
#pragma endregion UpdateWindow

#pragma region SetWindowLongPtrA
Napi::Number nwinuser::Wrap_SetWindowLongPtrA(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 3)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  else if (!info[1].IsNumber())
  {
    error = Napi::Error::New(env, "nIndex should be a number.");
  }
  else if (!info[2].IsNumber())
  {
    error = Napi::Error::New(env, "dwNewLong should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Number::New(env, 0);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  int nIndex = info[1].As<Napi::Number>();
  LONG_PTR dwNewLong = info[2].As<Napi::Number>();
  LONG_PTR result = SetWindowLongPtrA(hwnd, nIndex, dwNewLong);
  return Napi::Number::New(env, result);
}
#pragma endregion SetWindowLongPtrA

#pragma region GetWindowLongPtrA
Napi::Number nwinuser::Wrap_GetWindowLongPtrA(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 2)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  else if (!info[1].IsNumber())
  {
    error = Napi::Error::New(env, "nIndex should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Number::New(env, false);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  int nIndex = info[1].As<Napi::Number>();
  LONG_PTR result = GetWindowLongPtrA(hwnd, nIndex);
  return Napi::Number::New(env, result);
}
#pragma endregion GetWindowLongPtrA

#pragma region SetLayeredWindowAttributes
Napi::Boolean nwinuser::Wrap_SetLayeredWindowAttributes(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 4)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  else if (!info[1].IsNumber())
  {
    error = Napi::Error::New(env, "crKey should be a number.");
  }
  else if (!info[2].IsNumber())
  {
    error = Napi::Error::New(env, "bAlpha should be a number.");
  }
  else if (!info[3].IsNumber())
  {
    error = Napi::Error::New(env, "dwFlags should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  COLORREF crKey = (uint32_t)info[1].As<Napi::Number>();
  BYTE bAlpha = (BYTE)(int)info[2].As<Napi::Number>();
  DWORD dwFlags = (uint32_t)info[3].As<Napi::Number>();
  return Napi::Boolean::New(env, SetLayeredWindowAttributes(hwnd, crKey, bAlpha, dwFlags));
}
#pragma endregion SetLayeredWindowAttributes

#pragma region SetWindowPos
Napi::Boolean nwinuser::Wrap_SetWindowPos(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 7)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  else if (!info[1].IsNumber())
  {
    error = Napi::Error::New(env, "hWndInsertAfter should be a number.");
  }
  else if (!info[2].IsNumber())
  {
    error = Napi::Error::New(env, "x should be a number.");
  }
  else if (!info[3].IsNumber())
  {
    error = Napi::Error::New(env, "y should be a number.");
  }
  else if (!info[4].IsNumber())
  {
    error = Napi::Error::New(env, "cx should be a number.");
  }
  else if (!info[5].IsNumber())
  {
    error = Napi::Error::New(env, "cy should be a number.");
  }
  else if (!info[6].IsNumber())
  {
    error = Napi::Error::New(env, "uFlags should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  HWND hWndInsertAfter = (HWND) reinterpret_cast<size_t *>((int64_t)info[1].As<Napi::Number>());
  int x = info[2].As<Napi::Number>();
  int y = info[3].As<Napi::Number>();
  int cx = info[4].As<Napi::Number>();
  int cy = info[5].As<Napi::Number>();
  UINT uFlags = info[6].As<Napi::Number>();

  return Napi::Boolean::New(env, SetWindowPos(hwnd, hWndInsertAfter, x, y, cx, cy, uFlags));
}
#pragma endregion SetWindowPos

#pragma region PostMessageA
Napi::Boolean nwinuser::Wrap_PostMessageA(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 4)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  else if (!info[1].IsNumber())
  {
    error = Napi::Error::New(env, "Msg should be a number.");
  }
  else if (!info[2].IsNumber())
  {
    error = Napi::Error::New(env, "wParam should be a number.");
  }
  else if (!info[3].IsNumber())
  {
    error = Napi::Error::New(env, "lParam should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  UINT Msg = info[1].As<Napi::Number>();
  WPARAM wParam = (uint32_t)info[2].As<Napi::Number>();
  LPARAM lParam = info[3].As<Napi::Number>();
  return Napi::Boolean::New(env, PostMessageA(hwnd, Msg, wParam, lParam));
}
#pragma endregion PostMessageA

#pragma region SendMessage
Napi::Boolean nwinuser::Wrap_SendMessageA(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 4)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  else if (!info[1].IsNumber())
  {
    error = Napi::Error::New(env, "Msg should be a number.");
  }
  else if (!info[2].IsNumber())
  {
    error = Napi::Error::New(env, "wParam should be a number.");
  }
  else if (!info[3].IsNumber())
  {
    error = Napi::Error::New(env, "lParam should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  UINT Msg = info[1].As<Napi::Number>();
  WPARAM wParam = (uint32_t)info[2].As<Napi::Number>();
  LPARAM lParam = info[3].As<Napi::Number>();
  return Napi::Boolean::New(env, SendMessageA(hwnd, Msg, wParam, lParam));
}
#pragma endregion SendMessage

#pragma region GetLayeredWindowAttributes
Napi::Value nwinuser::Wrap_GetLayeredWindowAttributes(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  COLORREF pcrKey;
  BYTE pbAlpha;
  DWORD pdwFlags;
  bool ok = GetLayeredWindowAttributes(hwnd, &pcrKey, &pbAlpha, &pdwFlags);
  if (!ok)
  {
    return Napi::Boolean::New(env, false);
  }
  Napi::Object obj = Napi::Object::New(env);
  obj.Set("colorKey", pcrKey);
  obj.Set("alpha", pbAlpha);
  obj.Set("flags", pdwFlags);
  return obj;
}
#pragma endregion GetLayeredWindowAttributes

#pragma region Getwindowtext
Napi::String nwinuser::Wrap_GetWindowText(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::String::New(env, "");
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  int length = GetWindowTextLengthA(hwnd) + 1;
  char *name = new char[length];
  GetWindowTextA(hwnd, name, length);
  Napi::String result = Napi::String::New(env, AnsiToUtf8(name));
  delete[] name;
  name = nullptr;
  return result;
}
#pragma endregion GetWindowText

#pragma region SetForegroundWindow
Napi::Boolean nwinuser::Wrap_SetForegroundWindow(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  return Napi::Boolean::New(env, SetForegroundWindow(hwnd));
}
#pragma endregion SetForegroundWindow

#pragma region WindowFromPoint
Napi::Number nwinuser::Wrap_WindowFromPoint(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 2)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "x should be a number.");
  }
  else if (!info[1].IsNumber())
  {
    error = Napi::Error::New(env, "y should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Number::New(env, 0);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  LONG x = (int32_t)info[0].As<Napi::Number>();
  LONG y = (int32_t)info[1].As<Napi::Number>();
  POINT point;
  point.x = x;
  point.y = y;
  return Napi::Number::New(env,
                           reinterpret_cast<size_t>(WindowFromPoint(point)));
}
#pragma endregion WindowFromPoint

#pragma region GetWindowInfo
Napi::Value nwinuser::Wrap_GetWindowInfo(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  WINDOWINFO pwi;
  pwi.cbSize = sizeof(WINDOWINFO);
  bool ok = GetWindowInfo(hwnd, &pwi);
  if (!ok)
  {
    return Napi::Boolean::New(env, false);
  }
  Napi::Object result = Napi::Object::New(env);
  result.Set("cxWindowBorders", pwi.cxWindowBorders);
  result.Set("cyWindowBorders", pwi.cyWindowBorders);
  result.Set("atomWindowType", pwi.atomWindowType);
  result.Set("dwStyle", pwi.dwStyle);
  result.Set("dwExStyle", pwi.dwExStyle);
  result.Set("dwWindowStatus", pwi.dwWindowStatus);
  RECT _rect;
  Napi::Object rectW = Napi::Object::New(env);
  _rect = pwi.rcWindow;
  rectW.Set("left", _rect.left);
  rectW.Set("top", _rect.top);
  rectW.Set("right", _rect.right);
  rectW.Set("bottom", _rect.bottom);
  result.Set("rcWindow", rectW);
  Napi::Object rectC = Napi::Object::New(env);
  _rect = pwi.rcClient;
  rectC.Set("left", _rect.left);
  rectC.Set("top", _rect.top);
  rectC.Set("right", _rect.right);
  rectC.Set("bottom", _rect.bottom);
  result.Set("rcClient", rectC);
  result.Set("wCreatorVersion", pwi.wCreatorVersion);
  return result;
}
#pragma endregion GetWindowInfo

#pragma region EnumWindows
BOOL CALLBACK EnumFunc(HWND hWnd, LPARAM lparam)
{
  int iWnd = (int)reinterpret_cast<size_t>(hWnd);
  ((Napi::Array *)(void *)lparam)->Set(((Napi::Array *)(void *)lparam)->Length(), iWnd);
  return true;
}
Napi::Value nwinuser::Wrap_EnumWindows(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() > 0)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  //先声明数组
  Napi::Array result = Napi::Array::New(env);
  //不借助外部变量来接收回调的内容就把指针传递过去。
  bool ok = EnumWindows(EnumFunc, (LPARAM)(void *)&result);
  if (!ok)
  {
    return Napi::Boolean::New(env, false);
  }
  return result;
}
#pragma endregion EnumWindows

#pragma region GetDesktopWindow
Napi::Number nwinuser::Wrap_GetDesktopWindow(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() > 0)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Number::New(env, false);
  }

  return Napi::Number::New(env, reinterpret_cast<size_t>(GetDesktopWindow()));
}
#pragma endregion GetDesktopWindow

#pragma region Wrap_GetForegroundWindow
Napi::Number nwinuser::Wrap_GetForegroundWindow(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() != 0)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Number::New(env, false);
  }
  return Napi::Number::New(env, (reinterpret_cast<size_t>(GetForegroundWindow())));
}
#pragma endregion Wrap_GetForegroundWindow

#pragma region EnumDesktopWindows
BOOL CALLBACK EnumDeskWinFunc(HWND hWnd, LPARAM lparam)
{
  int iWnd = (int)reinterpret_cast<size_t>(hWnd);
  ((Napi::Array *)(void *)lparam)->Set(((Napi::Array *)(void *)lparam)->Length(), iWnd);
  return true;
}
Napi::Value nwinuser::Wrap_EnumDesktopWindows(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "desktopHwnd is a Number");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  //先声明数组
  Napi::Array result = Napi::Array::New(env);
  //不借助外部变量来接收回调的内容就把指针传递过去。
  bool ok = EnumDesktopWindows((HDESK) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>()),
                               EnumDeskWinFunc,
                               (LPARAM)(void *)&result);
  if (!ok)
  {
    return Napi::Boolean::New(env, false);
  }
  return result;
}
#pragma endregion EnumDesktopWindows

#pragma region GetLastError
Napi::Number nwinuser::Wrap_GetLastError(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() != 0)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Number::New(env, false);
  }
  return Napi::Number::New(env, GetLastError());
}
#pragma endregion GetLastError

#pragma region GetWindowThreadProcessId
Napi::Value nwinuser::Wrap_GetWindowThreadProcessId(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  DWORD Pid;
  DWORD Tid = GetWindowThreadProcessId(hwnd, &Pid);
  Napi::Object result = Napi::Object::New(env);
  result.Set("ProcessId", Pid);
  result.Set("ThreadId", Tid);
  return result;
}
#pragma endregion GetWindowThreadProcessId

#pragma region IsWindow系列
Napi::Boolean nwinuser::Wrap_IsWindow(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());

  return Napi::Boolean::New(env, IsWindow(hwnd));
}

Napi::Boolean nwinuser::Wrap_IsWindowEnabled(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  return Napi::Boolean::New(env, IsWindowEnabled(hwnd));
}

Napi::Boolean nwinuser::Wrap_IsWindowUnicode(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  return Napi::Boolean::New(env, IsWindowUnicode(hwnd));
}

Napi::Boolean nwinuser::Wrap_IsWindowVisible(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  return Napi::Boolean::New(env, IsWindowVisible(hwnd));
}

Napi::Boolean nwinuser::Wrap_IsZoomed(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  return Napi::Boolean::New(env, IsZoomed(hwnd));
}
#pragma endregion IsWindow系列

#pragma region GetClassName
Napi::String nwinuser::Wrap_GetClassName(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::String::New(env, "");
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  int length = 50;
  char *name = new char[length];
  GetClassNameA(hwnd, name, length);
  Napi::String result = Napi::String::New(env, AnsiToUtf8(name));
  delete[] name;
  name = nullptr;
  return result;
}
#pragma endregion GetClassName

#pragma region GetClassLongPtrA
Napi::Number nwinuser::Wrap_GetClassLongPtrA(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 2)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  else if (!info[1].IsNumber())
  {
    error = Napi::Error::New(env, "nIndex should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Number::New(env, 0);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  int idx = info[1].As<Napi::Number>();
  return Napi::Number::New(env, GetClassLongPtrA(hwnd, idx));
}
#pragma endregion GetClassLongPtrA

#pragma region SetClassLongPtrA
Napi::Number nwinuser::Wrap_SetClassLongPtrA(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 3)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  else if (!info[1].IsNumber())
  {
    error = Napi::Error::New(env, "nIndex should be a number.");
  }
  else if (!info[2].IsNumber())
  {
    error = Napi::Error::New(env, "dwNewLong should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Number::New(env, 0);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  int idx = info[1].As<Napi::Number>();
  LONG dwNewLong = (int32_t)info[2].As<Napi::Number>();
  return Napi::Number::New(env, SetClassLongPtrA(hwnd, idx, dwNewLong));
}
#pragma endregion SetClassLongPtrA

#pragma region GetWindowHicon
Napi::Number nwinuser::GetWindowHicon(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Number::New(env, false);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  ULONG Result = 0i64;
  LRESULT v4 = SendMessageTimeoutW(hwnd, 0x7Fu, 2ui64, 0i64, 3u, 0x14u, (PDWORD_PTR)(void *)&Result);
  if (!v4 || !Result)
  {
    v4 = SendMessageTimeoutW(hwnd, 0x7Fu, 0i64, 0i64, 3u, 0x14u, (PDWORD_PTR)(void *)&Result);
  }
  if (!v4 || !Result)
  {
    ULONG_PTR v5 = GetClassLongPtrW(hwnd, -34);
    Result = v5;
    if (!v5)
      Result = GetClassLongPtrW(hwnd, -14);
  }
  return Napi::Number::New(env, Result);
}
#pragma endregion GetWindowHicon

#pragma region GetWindow
Napi::Number nwinuser::Wrap_GetWindow(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 2)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  else if (!info[1].IsNumber())
  {
    error = Napi::Error::New(env, "cmd should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Number::New(env, false);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  return Napi::Number::New(env, reinterpret_cast<size_t>(GetWindow(hwnd, info[1].As<Napi::Number>())));
}
#pragma endregion GetWindow

#pragma region EnableWindow
Napi::Boolean nwinuser::Wrap_EnableWindow(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 2)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hWnd should be a number.");
  }
  else if (!info[1].IsBoolean())
  {
    error = Napi::Error::New(env, "flag should be a boolean.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  bool flag = info[1].As<Napi::Boolean>();

  return Napi::Boolean::New(env, EnableWindow(hwnd, flag));
}
#pragma endregion

#pragma region EnumChildWindows
BOOL CALLBACK EnumChildFunc(HWND hWnd, LPARAM lparam)
{
  int iWnd = (int)reinterpret_cast<size_t>(hWnd);
  ((Napi::Array *)(void *)lparam)->Set(((Napi::Array *)(void *)lparam)->Length(), iWnd);
  return true;
}
Napi::Value nwinuser::Wrap_EnumChildWindows(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "Parent should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  //先声明数组
  Napi::Array result = Napi::Array::New(env);
  //不借助外部变量来接收回调的内容就把指针传递过去。
  bool ok = EnumChildWindows(hwnd,EnumChildFunc, (LPARAM)(void *)&result);
  if (!ok)
  {
    return Napi::Boolean::New(env, false);
  }
  return result;
}
#pragma endregion

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("ClipCursor", Napi::Function::New(env, nwinuser::Wrap_ClipCursor));
  exports.Set("FindWindowA", Napi::Function::New(env, nwinuser::Wrap_FindWindowA));
  exports.Set("FindWindowExA", Napi::Function::New(env, nwinuser::Wrap_FindWindowExA));
  exports.Set("IsWindow", Napi::Function::New(env, nwinuser::Wrap_IsWindow));
  exports.Set("GetDpiForWindow", Napi::Function::New(env, nwinuser::Wrap_GetDpiForWindow));
  exports.Set("GetDpiForSystem", Napi::Function::New(env, nwinuser::Wrap_GetDpiForSystem));
  exports.Set("GetClientRect", Napi::Function::New(env, nwinuser::Wrap_GetClientRect));
  exports.Set("GetWindowRect", Napi::Function::New(env, nwinuser::Wrap_GetWindowRect));
  exports.Set("GetWindowText", Napi::Function::New(env, nwinuser::Wrap_GetWindowText));
  exports.Set("GetAncestor", Napi::Function::New(env, nwinuser::Wrap_GetAncestor));
  exports.Set("GetClipCursor", Napi::Function::New(env, nwinuser::Wrap_GetClipCursor));
  exports.Set("GetCursorInfo", Napi::Function::New(env, nwinuser::Wrap_GetCursorInfo));
  exports.Set("GetClassName", Napi::Function::New(env, nwinuser::Wrap_GetClassName));
  exports.Set("GetClassLongPtrA", Napi::Function::New(env, nwinuser::Wrap_GetClassLongPtrA));
  exports.Set("SetClassLongPtrA", Napi::Function::New(env, nwinuser::Wrap_SetClassLongPtrA));
  exports.Set("GetWindowLongPtrA", Napi::Function::New(env, nwinuser::Wrap_GetWindowLongPtrA));
  exports.Set("GetWindowInfo", Napi::Function::New(env, nwinuser::Wrap_GetWindowInfo));
  exports.Set("GetForegroundWindow", Napi::Function::New(env, nwinuser::Wrap_GetForegroundWindow));
  exports.Set("GetLayeredWindowAttributes", Napi::Function::New(env, nwinuser::Wrap_GetLayeredWindowAttributes));
  exports.Set("PostMessageA", Napi::Function::New(env, nwinuser::Wrap_PostMessageA));
  exports.Set("SetForegroundWindow", Napi::Function::New(env, nwinuser::Wrap_SetForegroundWindow));
  exports.Set("ShowCursor", Napi::Function::New(env, nwinuser::Wrap_ShowCursor));
  exports.Set("ShowWindow", Napi::Function::New(env, nwinuser::Wrap_ShowWindow));
  exports.Set("SetWindowLongPtrA", Napi::Function::New(env, nwinuser::Wrap_SetWindowLongPtrA));
  exports.Set("SetWindowPos", Napi::Function::New(env, nwinuser::Wrap_SetWindowPos));
  exports.Set("SetLayeredWindowAttributes", Napi::Function::New(env, nwinuser::Wrap_SetLayeredWindowAttributes));
  exports.Set("SendMessageA", Napi::Function::New(env, nwinuser::Wrap_SendMessageA));
  exports.Set("UpdateWindow", Napi::Function::New(env, nwinuser::Wrap_UpdateWindow));
  exports.Set("WindowFromPoint", Napi::Function::New(env, nwinuser::Wrap_WindowFromPoint));
  exports.Set("EnumWindows", Napi::Function::New(env, nwinuser::Wrap_EnumWindows));
  exports.Set("EnumDesktopWindows", Napi::Function::New(env, nwinuser::Wrap_EnumDesktopWindows));
  exports.Set("GetDesktopWindow", Napi::Function::New(env, nwinuser::Wrap_GetDesktopWindow));
  exports.Set("GetWindowThreadProcessId", Napi::Function::New(env, nwinuser::Wrap_GetWindowThreadProcessId));
  exports.Set("GetLastError", Napi::Function::New(env, nwinuser::Wrap_GetLastError));
  exports.Set("IsWindowEnabled", Napi::Function::New(env, nwinuser::Wrap_IsWindowEnabled));
  exports.Set("IsWindowVisible", Napi::Function::New(env, nwinuser::Wrap_IsWindowVisible));
  exports.Set("IsWindowUnicode", Napi::Function::New(env, nwinuser::Wrap_IsWindowUnicode));
  exports.Set("IsZoomed", Napi::Function::New(env, nwinuser::Wrap_IsZoomed));
  exports.Set("GetWindowHicon", Napi::Function::New(env, nwinuser::GetWindowHicon));
  exports.Set("GetWindow", Napi::Function::New(env, nwinuser::Wrap_GetWindow));
  exports.Set("EnableWindow", Napi::Function::New(env, nwinuser::Wrap_EnableWindow));
  exports.Set("EnumChildWindows", Napi::Function::New(env, nwinuser::Wrap_EnumChildWindows));

  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)