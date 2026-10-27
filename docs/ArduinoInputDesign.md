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

## 2. GPIO Pin Mapping (Draft)
The Thunderstick kit uses one switch per direction/button, so we need 12 input pins in total. The table below is our proposed mapping and matches `src/sg2000_usb_encoder/sg2000_usb_encoder.ino`.

| Index | SG2000X Pin | Function |
| :---: | :---: | :--- |
| 0 | GPIO0 | Joystick Up |
| 1 | GPIO1 | Joystick Down |
| 2 | GPIO2 | Joystick Left |
| 3 | GPIO3 | Joystick Right |
| 4 | GPIO4 | Button 1 (A) |
| 5 | GPIO5 | Button 2 (B) |
| 6 | GPIO6 | Button 3 (C) |
| 7 | GPIO7 | Button 4 (D) |
| 8 | GPIO8 | Button 5 |
| 9 | GPIO9 | Button 6 |
| 10 | GPIO10 | Start |
| 11 | GPIO11 | Coin / Select |

> **Open question:** GPIO0/GPIO1 can be shared with the boot/UART pins on some SG2000X configurations. We will verify these are free before finalizing the mapping, and reassign them if needed.

## 3. Wiring
Each switch uses a 2-wire harness (Signal + Ground):

- **Signal** goes to the assigned GPIO pin.
- **Ground** goes to a shared `GND` rail on the SG2000X header.

No external resistors are required. Every input pin is configured as `INPUT_PULLUP`, so the pin is internally tied to 3.3 V:

- Switch **open** (not pressed) -> pin reads `HIGH`.
- Switch **closed** (pressed) -> pin is pulled to `GND` and reads `LOW`.

Because the switches only ever short the pin to ground, this avoids wiring a separate pull-up resistor per button.

## 4. Input Logic
The draft sketch polls every pin on each pass of `loop()`:

1. **Configure:** `pinMode(pin, INPUT_PULLUP)` for all 12 pins in `setup()`.
2. **Poll:** `digitalRead(pin)` for each pin.
3. **Edge detect:** compare the reading to `lastButtonState[i]`.
4. **Report:** if the state changed, emit a `PRESS:<index>` or `RELEASE:<index>` line over serial and store the new state.
5. **Debounce:** the loop ends with a 5 ms delay, so a switch must stay in its new state between passes before the next change is reported.

The 5 ms delay is a simple first-pass debounce. If we see double-triggers during playtesting, we will replace it with a per-button timestamp check that ignores state changes within a set debounce window.

## 5. Serial Protocol
The SG2000X sends newline-delimited ASCII over USB serial at `115200` baud:

```text
PRESS:<index>
RELEASE:<index>
```

`<index>` is the 0-based index from the pin-mapping table (e.g. `PRESS:0` for joystick up, `RELEASE:4` for button 1). The Raspberry Pi side (`scripts/serial_gamepad_bridge.py`) translates these events into emulator/gamepad input.

## 6. Next Steps
- Confirm GPIO0/GPIO1 are safe to use, or remap them.
- Wire one button and verify `PRESS`/`RELEASE` output on the Pi.
- Replace the fixed loop delay with per-button debounce if needed.
- Decide whether the Pi reads raw serial or we present the SG2000X as a USB HID gamepad.
