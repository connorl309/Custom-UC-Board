# Custom 32-bit ARM Microcontroller Board
This project is my attempt at designing and fabricating a custom PCB for the [TMPM46BF10FG](https://www.mouser.com/ProductDetail/Toshiba/TMPM46BF10FG?qs=wd5RIQLrsJi6ktKViwPiDg%3D%3D), developed by Toshiba. It is rich in features, and while not a very beginner friendly chip to work with, satisfies a lot of my requirements in finding a great UC to use.

A few references for the microcontroller can be found below.  
![ucitself](https://www.mouser.com/images/toshibaamericaelectroniccomponentsinc/images/LQFP-100.jpg)
![pinout](https://user-images.githubusercontent.com/107018918/196840320-e3c00fdf-ebaa-409e-834d-bef1e220234e.png)
![Screenshot 2022-10-19 211736](https://user-images.githubusercontent.com/107018918/196840550-193e51a6-3385-49fe-9a11-1703a2a91a75.png)
![Screenshot 2022-10-19 212023](https://user-images.githubusercontent.com/107018918/196840892-760bd4ab-9a68-41af-8e41-17d93a052977.png)

## The Board
The board itself is originally starting out as a 2-layer board. I will be trying to be aware of EMI and signal degradation effects, but due to me being a student, I don't have tons of cash to throw around on multilayer boards if I mess something up.  
A few of my core goals are as follows.

* Ease of access to GPIO and special function pins: not restricting their access or usage.
* Ease of use for the board overall: accessibility of peripherals, pin input and outputs, and uploading programs to the UC.
* Smart layout choices: can an end user easily identify their required pins, and understand board functionality.
* Does it feel *good* to use? (I hope so!)

This is my first foray into real PCB design, and I'm excited to display my progress on this project here.
