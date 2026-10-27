# Mini-Arcade Cabinet — Project Overview & Timeline

## What We Are Building
Our goal is to build a working tabletop mini-arcade cabinet with a monitor display, speakers, and physical arcade controls (a joystick and buttons) that can play classic arcade and console games.

For the physical controls, we are using the [Thunderstick Studio GRS LED Single-Player Arcade DIY Kit](https://thunderstickstudio.com/products/grs-led-single-player-arcade-diy-kit?variant=43701902868709), which comes with the joystick, buttons, and wiring harnesses we need.

## Latest Project Updates & Design Changes

### 1. Switching to a Cardboard / DIY Cabinet Frame
In our original pitch, we planned to laser-cut a wooden frame in the campus makerspace. To keep the build simple, affordable, and easier to modify as we fit our parts together, we decided to build a custom cardboard/DIY cabinet frame instead. Using heavy-duty cardboard allows us to quickly cut mounting holes for the arcade joystick and buttons, route our wires cleanly, and adjust the layout around our monitor without waiting on laser-cutter scheduling.

### 2. Why We Are Using a Raspberry Pi 3 for the Display and Games
Originally, we looked into running everything on the Oz64 SG2000X board, including testing DSI screen setups. However, the SG2000X does not have an HDMI port, and running full game emulation alongside high-resolution display output puts a heavy strain on the board.

To solve this, we are adding a **Raspberry Pi 3** to our setup:
* The **Raspberry Pi 3** has built-in HDMI output, so it will connect directly to our monitor display and run the game emulation software.
* The **Oz64 SG2000X** will act as our dedicated **USB controller encoder board**, translating physical button presses and joystick movements into USB data that is sent to the Raspberry Pi.

### 3. How We Are Using the Arduino Core for Input Handling
Instead of fighting with Linux device trees (`gpio-keys`) on the Oz64, we are using the **Arduino core** on the SG2000X to handle all of the arcade controls:
1. **Wiring to GPIO:** Each directional switch on the joystick (Up, Down, Left, Right) and each arcade button is wired to a GPIO pin on the SG2000X and a shared Ground (`GND`) pin.
2. **Polling with Pull-Up Resistors:** In our Arduino sketch, we configure each input pin as `INPUT_PULLUP`. When a button is not pressed, the pin reads `HIGH`. When a player presses a button or moves the joystick, the switch closes to ground and the pin reads `LOW`.
3. **Debouncing:** Physical arcade switches can "bounce" when pressed, registering multiple accidental clicks in a few milliseconds. Our Arduino loop checks that a pin state stays stable for a few milliseconds before registering a real press or release.
4. **Sending Data Over USB:** The SG2000X packages the current state of all buttons and directions and sends them over USB to the Raspberry Pi 3, which reads the inputs and maps them to the emulator controls.

---

## 8-Week Project Timeline (Week 8 to Week 16)
We are currently in **Week 8** and have 8 weeks remaining until our final submission in **Week 16**.

| Week | Milestone & Tasks | Status |
| :--- | :--- | :--- |
| **Week 8 (Current)** | Finalize the dual-board plan (SG2000X + Raspberry Pi 3), switch enclosure plan to a DIY cardboard cabinet, and document the Arduino core input handling design. | ✅ Completed |
| **Week 9** | Set up the Arduino core environment for the SG2000X and test reading a single arcade button and LED using a basic GPIO test sketch. | 🔄 In Progress |
| **Week 10** | Wire all Thunderstick joystick directions and arcade buttons to the SG2000X GPIO header and write the full polling + debouncing Arduino code. | 📅 Planned |
| **Week 11** | Set up the Raspberry Pi 3 with the game emulator OS and verify HDMI video and speaker audio output on our monitor. | 📅 Planned |
| **Week 12** | Connect the SG2000X to the Raspberry Pi 3 over USB and write/configure the input script so button presses on the SG2000X control the Raspberry Pi. | 📅 Planned |
| **Week 13** | Measure the monitor, speakers, and control layout, then cut and assemble the cardboard DIY arcade cabinet frame. | 📅 Planned |
| **Week 14** | Mount the joystick, buttons, SG2000X, Raspberry Pi 3, and monitor inside the cardboard cabinet and organize internal wiring. | 📅 Planned |
| **Week 15** | Full system testing: playtest arcade games, fix any button lag or loose wires, and reinforce the cardboard frame where needed. | 📅 Planned |
| **Week 16 (Final Due Date)** | Final code cleanup, update all repository documentation, record demo/prepare final presentation, and submit project. | 📅 Planned |
