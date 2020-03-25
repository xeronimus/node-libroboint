#include "RoboInterface.h"

#include <roboint.h>

Napi::FunctionReference RoboInterface::constructor;

/*

 Is called when module is registered. will return node module

*/
Napi::Object RoboInterface::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "RoboInterface", {InstanceMethod("setMotor", &RoboInterface::SetMotor),
                                                           InstanceMethod("getInput", &RoboInterface::GetInput),
                                                           InstanceMethod("close", &RoboInterface::Close)});

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("RoboInterface", func);
  return exports;
}

/*

 The constructor
 called when instantiating a new RoboInterface

 const conn = new libroboint.RoboInterface();
 // do some stuff, and remember to close afterwards... conn.close();


*/
RoboInterface::RoboInterface(const Napi::CallbackInfo &info) : Napi::ObjectWrap<RoboInterface>(info) {

  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  // initialize
  InitFtUsbDeviceList();

  this->hFt = GetFtUsbDeviceHandle(0);

  // Open connection
  OpenFtUsbDevice(this->hFt);

  StartFtTransferArea(this->hFt, NULL);
  this->transfer_area = GetFtTransferAreaAddress(this->hFt);
}

/*

 Closes the connection to the ftDevice. Currently this must be called manually from your JS code.

 const conn = new libroboint.RoboInterface();
 // do some stuff
 conn.close();


*/
Napi::Value RoboInterface::Close(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (this->hFt) {
    StopFtTransferArea(this->hFt);
    CloseFtDevice(this->hFt);
    this->transfer_area = NULL;
  }

  return env.Null();
}

/*

 Set a Motor's speed and direction

 Example Usage in JS:

 ri.setMotor(1, 0); // stop motor 1
 ri.setMotor(2, 1, 5); // start motor 2, direction left (1) with speed 5
 ri.setMotor(2, 2); // start motor 2, direction right  (2) with default speed (max = 7)

*/
Napi::Value RoboInterface::SetMotor(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (!this->transfer_area) {
    Napi::TypeError::New(env, "Cannot setMotor, not connected...").ThrowAsJavaScriptException();
    return env.Null();
  }

  //--   check input parameters
  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsNumber() || !info[1].IsNumber() || (info.Length() > 2 && !info[2].IsNumber())) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  int motor = info[0].As<Napi::Number>().Int32Value();
  int direction = info[1].As<Napi::Number>().Int32Value();
  int speed = info.Length() > 2 ? info[2].As<Napi::Number>().Int32Value() : 7;

  if (motor < 0 || motor > 16) {
    Napi::TypeError::New(env, "Motor must be between 0 and 16").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (speed < 0 || speed > 7) {
    Napi::TypeError::New(env, "Speed must be between 0 and 7").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (direction < 0 || direction > 2) {
    Napi::TypeError::New(env, "Direction must be either 0 (stop), 1 (left) or 2 (right)").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (motor <= 4) { // main module
    this->transfer_area->M_Main &= ~(3 << (motor - 1) * 2);
    this->transfer_area->M_Main |= direction << (motor - 1) * 2;
    this->transfer_area->MPWM_Main[(motor - 1) * 2] = speed;
    this->transfer_area->MPWM_Main[(motor - 1) * 2 + 1] = speed;
  } else if (motor <= 8) { // extension module 1
    motor -= 4;
    this->transfer_area->M_Sub1 &= ~(3 << (motor - 1) * 2);
    this->transfer_area->M_Sub1 |= direction << (motor - 1) * 2;
    this->transfer_area->MPWM_Sub1[(motor - 1) * 2] = speed;
    this->transfer_area->MPWM_Sub1[(motor - 1) * 2 + 1] = speed;
  } else if (motor <= 12) { // extension module 2
    motor -= 8;
    this->transfer_area->M_Sub2 &= ~(3 << (motor - 1) * 2);
    this->transfer_area->M_Sub2 |= direction << (motor - 1) * 2;
    this->transfer_area->MPWM_Sub2[(motor - 1) * 2] = speed;
    this->transfer_area->MPWM_Sub2[(motor - 1) * 2 + 1] = speed;
  } else if (motor <= 16) { // extension module 3
    motor -= 12;
    this->transfer_area->M_Sub3 &= ~(3 << (motor - 1) * 2);
    this->transfer_area->M_Sub3 |= direction << (motor - 1) * 2;
    this->transfer_area->MPWM_Sub3[(motor - 1) * 2] = speed;
    this->transfer_area->MPWM_Sub3[(motor - 1) * 2 + 1] = speed;
  }

  return env.Null();
}

Napi::Value RoboInterface::GetInput(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (!this->transfer_area) {
    Napi::TypeError::New(env, "Cannot getInput, not connected...").ThrowAsJavaScriptException();
    return env.Null();
  }

  //--   check input parameters
  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Please specify the input number (1-32)").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsNumber()) {
    Napi::TypeError::New(env, "Please specify the input number (1-32)").ThrowAsJavaScriptException();
    return env.Null();
  }

  int inputNumber = info[0].As<Napi::Number>().Int32Value();

  if (inputNumber < 1 || inputNumber > 32) {
    Napi::TypeError::New(env, "Please specify the input number (1-32)").ThrowAsJavaScriptException();
    return env.Null();
  }

  int inputState = 0;

  if (inputNumber <= 8) {
    inputState = (this->transfer_area->E_Main & (1 << (inputNumber - 1))) >> (inputNumber - 1);
  } else if (inputNumber <= 16) {
    inputNumber -= 8;
    inputState = (this->transfer_area->E_Sub1 & (1 << (inputNumber - 1))) >> (inputNumber - 1);
  } else if (inputNumber <= 24) {
    inputNumber -= 16;
    inputState = (this->transfer_area->E_Sub2 & (1 << (inputNumber - 1))) >> (inputNumber - 1);
  } else if (inputNumber <= 32) {
    inputNumber -= 24;
    inputState = (this->transfer_area->E_Sub3 & (1 << (inputNumber - 1))) >> (inputNumber - 1);
  }

  Napi::Number result = Napi::Number::New(env, inputState);
  return result;
}