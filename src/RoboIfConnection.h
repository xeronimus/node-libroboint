#ifndef ROBOIFCONN_H
#define ROBOIFCONN_H

#include <roboint.h>

#include <napi.h>

class RoboIfConnection : public Napi::ObjectWrap<RoboIfConnection> {

public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  RoboIfConnection(const Napi::CallbackInfo &info);

private:
  static Napi::FunctionReference constructor;

  Napi::Value SetMotor(const Napi::CallbackInfo &info);
  Napi::Value Close(const Napi::CallbackInfo &info);
  Napi::Value GetInput(const Napi::CallbackInfo &info);

  FT_HANDLE hFt;
  FT_TRANSFER_AREA *transfer_area;
};

#endif