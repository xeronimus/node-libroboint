<!-- Generated by documentation.js. Update this documentation by updating the source code. -->

### Table of Contents

-   [connect][1]
    -   [Parameters][2]
    -   [Examples][3]
-   [hasInterface][4]
    -   [Examples][5]
-   [close][6]
    -   [Examples][7]
-   [getDeviceType][8]
-   [getDeviceTypeString][9]
-   [setMotor][10]
    -   [Parameters][11]
    -   [Examples][12]
-   [getInput][13]
    -   [Parameters][14]
    -   [Examples][15]
-   [getA1][16]
-   [getA2][17]
-   [getAX][18]
-   [getAY][19]
-   [getD1][20]
-   [getD2][21]
-   [loop][22]
    -   [Parameters][23]

## connect

Connect to the Robo Interface

### Parameters

-   `opts` **[object][24]** The connection options
    -   `opts.deviceNumber` **[number][25]** The number of the device to connect to, defaults to 0.
    -   `opts.usbSerial` **[number][25]** If specified, will connect using the serialNumber.
    -   `opts.serialType` **[number][25]** Type of device at serial port, either FT_INTELLIGENT_IF (10), FT_INTELLIGENT_IF_SLAVE (20) or FT_ROBO_IF_COM (70)
    -   `opts.enableDistance` **[boolean][26]** Enable D1 and D2 for use with the ft distance sensor, defaults to false
    -   `opts.startTransferArea` **[boolean][26]** Start the transfer area. Usually you want that, defaults to true

### Examples

```javascript
const libroboint = require('libroboint');
libroboint.connect({
   deviceNumber: 0
});
```

## hasInterface

Tells if we have a connection to the Interface
Useful to call after "connect()"

### Examples

```javascript
const libroboint = require('libroboint');
libroboint.connect();
if(libroboint.hasInterface()){
    // do something
}
```

Returns **[boolean][26]** 

## close

Closes the connection to the ftDevice. Currently this must be called manually from your JS code.

### Examples

```javascript
const libroboint = require('libroboint');
libroboint.connect();
// do something
libroboint.close();
```

Returns **any** null

## getDeviceType

Returns the type of the interface (as integer), which is one of

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

Returns **[number][25]** 

## getDeviceTypeString

Returns a string that identifies this interface in a human readable form like "Robo Interface"

Returns **[string][27]** 

## setMotor

Sets a motor's speed and direction

### Parameters

-   `motor` **[number][25]** The motor number, 1-4, with I/O Extensions also 5-8, 9-12, 13-16
-   `direction` **[number][25]** The direction. one of libroboint.MOTOR_DIR_LEFT (1), libroboint.MOTOR_DIR_RIGHT (2), libroboint.MOTOR_DIR_STOP (0)
-   `speed` **[number][25]** The speed between 0 and 7. Defaults to 7

### Examples

```javascript
const libroboint = require('libroboint');
libroboint.connect();
libroboint.setMotor(1, libroboint.MOTOR_DIR_STOP); // stop motor 1
libroboint.setMotor(2, libroboint.MOTOR_DIR_LEFT, 5); // start motor 2, direction left with speed 5
libroboint.setMotor(2, libroboint.MOTOR_DIR_RIGHT); // start motor 2, direction right with default speed (max = 7)
```

Returns **any** null

## getInput

Gets the state of a digital input.

### Parameters

-   `inputNumber` **[number][25]** The input between 1 and Max

### Examples

```javascript
const libroboint = require('libroboint');
libroboint.connect();
console.log(libroboint.getInput(1));
```

Returns **[number][25]** 1 or 0

## getA1

Reads analog input A1

Returns **[number][25]** The voltage between 0 and 1023

## getA2

Reads analog input A2

Returns **[number][25]** The voltage between 0 and 1023

## getAX

Reads analog input AX

Returns **[number][25]** The resistor value between 0 and 1023

## getAY

Reads analog input AY

Returns **[number][25]** The resistor value between 0 and 1023

## getD1

Reads analog input D1

Returns **[number][25]** The voltage or distance value between 0 and 1023. Depending on connect option flag "enableDistance"

## getD2

Reads analog input D2

Returns **[number][25]** The voltage or distance value between 0 and 1023. Depending on connect option flag "enableDistance"

## loop

### Parameters

-   `theLoop`  
-   `interval`   (optional, default `50`)

[1]: #connect

[2]: #parameters

[3]: #examples

[4]: #hasinterface

[5]: #examples-1

[6]: #close

[7]: #examples-2

[8]: #getdevicetype

[9]: #getdevicetypestring

[10]: #setmotor

[11]: #parameters-1

[12]: #examples-3

[13]: #getinput

[14]: #parameters-2

[15]: #examples-4

[16]: #geta1

[17]: #geta2

[18]: #getax

[19]: #getay

[20]: #getd1

[21]: #getd2

[22]: #loop

[23]: #parameters-3

[24]: https://developer.mozilla.org/docs/Web/JavaScript/Reference/Global_Objects/Object

[25]: https://developer.mozilla.org/docs/Web/JavaScript/Reference/Global_Objects/Number

[26]: https://developer.mozilla.org/docs/Web/JavaScript/Reference/Global_Objects/Boolean

[27]: https://developer.mozilla.org/docs/Web/JavaScript/Reference/Global_Objects/String