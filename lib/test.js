const libroboint = require('./index');


const conn = new libroboint.RoboIfConnection();

setTimeout(() => conn.setMotor(1, libroboint.MOTOR_DIR_RIGHT, 1), 1000);
setTimeout(() => conn.setMotor(1, libroboint.MOTOR_DIR_LEFT, 2), 2000);
setTimeout(() => conn.setMotor(1, libroboint.MOTOR_DIR_RIGHT, 3), 3000);
setTimeout(() => conn.setMotor(1, libroboint.MOTOR_DIR_LEFT, 4), 4000);
setTimeout(() => conn.setMotor(1, libroboint.MOTOR_DIR_RIGHT, 5), 5000);
setTimeout(() => conn.setMotor(1, libroboint.MOTOR_DIR_LEFT, 6), 6000);
setTimeout(() => conn.setMotor(1, libroboint.MOTOR_DIR_RIGHT), 7000);


setTimeout(() => conn.setMotor(1, libroboint.MOTOR_DIR_STOP), 8000);
setTimeout(() => {
    console.log('closing...');
    conn.close();
}, 9000);
