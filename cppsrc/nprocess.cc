
#include <Windows.h>
#include "nprocess.h"
#include "util.cc"
#include <TlHelp32.h>
#include <Psapi.h>
using namespace std;
#pragma region QueryFullProcessImageName
Napi::String nprocess::Wrap_QueryFullProcessImageName(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsNumber())
  {
    error = Napi::Error::New(env, "Pid should be a number.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::String::New(env, "");
  }
  DWORD Pid = (uint32_t)info[0].As<Napi::Number>();
  HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, Pid);
  DWORD dwSize = 1024;
  char *name = new char[dwSize];
  QueryFullProcessImageNameA(hProcess, PROCESS_NAME_NATIVE, name, &dwSize);
  CloseHandle(hProcess);
  return Napi::String::New(env, AnsiToUtf8(name));
}
#pragma endregion QueryFullProcessImageName

#pragma region DriveToDosDevice
Napi::Array nprocess::GetDrives(const Napi::CallbackInfo &info)
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
    return Napi::Array::New(env, 0);
  }
  DWORD drives;
  drives = GetLogicalDrives();
  int count = 0;
  Napi::Array result = Napi::Array::New(env);
  int idx = 0;
  while (drives != 0)
  {
    if ((drives & 1) != 0)
    {

      char drive = 'A' + count;
      result.Set(idx, drive);
      idx++;
    }
    drives >>= 1;
    count++;
  }
  return result;
}
Napi::String nprocess::DriveToDosDevice(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsString())
  {
    error = Napi::Error::New(env, "Drive should be a String.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::String::New(env, "");
  }
  std::string drive = info[0].As<Napi::String>();
  drive.push_back(':');
  char dos[MAX_PATH];
  QueryDosDeviceA(drive.c_str(), dos, MAX_PATH);
  drive = dos;
  return Napi::String::New(env, dos);
}
#pragma endregion DriveToDosDevice

#pragma region ProcessSnapshot
Napi::Value nprocess::ProcessSnapshot(const Napi::CallbackInfo &info)
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
    return Napi::Boolean::New(env, false);
  }
  HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (hProcessSnap == INVALID_HANDLE_VALUE)
  {
    return Napi::Boolean::New(env, false);
  }
  PROCESSENTRY32W pe32;
  pe32.dwSize = sizeof(pe32);
  BOOL bMore = ::Process32FirstW(hProcessSnap, &pe32);
  Napi::Array result = Napi::Array::New(env);
  while (bMore)
  {
    wstring ws(pe32.szExeFile);
    DWORD dBufSize = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, 0, 0, NULL, NULL);
    char *dBuf = new char[dBufSize];
    memset(dBuf, 0, dBufSize);
    int nRet = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, dBuf, dBufSize, NULL, FALSE);
    Napi::Object p = Napi::Object::New(env);
    p.Set("ExeFile", dBuf);
    delete[] dBuf;
    p.Set("ParentId", pe32.th32ParentProcessID);
    p.Set("Id", pe32.th32ProcessID);
    p.Set("cntThreads", pe32.cntThreads);
    p.Set("pcPriClassBase", pe32.pcPriClassBase);
    result.Set(result.Length(), p);
    bMore = ::Process32NextW(hProcessSnap, &pe32);
  }
  ::CloseHandle(hProcessSnap);
  return result;
}
#pragma endregion ProcessSnapshot

#pragma region ProcessSnapshot_cb
Napi::Boolean nprocess::ProcessSnapshot_cb(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  if (!info[0].IsFunction())
  {
    error = Napi::Error::New(env, "callback not is Function ");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  PROCESSENTRY32W pe32;
  pe32.dwSize = sizeof(pe32);
  BOOL bMore = ::Process32FirstW(hProcessSnap, &pe32);
  Napi::Function cb = info[0].As<Napi::Function>();
  while (bMore)
  {
    wstring ws(pe32.szExeFile);
    DWORD dBufSize = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, 0, 0, NULL, NULL);
    char *dBuf = new char[dBufSize];
    memset(dBuf, 0, dBufSize);
    int nRet = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, dBuf, dBufSize, NULL, FALSE);
    Napi::Object p = Napi::Object::New(env);
    p.Set("ExeFile", dBuf);
    delete[] dBuf;
    p.Set("ParentId", pe32.th32ParentProcessID);
    p.Set("Id", pe32.th32ProcessID);
    p.Set("cntThreads", pe32.cntThreads);
    p.Set("pcPriClassBase", pe32.pcPriClassBase);
    cb.Call(env.Global(), {p});
    bMore = ::Process32NextW(hProcessSnap, &pe32);
  }
  ::CloseHandle(hProcessSnap);
  return Napi::Boolean::New(env, true);
}
#pragma endregion ProcessSnapshot_cb

#pragma region EnumProcesses
Napi::Boolean nprocess::Wrap_EnumProcesses(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsFunction())
  {
    error = Napi::Error::New(env, "callback should be a function.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  Napi::Function cb = info[0].As<Napi::Function>();
  DWORD aProcesses[1024], cbNeeded;
  if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
  {
    return Napi::Boolean::New(env, false);
  }
  int cProcesses = cbNeeded / sizeof(DWORD);
  for (int i = 0; i < cProcesses; i++)
  {
    cb.Call(env.Global(), {Napi::Number::New(env, aProcesses[i])});
  }
  return Napi::Boolean::New(env, true);
}
#pragma endregion EnumProcesses

#pragma region GetCurrentProcess
Napi::Number nprocess::Wrap_GetCurrentProcessId(const Napi::CallbackInfo &info)
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
  return Napi::Number::New(env, GetCurrentProcessId());
}
#pragma endregion GetCurrentProcess

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("QueryFullProcessImageName", Napi::Function::New(env, nprocess::Wrap_QueryFullProcessImageName));
  exports.Set("DriveToDosDevice", Napi::Function::New(env, nprocess::DriveToDosDevice));
  exports.Set("GetDrives", Napi::Function::New(env, nprocess::GetDrives));
  exports.Set("ProcessSnapshot", Napi::Function::New(env, nprocess::ProcessSnapshot));
  exports.Set("ProcessSnapshot_cb", Napi::Function::New(env, nprocess::ProcessSnapshot_cb));
  exports.Set("EnumProcesses", Napi::Function::New(env, nprocess::Wrap_EnumProcesses));
  exports.Set("GetCurrentProcessId", Napi::Function::New(env, nprocess::Wrap_GetCurrentProcessId));
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)