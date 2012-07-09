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
reflects the pot. The update rate is 10 Hz, but it's easy to change.

Here's a couple working pictures. I used a Mega 2560, because my Uno was running my lights controller (coming soon):

ON, POT at max:
<a href="http://www.flickr.com/photos/syrnick/7536559182/" title="ON, pot at max by syrnick, on Flickr"><img src="http://farm9.staticflickr.com/8015/7536559182_a0d3c988ff.jpg" width="500" height="333" alt="ON, pot at max"></a>

ON, POT at midway:
<a href="http://www.flickr.com/photos/syrnick/7536524300/" title="ON, pot midway by syrnick, on Flickr"><img src="http://farm9.staticflickr.com/8012/7536524300_a66c683bb9.jpg" width="500" height="333" alt="ON, pot midway"></a>

ON, POT at min:
<a href="http://www.flickr.com/photos/syrnick/7536559966/" title="ON, pot at min by syrnick, on Flickr"><img src="http://farm8.staticflickr.com/7262/7536559966_a40a014f1c.jpg" width="500" height="333" alt="ON, pot at min"></a>

OFF:
<a href="http://www.flickr.com/photos/syrnick/7536560646/" title="OFF by syrnick, on Flickr"><img src="http://farm8.staticflickr.com/7118/7536560646_4f849929d7.jpg" width="500" height="333" alt="OFF"></a>


### Why TDD?

Tracking down a problem in a large project is tough. Do I understand
the schematic ? (prob. I don't) Are parts OK? What's wrong?

To simplify things, we make sure that parts work well in
isolation. This test verifies that the makershield components are
doing what they're supposed to do. If something is wrong, you can fix
it before adding your own project.

For example, my BTN1 was not working. I found that it is not connected
to the ground. A simple extra wire did the trick:

<a href="http://www.flickr.com/photos/syrnick/7536561256/" title="Bugfix by syrnick, on Flickr"><img src="http://farm9.staticflickr.com/8022/7536561256_e21dc0c9fc.jpg" width="500" height="333" alt="Bugfix"></a>
