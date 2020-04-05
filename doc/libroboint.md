<a name="module_libroboint"></a>

## libroboint
The single entry point for interacting with the ROBO Interface


* [libroboint](#module_libroboint)
    * [.RoboInterface](#module_libroboint.RoboInterface)
    * [.MOTOR_DIR_LEFT](#module_libroboint.MOTOR_DIR_LEFT)
    * [.MOTOR_DIR_RIGHT](#module_libroboint.MOTOR_DIR_RIGHT)
    * [.MOTOR_DIR_STOP](#module_libroboint.MOTOR_DIR_STOP)
    * [.connect([opts])](#module_libroboint.connect)
    * [.hasInterface()](#module_libroboint.hasInterface) ⇒ <code>boolean</code>
    * [.close()](#module_libroboint.close)
    * [.getDeviceTypeString()](#module_libroboint.getDeviceTypeString) ⇒ <code>string</code>
    * [.getDeviceType()](#module_libroboint.getDeviceType) ⇒ <code>number</code>
    * [.setMotor(motor, direction, [speed])](#module_libroboint.setMotor) ⇒
    * [.setOutput(output, [power])](#module_libroboint.setOutput)
    * [.getInput(inputNumber)](#module_libroboint.getInput) ⇒ <code>number</code>
    * [.getA1()](#module_libroboint.getA1) ⇒ <code>number</code>
    * [.getA2()](#module_libroboint.getA2) ⇒ <code>number</code>
    * [.getAX()](#module_libroboint.getAX) ⇒ <code>number</code>
    * [.getAY()](#module_libroboint.getAY) ⇒ <code>number</code>
    * [.getD1()](#module_libroboint.getD1) ⇒ <code>number</code>
    * [.getD2()](#module_libroboint.getD2) ⇒ <code>number</code>
    * [.loop(theLoop, interval)](#module_libroboint.loop)
    * [.useCounter(inputNumber)](#module_libroboint.useCounter)

<a name="module_libroboint.RoboInterface"></a>

### libroboint.RoboInterface
If you need multiple instances (e.g. two Robo interfaces on two separate USB ports), you can use the class directly.
Remember to call *close* on each of your instances.

**Kind**: static constant of [<code>libroboint</code>](#module_libroboint)  
**Example**  
```js
const libroboint = require('libroboint');
const ri = new libroboint.RoboInterface(connectOptions);
ri.setMotor(1,libroboint.MOTOR_DIR_LEFT);
ri.close();
```
<a name="module_libroboint.MOTOR_DIR_LEFT"></a>

### libroboint.MOTOR\_DIR\_LEFT
**Kind**: static constant of [<code>libroboint</code>](#module_libroboint)  
<a name="module_libroboint.MOTOR_DIR_RIGHT"></a>

### libroboint.MOTOR\_DIR\_RIGHT
**Kind**: static constant of [<code>libroboint</code>](#module_libroboint)  
<a name="module_libroboint.MOTOR_DIR_STOP"></a>

### libroboint.MOTOR\_DIR\_STOP
**Kind**: static constant of [<code>libroboint</code>](#module_libroboint)  
<a name="module_libroboint.connect"></a>

### libroboint.connect([opts])
Connect to the Robo Interface

**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  

| Param | Type | Description |
| --- | --- | --- |
| [opts] | <code>Object</code> | The connection options. Optional. |
| opts.deviceNumber | <code>number</code> | The number of the device to connect to, defaults to 0. |
| opts.usbSerial | <code>number</code> | If specified, will connect using the serialNumber. |
| opts.serialType | <code>number</code> | Type of device at serial port, either FT_INTELLIGENT_IF (10), FT_INTELLIGENT_IF_SLAVE (20) or FT_ROBO_IF_COM (70) |
| opts.enableDistance | <code>boolean</code> | Enable D1 and D2 for use with the ft distance sensor, defaults to false |
| opts.startTransferArea | <code>boolean</code> | Start the transfer area. Usually you want that, defaults to true |

**Example**  
```js
const libroboint = require('libroboint');
libroboint.connect({
   deviceNumber: 0
});
```
<a name="module_libroboint.hasInterface"></a>

### libroboint.hasInterface() ⇒ <code>boolean</code>
Tells if we have a connection to the Interface.
Useful to call after "connect()"

**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  
**Example**  
```js
const libroboint = require('libroboint');
libroboint.connect();
if(libroboint.hasInterface()){
    // do something
}
```
<a name="module_libroboint.close"></a>

### libroboint.close()
Closes the connection to the ftDevice. This is also done when the nodeJS process is terminated (SIGINT).

**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  
**Example**  
```js
const libroboint = require('libroboint');
libroboint.connect();
// do something
libroboint.close();
```
<a name="module_libroboint.getDeviceTypeString"></a>

### libroboint.getDeviceTypeString() ⇒ <code>string</code>
Returns a string that identifies this interface in a human readable form like "Robo Interface"

**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  
<a name="module_libroboint.getDeviceType"></a>

### libroboint.getDeviceType() ⇒ <code>number</code>
Returns the type of the interface (as integer), which is one of

```
NO_FT_DEVICE                0       // No ft Device connected
FT_AUTO_TYPE                1       // Search for Device
FT_INTELLIGENT_IF           10      // FT-Intelligent Interface connect (serial)
FT_INTELLIGENT_IF_SLAVE     20      // FT-Intelligent Interface with Extension connect (serial)
FT_ROBO_IF_IIM              50      // FT-Robo Interface with Intelligent-Interface-Modus connect (serial)
FT_ROBO_IF_USB              60      // FT-Robo Interface connect with USB-Port
FT_ROBO_IF_COM              70      // FT-Robo Interface connect with COM- (serial-) Port
FT_ROBO_IF_OVER_RF          80      // FT-Robo Interface connect over RF-Data-Link
FT_ROBO_IO_EXTENSION        90      // FT-Robo I/O-Extension
FT_ROBO_LT_CONTROLLER       91      // FT-Robo LT Controller
FT_ROBO_RF_DATA_LINK        110     // FT-Robo RF Data Link
FT_SOUND_AND_LIGHTS         120     // FT-Sound + Lights Module
```

**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  
<a name="module_libroboint.setMotor"></a>

### libroboint.setMotor(motor, direction, [speed]) ⇒
Sets a motor's speed and direction

**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  
**Returns**: null  

| Param | Type | Default | Description |
| --- | --- | --- | --- |
| motor | <code>number</code> |  | The motor number, 1-4, with I/O Extensions also 5-8, 9-12, 13-16 |
| direction | <code>number</code> |  | The direction. one of libroboint.MOTOR_DIR_LEFT (1), libroboint.MOTOR_DIR_RIGHT (2), libroboint.MOTOR_DIR_STOP (0) |
| [speed] | <code>number</code> | <code>7</code> | The speed between 0 and 7. Optional. Defaults to 7 |

**Example**  
```js
const libroboint = require('libroboint');
libroboint.connect();
libroboint.setMotor(1, libroboint.MOTOR_DIR_STOP); // stop motor 1
libroboint.setMotor(2, libroboint.MOTOR_DIR_LEFT, 5); // start motor 2, direction left with speed 5
libroboint.setMotor(2, libroboint.MOTOR_DIR_RIGHT); // start motor 2, direction right with default speed (max = 7)
```
<a name="module_libroboint.setOutput"></a>

### libroboint.setOutput(output, [power])
Sets a outputs's power

**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  

| Param | Type | Default | Description |
| --- | --- | --- | --- |
| output | <code>number</code> |  | The putput number, 1-8, with I/O Extensions also 9-16, 17-24, 25-32 |
| [power] | <code>number</code> | <code>7</code> | The power between 0 and 7. Optional. Defaults to 7 |

**Example**  
```js
const libroboint = require('libroboint');
libroboint.connect();
libroboint.setOutput(7); // set output 7 on (default power)
libroboint.setOutput(2, 5); // set output 2 on, with power 5
```
<a name="module_libroboint.getInput"></a>

### libroboint.getInput(inputNumber) ⇒ <code>number</code>
Gets the state of a digital input.

**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  
**Returns**: <code>number</code> - 1 or 0  

| Param | Type | Description |
| --- | --- | --- |
| inputNumber | <code>number</code> | The input between 1 and Max |

**Example**  
```js
const libroboint = require('libroboint');
libroboint.connect();
console.log(libroboint.getInput(1));
```
<a name="module_libroboint.getA1"></a>

### libroboint.getA1() ⇒ <code>number</code>
Reads analog input A1

**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  
**Returns**: <code>number</code> - The voltage between 0 and 1023  
<a name="module_libroboint.getA2"></a>

### libroboint.getA2() ⇒ <code>number</code>
Reads analog input A2

**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  
**Returns**: <code>number</code> - The voltage between 0 and 1023  
<a name="module_libroboint.getAX"></a>

### libroboint.getAX() ⇒ <code>number</code>
Reads analog input AX

**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  
**Returns**: <code>number</code> - The resistor value between 0 and 1023  
<a name="module_libroboint.getAY"></a>

### libroboint.getAY() ⇒ <code>number</code>
Reads analog input AY

**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  
**Returns**: <code>number</code> - The resistor value between 0 and 1023  
<a name="module_libroboint.getD1"></a>

### libroboint.getD1() ⇒ <code>number</code>
Reads analog input D1

**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  
**Returns**: <code>number</code> - The voltage or distance value between 0 and 1023. Depending on connect option flag "enableDistance"  
<a name="module_libroboint.getD2"></a>

### libroboint.getD2() ⇒ <code>number</code>
Reads analog input D2

**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  
**Returns**: <code>number</code> - The voltage or distance value between 0 and 1023. Depending on connect option flag "enableDistance"  
<a name="module_libroboint.loop"></a>

### libroboint.loop(theLoop, interval)
**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  

| Param | Type | Default | Description |
| --- | --- | --- | --- |
| theLoop | <code>function</code> |  |  |
| interval | <code>number</code> | <code>50</code> | The interval in milliseconds |

<a name="module_libroboint.useCounter"></a>

### libroboint.useCounter(inputNumber)
Use within loop to count "switching" on a digital input.
This will count state change from 0 to 1.
Handy when using a mini switch on a axle.

**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  

| Param | Type |
| --- | --- |
| inputNumber | <code>number</code> | 

**Example**  
```js
const [c, resetC] = libroboint.useCounter(1);
if (c > 10) {
      console.log('reached 11, resetting');
      resetC();
  }
```
