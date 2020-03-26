const addon = require('bindings')('nlibroboint');

const utils = require('./utils');

module.exports = {
    ...addon,

    ...utils,

    MOTOR_DIR_LEFT: 1,
    MOTOR_DIR_RIGHT: 2,
    MOTOR_DIR_STOP: 0,

    SERIAL_TYPE_INTELLIGENT_IF: 10,
    SERIAL_TYPE_INTELLIGENT_IF_SLAVE: 20,
    SERIAL_TYPE_ROBO_IF_COM: 70,
};
