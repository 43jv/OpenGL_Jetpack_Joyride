# Barry the Square

## Description

Arcade game similar to "Jetpack Joyride" made using OpenGL and C++.

* Commands to run the game:
  
	```console
	mkdir build
	cd build
	cmake ..
	make
	./JetPack_JoyRide
	```

## Features 

* Three different levels based on number of coins collected. Speed increases as levels increase.
* Level number and number of lives are displayed on the screen header.
* Pressing space activates the "jetpack"
* Zappers kill player on contact. There are static zappers in round 1 and vertically oscillating zappers from round 2 onwards.
* Coins determine player score. 1 coin = +1 score.
* Number of coins collected are displayed on screen.
