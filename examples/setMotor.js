/**
 *  Shows how to write a program that uses "setMotor"
 */

const sleep = require('util').promisify(setTimeout);

const libroboint = require('../lib/index');

async function program() {
    const M1 = 1;

    libroboint.connect();

    libroboint.setMotor(M1, libroboint.MOTOR_DIR_RIGHT, 2);
    await sleep(500);
    libroboint.setMotor(M1, libroboint.MOTOR_DIR_LEFT, 3);
    await sleep(500);
    libroboint.setMotor(M1, libroboint.MOTOR_DIR_RIGHT, 4);
    await sleep(500);
    libroboint.setMotor(M1, libroboint.MOTOR_DIR_LEFT, 5);
    await sleep(500);
    libroboint.setMotor(M1, libroboint.MOTOR_DIR_STOP);
}

program();
