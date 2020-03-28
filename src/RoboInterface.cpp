#include "RoboInterface.h"

#include <roboint.h>

// Default Distance sensor-Input configuration
#define IF_DS_INPUT_TOL 20     // Toleranz (Standard)
#define IF_DS_INPUT_REP 3      // Repeat (Standard)
#define IF_DS_INPUT_THRESH 100 // Threshold (Standard)

Napi::FunctionReference RoboInterface::constructor;

/**
*
* Is called when module is registered. will return node module
*
*/
Napi::Object RoboInterface::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(
      env, "RoboInterface",
      {

          InstanceMethod("hasInterface", &RoboInterface::HasInterface), InstanceMethod("close", &RoboInterface::Close),

          InstanceMethod("getDeviceType", &RoboInterface::GetDeviceType),
          InstanceMethod("getDeviceTypeString", &RoboInterface::GetDeviceTypeString),

          InstanceMethod("setMotor", &RoboInterface::SetMotor), InstanceMethod("setOutput", &RoboInterface::SetOutput),

          InstanceMethod("getInput", &RoboInterface::GetInput), InstanceMethod("getA1", &RoboInterface::GetA1),
          InstanceMethod("getA2", &RoboInterface::GetA2), InstanceMethod("getAX", &RoboInterface::GetAX),
          InstanceMethod("getAY", &RoboInterface::GetAY), InstanceMethod("getD1", &RoboInterface::GetD1),
          InstanceMethod("getD2", &RoboInterface::GetD2),

      });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("RoboInterface", func);
  return exports;
}

/**
*
* Parses constructor arguments into RI_OPTIONS
*
*/
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

