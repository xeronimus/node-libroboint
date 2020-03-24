const libroboint = require('./index');


const conn = new libroboint.RoboIfConnection();

/*
setTimeout(() => conn.setMotor(1, libroboint.MOTOR_DIR_RIGHT, 1), 1000);
setTimeout(() => conn.setMotor(1, libroboint.MOTOR_DIR_LEFT, 2), 2000);
setTimeout(() => conn.setMotor(1, libroboint.MOTOR_DIR_RIGHT, 3), 3000);
setTimeout(() => conn.setMotor(1, libroboint.MOTOR_DIR_LEFT, 4), 4000);
setTimeout(() => conn.setMotor(1, libroboint.MOTOR_DIR_RIGHT, 5), 5000);
setTimeout(() => conn.setMotor(1, libroboint.MOTOR_DIR_LEFT, 6), 6000);
setTimeout(() => conn.setMotor(1, libroboint.MOTOR_DIR_RIGHT), 7000);


setTimeout(() => conn.setMotor(1, libroboint.MOTOR_DIR_STOP), 8000);


*/

conn.setMotor(2, libroboint.MOTOR_DIR_RIGHT, 1);

const intervalH = libroboint.notifyOnInputChange(conn, [1], (state) => {
    if (state[1]) {
        conn.setMotor(2, libroboint.MOTOR_DIR_STOP);
    } else {
        conn.setMotor(2, libroboint.MOTOR_DIR_RIGHT, 1);
    }
});

setTimeout(() => {
    console.log('closing...');

    clearInterval(intervalH);

    conn.close();

}, 15000);

