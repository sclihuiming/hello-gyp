#include <napi.h>

// 用来覆盖 valueOf 实现的函数
Napi::Value GetValue(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  // 获取我们在创建 valueOf 函数的时候传入的 result
  double* storageData = reinterpret_cast<double*>(info.Data());

  // 避免空指针情况
  if (storageData == NULL) {
    return Napi::Number::New(env, 0);
  } else {
    return Napi::Number::New(env, *storageData);
  }

}

Napi::Function CurryAdd(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  // 获取我们下边在创建 curryAdd 函数的时候传入的 result
  double* storageData = reinterpret_cast<double*>(info.Data());

  double* result = new double;

  // 遍历传入的所有参数
  long len, index;
  for (len = info.Length(), index = 0; index < len; index++) {
    double arg = info[index].As<Napi::Number>().DoubleValue();

    *result += arg;
  }

  // 用于多次的计算
  if (storageData != NULL) {
    *result += *storageData;
  }

  // 创建一个新的函数用于函数的返回值
  Napi::Function fn = Napi::Function::New(env, CurryAdd, "curryAdd", result);

  // 篡改 valueOf 方法，用于输出结果
  fn.Set("valueOf", Napi::Function::New(env, GetValue, "valueOf", result));

  return fn;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  Napi::Function fn = Napi::Function::New(env, CurryAdd, "curryAdd");

  exports.Set(Napi::String::New(env, "curryAdd"), fn);

  return exports;
}

NODE_API_MODULE(curryadd, Init)