# Current Status
## Week 09/27 - 10/03
We were able to successfully SSH into the MilkV board using the Sophgo and Fishwaldo images. After lots of turmoil, reflashing, and monitor smashing 

we are gonna start experimenting with the boards.

## Week 10/04 - 10/10
Wifi board connection has been established

## Week 10/11 - 10/18
Emmett was unable to hook up the DSI screen on the Duo-S

Now focusing on getting the Arduino core on the Duo-S to function as a USB Encoder for GPIO input

We ordered this LCD Screen and this arcade button kit:
- https://www.amazon.com/dp/B0G6KP328Q?ref=ppx_yo2ov_dt_b_fed_asin_title
- https://thunderstickstudio.com/products/grs-led-single-player-arcade-diy-kit?variant=43701902934245

They will arrive next week. We are still in the early project stages, so we have no setup scripts, encoder configuration, or wiring documentation

## Week 10/19 - 10/31
Get the LCD Screen to work with the pi

Encode the arcade kit button inputs into USB mouse/keyboard/controller inputs
- Will require some rewiring of the arcade button wires
- Test in the meantime by using simple GPIO buttons from basic wire kits

### Success!
Using the Arduino core and an official button programming documentation, we got a successful button communication on the board! The .ino file is in the programs folder.

It seems plausible we can expand this from digital output into analog output and get communication between Duo S and Pi.


## Week 11/1 - 11/7
Hopefully, buttons now work.

- Set it up so that the pi interprets the inputs into/from the MilkV

## Week 11/8 - 11/14
- Set up the firmware on the pi for running games
- Create the case for the project using the diagram detailed in the README

## Week 11/15 - 11/21
- Iron out any last kinks in the wiring, firmware, or missed goals.

## Week 11/22 - 11/28
- Hopefully, project will be done!

## Week 8 Status Update (Report 07)

### Current Status
We are currently in Week 8 and on schedule to finish by Week 16. This week we simplified our physical build plan and fleshed out the technical details for how our two boards (the Oz64 SG2000X and the Raspberry Pi 3) will work together.

### What We Accomplished This Week
* **Updated `README.md` with Project Overview and Week 8-16 Timeline:** Documented our updated project plan and added a week-by-week timeline through Week 16.
* **Pivoted to a Cardboard / DIY Cabinet Frame:** Decided to build the arcade enclosure out of sturdy cardboard instead of laser-cutting wood in the makerspace so we can prototype and mount our controls and display faster.
* **Confirmed Display & Compute Split:** Because the SG2000X does not have HDMI output, we confirmed we will use a Raspberry Pi 3 to run the games and output HDMI video/audio to the monitor.
* **Created `docs/ArduinoInputDesign.md`:** Flushed out the design for using the Arduino core on the SG2000X as our USB input encoder, including the hardware connection plan for the Thunderstick arcade kit and the pull-up resistor wiring design.
* **Added Draft Encoder Sketch:** Committed `src/sg2000_usb_encoder/sg2000_usb_encoder.ino`, a first-pass Arduino sketch that polls the arcade switches with `INPUT_PULLUP`, debounces, and reports press/release events over serial.
