<a name="module_libroboint"></a>

## libroboint
The single entry point for interacting with the ROBO Interface


* [libroboint](#module_libroboint)
    * [.RoboInterface](#module_libroboint.RoboInterface)
    * [.MOTOR_DIR_LEFT](#module_libroboint.MOTOR_DIR_LEFT)
    * [.MOTOR_DIR_RIGHT](#module_libroboint.MOTOR_DIR_RIGHT)
    * [.MOTOR_DIR_STOP](#module_libroboint.MOTOR_DIR_STOP)
    * [.connect(opts)](#module_libroboint.connect)
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

### libroboint.connect(opts)
**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  

| Param | Type | Description |
| --- | --- | --- |
| opts | <code>Object</code> | The connection options |
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
**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  
<a name="module_libroboint.getDeviceType"></a>

### libroboint.getDeviceType() ⇒ <code>number</code>
**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  
<a name="module_libroboint.setMotor"></a>

### libroboint.setMotor(motor, direction, [speed]) ⇒
**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  
**Returns**: null  

| Param | Type | Description |
| --- | --- | --- |
| motor | <code>number</code> | The motor number, 1-4, with I/O Extensions also 5-8, 9-12, 13-16 |
| direction | <code>number</code> | The direction. one of libroboint.MOTOR_DIR_LEFT (1), libroboint.MOTOR_DIR_RIGHT (2), libroboint.MOTOR_DIR_STOP (0) |
| [speed] | <code>number</code> | The speed between 0 and 7. Defaults to 7 |

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
**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  

| Param | Type | Description |
| --- | --- | --- |
| output | <code>number</code> | The putput number, 1-8, with I/O Extensions also 9-16, 17-24, 25-32 |
| [power] | <code>number</code> | The power between 0 and 7. Defaults to 7 |

<a name="module_libroboint.getInput"></a>

### libroboint.getInput(inputNumber) ⇒ <code>number</code>
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
**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  
**Returns**: <code>number</code> - The voltage between 0 and 1023  
<a name="module_libroboint.getA2"></a>

### libroboint.getA2() ⇒ <code>number</code>
**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  
**Returns**: <code>number</code> - The voltage between 0 and 1023  
<a name="module_libroboint.getAX"></a>

### libroboint.getAX() ⇒ <code>number</code>
**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  
**Returns**: <code>number</code> - The resistor value between 0 and 1023  
<a name="module_libroboint.getAY"></a>

### libroboint.getAY() ⇒ <code>number</code>
**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  
**Returns**: <code>number</code> - The resistor value between 0 and 1023  
<a name="module_libroboint.getD1"></a>

### libroboint.getD1() ⇒ <code>number</code>
**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  
**Returns**: <code>number</code> - The voltage or distance value between 0 and 1023. Depending on connect option flag "enableDistance"  
<a name="module_libroboint.getD2"></a>

### libroboint.getD2() ⇒ <code>number</code>
**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  
**Returns**: <code>number</code> - The voltage or distance value between 0 and 1023. Depending on connect option flag "enableDistance"  
<a name="module_libroboint.loop"></a>

### libroboint.loop(theLoop, interval)
**Kind**: static method of [<code>libroboint</code>](#module_libroboint)  

| Param | Default |
| --- | --- |
| theLoop |  | 
| interval | <code>50</code> | 

<a name="module_libroboint.useCounter"></a>

### libroboint.useCounter(inputNumber)
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
