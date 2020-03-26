const libroboint = require('./index');


const ri = new libroboint.RoboInterface({
    deviceNumber: 0,
    //  usbSerial:12345,
    startTransferArea: true,
    //   serialDevice :'/dev/ttyS0',
    // serialType:libroboint.SERIAL_TYPE_INTELLIGENT_IF,
    enableDistance: false
});

if (ri.hasInterface()) {

    console.log(ri.getDeviceType());
    console.log(ri.getDeviceTypeString());

    ri.setMotor(2, libroboint.MOTOR_DIR_RIGHT, 1);

    const intervalH = libroboint.notifyOnInputChange(ri, [1], (state) => {
        if (state[1]) {
            ri.setMotor(2, libroboint.MOTOR_DIR_STOP);
        } else {
            ri.setMotor(2, libroboint.MOTOR_DIR_RIGHT, 1);
        }
    });

    setTimeout(() => {
        console.log('closing...');

        clearInterval(intervalH);

        ri.close();

    }, 15000);


} else {
    console.error('Sorry, could not connect');
}
