[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![GitHub Issues or Pull Requests](https://img.shields.io/github/issues/the78mole/esphome_components)
![GitHub Issues or Pull Requests](https://img.shields.io/github/issues-pr/the78mole/esphome_components)
![GitHub forks](https://img.shields.io/github/forks/the78mole/esphome_components)
![GitHub Repo stars](https://img.shields.io/github/stars/the78mole/esphome_components)
![GitHub Release](https://img.shields.io/github/v/release/the78mole/esphome_components)

[![Matrix](https://img.shields.io/matrix/molesblog%3Amatrix.org)](https://matrix.to/#/#molesblog:matrix.org)
[![Ask DeepWiki](https://deepwiki.com/badge.svg)](https://deepwiki.com/the78mole/esphome_components)


# esphome_components
ESPhome Components from the little digger and Jens

We collected some (currently one) of our ESPhome components here to share with other diggers:

- KM271-WiFi is also described in detail in one of my [blog posts](https://the78mole.de/reverse-engineering-the-buderus-km217/) and it received a [how-to page](https://the78mole.de/projects/km271-wifi-howto/) to take it into action e.g. with the default ESPhome firmware.

You will find some precompiled bin-files to upload to your hardware in the [gh-pages-branch](https://github.com/the78mole/esphome_components/tree/gh-pages).

## KM217 Wifi

### Overview
This component uses the hardware designed by the78mole to read interesting values from a buderus logamatic oil fired heating system (Logamatic 2107 M). We also had reports of gas burning systems, this module fits in and communicates with the controller. 

![image](components/km271_wifi/IMG/Buderus-KM217-Clone_0.0.5.jpg)

Here is just a short overview of the information you can get from the logamatic:

 ![image](images/home-assistant-values.png)
 ![image](images/home-assistant-values-2.png)
 ![image](images/home-assistant-values-3.png)


 
### Usage
See https://esphome.io/components/external_components.html for information about integrating this into your esphome environemnt.

To configure the component, see the included file buderus-km271.yaml.
If you are not interested in some of the provided values, just remove the respective entry in the the section "sensor" or "binary_sensor", but leave the empty sections in place to avoid comiler errors with missing headers.

### Example Configurations

You can find many example YAML configurations in the root of this repository. They all get verified by Github Actions workflows to be correct and can be compiled with the latest ESPHome version. Using the latest esphome is ensured by renovate bot and can have a delay of some days, because it needs to undergo some checks and if there is a problem with the YAML files and the new versions, it mostly needs to be fixed manually.

The main intention of these examples are:
| Filename | Description |
|---|---|
| buderus-km271.yaml | Standard configuration for the KM271 component (German). |
| buderus-km271_en.yaml | Standard configuration for the KM271 component (English). |
| buderus-km271_en_noimprov.yaml | English configuration without [improv](https://www.improv-wifi.com/). |
| buderus-km271-hc2-rw.yaml | Configuration for KM271 with read/write support for heating circuit 2. |
| buderus-km271-writable-espidf.yaml | Configuration using the ESP-IDF framework (saves ~50% of flash space). |
| buderus-km271-writable-8MB.yaml | Configuration using 8MB flash memory (not supported by all HW versions). |
| components/km271_wifi/km271-for-friends.yaml | This is the version usually delivered with the HW. |
| components/km271_wifi/km271_hc1_only.yaml | Example configuration for KM271 only using heating circuit 1. |


#### Writing Values and Changing Parameters 
If you plan to change settings for your heater, see the included file buderus-km271-writable.yaml. This file also provides integration for changing values via home assistant.

*CAUTION*: 
Changing settings of your heater might lead to undesired results, e.g. increased fuel consumption, annoyed family members or even failure of your device.
Please use caution when changing settings of your heater and verify that the results are as desired. Rule of thumb: If you don't feel comfortable changing the settings directly on the heater control unit,
do dot do it via this software either.

*MORE CAUTION*: 
If you plan to change settings, please take care not to change settings too
frequently. Devices such as these heaters typically use so called EEPROM chips to store settings. Such chips only support a certain number of write operations before breaking down.
You should be safe for some years if you don't write more 20 values per day - but there is no guarantee. Maybe someone can dig out some documentation about this to make sure.

### Limitations
   * The software only provides a sub-set of the available data. Feel free to create a pull request to add data you want to see.
   * Changing of values is only supported for a few values
   * Only one write request can be active at the same time
   * Written values are not read back for verification.
