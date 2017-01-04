// Copyright (C) 2017 Pierre Grabolosa
// 
// This file is part of the GfxHelper library.
// GfxHelper is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// GfxHelper is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Bash.  If not, see <http://www.gnu.org/licenses/>.

#include <GfxHelper.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

int rx, ry, gx, gy, bx, by;
bool mouseWasDown = false;
bool mouseWasReleased = false;
bool mouseWasPressed = false;
char current = ' ';
const float radius = 100;
int offset_x = 0;
int offset_y = 0;

void onKeyUp ( ) {  
	char c;
	
	switch ( getKeyPressed( )) {
		case 'c':
		case 'C':
			c = 'c';
			break;
		case 'm':
		case 'M':
			c = 'm';
			break;
		case 'j':
		case 'J':
		case 'y':
		case 'Y':
			c = 'y';
			break;
		default:
			c = ' '; // none
	}
	
	if ( c == current ) current = ' ';
	else current = c;
}

void setup ( ) {
	rx = getWidth()/2;
	ry = getHeight()/4;
	gx = getWidth()/3;
	gy = getHeight()/2;
	bx = 2*getWidth()/3;
	by = getHeight()/2;
	
	setKeyUpHandler( onKeyUp );
}

float dist ( const float x0, const float y0, const float x1, const float y1 ) {
	return hypotf( x0 - x1, y0 - y1 );
}



void draw ( ) {
  mouseWasReleased = mouseWasDown && !isMousePressed();
  mouseWasPressed = !mouseWasDown && isMousePressed();
  
  if (mouseWasReleased) {
    current = ' '; // disabled
    offset_x = 0;
    offset_y = 0;
  } else if (mouseWasPressed) {
    const int mx = getMouseX();
    const int my = getMouseY();

    const float dr = dist(mx,my,rx,ry);
    const float dg = dist(mx,my,gx,gy);
    const float db = dist(mx,my,bx,by);
    
    if (dr <= radius && dr <= dg && dr <= db) {
      current = 'c';
      offset_x = mx-rx;
      offset_y = my-ry;
    } else if (db <= radius && db <= dg && db <= dr) {
      current = 'y';
      offset_x = mx-bx;
      offset_y = my-by;
    } else if (dg <= radius && dg <= db && dg <= dr) {
      current = 'm';
      offset_x = mx-gx;
      offset_y = my-gy;
    }
  }
  
	background( 1, 1, 1 );
	int w, h;
	PixelColor_t** pixels = getPixels_2D( &w, &h );
	
	int* mx = NULL;
	int* my = NULL;
	
	switch ( current ) {
		case 'c':
			mx = &rx;
			my = &ry;
			break;
		case 'm':
			mx = &gx;
			my = &gy;
			break;
		case 'y':
			mx = &bx;
			my = &by;
			break;
		default:
			break; // do nothing
	}
	
	if ( mx ) { *mx = getMouseX( ) - offset_x; }
	if ( my ) { *my = getMouseY( ) - offset_y; }
	
	for ( int x = 0; x < w; x++ ) {
		for ( int y = 0; y < h; y++ ) {
			pixels[ x ][ y ].red   = 1 - ( radius >= dist( x, y, rx, ry ));
			pixels[ x ][ y ].green = 1 - ( radius >= dist( x, y, gx, gy ));
			pixels[ x ][ y ].blue  = 1 - ( radius >= dist( x, y, bx, by ));
		}
	}
	
	setPixels_2D( (const PixelColor_t**)pixels );
	freePixels_2D( pixels );
  
  mouseWasDown = isMousePressed();
}

int main ( int argc, char** argv ) {
	startGraphicsLoopWithSetup( 500, 500, setup, draw );
	return 0;
}