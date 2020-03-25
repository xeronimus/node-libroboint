const libroboint = require('./index');


const ri = new libroboint.RoboInterface();

/*
setTimeout(() => ri.setMotor(1, libroboint.MOTOR_DIR_RIGHT, 1), 1000);
setTimeout(() => ri.setMotor(1, libroboint.MOTOR_DIR_LEFT, 2), 2000);
setTimeout(() => ri.setMotor(1, libroboint.MOTOR_DIR_RIGHT, 3), 3000);
setTimeout(() => ri.setMotor(1, libroboint.MOTOR_DIR_LEFT, 4), 4000);
setTimeout(() => ri.setMotor(1, libroboint.MOTOR_DIR_RIGHT, 5), 5000);
setTimeout(() => ri.setMotor(1, libroboint.MOTOR_DIR_LEFT, 6), 6000);
setTimeout(() => ri.setMotor(1, libroboint.MOTOR_DIR_RIGHT), 7000);


setTimeout(() => ri.setMotor(1, libroboint.MOTOR_DIR_STOP), 8000);


*/

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

