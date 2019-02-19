# GfxHelper Library

[![Platforms](https://img.shields.io/badge/platforms-Linux%20%7C%20Mac-lightgrey.svg?style=plastic)]() [![Dependency](https://img.shields.io/badge/dependency-Gtk%2B3-red.svg?style=plastic)](https://www.gtk.org/) [![License](https://img.shields.io/badge/license-GPLv3-blue.svg?style=plastic)](http://www.gnu.org/licenses/)

## About

This library was created for academic purposes to help freshmen get started with C programming at [IMERIR](https://www.imerir.com/). The focus was not to provide a well coded or optimised library (sources were closed). The goal was to provide a simple API, [Processing](https://processing.org) inspired.

## Requirements

   * Gtk+3 / Cairo
	 * CMake


## Quickstart 

Once you've downloaded this repository:

```
cmake -G "Unix Makefiles" .
cmake --build . --target GfxHelperDemo
```

On GNU/Linux, the follow extra step may be necessary:

```
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
```

Then, run the program:

```
./GfxHelperDemo
```


## Brief example


    #include <GfxHelper.h>

    void draw ( ) {
    	background( 0.8, 0.8, 1.0 );
	
    	noStroke( );
	
    	// herbe
    	fill( 0, 0.8, 0 );
    	rect( 0, 300, 500, 200 );
	
    	// soleil
    	fill( 255, 255, 0 );
    	disc( 80, 80, 30 );
    }

    int main ( int argc, char** argv ) {
    	startGraphicsLoop( 500, 500, draw );
    	return 0;
    }  


Then:

  1. Save this code to a file, let's name it `my_custom_main.c`.
  2. Then build the library (if not already done) `cmake --build . --target GfxHelper`
	3. Compile and link against the library (and Gtk+3): `gcc -L. -I./src my_custom_main.c -lGfxHelper`

## Mac Support

To use this library with macOS, the usage of [brew](https://brew.sh/) to install the dependencies is recommended as the way to go. The usage of [JetBrain's CLion](https://www.jetbrains.com/clion/) is recommended as well.

## Documentation

The file [`src/public_header.h`](https://github.com/pgrabolosa/gfxhelper/blob/master/src/public_header.h) contains the API documentation.

## Known Bugs/Issues

  * improper use of the timer + events to refresh the display
	* key and mouse events trigger extra events
	* lack of framerate checks (no alerts)
	* no multithreading support (untested)

Plans to fix? None. This is is merely a small convenience wrapper around Cairo/Gtk to ease some C programming beginner coding.
