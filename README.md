# GfxHelper Library

[![Platforms](https://img.shields.io/badge/platforms-Linux%20%7C%20Mac-lightgrey.svg?style=plastic)]() [![Dependency](https://img.shields.io/badge/dependency-Gtk%2B3-red.svg?style=plastic)](https://www.gtk.org/) [![License](https://img.shields.io/badge/license-GPLv3-blue.svg?style=plastic)](http://www.gnu.org/licenses/)

## About

This library was created for academic purposes to help freshmen get started with graphics programming in C at [IMERIR](https://www.imerir.com/). The goal was not to provide a well coded library (sources were closed) nor a performance-tuned one. The goal was to provide a simple API, [processing](https://processing.org) inspired.

The library was initially available for Ubuntu only, required Gtk+3, and was only available as a binary (see [http://perso.imerir.com/pgrabolosa/2016/langc-gfxhelper/](http://perso.imerir.com/pgrabolosa/2016/langc-gfxhelper/) for extra details).


## Quickstart 

```
./build/default/build.sh examples/main_cymn.c
cd bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
./app.exe
```


## Tutorial

The [`src/public_header.h`](https://github.com/pgrabolosa/gfxhelper/blob/master/src/public_header.h) file contains the API documentation.

Meanwhile, here is a simple example:

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

Save this code to a file `toto.c`. Then execute the script `build/default/build.sh` from the project with a path to `toto.c` as argument. This will build the library and an executable from `toto.c`.

TODO: a better documentation + release.

## Mac Support

The Mac support supposes you compiled and installed Gtk+3 on your Mac:

  1. Follow the steps from [Building GTK-OSX](https://wiki.gnome.org/Projects/GTK+/OSX/Building) - mind to substitute `meta-gtk-osx-gtk3` for `meta-gtk-osx-core` as we requires Gtk3 instead of Gtk2. Compiling takes some time but the process is quite straightforward.
  2. Get the GTK [Bundler](https://wiki.gnome.org/Projects/GTK+/OSX/Bundling) which will let you create "regular" looking Mac apps with Gtk+3 embedded.

## Documentation

Partially out of date documentation and extra information can be found on the previous home (no sources there): 

http://perso.imerir.com/pgrabolosa/2016/langc-gfxhelper/