/**
*
* The constructor
* called when instantiating a new RoboInterface
*
*/
RoboInterface::RoboInterface(const Napi::CallbackInfo &info) : Napi::ObjectWrap<RoboInterface>(info) {
  this->transfer_area = NULL;

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

/**
*
* Returns the type of the interface (as integer), which is one of
*
* NO_FT_DEVICE                0       // No ft Device connected
* FT_AUTO_TYPE                1       // Search for Device
* FT_INTELLIGENT_IF           10      // FT-Intelligent Interface connect (serial)
* FT_INTELLIGENT_IF_SLAVE     20      // FT-Intelligent Interface with Extension connect (serial)
* FT_ROBO_IF_IIM              50      // FT-Robo Interface with Intelligent-Interface-Modus connect (serial)
* FT_ROBO_IF_USB              60      // FT-Robo Interface connect with USB-Port
* FT_ROBO_IF_COM              70      // FT-Robo Interface connect with COM- (serial-) Port
* FT_ROBO_IF_OVER_RF          80      // FT-Robo Interface connect over RF-Data-Link
* FT_ROBO_IO_EXTENSION        90      // FT-Robo I/O-Extension
* FT_ROBO_LT_CONTROLLER       91      // FT-Robo LT Controller
* FT_ROBO_RF_DATA_LINK        110     // FT-Robo RF Data Link
* FT_SOUND_AND_LIGHTS         120     // FT-Sound + Lights Module
*
*/
Napi::Value RoboInterface::GetDeviceType(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (this->hFt) {
    return Napi::Number::New(env, GetFtDeviceTyp(this->hFt));
  } else {
    return Napi::Number::New(env, 0);
  }
}

/**
*
* Returns a string that identifies this interface in a human readable form like "Robo Interface"
*
*/
Napi::Value RoboInterface::GetDeviceTypeString(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (this->hFt) {
    char *result = new char[128];
    GetFtDeviceTypeString(this->hFt, result, 128);
    return Napi::String::New(env, result);
  } else {
    return Napi::String::New(env, "0");
  }
}

/**
*
* Tells if we have a connection to the Interface
*
*
*/
Napi::Value RoboInterface::HasInterface(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (this->hFt && this->transfer_area) {
    return Napi::Boolean::New(env, true);
  } else {
    return Napi::Boolean::New(env, false);
  }
}

/**
*
* Closes the connection to the ftDevice
*
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

/**
*
* Set a Motor's speed and direction
*
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

/**
*
* Set an output's power
*
*/
Napi::Value RoboInterface::SetOutput(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (!this->transfer_area) {
    Napi::TypeError::New(env, "Cannot setOutput, not connected...").ThrowAsJavaScriptException();
    return env.Null();
  }

  //--   check input parameters
  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsNumber() || (info.Length() > 1 && !info[1].IsNumber())) {
    Napi::TypeError::New(env, "Wrong arguments, pass in two numbers").ThrowAsJavaScriptException();
    return env.Null();
  }

  int output = info[0].As<Napi::Number>().Int32Value();
  int speed = info.Length() > 1 ? info[1].As<Napi::Number>().Int32Value() : 7;

  if (output < 0 || output > 32) {
    Napi::TypeError::New(env, "Output must be between 0 and 32").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (speed < 0 || speed > 7) {
    Napi::TypeError::New(env, "Speed must be between 0 and 7").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (output <= 8) {
    if (speed == 0) {
      this->transfer_area->M_Main &= ~(1 << (output - 1));
    } else {
      this->transfer_area->M_Main |= (1 << (output - 1));
    }
    this->transfer_area->MPWM_Main[output - 1] = speed;
  } else if (output <= 16) {
    output -= 8;

    if (speed == 0) {
      this->transfer_area->M_Sub1 &= ~(1 << (output - 1));
    } else {
      this->transfer_area->M_Sub1 |= (1 << (output - 1));
    }
    this->transfer_area->MPWM_Sub1[output - 1] = speed;
  } else if (output <= 24) {
    output -= 16;

    if (speed == 0) {
      this->transfer_area->M_Sub2 &= ~(1 << (output - 1));
    } else {
      this->transfer_area->M_Sub2 |= (1 << (output - 1));
    }
    this->transfer_area->MPWM_Sub2[output - 1] = speed;
  } else if (output <= 32) {
    output -= 24;

    if (speed == 0) {
      this->transfer_area->M_Sub3 &= ~(1 << (output - 1));
    } else {
      this->transfer_area->M_Sub3 |= (1 << (output - 1));
    }
    this->transfer_area->MPWM_Sub3[output - 1] = speed;
  }

  return env.Null();
}

/**
 *
 * Gets the state of a digital input. Pass in the number of the input (1...Max).
 * Will return 1 or 0
 *
*/
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

/**
*
* helper function that reads a analog input (A1, A2, AX, AY, D1, D2)
*
*/
Napi::Value _getAnalogInput(FT_TRANSFER_AREA *transfer_area, int analogInput, const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (!transfer_area) {
    Napi::TypeError::New(env, "Cannot get analog input, not connected...").ThrowAsJavaScriptException();
    return env.Null();
  }

  unsigned short analogValue;

  switch (analogInput) {
  case 1:
    analogValue = transfer_area->A1;
    break;
  case 2:
    analogValue = transfer_area->A2;
    break;
  case 3:
    analogValue = transfer_area->AY;
    break;
  case 4:
    analogValue = transfer_area->AX;
    break;
  case 5:
    analogValue = transfer_area->D1;
    break;
  case 6:
    analogValue = transfer_area->D2;
    break;

  default:
    analogValue = transfer_area->A1;
  }

  Napi::Number result = Napi::Number::New(env, analogValue);

  return result;
}

/**
*
* Reads analog voltage input A1
*
*/
Napi::Value RoboInterface::GetA1(const Napi::CallbackInfo &info) {
  return _getAnalogInput(this->transfer_area, 1, info);
}

/**
*
* Reads analog voltage input A2
*
*/
Napi::Value RoboInterface::GetA2(const Napi::CallbackInfo &info) {
  return _getAnalogInput(this->transfer_area, 2, info);
}

/**
*
* Reads analog resistor input AX
*
*/
Napi::Value RoboInterface::GetAX(const Napi::CallbackInfo &info) {
  return _getAnalogInput(this->transfer_area, 3, info);
}

/**
*
* Reads analog resistor input AY
*
*/
Napi::Value RoboInterface::GetAY(const Napi::CallbackInfo &info) {
  return _getAnalogInput(this->transfer_area, 4, info);
}

/**
*
* Reads analog (voltage or distance) input D1
*
*/
Napi::Value RoboInterface::GetD1(const Napi::CallbackInfo &info) {
  return _getAnalogInput(this->transfer_area, 5, info);
}

/**
*
* Reads analog (voltage or distance) input D2
*
*/
Napi::Value RoboInterface::GetD2(const Napi::CallbackInfo &info) {
  return _getAnalogInput(this->transfer_area, 6, info);
}
