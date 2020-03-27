/**
 *
 */

const libroboint = require('../lib/index');

libroboint.connect();

libroboint.loop((endCb, loopCounter) => {
    const [turnCounter, resetTurnCounter] = libroboint.useCounter(1);

    if (turnCounter > 10) {
        console.log('reached 11, resetting');
        resetTurnCounter();
    }

    if (loopCounter > 200) {
        endCb();
    }
}, 20);
