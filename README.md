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

The file [`src/public_header.h`](https://github.com/pgrabolosa/gfxhelper/blob/master/src/public_header.h) contains the API documentation.

Here is a short example:

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

The Mac support supposes you compiled and installed Gtk+3 on your Mac:

  1. Follow the steps from [Building GTK-OSX](https://wiki.gnome.org/Projects/GTK+/OSX/Building) - mind to substitute `meta-gtk-osx-gtk3` for `meta-gtk-osx-core` as we requires Gtk3 instead of Gtk2. Compiling takes some time but the process is quite straightforward.
  2. Get the GTK [Bundler](https://wiki.gnome.org/Projects/GTK+/OSX/Bundling) which will let you create "regular" looking Mac apps with Gtk+3 embedded.

## Documentation

Partially out of date documentation and extra information can be found on the previous home (no sources there): 

http://perso.imerir.com/pgrabolosa/2016/langc-gfxhelper/
