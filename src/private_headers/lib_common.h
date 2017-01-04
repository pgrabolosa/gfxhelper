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

#ifndef GFXHELPER_COMMON
#define GFXHELPER_COMMON 1

#include <gtk/gtk.h>
#include <stdlib.h>
#include <sys/time.h>
#include <private_headers/cairomatrixlist.h>

extern int frameRate;

/*--------------------------------------------------------------------------------------------------------------------*/
/** This struct centralizes in one location many global states of our app.
 * */
typedef struct {
	
	GtkWidget* widget; // expected to be created with gtk_drawing_area_new()
	GtkWindow* window; // the window
	
	cairo_surface_t* cairoContextSurface;
	cairo_t* cairoContext;
	
	unsigned long programStartTime;
	
	int noFill; // 1 for true, 0 for false
	
	float fill_r; // red   : 0.0 - 1.0
	float fill_g; // green : 0.0 - 1.0
	float fill_b; // blue  : 0.0 - 1.0
	float fill_a; // alpha : 0.0 - 1.0
	
	int noStroke; // 1 for true, 0 for false
	float strokeWidth; // 1.0 by default
	
	float stroke_r; // red   : 0.0 - 1.0
	float stroke_g; // green : 0.0 - 1.0
	float stroke_b; // blue  : 0.0 - 1.0
	float stroke_a; // alpha : 0.0 - 1.0
	
	int mouseX;
	int mouseY;
	_Bool mouseClicked;
	
	_Bool keyPressed;
	guint32 keyUnicode;
	
	CairoMatrixList* matrixList;
	
	int paused; // 0: not paused, 1: paused requested, 2: pause granted
	
	CallbackNoArgs onDraw;
	CallbackNoArgs onMouseMoved;
	CallbackNoArgs onMouseClicked;
	CallbackNoArgs onKeyUp;
	CallbackNoArgs onKeyDown;
	
	char fontName[120];
	_Bool fontBold;
	_Bool fontItalics;
	float fontSize;
	
} GraphicContext;


/*--------------------------------------------------------------------------------------------------------------------*/
/** Returns the current graphic context. Ideally this can/should be implemented as a stack or multi-window, but for
 * now there is just a single graphic context.
 * */
GraphicContext* _getCurrentGraphicContext ( );


/*--------------------------------------------------------------------------------------------------------------------*/
/** A renderer draws the current cairo instructions. There are two renderers: stroke and fill. Because some drawing
 * functions only work as stoke or fill, while others can use both, we must provide the drawing instructions potentially
 * twice before each renderer. Having this `Renderer` function pointer type allows us to loop over the supported
 * renderes, leading to cleaner code, without repetition. See the implementation of `rect` or `disc` for examples.
 *
 * Note: The renderer can be "effective" or not (parameter `shouldProceed`. The point is to test whether the renderer
 * is enabled or not. This makes the renderer functions have two roles: testing whether a renderer is enabled and
 * doing the drawing.
 * */
typedef _Bool (* Renderer) ( _Bool shouldProceed );

_Bool renderer_stroke ( _Bool shouldProceed );
_Bool renderer_fill ( _Bool shouldProceed );
_Bool renderer_text ( _Bool shouldProceed );


/*--------------------------------------------------------------------------------------------------------------------*/


#endif // GFXHELPER_COMMON