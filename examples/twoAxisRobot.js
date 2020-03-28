/**
 * Two Axis Welding Robot from the Set "Industry Robots II"  2005: 96782p
 * https://ft-datenbank.de/binary/7084
 */

const libroboint = require('../lib/index');

libroboint.connect();

// turning constants
const TURN_END_SWITCH = 1; // the input of the mini touch sensor that marks end position
const TURN_COUNT_SWITCH = 5; // the input of the mini touch sensor on the turn motor
const TURN_SPEED = 5; // how fast should the robot turn
const TURN_ES_TOWARDS = libroboint.MOTOR_DIR_LEFT;
const TURN_ES_AWAY = libroboint.MOTOR_DIR_RIGHT;
const MOTOR_TURN = 1; // Motor output for turning

// arm constants
const ARM_END_SWITCH = 2; // the input of the mini touch sensor at the top of the arm
const ARM_COUNT_SWITCH = 4; // the input mini touch sensor on the axis of the arm motor
const ARM_SPEED = 6; // how fast should the arm extend / retract
const ARM_ES_TOWARDS = libroboint.MOTOR_DIR_LEFT;
const ARM_ES_AWAY = libroboint.MOTOR_DIR_RIGHT;
const MOTOR_ARM = 2; // Motor output for the arm

const MOTOR_LIGHT = 3;

let initTurnPositionReached = false;
let initArmPositionReached = false;
libroboint.loop((endCb, loopCounter) => {
    // initializing state
    if (!initTurnPositionReached) {
        libroboint.setMotor(MOTOR_TURN, TURN_ES_TOWARDS, TURN_SPEED);
        if (libroboint.getInput(TURN_END_SWITCH)) {
            initTurnPositionReached = true;
            libroboint.setMotor(MOTOR_TURN, libroboint.MOTOR_DIR_STOP);
        }
    }

    if (!initArmPositionReached) {
        libroboint.setMotor(MOTOR_ARM, ARM_ES_TOWARDS, ARM_SPEED);
        if (libroboint.getInput(ARM_END_SWITCH)) {
            initArmPositionReached = true;
            libroboint.setMotor(MOTOR_ARM, libroboint.MOTOR_DIR_STOP);
        }
    }

    if (!initArmPositionReached || !initTurnPositionReached) {
        return;
    }

    // robot is moving

    const [turnCounter, resetTurnCounter] = libroboint.useCounter(TURN_COUNT_SWITCH);
    const [armCounter, resetArmCounter] = libroboint.useCounter(ARM_COUNT_SWITCH);

    if (libroboint.getInput(TURN_END_SWITCH)) {
        // we reached end position, reverse direction
        libroboint.setMotor(MOTOR_TURN, TURN_ES_AWAY, TURN_SPEED);

        // turn the light on
        libroboint.setMotor(MOTOR_LIGHT, libroboint.MOTOR_DIR_LEFT);

        resetTurnCounter();
    } else if (turnCounter > 110) {
        // limit on the other side is reached when turnCounter is above threshold, reverse direction
        libroboint.setMotor(MOTOR_TURN, TURN_ES_TOWARDS, TURN_SPEED);

        // turn the light off
        libroboint.setMotor(MOTOR_LIGHT, libroboint.MOTOR_DIR_STOP);
    }

    if (libroboint.getInput(ARM_END_SWITCH)) {
        // we reached end position, reverse direction
        libroboint.setMotor(MOTOR_ARM, ARM_ES_AWAY, ARM_SPEED);
    } else if (armCounter > 80) {
        // limit on the other side is reached when turnCounter is above threshold, reverse direction
        libroboint.setMotor(MOTOR_ARM, ARM_ES_TOWARDS, ARM_SPEED);

        resetArmCounter();
    }

    if (loopCounter > 100000) {
        // just make sure to end at some point
        endCb();
    }
}, 10);
