# Small Scale Automatic Plant Watering System
An arduino, powered small scale plant watering system.
Allows plants to be watered both manually and automatically whenever needed, with the only thing left for you to do is to occasionally replenish its water source.

##  Features

- Automatic watering based on soil moisture
- Manual pump control using a button
- Auto / Manual mode selector
- 16×2 LCD showing soil moisture
- Status LED for mode indication
- 12V DC pump controlled through a relay


##  Hardware Used

- Arduino (Uno, Nano, or compatible)
- Capacitive Soil Moisture Sensor v2.0
- 5V Relay Module
- 12V 5W DC Water Pump 
- 12V 1.5A Power Adapter
- 16×2 LCD (LCD1602)
- 2 Push Buttons
- 1 LED + 220Ω resistor
- 10k potentiometer 
- Jumper wires
- Tubing and water container
- 5.5x2.5 mm Female DC Barrel Jack Adapter
- Breadboard (optional)


##  Wiring

### Arduino Connections

| Component | Arduino Pin |
|----------|-------------|
| Soil Sensor (AOUT) | A0 |
| Relay IN | D4 |
| Manual Button | D2 |
| Mode Button | D5 |
| Status LED | D6 |
| LCD RS | D7 |
| LCD E | D8 |
| LCD D4 | D9 |
| LCD D5 | D10 |
| LCD D6 | D11 |
| LCD D7 | D12 |


### Pump Wiring

| Component | Connection |
|----------|------------|
| 12V Adapter (+) via Barrel Jack | Relay COM |
| Relay NO | Pump (+) |
| Pump (–) | 12V Adapter (–) via Barrel Jack |


### Power Distribution 

- **Arduino 5V** → Sensor VCC, Relay VCC, LCD VDD, LED (through resistor)
- **Arduino GND** → Sensor GND, Relay GND, LCD GND, Buttons, LED 

⚠ The 12V pump power is isolated from the Arduino and only passes through the relay.

##  LCD Display

The LCD shows:
- Scaled soil moisture value
- Raw sensor value

A potentiometer is used to adjust LCD contrast.

###  Calibration

Capacitive soil moisture sensors might not produce the same values for every unit or soil type, so a recalibration is strongly recommended.

Measure the sensor output in:
- Completely dry soil
- Fully wet soil

Use the raw values to update the following lines in the code:

```cpp
const int dryValue = 530;
const int wetValue = 235;
```

The higher raw value indicates dry soil while a low raw value indicates wet soil.


##  Code

Once all hardware is assembled, upload the Arduino sketch using the Arduino IDE.

After uploading:

1. Power the Arduino.
2. Connect the 12V adapter to the pump.
3. Place the soil moisture sensor into the plant’s soil.
4. Put the pump into a container filled with water.
5. Run the tube from the pump to the plant.
6. Set the system to **Automatic mode**.

The system will now automatically water the plant whenever the soil becomes too dry, as long as there is water in the container.
