const addon = require('bindings')('nlibroboint');

module.exports = {
    ...addon,
    MOTOR_DIR_LEFT: 1,
    MOTOR_DIR_RIGHT: 2,
    MOTOR_DIR_STOP: 0,
};