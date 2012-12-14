# The Copter Glove #
#### Arduino-Powered IR motion control glove for the S107 toy helicopter ####

## The Idea ##
### 11/9/12 ###

Yeasterday, I was reading Hackaday and came upon an article talking about [reverse-engineering a Syma S107 RC helicopter][1]. As I own one myself, I was interested in the project. That same day, I found an RC heli on ThinkGeek that was [controlled with a glove][2]. Reading through the comments, it seemed that many cheap RC helicopters aren't the best. The S107, on the contrary, *is* is an amazing copter for the money. So, I came up with an idea. Why not make one of these gloves for the S107?

## The Beginning of the Implementation ##
### 11/10/12 ###

Today, I began the actual implementation of the IR protocol. Using the links [here][3] and [here][4] as references, I wrote up an Arduino sketch that should have caused the helicopter to turn its throttle up to 50%. I scavenged an IR LED from an old A/C remote, and slapped it on a breadboard, hoping it would work. Unfortunately, it did not. I know it's blinking from my phone's camera, and putting it side by side with the controller, it seems as if they're blinking at the same speed. Odd. 

I'm going to try just using kerry wont's sketch directly, and seeing if that works. If it doesn't, I'm just going to say that my LED isn't strong enough. I ordered a pack of 25 super-bright ones, so maybe that'll make a difference.

### 2 Hours later… ###

Tested it again, and it worked with Kerry Wong's sketch. It didn't have good range, but the super-bright LEDs should fix that. So at least I know that I have a working protocol. I think the problem was how I was producing the carrier frequency. I was using the `tone()` function, which is used for piezo buzzers to produce a certain, well, tone. I'd used it in the past for IR LEDs, but I guess it wasn't working properly. I used the `pulseIR()` function from [this blog post][7], which was a pretty much manual solution, relying on the clock speed of the Arduino Uno. I better read up on PWM and exactly what it is (besides being used to make LEDs less bright). Turns out, the new code worked. I ordered the [LEDs][5] and [accelerometer][6] from Adafruit on Priority Mail, so they should be coming soon.

## Parts Arrive, prototyping! ##
### 12/13/12 ###

Today the accelerometer and IR LEDs arrived! As soon as I got the package from Adafruit I opened it up and soldered the header to the accelerometer. After playing with it a little, I decided that the range for the tilt should be the equivalent of 330 - 340 on the output of the accelerometer. It was about 45 degrees from 335 (center, no movement) to 340 (tilted to a side). Observing the Z-axis, I decided that there wasn't enough change to measure up/down for throttle control, so I'll just use a potentiometer instead. I modified the sketch to let the pitch and yaw be controlled by the x and y axes, respectively. The Throttle is now controlled by a pot connected to analog pin 5. Tomorrow I'll have some more time to play with this setup, and see how sensitive it actually is.


[1]: http://hackaday.com/2012/12/08/more-fun-with-syma-107-reverse-engineering/
[2]: http://www.thinkgeek.com/product/f2c6/
[3]: http://www.jimhung.co.uk/?p=901
[4]: http://www.kerrywong.com/2012/08/27/reverse-engineering-the-syma-s107g-ir-protocol/
[5]: http://adafruit.com/products/388
[6]: http://adafruit.com/products/1018
[7]: http://www.avergottini.com/2011/05/arduino-helicopter-infrared-controller.html