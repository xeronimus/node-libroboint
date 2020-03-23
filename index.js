const addon = require('bindings')('nlibroboint');
exports.hello = addon.greetHello;