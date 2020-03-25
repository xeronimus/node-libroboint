#include "RoboInterface.h"

#include <roboint.h>

// Default Distance sensor-Input configuration
#define IF_DS_INPUT_TOL 20     // Toleranz (Standard)
#define IF_DS_INPUT_REP 3      // Repeat (Standard)
#define IF_DS_INPUT_THRESH 100 // Threshold (Standard)

Napi::FunctionReference RoboInterface::constructor;

/*

 Is called when module is registered. will return node module

*/
Napi::Object RoboInterface::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "RoboInterface", {InstanceMethod("setMotor", &RoboInterface::SetMotor),
                                                           InstanceMethod("getInput", &RoboInterface::GetInput),
                                                           InstanceMethod("hasInterface", &RoboInterface::HasInterface),
                                                           InstanceMethod("close", &RoboInterface::Close)});

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("RoboInterface", func);
  return exports;
}

RI_OPTIONS parseConstructorOptions(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  RI_OPTIONS opts;

  // defaults
  opts.deviceNumber = 0;
  opts.usbSerial = 0;
  opts.startTransferArea = true;
  opts.serialDevice = NULL;
  opts.enableDistance = false;

  if (info.Length() < 1) {
    return opts;
  }

  if (!info[0].IsObject()) {
    Napi::TypeError::New(env, "If you want to configure the interface, pass in a options object..")
        .ThrowAsJavaScriptException();
    return opts;
  }

  // we have a options object
  Napi::Object options = info[0].As<Napi::Object>();

  if (options.Has("deviceNumber")) {
    opts.deviceNumber = options.Get("deviceNumber").As<Napi::Number>().Uint32Value();
  }
  if (options.Has("usbSerial")) {
    opts.usbSerial = options.Get("usbSerial").As<Napi::Number>().Uint32Value();
  }
  if (options.Has("serialDevice")) {
    std::string sdValue = options.Get("serialDevice").As<Napi::String>().Utf8Value();
    opts.serialDevice = &sdValue[0u];
  }

  if (options.Has("startTransferArea")) {
    opts.startTransferArea = options.Get("startTransferArea").As<Napi::Boolean>().Value();
  }
  if (options.Has("enableDistance")) {
    opts.enableDistance = options.Get("enableDistance").As<Napi::Boolean>().Value();
  }

  return opts;
}

/*

 The constructor
 called when instantiating a new RoboInterface

 const ri = new libroboint.RoboInterface();
 // do some stuff, and remember to close afterwards... ri.close();


*/
RoboInterface::RoboInterface(const Napi::CallbackInfo &info) : Napi::ObjectWrap<RoboInterface>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  // initialize connection according to options
  RI_OPTIONS opts = parseConstructorOptions(info);

  if (opts.serialDevice) {
    this->hFt = OpenFtCommDevice(opts.serialDevice, opts.serialType, 10);
  } else {
    InitFtUsbDeviceList();
    if (opts.usbSerial > 0) {
      this->hFt = GetFtUsbDeviceHandleSerialNr(opts.usbSerial, 1);
    } else {
      this->hFt = GetFtUsbDeviceHandle(opts.deviceNumber);
    }
    OpenFtUsbDevice(this->hFt);
  }

  if (opts.enableDistance) {
    SetFtDistanceSensorMode(this->hFt, 1, IF_DS_INPUT_TOL, IF_DS_INPUT_TOL, IF_DS_INPUT_THRESH, IF_DS_INPUT_THRESH,
                            IF_DS_INPUT_REP, IF_DS_INPUT_REP);
  } else {
    SetFtDistanceSensorMode(this->hFt, 0, IF_DS_INPUT_TOL, IF_DS_INPUT_TOL, IF_DS_INPUT_THRESH, IF_DS_INPUT_THRESH,
                            IF_DS_INPUT_REP, IF_DS_INPUT_REP);
  }

  if (opts.startTransferArea) {
    StartFtTransferArea(this->hFt, NULL);
    this->transfer_area = GetFtTransferAreaAddress(this->hFt);
  }
}

/*

 Tells if we have a connection to the Interface

 Useful to call after the constructor., e.g:
        const ri = new libroboint.RoboInterface();

        if(ri.hasInterface()){
         // do something
        }

*/
Napi::Value RoboInterface::HasInterface(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (this->hFt && this->transfer_area) {
    return Napi::Boolean::New(env, true);
  } else {
    return Napi::Boolean::New(env, false);
  }
}

/*

 Closes the connection to the ftDevice. Currently this must be called manually from your JS code.

 const ri = new libroboint.RoboInterface();
 // do some stuff
 ri.close();


*/
Napi::Value RoboInterface::Close(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (this->transfer_area) {
    StopFtTransferArea(this->hFt);
    this->transfer_area = NULL;
  }

  if (this->hFt) {
    CloseFtDevice(this->hFt);
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