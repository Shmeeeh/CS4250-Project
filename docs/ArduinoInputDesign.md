# SG2000X Arduino Core Input & Wiring Design

## Overview
This document lays out how we are connecting the Thunderstick Studio GRS LED Arcade DIY Kit to the Oz64 SG2000X board and how our Arduino core program will turn those physical switches into controller inputs for the Raspberry Pi 3.

## 1. Hardware Connection Plan
```text
[Thunderstick Joystick & Buttons]
        │ (2-wire harnesses per switch: Signal + Ground)
        ▼
[Oz64 SG2000X GPIO Pins] (Running Arduino Core Firmware)
        │ (USB Connection)
        ▼
[Raspberry Pi 3] (Reads USB inputs & runs Emulator)
        │ (HDMI Cable)
        ▼
[Monitor & Speakers]
```
