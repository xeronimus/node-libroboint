/**
 *  Shows how to write a program that uses "setOutput"
 */

const sleep = require('util').promisify(setTimeout);

const libroboint = require('../lib/index');

async function program() {
    const o1 = 1;
    const o2 = 2;

    libroboint.connect();

    libroboint.setOutput(o1, 2);
    await sleep(500);
    libroboint.setOutput(o2, 5);
    await sleep(500);
    libroboint.setOutput(o1); // set to max power
    await sleep(500);
    libroboint.setOutput(o2, 0);
    await sleep(500);
    libroboint.setOutput(o1, 2);
}

program();
