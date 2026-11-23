# CS4250 Mini-Arcade Cabinet — Remaining Build & Code Plan (UART Architecture)

## System Overview
We are splitting the arcade cabinet across two boards connected by **2 jumper wires (3.3V Hardware UART)**:

```text
[Thunderstick Joystick & 8 Buttons]
               │  (Signal -> GPIO, Black -> Shared GND, Red -> 5V if LEDs wanted)
               ▼
   [Oz64 SG2000X / Milk-V Duo S]
   (Arduino Core on remoteproc0: INPUT_PULLUP, debounce, packs 12 inputs into 3-byte packet)
               │  (2 Jumper Wires: DuoS Pin 18 UART1_TX -> Pi 3 Pin 10 RXD, Pin 6 GND -> Pin 6 GND)
               ▼
        [Raspberry Pi 3]
   (Python uinput bridge reads /dev/serial0 -> virtual gamepad -> RetroPie/Emulator)
               │  (HDMI + Audio)
               ▼
     [Monitor & Speakers]