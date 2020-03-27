/**
 *  Shows how to read analog inputs
 */

const libroboint = require('../lib/index');

const ri = new libroboint.RoboInterface({
    enableDistance: false,
});

console.log('A1', ri.getA1());
console.log('A2', ri.getA2());
console.log('AY', ri.getAY());
console.log('AX', ri.getAX());
console.log('D1', ri.getD1());
console.log('D2', ri.getD2());

ri.close();

const ri2 = new libroboint.RoboInterface({
    enableDistance: true,
});

console.log('D1', ri2.getD1());
console.log('D2', ri2.getD2());

ri2.close();
