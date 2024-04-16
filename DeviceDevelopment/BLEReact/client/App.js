import React, { useEffect, useState } from 'react';
import { View, Text, Button } from 'react-native';
import { BleManager } from 'react-native-ble-plx';
import 'expo-dev-client';


const SERVICE_UUID = '4fafc201-1fb5-459e-8fcc-c5c9c331914b';
const STEP_DATA_CHAR_UUID = 'beefcafe-36e1-4688-b7f5-00000000000b';

const App = () => {
  const [stepCount, setStepCount] = useState(0);
  const [isScanning, setIsScanning] = useState(false);
  const [isConnecting, setIsConnecting] = useState(false);
  const [device, setDevice] = useState(null);
  const bleManager = new BleManager();

  useEffect(() => {
    scanDevices();
  }, []);

  const scanDevices = async () => {
    setIsScanning(true);
    try {
      bleManager.startDeviceScan(null, null, (error, scannedDevice) => {
        if (error) {
          console.error('Scanning error:', error);
          setIsScanning(false);
          return;
        }
        if (scannedDevice) {
          // Process the scanned device, e.g., filter by UUIDs
          console.log('Scanned device:', scannedDevice.name);
        }
      });
    } catch (error) {
      console.error('Error starting device scan:', error);
      setIsScanning(false);
    }
  };

  const stopScan = () => {
    bleManager.stopDeviceScan();
    setIsScanning(false);
  };

  const connectToDevice = async () => {
    setIsConnecting(true);
    try {
      const scannedDevice = await bleManager.connectToDevice(device.id);
      setDevice(scannedDevice);
      setIsConnecting(false);
      console.log('Connected to device:', scannedDevice.name);
      // Once connected, read the characteristic
      readCharacteristic(scannedDevice);
    } catch (error) {
      console.error('Error connecting to device:', error);
      setIsConnecting(false);
    }
  };

  const readCharacteristic = async (connectedDevice) => {
    try {
      const characteristic = await connectedDevice.readCharacteristicForService(
        SERVICE_UUID,
        STEP_DATA_CHAR_UUID
      );
      const newStepCount = characteristic.value.readInt8(0); // Assuming the value is an 8-bit integer
      setStepCount(newStepCount);
      console.log('Characteristic read successful:', newStepCount);
    } catch (error) {
      console.error('Error reading characteristic:', error);
    }
  };

  return (
    <View style={{ flex: 1, justifyContent: 'center', alignItems: 'center' }}>
      <Text>Step Count: {stepCount}</Text>
      <Button title={isScanning ? 'Scanning...' : 'Scan Devices'} onPress={isScanning ? stopScan : scanDevices} disabled={isScanning || isConnecting} />
      {device && !isConnecting && <Button title="Connect to Device" onPress={connectToDevice} disabled={isScanning || isConnecting} />}
    </View>
  );
};


export default App;

