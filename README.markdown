# Arduino hacks and fun

## Makershield test

I got through soldering the thing together. Am I done? No! Run this test to declare victory!

### Code

    makershield_tdd/makershield_tdd.ino

### Setup

Connect all makershield parts to arduino:

 * POT to A1
 * LED1 to D2
 * LED2 to D3
 * BTN1 to D4

### Behavior

Hold the button (BTN1) for 1 second to turn it ON or OFF. When OFF,
all LEDs will be off. When ON, the LED1 is always on, LED2 brightness
reflects the pot. The update rate is 10 Hz, but it's easy to update.

### Why TDD?

Tracking down a problem in a large project is tough. Do I understand
the schematic ? (prob. I don't) Are parts OK? What's wrong?

To simplify things, we make sure that parts work well in
isolation. This test verifies that the makershield components are
doing what they're supposed to do. If something is wrong, you can fix
it before adding your own project.

For example, my BTN1 was not working. I found that it is not connected
to the ground. A simple extra wire did the trick IMAGE_IS_COMING.
