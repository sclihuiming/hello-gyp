#include <napi.h>

// 定义 Add 函数
Napi::Value Add(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  // 接收第一个参数
  double arg0 = info[0].As<Napi::Number>().DoubleValue();
  // 接收第二个参数
  double arg1 = info[1].As<Napi::Number>().DoubleValue();
  // 将两个参数相加并返回
  Napi::Number num = Napi::Number::New(env, arg0 + arg1);

  return num;
}

// 入口函数，用于注册我们的函数、对象等等
Napi::Object Init(Napi::Env env, Napi::Object exports) {
  // 将一个名为 add 的函数挂载到 exports 上
  exports.Set(Napi::String::New(env, "add"), Napi::Function::New(env, Add));
  return exports;
}

// 固定的宏使用
NODE_API_MODULE(addon, Init)