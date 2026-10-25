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

Encoding inputs with the Arduino did not seem to work, arduino core is maybe too old?

Now testing [gpio-keys kernel](https://www.kernel.org/doc/Documentation/devicetree/bindings/input/gpio-keys.txt)

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
