const addon = require('bindings')('nlibroboint');
/**
 * The single entry point for interacting with the ROBO Interface
 *
 * @module libroboint
 */

/**
 * @private
 * single instance of {@link RoboInterface} after "connect()" was invoked
 */
let RI_INSTANCE;

/**
 *
 * If you need multiple instances (e.g. two Robo interfaces on two separate USB ports), you can use the class directly.
 * Remember to call *close* on each of your instances.
 *
 * @example
 * const libroboint = require('libroboint');
 * const ri = new libroboint.RoboInterface(connectOptions);
 * ri.setMotor(1,libroboint.MOTOR_DIR_LEFT);
 * ri.close();
 *
 * @static RoboInterface
 */
const RoboInterface = addon.RoboInterface;

/**
 *
 * Connect to the Robo Interface
 *
 * @example
 * const libroboint = require('libroboint');
 * libroboint.connect({
 *    deviceNumber: 0
 * });
 *
 * @param {Object} [opts] The connection options. Optional.
 * @param {number} opts.deviceNumber The number of the device to connect to, defaults to 0.
 * @param {number} opts.usbSerial If specified, will connect using the serialNumber.
 * @param {number} opts.serialType Type of device at serial port, either FT_INTELLIGENT_IF (10), FT_INTELLIGENT_IF_SLAVE (20) or FT_ROBO_IF_COM (70)
 * @param {boolean} opts.enableDistance Enable D1 and D2 for use with the ft distance sensor, defaults to false
 * @param {boolean} opts.startTransferArea  Start the transfer area. Usually you want that, defaults to true
 *
 * @static
 */
const connect = (opts) => {
    RI_INSTANCE = new addon.RoboInterface(opts || {});
};

/**
 *
 * Tells if we have a connection to the Interface.
 * Useful to call after "connect()"
 *
 * @example
 * const libroboint = require('libroboint');
 * libroboint.connect();
 * if(libroboint.hasInterface()){
 *     // do something
 * }
 *
 * @return {boolean}
 *
 * @static
 */
const hasInterface = () => RI_INSTANCE.hasInterface();

/**
 *
 * Closes the connection to the ftDevice. This is also done when the nodeJS process is terminated (SIGINT).
 *
 * @example
 * const libroboint = require('libroboint');
 * libroboint.connect();
 * // do something
 * libroboint.close();
 *
 * @static
 */
const close = () => {
    if (!RI_INSTANCE) {
        return;
    }

    if (RI_INSTANCE.loopIntervalHs) {
        RI_INSTANCE.loopIntervalHs.forEach((h) => clearInterval(h));
    }

    RI_INSTANCE.close();
};
process.on('SIGINT', close);

/**
 *
 * Returns a string that identifies this interface in a human readable form like "Robo Interface"
 *
 * @return {string}
 *
 * @static
 */
const getDeviceTypeString = () => RI_INSTANCE.getDeviceTypeString();

/**
 *
 * Returns the type of the interface (as integer), which is one of
 *
 * ```
 * NO_FT_DEVICE                0       // No ft Device connected
 * FT_AUTO_TYPE                1       // Search for Device
 * FT_INTELLIGENT_IF           10      // FT-Intelligent Interface connect (serial)
 * FT_INTELLIGENT_IF_SLAVE     20      // FT-Intelligent Interface with Extension connect (serial)
 * FT_ROBO_IF_IIM              50      // FT-Robo Interface with Intelligent-Interface-Modus connect (serial)
 * FT_ROBO_IF_USB              60      // FT-Robo Interface connect with USB-Port
 * FT_ROBO_IF_COM              70      // FT-Robo Interface connect with COM- (serial-) Port
 * FT_ROBO_IF_OVER_RF          80      // FT-Robo Interface connect over RF-Data-Link
 * FT_ROBO_IO_EXTENSION        90      // FT-Robo I/O-Extension
 * FT_ROBO_LT_CONTROLLER       91      // FT-Robo LT Controller
 * FT_ROBO_RF_DATA_LINK        110     // FT-Robo RF Data Link
 * FT_SOUND_AND_LIGHTS         120     // FT-Sound + Lights Module
 * ```
 *
 * @return {number}
 *
 * @static
 */
const getDeviceType = () => RI_INSTANCE.getDeviceType();

/**
 *
 * Sets a motor's speed and direction
 *
 * @example
 * const libroboint = require('libroboint');
 * libroboint.connect();
 * libroboint.setMotor(1, libroboint.MOTOR_DIR_STOP); // stop motor 1
 * libroboint.setMotor(2, libroboint.MOTOR_DIR_LEFT, 5); // start motor 2, direction left with speed 5
 * libroboint.setMotor(2, libroboint.MOTOR_DIR_RIGHT); // start motor 2, direction right with default speed (max = 7)
 *
 * @param {number} motor The motor number, 1-4, with I/O Extensions also 5-8, 9-12, 13-16
 * @param {number} direction The direction. one of libroboint.MOTOR_DIR_LEFT (1), libroboint.MOTOR_DIR_RIGHT (2), libroboint.MOTOR_DIR_STOP (0)
 * @param {number} [speed=7] The speed between 0 and 7. Optional. Defaults to 7
 *
 * @return null
 *
 * @static
 */
function setMotor(motor, direction, speed) {
    RI_INSTANCE.setMotor.apply(RI_INSTANCE, arguments);
}

