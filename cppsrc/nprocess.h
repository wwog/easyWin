#include <napi.h>

namespace nprocess
{
  Napi::String Wrap_QueryFullProcessImageName(const Napi::CallbackInfo &info);
  Napi::String DriveToDosDevice(const Napi::CallbackInfo &info);
  Napi::Array GetDrives(const Napi::CallbackInfo &info);
  Napi::Boolean Wrap_EnumProcesses(const Napi::CallbackInfo &info);
  Napi::Value ProcessSnapshot(const Napi::CallbackInfo &info);
  Napi::Boolean ProcessSnapshot_cb(const Napi::CallbackInfo &info);
  Napi::Number Wrap_GetCurrentProcessId(const Napi::CallbackInfo &info);
}