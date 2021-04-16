#include <napi.h>

namespace nwinuser
{
  Napi::Boolean Wrap_ClipCursor(const Napi::CallbackInfo &info);
  Napi::Number Wrap_FindWindowA(const Napi::CallbackInfo &info);
  Napi::Number Wrap_FindWindowExA(const Napi::CallbackInfo &info);
  Napi::Boolean Wrap_PostMessageA(const Napi::CallbackInfo &info);
  Napi::Boolean Wrap_SendMessageA(const Napi::CallbackInfo &info);
  Napi::Number Wrap_GetDpiForWindow(const Napi::CallbackInfo &info);
  Napi::Number Wrap_GetDpiForSystem(const Napi::CallbackInfo &info);
  Napi::Value Wrap_GetClientRect(const Napi::CallbackInfo &info);
  Napi::Value Wrap_GetClipCursor(const Napi::CallbackInfo &info);
  Napi::Value Wrap_GetWindowRect(const Napi::CallbackInfo &info);
  Napi::Number Wrap_GetWindow(const Napi::CallbackInfo &info);
  Napi::Number Wrap_GetAncestor(const Napi::CallbackInfo &info);
  Napi::Value Wrap_GetCursorInfo(const Napi::CallbackInfo &info);
  Napi::Number Wrap_ShowCursor(const Napi::CallbackInfo &info);
  Napi::Boolean Wrap_ShowWindow(const Napi::CallbackInfo &info);
  Napi::Boolean Wrap_UpdateWindow(const Napi::CallbackInfo &info);
  Napi::Number Wrap_SetWindowLongPtrA(const Napi::CallbackInfo &info);
  Napi::Number Wrap_GetWindowLongPtrA(const Napi::CallbackInfo &info);
  Napi::Boolean Wrap_SetLayeredWindowAttributes(const Napi::CallbackInfo &info);
  Napi::Value Wrap_GetLayeredWindowAttributes(const Napi::CallbackInfo &info);
  Napi::Boolean Wrap_SetWindowPos(const Napi::CallbackInfo &info);
  Napi::String Wrap_GetWindowText(const Napi::CallbackInfo &info);
  Napi::Boolean Wrap_SetForegroundWindow(const Napi::CallbackInfo &info);
  Napi::Number Wrap_WindowFromPoint(const Napi::CallbackInfo &info);
  Napi::Boolean Wrap_IsWindow(const Napi::CallbackInfo &info);
  Napi::Value Wrap_GetWindowInfo(const Napi::CallbackInfo &info);
  Napi::Value Wrap_EnumWindows(const Napi::CallbackInfo &info);
  Napi::Value Wrap_EnumDesktopWindows(const Napi::CallbackInfo &info);
  Napi::Number Wrap_GetDesktopWindow(const Napi::CallbackInfo &info);
  Napi::Number Wrap_GetActiveWindow(const Napi::CallbackInfo &info);
  Napi::Number Wrap_GetLastError(const Napi::CallbackInfo &info);
  Napi::Number Wrap_GetForegroundWindow(const Napi::CallbackInfo &info);
  Napi::Value Wrap_GetWindowThreadProcessId(const Napi::CallbackInfo &info);
  Napi::Boolean Wrap_IsWindowVisible(const Napi::CallbackInfo &info);
  Napi::Boolean Wrap_IsWindowEnabled(const Napi::CallbackInfo &info);
  Napi::Boolean Wrap_IsWindowUnicode(const Napi::CallbackInfo &info);
  Napi::Boolean Wrap_IsZoomed(const Napi::CallbackInfo &info);
  Napi::String Wrap_GetClassName(const Napi::CallbackInfo &info);
  Napi::Number Wrap_GetClassLongPtrA(const Napi::CallbackInfo &info);
  Napi::Number Wrap_SetClassLongPtrA(const Napi::CallbackInfo &info);
  Napi::Number GetWindowHicon(const Napi::CallbackInfo &info);
  Napi::Boolean Wrap_EnableWindow(const Napi::CallbackInfo &info);
  Napi::Value Wrap_EnumChildWindows(const Napi::CallbackInfo &info);

}