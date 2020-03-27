/**
 *  Shows how to write a program that uses the "loop" utility function to count input changes on digital input
 */

const libroboint = require('../lib/index');

libroboint.connect();

let inpOneLastState = 0;
let inpOneCounter = 0;
libroboint.loop((endCb) => {
    let inpOneNewState = libroboint.getInput(1);

    if (inpOneNewState !== inpOneLastState) {
        // input changed, let's count
        if (inpOneNewState) {
            inpOneCounter++;
            console.log(inpOneCounter);
        }

        if (inpOneCounter >= 10) {
            endCb();
        }
    }

    inpOneLastState = inpOneNewState;
}, 10);