/**
 *
 * Sets a outputs's power
 *
 * @param {number} output The putput number, 1-8, with I/O Extensions also 9-16, 17-24, 25-32
 * @param {number} [power=7] The power between 0 and 7. Optional. Defaults to 7
 *
 * @example
 * const libroboint = require('libroboint');
 * libroboint.connect();
 * libroboint.setOutput(7); // set output 7 on (default power)
 * libroboint.setOutput(2, 5); // set output 2 on, with power 5
 *
 * @static
 */
function setOutput(output, power) {
    RI_INSTANCE.setOutput.apply(RI_INSTANCE, arguments);
}

/**
 *
 * Gets the state of a digital input.
 *
 * @example
 * const libroboint = require('libroboint');
 * libroboint.connect();
 * console.log(libroboint.getInput(1));
 *
 * @param {number} inputNumber The input between 1 and Max
 * @return {number} 1 or 0
 *
 * @static
 */
const getInput = (inputNumber) => RI_INSTANCE.getInput(inputNumber);

/**
 *
 * Reads analog input A1
 *
 * @return {number} The voltage between 0 and 1023
 *
 * @static
 */
const getA1 = () => RI_INSTANCE.getA1();

/**
 *
 * Reads analog input A2
 *
 * @return {number} The voltage between 0 and 1023
 *
 * @static
 */
const getA2 = () => RI_INSTANCE.getA2();

/**
 *
 * Reads analog input AX
 *
 * @return {number} The resistor value between 0 and 1023
 *
 * @static
 */
const getAX = () => RI_INSTANCE.getAX();

/**
 *
 * Reads analog input AY
 *
 * @return {number} The resistor value between 0 and 1023
 *
 * @static
 */
const getAY = () => RI_INSTANCE.getAY();

/**
 *
 * Reads analog input D1
 *
 * @return {number} The voltage or distance value between 0 and 1023. Depending on connect option flag "enableDistance"
 *
 * @static
 */
const getD1 = () => RI_INSTANCE.getD1();

/**
 *
 * Reads analog input D2
 *
 * @return {number} The voltage or distance value between 0 and 1023. Depending on connect option flag "enableDistance"
 *
 * @static
 */
const getD2 = () => RI_INSTANCE.getD2();

/**
 *
 * @param {function} theLoop
 * @param {number} interval The interval in milliseconds
 *
 * @static
 */
function loop(theLoop, interval = 50) {
    if (!RI_INSTANCE || !RI_INSTANCE.hasInterface()) {
        console.error('not connected, will not loop');
    }

    let loopCounter = 1;
    let intervalH = setInterval(() => {
        checkCounters();
        theLoop.call(theLoop, endCb, loopCounter);
        loopCounter++;
    }, interval);

    // keep a reference to all intervalHandles
    if (!RI_INSTANCE.loopIntervalHs) {
        RI_INSTANCE.loopIntervalHs = [];
    }
    RI_INSTANCE.loopIntervalHs.push(intervalH);

    function endCb() {
        clearInterval(intervalH);
        RI_INSTANCE.close();
    }
}

/**
 * Checking registered input counters (once per loop iteration)
 *
 * @private
 */
function checkCounters() {
    if (!RI_INSTANCE.counters) {
        return;
    }

    Object.entries(RI_INSTANCE.counters).forEach((entry) => {
        const newState = RI_INSTANCE.getInput(parseInt(entry[0], 10));

        if (newState !== entry[1].s) {
            if (newState) {
                entry[1].v++;
            }
        }
        entry[1].s = newState;
    });
}

/**
 *
 * Use within loop to count "switching" on a digital input.
 * This will count state change from 0 to 1.
 * Handy when using a mini switch on a axle.
 *
 * @example
 * const [c, resetC] = libroboint.useCounter(1);
 * if (c > 10) {
 *       console.log('reached 11, resetting');
 *       resetC();
 *   }
 *
 * @param {number} inputNumber
 *
 * @static
 */
function useCounter(inputNumber) {
    if (!RI_INSTANCE || !RI_INSTANCE.hasInterface()) {
        console.error('not connected, cannot count');
    }

    let inputNumberParsed = parseInt(inputNumber, 10);

    if (!RI_INSTANCE.counters) {
        RI_INSTANCE.counters = {};
    }

    if (RI_INSTANCE.counters[inputNumberParsed]) {
        return [RI_INSTANCE.counters[inputNumberParsed].v, resetCounter];
    }

    RI_INSTANCE.counters[inputNumberParsed] = {
        v: 0,
        s: undefined,
    };

    function resetCounter() {
        RI_INSTANCE.counters[inputNumberParsed].v = 0;
    }

    return [RI_INSTANCE.counters[inputNumberParsed].v, resetCounter];
}

const libroboint = {
    connect,
    hasInterface,
    close,
    getDeviceType,
    getDeviceTypeString,

    setMotor,
    setOutput,

    getInput,
    getA1,
    getA2,
    getAX,
    getAY,
    getD1,
    getD2,

    RoboInterface,

    loop,

    useCounter,

    /**
     * @static
     *
     * @constant MOTOR_DIR_LEFT
     */
    MOTOR_DIR_LEFT: 1,

    /**
     * @static
     *
     * @constant MOTOR_DIR_RIGHT
     */
    MOTOR_DIR_RIGHT: 2,

    /**
     * @static
     *
     * @constant MOTOR_DIR_STOP
     */
    MOTOR_DIR_STOP: 0,

    SERIAL_TYPE_INTELLIGENT_IF: 10,
    SERIAL_TYPE_INTELLIGENT_IF_SLAVE: 20,
    SERIAL_TYPE_ROBO_IF_COM: 70,
};

module.exports = libroboint;
