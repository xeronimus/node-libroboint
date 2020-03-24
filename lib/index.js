const addon = require('bindings')('nlibroboint');


module.exports = {
    ...addon,
    notifyOnInputChange,
    MOTOR_DIR_LEFT: 1,
    MOTOR_DIR_RIGHT: 2,
    MOTOR_DIR_STOP: 0,
};

const INPUT_CHECK_INTERVAL = 50;


/**
 *
 * @param conn
 * @param inputsToCheck
 * @param onInputChange
 * @return {number}
 */
function notifyOnInputChange(conn, inputsToCheck, onInputChange) {

    let inputState = {};
    return setInterval(() => {

        const newState = {};
        inputsToCheck.forEach((input) => {
            newState[input] = conn.getInput(input);
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
