const addon = require('bindings')('nlibroboint');


module.exports = {
    ...addon,
    notifyOnInputChange,
    MOTOR_DIR_LEFT: 1,
    MOTOR_DIR_RIGHT: 2,
    MOTOR_DIR_STOP: 0,

    SERIAL_TYPE_INTELLIGENT_IF: 10,
    SERIAL_TYPE_INTELLIGENT_IF_SLAVE: 20,
    SERIAL_TYPE_ROBO_IF_COM: 70,

};

const INPUT_CHECK_INTERVAL = 50;


/**
 *
 * @param {object} ri The RoboInterface instance
 * @param inputsToCheck
 * @param onInputChange
 * @return {number}
 */
function notifyOnInputChange(ri, inputsToCheck, onInputChange) {

    let inputState = {};
    return setInterval(() => {

        const newState = {};
        inputsToCheck.forEach((input) => {
            newState[input] = ri.getInput(input);
        });
        if (!statesEqual(inputState, newState)) {
            onInputChange(newState);
        }
        inputState = newState;

    }, INPUT_CHECK_INTERVAL);

}

function statesEqual(stateOne, stateTwo) {
    return !Object.entries(stateOne).find((entry) => stateTwo[entry[0]] !== entry[1]);
}
