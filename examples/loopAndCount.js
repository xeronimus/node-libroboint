/**
 *  Shows how to write a program that uses the "loop" utility function to count input changes on digital input
 */

const libroboint = require('../lib/index');

const ri = new libroboint.RoboInterface();

let inpOneLastState = 0;
let inpOneCounter = 0;
libroboint.loop(
    ri,
    (endCb) => {
        let inpOneNewState = ri.getInput(1);

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
    },
    10
);
