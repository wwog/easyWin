#include <napi.h>

namespace ndraw
{
  Napi::Boolean Wrap_drawBorder(const Napi::CallbackInfo &info);
  Napi::Boolean HIconSave(const Napi::CallbackInfo &info);
  Napi::Value HIconToBuffer(const Napi::CallbackInfo &info);
  
}