
#include "RoboInterface.h"

#include <napi.h>

#include <string>

/*
 some resources that might be helpful

 - good guide
 https://itnext.io/a-simple-guide-to-load-c-c-code-into-node-js-javascript-applications-3fcccf54fd32
 - node-gyp repo https://github.com/nodejs/node-gyp
 - node-addon-api https://github.com/nodejs/node-addon-api
*/

Napi::Object InitAll(Napi::Env env, Napi::Object exports) { return RoboInterface::Init(env, exports); }

NODE_API_MODULE(nlibroboint, InitAll)
