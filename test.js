const libroboint = require('./index');


console.log(libroboint);


libroboint.initFtUsbDeviceList();
const n = libroboint.getNumFtUsbDevice();

console.log('Number of FT Devices on USB:', n);

if (n > 0) {
    console.log('getting handle...');
    libroboint.getFtUsbDeviceHandle(1);
}