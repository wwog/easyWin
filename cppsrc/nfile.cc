#include <ShlObj_core.h>
#include "nfile.h"
#include <string>
#include "util.cc"
#include <iostream>
using namespace std;

#pragma region OpenFolderAndSelect
Napi::Boolean nfile::Wrap_SHOpenFolderAndSelectItems(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Error error;
  if (info.Length() < 1)
  {
    error = Napi::Error::New(env, "Wrong number of arguments.");
  }
  else if (!info[0].IsString())
  {
    error = Napi::Error::New(env, "path should be a string.");
  }
  if (error)
  {
    error.ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  string p = Utf8ToAnsi(info[0].As<Napi::String>());
  LPITEMIDLIST pidlFolder = ILCreateFromPathA(p.c_str());
  if (pidlFolder == 0)
  {
    cout << "pidlFolder" << endl;
    return Napi::Boolean::New(env, false);
  }
  CoInitialize(NULL);
  HRESULT result = SHOpenFolderAndSelectItems(pidlFolder, 0, 0, 0);
  ILFree(pidlFolder);
  return Napi::Boolean::New(env, result == S_OK);
}
#pragma endregion

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("OpenFolderAndSelect", Napi::Function::New(env, nfile::Wrap_SHOpenFolderAndSelectItems));
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)