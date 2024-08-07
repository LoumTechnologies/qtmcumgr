# qtmcumgr

This is a port of [AuTerm](https://github.com/thedjnK/AuTerm/) with a stdin/stdout JSON API instead of a GUI. It focuses on providing a client implementation of mcumgr for Bluetooth on Windows.

The executable takes no command line arguments. It immediately starts discovering devices. When a device is discovered, something like this gets printed out in stdout:

```
{ "eventType": "deviceDiscovered", "address": "00:00:00:00:00:00", "name": "Bluetooth 00:00:00:00:00:00", "cached": true, "valid": true, "rssi": -80, "majorDeviceClass": "MiscellaneousDevice", "minorDeviceClass": 0 }
```

Once the device has been discovered, you can connect to it by sending this to stdin:

```
{ "commandType": "connect", "address": "00:00:00:00:00:00" }
```

This will result in messages like the following:

```
{ "eventType": "deviceConnected", "address": "00:00:00:00:00:00" }
{ "eventType": "deviceServiceDiscovered", "address": "00:00:00:00:00:00", "service": "8d53dc1d-1db7-4cd3-868b-8a527460aa84", "serviceDescription": "MCUMGR" }
{ "eventType": "serviceDiscoveryFinished", "address": "00:00:00:00:00:00" }
```

The second line means that you can send mcumgr commands to this device. Not all commands are supported yet. Once the mcumgr service has been discovered, you can send mcumgr commands like this:

```
{ "commandType": "reset", "address": "00:00:00:00:00:00", "force": true }
```

This results in the following output:

```
{ "eventType": "resetCompleted", "address": "00:00:00:00:00:00" }
{ "eventType": "deviceDisconnected", "address": "00:00:00:00:00:00" }
```

(The disconnect happens because the device was reset; normally the disconnect doesn't happen after every command.)

## Installing

This requires the following DLLs:

- Qt6Network.dll
- Qt6Bluetooth.dll
- Qt6Core.dll

Or for the debug build:

- Qt6Networkd.dll
- Qt6Bluetoothd.dll
- Qt6Cored.dll

