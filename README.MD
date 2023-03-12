# Credits
Thanks to https://github.com/otti/Growatt_ShineWiFi-S

# Growatt_ShineWiFi
Firmware replacement for Growatt ShineWiFi-S (serial), ShineWiFi-X (USB) or custom build sticks (ESP8266/ESP32).
I only use it for the ShineWiFi-X (USB) and Growatt SPH 8000TL3 BH-UP


# How to install
* Checkout this repo
* Setup the IDE of your choice
    * **Recommended:** For platformio just open the project folder and choose the correct env for your hardware  - Use it in Visual Studio Code
* Modify the config.h

After you obtained an image you want to flash:


* Setup  the Stick
** Bridge  GPIO-0 and  GND on the Switch
** Power on  the Stick  with an USB-Cable connected to the Computer - should be detected as COM-Port
* Flash to the Original ShineWiFi-S Stick - Use  "esptool" from python to flash
** Earse all Data: python -m esptool erase_data
** Flash the Firmeware: python -m esptool write_flash --flash_mode dio --flash_size detect 0x0 firmware.bin
* Connect to the setup wifi called GrowattConfig (PW: growsolar) and configure the firmware via the webinterface at http://192.168.4.1
* If you need to reconfigure the stick later on you have to either press the ap button (configured in Config.h) or reset the stick twice within 10sec

## Features
Implemented Features:
* Built-in simple Webserver
* The inverter is queried using Modbus Protocol
* The data received will be transmitted by MQTT to a server of your choice.
* The data received is also provied as JSON
* Show a simple live graph visualization  (`http://<ip>`) with help from highcharts.com
* It supports convenient OTA firmware update (`http://<ip>/firmware`)
* It supports basic access to arbitrary modbus data
* It tries to autodected which stick type to use
* Wifi manager with own access point for initial configuration of Wifi and MQTT server (IP: 192.168.4.1, : GrowattConfig, Pass: growsolar)
* Currently Growatt v1.20, v1.24 and v3.05 protocols are implemented and can be easily extended/changed to fit anyone's needs
* TLS support for esp32

Not supported:
* It does not make use the RTC or SPI Flash of these boards.
* It does not communicate to Growatt Cloud at all.

## Supported sticks/microcontrollers
* ShineWifi-X with a Growatt Inverter connected via USB (USB-Serial Chip from Exar)

## Supported Inverters
* Growatt SPH 4000-10000KTL3 BH (Protocol 124 via Serial)


## Modbus Protocol Versions
The documentation from Growatt on the Modbus interface is avaliable, search for "Growatt PV Inverter Modbus RS485 RTU Protocol" on Google.

The older inverters apparently use Protocol v3.05 from year 2013.
The newer inverters apparently use protocol v1.05 from year 2018.
There is also a new protocol version v1.24 from 2020. (used with SPH4-10KTL3 BH-UP inverter)

## JSON Format Data
For IoT applications the raw data can now read in JSON format (application/json) by calling `http://<ip>/status`

## Homeassistant configuration
This will put the inverter on the energy dashboard.
     
     mqtt:
        sensor:
          - state_topic: "energy/solar"
            unique_id: "growatt_wr_total_production"
            name: "Growatt.TotalGenerateEnergy"
            unit_of_measurement: "kWh"
            value_template: "{{ float(value_json.TotalGenerateEnergy) | round(1) }}"
            device_class: energy
            state_class: total_increasing
            json_attributes_topic: "energy/solar"
            last_reset_topic: "energy/solar"
            last_reset_value_template: "1970-01-01T00:00:00+00:00"
            payload_available: "1"
            availability_mode: latest
            availability_topic: "energy/solar"
            availability_template: "{{ value_json.InverterStatus }}"


To extract the current AC Power you have to add a sensor template.

    template:
      - sensor:
          - name: "Growatt inverter AC Power"
            unit_of_measurement: "W"
            state: "{{ float(state_attr('sensor.growatt_inverter', 'OutputPower')) }}"

## Change log

See [here](CHANGELOG.md)

## Acknowledgements

This arduino sketch will replace the original firmware of the Growatt ShineWiFi stick.