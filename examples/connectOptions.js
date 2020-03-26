/**
 *  Shows different connection options (via usb, serial, serialNumber or deviceId, etc.)
 */

const libroboint = require('../lib/index');

const ri = new libroboint.RoboInterface({
    deviceNumber: 0,
    //  usbSerial:12345,
    startTransferArea: true,
    //   serialDevice :'/dev/ttyS0',
    // serialType:libroboint.SERIAL_TYPE_INTELLIGENT_IF,
    enableDistance: true,
});

if (ri.hasInterface()) {
    console.log('type', ri.getDeviceType(), ri.getDeviceTypeString());
}

ri.close();
