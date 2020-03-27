/**
 *  Shows how to read analog inputs
 */

const libroboint = require('../lib/index');

libroboint.connect({
    enableDistance: false,
});

console.log('A1', libroboint.getA1());
console.log('A2', libroboint.getA2());
console.log('AX', libroboint.getAX());
console.log('AY', libroboint.getAY());
console.log('D1', libroboint.getD1());
console.log('D2', libroboint.getD2());

libroboint.close();

// now connect again with "enableDistance=true"
libroboint.connect({
    enableDistance: true,
});

console.log('A1', libroboint.getA1());
console.log('A2', libroboint.getA2());
console.log('AX', libroboint.getAX());
console.log('AY', libroboint.getAY());
console.log('D1', libroboint.getD1());
console.log('D2', libroboint.getD2());

libroboint.close();
