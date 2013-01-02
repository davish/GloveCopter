# The Copter Glove #
### Arduino-Powered IR motion control glove for the S107 toy helicopter ###
#### Progress documented on [GitHub][8] ####

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

Today the accelerometer and IR LEDs arrived! As soon as I got the package from Adafruit I opened it up and soldered the headers to the accelerometer. After playing with it a little, I decided that the range for the tilt should be the equivalent of 330 - 340 on the output of the accelerometer. It was about 45 degrees from 335 (center, no movement) to 340 (tilted to a side). Observing the Z-axis, I decided that there wasn't enough change to measure up/down for throttle control, so I'll just use a potentiometer instead. I modified the sketch to let the pitch and yaw be controlled by the x and y axes, respectively. The Throttle is now controlled by a pot connected to analog pin 5. Tomorrow I'll have some more time to play with this setup, and see how sensitive it actually is.

## A working controller ##
### 12/14/12 ###

Today, I really got down to a working prototype. I had a glitch in the code from the night before that I had fixed during the day, so I uploaded it when I got home and got cracking. After a change which made it easier to keep the copter steady, I was really flying. Since this is still more than a little rough around the edges, it's a challenge to fly. I was bumping into walls a lot of the time, and every time the helicopter hit a wall, it fell. Finally, I run out of charge, so I take a break to charge back up. When I come back, I turn on my camera to document the working prototype when I realize my back rotor is not completely on. It had come off while it was spinning and hitting the wall at the same time. Luckily, every S107 comes with a spare one of these small rotors, so I grabbed mine, slapped it on, and tested it with the regular controller to make sure it was on correctly. When I was back to video documenting the project, I realize how hard it is to capture both the copter and me in the same frame with a homemade tripod (really just my walled in the front, and my Kelvin.23 in the back with my Bloggie in the middle). I did get a few good shots, but they were all at most 15 seconds long. If I want this to be a good controller, flights should be at least a minute and a half long. Now that I know that everything is basically functioning, I have two main goals:

1. Add stability to the controller
	- make it easier to control throttle (joystick maybe?)
2. Add range to the controller
	- the range is better with the super-bright LEDs, but still not good. I don't know if wiring more LEDs in parallel would help, but in one of the articles I read about the S107 it said that transistor switching would enlarge the range. 
		- do research on transistor switching and how they relate to LEDs.

## Improving the code ##
### 12/16/12 ###

Yesterday and today all I was working on really was taking out some of the kinks. You can check out the commits from those two days on [GitHub][8] if you're interested. I really need to work out the trim though, right now I have to tilt my hand to the right to get the copter flying steady. Once I get the final parts and build I'll probably add a pot for trim.

## Finishing the controller ##
### 12/18/12 ###

I think today I can finally say that the controller is finished. I will still need to tweak calibrations when I move from the prototype controller to a final, more glove-like form. An [Arduino Micro][9] some [Adafruit Proto-Boards][10]. I don't have access to a 3D printer, but I was thinking of either covering a bent clothes hanger with sugru, or designing a model to get printed on Shapeways. With the addition of an adjustable minimum/maximum values for x and y axes, the program can be used by anyone with an arduino, accelerometer (not just the one I use) and an IR LED. The one more thing on my to-do list is to add support for a trim potentiometer.

## Modifying the Throttle Control ##
### 1/1/13 ###

Back from Winter Break, I'm starting to put together the less clunky version 2.0 of the remote. I realized that using a volume dial to control the throttle wouldn't be too practical if you wanted to use the remote with only one hand (the hand you're wearing it on). So, I decided to use a joystick. Moving the joystick up or down would add or subtract a certain number from the throttle. Leaving the joystick alone would keep the throttle the same, so no need to keep your hand on the throttle all the time if you're just hovering. Hopefully tonight I can draw up some circuit diagrams for reference and get started soldering everything into the final package. About that "final package:" My first idea was to use a 3D printer to print out something that would be like a more stable and solid version of my first prototype, but I don't have access to a 3D printer. Next idea: bend a clothes hanger into a shape I can mount my components on, and then cover it with sugru to make it smooth and look pretty. While (idiotically) trying to cut the clothes hangar, I broke my wire cutters. So, I've decided to just put velcro around the Adafruit perf board I have, and strap it to my hand, and hold the battery pack a kind of grip in my palm. The velcro is good because I can just remove it if I find a better solution.

## Remote is complete! ##
### 1/2/13 ###

Today, I finished soldering everything onto the board. After the Arduino was on there, I tested the throttle joystick and IR LEDs to make sure everything was connected properly, and it was. Next was the accelerometer. I hooked it up and that worked fine as well.


[1]: http://hackaday.com/2012/12/08/more-fun-with-syma-107-reverse-engineering/
[2]: http://www.thinkgeek.com/product/f2c6/
[3]: http://www.jimhung.co.uk/?p=901
[4]: http://www.kerrywong.com/2012/08/27/reverse-engineering-the-syma-s107g-ir-protocol/
[5]: http://adafruit.com/products/388
[6]: http://adafruit.com/products/1018
[7]: http://www.avergottini.com/2011/05/arduino-helicopter-infrared-controller.html
[8]: https://github.com/dbh937/GloveCopter
[9]: http://adafruit.com/products/1086
[10]: http://adafruit.com/products/571