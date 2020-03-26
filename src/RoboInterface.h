#ifndef ROBOIFCONN_H
#define ROBOIFCONN_H

#include <roboint.h>

#include <napi.h>

typedef struct _RI_OPTIONS {

  // USB Device to use. 0 will be the first Interface found.
  int deviceNumber;

  // Open the USB Device with this serial number
  int usbSerial;

  // Use a serial device: Don't use USB. e.g. "/dev/ttyS0"
  char *serialDevice;

  //  Type of device at serial port, either FT_INTELLIGENT_IF (10), FT_INTELLIGENT_IF_SLAVE (20) or FT_ROBO_IF_COM (70)
  int serialType;

  // Start the transfer area. Usually you want that
  bool startTransferArea;

  // Enable D1 and D2 for use with the ft distance sensor
  bool enableDistance;

} RI_OPTIONS;

class RoboInterface : public Napi::ObjectWrap<RoboInterface> {

public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  RoboInterface(const Napi::CallbackInfo &info);

private:
  static Napi::FunctionReference constructor;

  Napi::Value HasInterface(const Napi::CallbackInfo &info);
  Napi::Value Close(const Napi::CallbackInfo &info);

  Napi::Value GetDeviceType(const Napi::CallbackInfo &info);
  Napi::Value GetDeviceTypeString(const Napi::CallbackInfo &info);

  Napi::Value SetMotor(const Napi::CallbackInfo &info);

  Napi::Value GetInput(const Napi::CallbackInfo &info);
  Napi::Value GetA1(const Napi::CallbackInfo &info);
  Napi::Value GetA2(const Napi::CallbackInfo &info);
  Napi::Value GetAX(const Napi::CallbackInfo &info);
  Napi::Value GetAY(const Napi::CallbackInfo &info);
  Napi::Value GetD1(const Napi::CallbackInfo &info);
  Napi::Value GetD2(const Napi::CallbackInfo &info);

  FT_HANDLE hFt;
  FT_TRANSFER_AREA *transfer_area;
};

#endif