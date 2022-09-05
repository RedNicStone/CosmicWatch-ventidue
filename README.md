<p align="center">
    <img src="images/pcb/combined/bottom.svg" alt="CosmicWatch logo" width="25%"/>
    <img src="images/pcb/combined/top.svg"    alt="CosmicWatch logo" width="25%"/>
</p>

---
[![OPEN](https://img.shields.io/badge/open-SOURCE-red.svg?style=for-the-badge)]()
[![MUONS](https://img.shields.io/badge/powered_by-MUONS-green.svg?style=for-the-badge)]()
[![TEENSY](https://img.shields.io/badge/runs_on-TEENSY_4.1-blue.svg?style=for-the-badge&logoColor=white&logo=arm)]()

# CosmicWatch Ventidue
Continuation of the original CosmicWatch project by Spencer featuring many improvements and additions.

## What's new?
CosmicWatch Ventidue's new features are plentiful so here is a quick summary:
- Flexible design that allows connecting either one or two detectors
- Built in on-silicon coincidence detection between the two modules
  - Time resolutions from 5ns down to just 1ns [cooling required]
- Powerful Teensy 4.1 microcontroller
- Full color 1.5" OLED display with great user interface
  - Rotary encoder for easy navigation
  - Buzzer for audible counting and interface feedback
  - Custom rendering library for maximum performance
- Optional solder-free support for multiple prebuilt sensor modules
  - GPS, Pressure, Humidity, Temperature and RTC supported
- Built in Ethernet module for intra & intercommunication
- Improved mechanical stability and 3D printed casing
- Interrupt driven software architecture for accurate counting and a responsive user interface

## Hardware [![SATE](https://img.shields.io/badge/Status-Undergoing_Testing-orange.svg?style=flat-square)]()
A first prototype has been produced and tested. 
We are currently busy on fabricating a newer board that will be tested as soon as finished.  
There are plans to provide a kit with a pre-assembled board for purchase once hardware development has sized.

### Overview
> todo


## Software [![SATE](https://img.shields.io/badge/Status-In_Development-red.svg?style=flat-square)]()
Software is currently undergoing heavy development and is only barely runnable.  
If you do want to take a look [check this folder](software/arduino).

The following modules have been written so far:
- Custom rendering pipeline
- OLED driver [Needs push to support DMA]
- On-chip coincidence detection
- Example for testing peripherals

The following modules still need tending:
- True type font rendering
- UI and windowing system
- Data acquisition and storage
- Ethernet communication

**Any help is much appreciated!**

