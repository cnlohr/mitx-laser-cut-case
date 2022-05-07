# mitx-laser-cut-case

A custom acrylic, laser cut computer case for a mini-ITX motherboard, SFX power supply and RTX 3090 FE.

![Picture Of Completed Case](https://i.imgur.com/DFvdf7r.jpeg)

This was created using C and output to an SVG to be laser cut.  You can easily change parameters within the code to adjust all aspects of the case.

![Laser Cut Case](https://raw.githubusercontent.com/cnlohr/mitx-laser-cut-case/817c6c4a5f47b9cad9c90885fa5363badb07be6f/case.svg)

Note, you will need: 
 * A Laser Cutter
 * A little more than 24x18" of 3/4" (8.5-9mm) acrylic.
 * 6x #6-32 3/4" bolts, 6 #6-32 nuts.
 * A lot of M3 hardware.
 * A 144 LED/meter right-angle LED strip. (You'll need 72 LEDs)

Included for convenience is the SVG from my code.

Run this with the following command:

```
tcc -run gen_svg.c > case.svg
```
