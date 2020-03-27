/**
 * One Axis Welding Robot from the Set "Industry Robots II"  2005: 96782p
 * https://ft-datenbank.de/binary/7084
 */

const libroboint = require('../lib/index');

libroboint.connect();

const TURN_END_SWITCH = 2;
const TURN_COUNT_SWITCH = 1;
const TURN_SPEED = 5;
const TURN_ES_TOWARDS = libroboint.MOTOR_DIR_RIGHT;
const TURN_ES_AWAY = libroboint.MOTOR_DIR_LEFT;

const MOTOR_TURN = 1;
const MOTOR_LIGHT = 4;

let initPositionReached = false;
libroboint.loop((endCb, loopCounter) => {
    // initializing state

    if (!initPositionReached) {
        libroboint.setMotor(MOTOR_TURN, TURN_ES_TOWARDS, TURN_SPEED);
        if (libroboint.getInput(TURN_END_SWITCH)) {
            initPositionReached = true;
        }
        return;
    }

    // robot is moving

    const [turnCounter, resetTurnCounter] = libroboint.useCounter(TURN_COUNT_SWITCH);

    if (libroboint.getInput(TURN_END_SWITCH)) {
        // we reached end position, reverse direction
        libroboint.setMotor(MOTOR_TURN, TURN_ES_AWAY, TURN_SPEED);

        // turn the light on
        libroboint.setMotor(MOTOR_LIGHT, libroboint.MOTOR_DIR_LEFT);

        resetTurnCounter();
    } else if (turnCounter > 20) {
        // limit on the other side is reached when turnCounter is above 20, reverse direction
        libroboint.setMotor(MOTOR_TURN, TURN_ES_TOWARDS, TURN_SPEED);

        // turn the light off
        libroboint.setMotor(MOTOR_LIGHT, libroboint.MOTOR_DIR_STOP);
    }

    if (loopCounter > 100000) {
        // just make sure to end at some point
        endCb();
    }
}, 10);
