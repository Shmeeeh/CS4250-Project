## Week 11 Status Update (HW 09, report) (Current)

### Current Status
We are currently in Week 11 and remain on schedule to finish by Week 16. This week we finalized our board-to-board communication architecture, resolved a hardware GPIO conflict on the Milk-V Duo S, and wired and verified all four directions of the arcade joystick on the Arduino core (`remoteproc0`).

### What We Accomplished This Week
- **Evaluated Inter-Core Communication & Pivoted to Hardware UART:** While moving from our single-button test to full controller communication, we worked through three architectures on the Milk-V Duo S:
  1. *Arduino Core Direct USB:* Initially planned to have the Arduino core (`remoteproc0`) stream inputs straight over USB, but confirmed that Debian Linux owns the Duo S USB-C port while `remoteproc0` controls the physical Header J3 GPIO and UART pins.
  2. *Linux Mailbox IPC:* Investigated passing debounced button states from `remoteproc0` to Debian Linux via the SG2000 hardware mailbox and forwarding them over USB Serial Gadget (`/dev/ttyGS0`). We found that our Debian image does not expose the stock `/dev/cvi-rtos-cmdqu` mailbox device out of the box, and managing a mailbox daemon plus USB gadget mode added unnecessary failure points.
  3. *Direct 3.3V Hardware UART (Final Architecture):* Pivoted to sending compact 3-byte controller state packets (`[0xAA, HighByte, LowByte]`) directly from the Arduino core's `Serial1` (`UART1_TX`, Pin 18) to the Raspberry Pi 3's `RXD` (Pin 10) with a shared ground. This keeps low-level `INPUT_PULLUP` polling and debouncing on `remoteproc0` with zero extra Linux IPC code on the Duo S.
- **Wired & Verified 4-Way Arcade Joystick (`src/joystick_test/joystick_test.ino`):** Built a shared breadboard ground rail from Duo S Pin 6 (`GND`), wired all four Thunderstick joystick switches to Header J3 Pins 3, 5, 7, and 11, and verified every direction on hardware using a blink-code diagnostic sketch on `remoteproc0` (1–4 blinks on the onboard blue LED for UP/DOWN/LEFT/RIGHT).
- **Diagnosed Hardware Pin Conflict & Finalized 10-Input Layout:** During testing, we caught that Header J3 Pin 16 (`JTAG_CPU_TRST`) pulls `LOW` even when unwired, locking the status LED on. We reassigned Button Y to Pin 23 (`XGPIOB_15`) and streamlined the layout from 12 inputs to 10 (4 joystick directions + 4 action buttons + Start & Select, dropping L1/R1 after finding a faulty switch in the kit).

## Week 10 Status Update (Report 08)

### Status
We are currently in Week 10 and still on schedule to finish by Week 16. This week we continued to work on the buttons and got the Raspberry Pi, Video output, and Audio output functioning. We will continue to work on it during Fall break of week 11.

### What We Accomplished This Week
* **Flashed Emulation OS Onto the Raspberry Pi:** Flashed a micro-SD card with "RetroPie" allowing us to run any number of retro games on it. Currently tested with N64 games, functioning without issue.


## Week 9 Status Update (Report 07)

###  Status
We are currently in Week 9 and still on schedule to finish by Week 16. This week we proved out the input path for the arcade controls by getting a single button working on the Arduino core.

### What We Accomplished This Week
* **Got a Single Button Working on the Arduino Core:** Using the Arduino core on the Duo-S, we wired up and successfully read a single arcade button over GPIO on pins 6, 11, and 12. The button uses `INPUT_PULLUP` with debounce logic, and pressing it drives both the button's LED and the onboard blue LED.
* **Added `src/single_button_test.ino`:** Committed the working single-button test sketch so the wiring and logic are documented and reproducible.


## Week 8 Status Update (Report 06)

### Status
We are currently in Week 8 and on schedule to finish by Week 16. This week we simplified our physical build plan and fleshed out the technical details for how our two boards (the Oz64 SG2000X and the Raspberry Pi 3) will work together.

### What We Accomplished This Week
* **Updated `README.md` with Project Overview and Week 8-16 Timeline:** Documented our updated project plan and added a week-by-week timeline through Week 16.
* **Pivoted to a Cardboard / DIY Cabinet Frame:** Decided to build the arcade enclosure out of sturdy cardboard instead of laser-cutting wood in the makerspace so we can prototype and mount our controls and display faster.
* **Confirmed Display & Compute Split:** Because the SG2000X does not have HDMI output, we confirmed we will use a Raspberry Pi 3 to run the games and output HDMI video/audio to the monitor.
* **Created `docs/ArduinoInputDesign.md`:** Flushed out the design for using the Arduino core on the SG2000X as our USB input encoder, including the hardware connection plan for the Thunderstick arcade kit and the pull-up resistor wiring design.
* **Added Draft Encoder Sketch:** Committed `src/sg2000_usb_encoder/sg2000_usb_encoder.ino`, a first-pass Arduino sketch that polls the arcade switches with `INPUT_PULLUP`, debounces, and reports press/release events over serial.


## Week 11/22 - 11/28
- Hopefully, project will be done!

## Week 11/15 - 11/21
- Iron out any last kinks in the wiring, firmware, or missed goals.

## Week 11/8 - 11/14
- Set up the firmware on the pi for running games
- Create the case for the project using the diagram detailed in the README

## Week 11/1 - 11/7
Hopefully, buttons now work.

- Set it up so that the pi interprets the inputs into/from the MilkV

## Week 10/19 - 10/31
Get the LCD Screen to work with the pi

Encode the arcade kit button inputs into USB mouse/keyboard/controller inputs
- Will require some rewiring of the arcade button wires
- Test in the meantime by using simple GPIO buttons from basic wire kits

### Success!
Using the Arduino core and an official button programming documentation, we got a successful button communication on the board! The .ino file is in the programs folder.

It seems plausible we can expand this from digital output into analog output and get communication between Duo S and Pi.


## Week 10/11 - 10/18
Emmett was unable to hook up the DSI screen on the Duo-S

Now focusing on getting the Arduino core on the Duo-S to function as a USB Encoder for GPIO input

We ordered this LCD Screen and this arcade button kit:
- https://www.amazon.com/dp/B0G6KP328Q?ref=ppx_yo2ov_dt_b_fed_asin_title
- https://thunderstickstudio.com/products/grs-led-single-player-arcade-diy-kit?variant=43701902934245

They will arrive next week. We are still in the early project stages, so we have no setup scripts, encoder configuration, or wiring documentation


## Week 10/04 - 10/10
Wifi board connection has been established


# Current Status
## Week 09/27 - 10/03
We were able to successfully SSH into the MilkV board using the Sophgo and Fishwaldo images. After lots of turmoil, reflashing, and monitor smashing 

we are gonna start experimenting with the boards.

