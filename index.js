const addon = require('bindings')('nlibroboint');


const api = {
    initFtUsbDeviceList: addon.initFtUsbDeviceList,
    getNumFtUsbDevice: addon.getNumFtUsbDevice,
    getFtUsbDeviceHandle: addon.getFtUsbDeviceHandle
};


module.exports = api;