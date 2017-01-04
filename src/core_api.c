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

#include <public_header.h>
#include <private_headers/lib_common.h>

/*--------------------------------------------------------------------------------------------------------------------*/
float randomUniform ( ) {
	
	static GRand* rand = NULL;
	if ( rand == NULL) {
		rand = g_rand_new( );
	}
	
	return ( float ) g_rand_double( rand );
}

/*--------------------------------------------------------------------------------------------------------------------*/
int getMouseX ( ) {
	
	return _getCurrentGraphicContext( )->mouseX;
}


/*--------------------------------------------------------------------------------------------------------------------*/
int getMouseY ( ) {
	
	return _getCurrentGraphicContext( )->mouseY;
}


/*--------------------------------------------------------------------------------------------------------------------*/
void background ( const float r, const float g, const float b ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	
	cairo_set_source_rgb( cg->cairoContext, r, g, b );
	cairo_paint( cg->cairoContext );
}


/*--------------------------------------------------------------------------------------------------------------------*/
void backgroundAlpha ( const float r, const float g, const float b, const float a ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	
	cairo_set_source_rgba( cg->cairoContext, r, g, b, a );
	cairo_paint( cg->cairoContext );
}


/*--------------------------------------------------------------------------------------------------------------------*/
void fill ( const float r, const float g, const float b ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	
	cg->noFill = 0;
	cg->fill_r = r;
	cg->fill_g = g;
	cg->fill_b = b;
	cg->fill_a = 1;
}


/*--------------------------------------------------------------------------------------------------------------------*/
void fillAlpha ( const float r, const float g, const float b, const float a ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	
	cg->noFill = 0;
	cg->fill_r = r;
	cg->fill_g = g;
	cg->fill_b = b;
	cg->fill_a = a;
}


/*--------------------------------------------------------------------------------------------------------------------*/
void noFill ( ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	cg->noFill = 1;
}


/*--------------------------------------------------------------------------------------------------------------------*/
void stroke ( const float r, const float g, const float b ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	
	cg->noStroke = 0;
	if ( cg->strokeWidth == 0 ) {
		cg->strokeWidth = 1.0;
	}
	cg->stroke_r = r;
	cg->stroke_g = g;
	cg->stroke_b = b;
	cg->stroke_a = 1;
}


/*--------------------------------------------------------------------------------------------------------------------*/
void strokeAlpha ( const float r, const float g, const float b, const float a ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	
	cg->noStroke = 0;
	if ( cg->strokeWidth == 0 ) {
		cg->strokeWidth = 1.0;
	}
	cg->stroke_r = r;
	cg->stroke_g = g;
	cg->stroke_b = b;
	cg->stroke_a = a;
}


/*--------------------------------------------------------------------------------------------------------------------*/
void strokeWidth ( const float width ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	cg->strokeWidth = width;
}


/*--------------------------------------------------------------------------------------------------------------------*/
void noStroke ( ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	cg->noStroke = 1;
}

/*--------------------------------------------------------------------------------------------------------------------*/
void rect ( const int topLeftX, const int topLeftY, const int width, const int height ) {
	
	cairo_t* cr = _getCurrentGraphicContext( )->cairoContext;
	
	Renderer renderPasses[] = { renderer_fill, renderer_stroke, NULL };
	for ( Renderer* renderCall = renderPasses; ( *renderCall ) != NULL; renderCall++ ) {
		if (( *renderCall )(FALSE)) {
			
			cairo_rectangle( cr, topLeftX, topLeftY, width, height );
			
			( *renderCall )(TRUE);
		}
	}
}


/*--------------------------------------------------------------------------------------------------------------------*/
void line ( const int x0, const int y0, const int x1, const int y1 ) {
	
	cairo_t* cr = _getCurrentGraphicContext( )->cairoContext;
	
	Renderer renderPasses[] = {/*renderer_fill,*/ renderer_stroke, NULL };
	for ( Renderer* renderCall = renderPasses; ( *renderCall ) != NULL; renderCall++ ) {
		if (( *renderCall )(FALSE)) {
			
			cairo_new_path( cr );
			cairo_move_to( cr, x0, y0 );
			cairo_line_to( cr, x1, y1 );
			
			( *renderCall )(TRUE);
		}
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/
void triangle ( const int x0, const int y0, const int x1, const int y1, const int x2, const int y2 ) {
	
	cairo_t* cr = _getCurrentGraphicContext( )->cairoContext;
	
	Renderer renderPasses[] = { renderer_fill, renderer_stroke, NULL };
	for ( Renderer* renderCall = renderPasses; ( *renderCall ) != NULL; renderCall++ ) {
		if (( *renderCall )(FALSE)) {
			
			cairo_new_path( cr );
			cairo_move_to( cr, x0, y0 );
			cairo_line_to( cr, x1, y1 );
			cairo_line_to( cr, x2, y2 );
			cairo_close_path( cr );
			
			( *renderCall )(TRUE);
		}
	}
}


/*--------------------------------------------------------------------------------------------------------------------*/
void disc ( const int x, const int y, const int radius ) {
	
	cairo_t* cr = _getCurrentGraphicContext( )->cairoContext;
	
	Renderer renderPasses[] = { renderer_fill, renderer_stroke, NULL };
	for ( Renderer* renderCall = renderPasses; ( *renderCall ) != NULL; renderCall++ ) {
		if (( *renderCall )(FALSE)) {
			
			cairo_arc( cr, x, y, radius, 0, 2 * G_PI );
			
			( *renderCall )(TRUE);
		}
	}
}


/*--------------------------------------------------------------------------------------------------------------------*/
int getWidth ( ) {
	
	return gtk_widget_get_allocated_width( _getCurrentGraphicContext( )->widget );
}


/*--------------------------------------------------------------------------------------------------------------------*/
int getHeight ( ) {
	
	return gtk_widget_get_allocated_height( _getCurrentGraphicContext( )->widget );
}


/*--------------------------------------------------------------------------------------------------------------------*/
long millis ( ) {
	
	struct timeval tv;
	gettimeofday( &tv, NULL);
	unsigned long ms = ( unsigned long ) ( tv.tv_sec * 1000 + tv.tv_usec / 1000 );
	
	unsigned long uptime = ms - _getCurrentGraphicContext( )->programStartTime;
	
	return ( long ) uptime;
}


/*--------------------------------------------------------------------------------------------------------------------*/
void hideCursor ( ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	
	static GdkCursor* blankCursor = NULL;
	if ( blankCursor == NULL) {
		blankCursor = gdk_cursor_new_for_display( gdk_display_get_default(), GDK_BLANK_CURSOR );
	}
	
	GdkWindow* wnd = gtk_widget_get_window( GTK_WIDGET(cg->window) );
	gdk_window_set_cursor( wnd, blankCursor );
}


/*--------------------------------------------------------------------------------------------------------------------*/
void showCursor ( ) {
	
	GdkWindow* wnd = GDK_WINDOW( gtk_widget_get_window( _getCurrentGraphicContext( )->widget ));
	gdk_window_set_cursor( wnd, NULL);
}


/*--------------------------------------------------------------------------------------------------------------------*/
void setFrameRate ( int rate ) {
	
	if (_getCurrentGraphicContext() != NULL) {
		fprintf(stderr, "Error: setFrameRate must be called before setup\n");
		return;
	}
	
	frameRate = rate;
}


/*--------------------------------------------------------------------------------------------------------------------*/
int getFrameRate ( ) {
	
	return frameRate;
}
