# GfxHelper Library

[![Platforms](https://img.shields.io/badge/platforms-Linux%20%7C%20Mac-lightgrey.svg?style=plastic)]()
   
[![Dependency](https://img.shields.io/badge/dependency-Gtk%2B3-red.svg?style=plastic)](https://www.gtk.org/)

[![License](https://img.shields.io/badge/license-GPLv3-blue.svg?style=plastic)](http://www.gnu.org/licenses/)

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

## Documentation

Partially out of date documentation and extra information can be found on the previous home (no sources there): 

http://perso.imerir.com/pgrabolosa/2016/langc-gfxhelper/
