/**
 *  Shows different connection options (via usb, serial, serialNumber or deviceId, etc.)
 */

const libroboint = require('../lib/index');

const ri = new libroboint.RoboInterface({
    deviceNumber: 0,
    //  usbSerial:12345,
    startTransferArea: false,
    //   serialDevice :'/dev/ttyS0',
    // serialType:libroboint.SERIAL_TYPE_INTELLIGENT_IF,
    enableDistance: true,
});

// this works without starting transfer area
console.log('type', ri.getDeviceType(), ri.getDeviceTypeString());

if (!ri.hasInterface()) {
    console.log('we did not start transferArea. hasInterface() returns false.');
}

ri.close();
