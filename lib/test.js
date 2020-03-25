const libroboint = require('./index');


const ri = new libroboint.RoboInterface();

if (ri.hasInterface()) {


    ri.setMotor(2, libroboint.MOTOR_DIR_RIGHT, 1);

    const intervalH = libroboint.notifyOnInputChange(ri, [1], (state) => {
        if (state[1]) {
            ri.setMotor(2, libroboint.MOTOR_DIR_STOP);
        } else {
            ri.setMotor(2, libroboint.MOTOR_DIR_RIGHT, 1);
        }
    });

    setTimeout(() => {
        console.log('closing...');

        clearInterval(intervalH);

        ri.close();

    }, 15000);


} else {
    console.error('Sorry, could not connect');
}
