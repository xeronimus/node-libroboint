
#include <roboint.h>

#include <napi.h>

#include <string>


void _initFtUsbDeviceList(const Napi::CallbackInfo& info) {
    InitFtUsbDeviceList();
}

Napi::Number _getNumFtUsbDevice(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    unsigned int result = GetNumFtUsbDevice();

    return Napi::Number::New(env, result);
}

void _getFtUsbDeviceHandle(const Napi::CallbackInfo& info) {

    unsigned char deviceNr = info[0].As<Napi::Number>().Uint32Value();

    FT_HANDLE hFt = GetFtUsbDeviceHandle(deviceNr);
}



Napi::Object Init(Napi::Env env, Napi::Object exports) {

    exports.Set(
        "initFtUsbDeviceList",
        Napi::Function::New(env, _initFtUsbDeviceList)
    );

    exports.Set(
        "getNumFtUsbDevice",
        Napi::Function::New(env, _getNumFtUsbDevice)
    );
    exports.Set(
        "getFtUsbDeviceHandle",
        Napi::Function::New(env, _getFtUsbDeviceHandle)
    );

    return exports;
}

NODE_API_MODULE(nlibroboint, Init)