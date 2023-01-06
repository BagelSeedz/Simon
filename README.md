# Simon

## The Device:

The end goal for this project was to create a device that mimics the functionality and entertainment of the well known simon by Hasbro gaming.

This toy is directed towards audiences of all ages, including those whose hearing or vision is impaired.

The device simulates a memorization game which the user can play to test their memorization skills. A sequence of colors are lit up on the device, and the user must press the buttons corresponding to those colors in the exact order that they were lit up in order to keep playing. In order to make the game more challenging after each correct answer, the length of the sequence will increment by one and the speed at which the sequence is displayed will increase until it reaches its maximum speed.

## Designing:

With limited supplies and a tight deadline, I had to resort to simple 3D printing that doesn’t take very long to design. I settled for a simple square, rather than a circle, with filet corners so that the device is easy to hold and not dangerous to give to a child. I spent the most time researching and measuring the dimensions of the components I will be using so that I can design openings for the conductive parts of the components to stick through. After 3 prototypes and failed prints, I finally got a good finalized top plate. The openings allowed for the easy installation of the four LEDs and four buttons required for the functionality of the game:

## Assembly:

After completing my previous project (an alarm clock powered by arduino) I quickly learned that the process of wiring everything together would have been so much easier if I followed some sort of organization to manage the electricity.

When I wired the buttons to the board, I used one red wire connected to all four buttons and one of the analog pins on the arduino to create an easy circuit to power all of them. Contrarily, each button has their own individual pin assigned to it for data.

After testing the device I ran into an issue where I did not have control over the buttons and they were constantly being pressed without me pressing them, which is what the code was telling me while I was debugging. I found that I forgot to wire the buttons to ground unlike how I did digitally with tinkercad: https://www.tinkercad.com/things/fXHrg0fRCFs-q2-project/editel

Because the functionality of the game was finished, I decided to add 2 more components: a piezo speaker that will sing at specific frequencies designated to each color, and a battery that will allow my device to be portable and not required to be connected to a USB to play. After researching, I found that the 12V Battery would work perfectly for powering the arduino in the circuit through its VIN pin.

I then showed my device around to other people to gather reviews so that I could see if anything needed to be changed. All the reviews were very positive, but I did receive a suggestion to change the frequencies to a G Major scale for a more pleasant sounding device.

- Red = D
- Blue = E
- Yellow = F#
- Green = G
- Start Game = High Octave A
- End Game = Low Octave A

## How to produce this product:

1. 3D print the top plate design with the correct dimensions.
2. Install the LEDs and Buttons onto the top plate.
- I used hot glue on the parts of the buttons and LEDs that I will not be soldering to on the back of the plate to secure them.
3. Solder (or attach depending on your board) to the arduino and all wires required for proper management to the breadboard.
4. Solder all power and ground components of the buttons together to an analog pin.
- Note that these will require about 1k ohm resistors.
5. Solder all data components of the buttons to their respective pins on the breadboard.
6. Solder all power and ground components of the LEDs to the breadboard
- Note that these will require about 1k resistors.
7. Solder a piezo speaker to the arduino
8. Use a 12V battery case and solder the power wire to VIN and the ground wire to GND.
9. 3D print an outer casing for the device so that the wires are not exposed.
- I did not have time to finish this because my print failed.

## Reflection:

I think this project went very well. It made me happy that all the reviews from friends, teachers, and family were positive. The mission was to create a device that everyone can use to train their memorization skills that is fun to use, and I believe that mission is accomplished. If I had a bit more time, I would have made a better design for the outer casing of the project, which includes a door with a hinge so that I can easily replace the battery or fix anything that needs to be fixed inside the device. This project overall was very fun, and I hope that whoever plays my simon game thinks that it is fun as well.
