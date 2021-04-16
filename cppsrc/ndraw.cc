#include <Windows.h>
#include <gdiplus.h>
#include <iostream>
#include "ndraw.h"
#include "util.cc"
#pragma comment(lib, "gdiplus.lib")
using namespace std;

#pragma region tool
void doEvent()
{
  MSG currMSG;
  while (PeekMessageA(&currMSG, 0, 0, 0, 1))
  {
    TranslateMessage(&currMSG);
    DispatchMessageA(&currMSG);
  }
}
void SleepApp(int ms)
{
  LARGE_INTEGER liDueTime;
  liDueTime.QuadPart = -10 * ms * 1000;
  HANDLE timer = CreateWaitableTimerA(0, false, 0);
  SetWaitableTimer(timer, &liDueTime, 0, 0, 0, false);
  while (MsgWaitForMultipleObjects(1, &timer, false, -1, 255))
  {
    if (GetInputState() != 0)
      doEvent();
  }
}
int GetImageCLSID(const WCHAR *format, CLSID *pCLSID)
{
  UINT num = 0;
  UINT size = 0;
  Gdiplus::ImageCodecInfo *pImageCodecInfo = NULL;
  Gdiplus::GetImageEncodersSize(&num, &size);
  if (size == 0)
    return FALSE;

  pImageCodecInfo = (Gdiplus::ImageCodecInfo *)(malloc(size));
  if (pImageCodecInfo == NULL)
    return FALSE;

  Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

  for (UINT i = 0; i < num; ++i)
  {
    if (wcscmp(pImageCodecInfo[i].MimeType, format) == 0)
    {
      *pCLSID = pImageCodecInfo[i].Clsid;
      free(pImageCodecInfo);
      return TRUE;
    }
  }
  free(pImageCodecInfo);
  return FALSE;
}
#pragma endregion tool

#pragma region drawBorder
Napi::Boolean ndraw::Wrap_drawBorder(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  //(hwnd,color,width,flash)
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
    error = Napi::Error::New(env, "width should be a number.");
  }
  else if (!info[2].IsNumber())
  {
    error = Napi::Error::New(env, "color should be a number.");
  }
  else if (!info[3].IsBoolean())
  {
    error = Napi::Error::New(env, "flash should be a boolean.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  RECT rect;
  HWND hwnd = (HWND) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  int PenWidth = info[1].As<Napi::Number>();
  int color = info[2].As<Napi::Number>();
  bool flash = info[3].As<Napi::Boolean>();
  HWND desktop = GetDesktopWindow();
  HDC desktopDC = GetWindowDC(desktop);
  int oldMode = SetROP2(desktopDC, R2_NOTXORPEN);
  GetWindowRect(hwnd, &rect);
  if (rect.left < 0)
  {
    rect.left = 0;
  }
  if (rect.top < 0)
  {
    rect.top = 0;
  }
  HPEN pen = CreatePen(0, PenWidth, color);
  HGDIOBJ obj = SelectObject(desktopDC, pen);
  Rectangle(desktopDC, rect.left, rect.top, rect.right, rect.bottom);
  if (flash)
  {
    SleepApp(60);
    Rectangle(desktopDC, rect.left, rect.top, rect.right, rect.bottom);
    SetROP2(desktopDC, oldMode);
  }

  SelectObject(desktopDC, obj);
  DeleteObject(pen);
  ReleaseDC(desktop, desktopDC);

  return Napi::Boolean::New(env, true);
}
#pragma endregion drawBorder

#pragma region HIconSave
Napi::Boolean ndraw::HIconSave(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 2)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "hIcon should be a number.");
  }
  else if (!info[1].IsString())
  {
    error = Napi::Error::New(env, "filePath should be a string.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  HICON hIcon = (HICON) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  string filePath = info[1].As<Napi::String>();
  Gdiplus::GdiplusStartupInput gdiplusStartupInput;
  ULONG_PTR gdiplusToken;
  CLSID clsid;

  GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
  Gdiplus::Bitmap *bmp = Gdiplus::Bitmap::FromHICON(hIcon);

  GetImageCLSID(L"image/png", &clsid);
  Gdiplus::Status stat = bmp->Save(AnsiToUnicode(filePath).c_str(), &clsid, NULL);
  delete bmp;
  Gdiplus::GdiplusShutdown(gdiplusToken);
  return Napi::Boolean::New(env, stat == Gdiplus::Ok);
}
#pragma endregion HIconSave

#pragma region HIconToArrayBuffer
Napi::Value ndraw::HIconToBuffer(const Napi::CallbackInfo &info)
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
  HICON hIcon = (HICON) reinterpret_cast<size_t *>((int64_t)info[0].As<Napi::Number>());
  Gdiplus::GdiplusStartupInput gdiplusStartupInput;
  ULONG_PTR gdiplusToken;
  CLSID clsid;

  Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

  Gdiplus::Bitmap *bmp = Gdiplus::Bitmap::FromHICON(hIcon);
  GetImageCLSID(L"image/png", &clsid);

  IStream *pStream = NULL;

  HGLOBAL pMem = GlobalAlloc(GMEM_MOVEABLE, 0);
  CreateStreamOnHGlobal(pMem, true, &pStream);
  bmp->Save(pStream, &clsid, NULL);

  DWORD dwSize = GlobalSize(pMem);
  LPVOID i = GlobalLock(pMem);
  BYTE *bytes = new BYTE[dwSize];
  CopyMemory(bytes, i, dwSize);

  Napi::Array res = Napi::Array::New(env);

  for (int idx = 0; idx < (int)dwSize; idx++)
  {
    res.Set(idx, bytes[idx]);
  }
  delete[] bytes;
  GlobalUnlock(pMem);
  GlobalFree(pMem);
  Gdiplus::GdiplusShutdown(gdiplusToken);
  return res;
}
#pragma endregion HIconToBuffer

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("drawBorder", Napi::Function::New(env, ndraw::Wrap_drawBorder));
  exports.Set("HIconSave", Napi::Function::New(env, ndraw::HIconSave));
  exports.Set("HIconToBuffer", Napi::Function::New(env, ndraw::HIconToBuffer));
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)