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
#include <string.h>

#ifdef __APPLE__
#include <foreground.h>
#endif

// GTK uses (!FALSE) for TRUE causing warnings that expression can be simplified. This redef resolves this.
#ifdef TRUE
#undef TRUE
#define TRUE (1)
#endif



/*--------------------------------------------------------------------------------------------------------------------*/
// Global Variables

static GtkApplication* currentApplication = NULL;
static GraphicContext* _currentGraphicContext = NULL;
int frameRate = 30;


/*--------------------------------------------------------------------------------------------------------------------*/
GraphicContext* _getCurrentGraphicContext ( ) {
	
	return _currentGraphicContext;
}


/*--------------------------------------------------------------------------------------------------------------------*/
void _setCurrentGraphicContext ( GraphicContext* cg ) {
	
	_currentGraphicContext = cg;
}


/*--------------------------------------------------------------------------------------------------------------------*/
GraphicContext* GraphicContext_new ( CallbackNoArgs onDraw, int width, int height ) {
	
	GraphicContext* gc = malloc( sizeof( GraphicContext ));
	
	gc->widget = gtk_drawing_area_new( );
	
	struct timeval tv;
	gettimeofday( &tv, NULL);
	gc->programStartTime = ( unsigned long ) ( tv.tv_sec * 1000 + tv.tv_usec / 1000 );
	
	gc->mouseX = 0;
	gc->mouseY = 0;
	gc->mouseClicked = 0;
	
	gc->noFill = 1;
	gc->fill_r = 0;
	gc->fill_g = 0;
	gc->fill_b = 0;
	gc->fill_a = 0;
	
	gc->noStroke = 0;
	gc->strokeWidth = 1.0;
	gc->stroke_r = 0;
	gc->stroke_g = 0;
	gc->stroke_b = 0;
	gc->stroke_a = 0;
	
	gc->matrixList = CairoMatrixList_new( );
	
	gc->paused = 0;
	
	gc->onDraw = onDraw;
	gc->onKeyDown = NULL;
	gc->onKeyUp = NULL;
	gc->onMouseMoved = NULL;
	gc->onMouseClicked = NULL;

	gc->keyUnicode = 0;
	gc->keyCode = 0;
	gc->keyRawCode = 0;

	gc->cairoContextSurface = cairo_image_surface_create( CAIRO_FORMAT_ARGB32, width, height );
	gc->cairoContext = cairo_create( gc->cairoContextSurface );
	
	strcpy(gc->fontName, "Sans");
	gc->fontBold = 0;
	gc->fontItalics = 0;
	gc->fontSize = 30;
	
	return gc;
}


/*--------------------------------------------------------------------------------------------------------------------*/
typedef struct {
	int width;
	int height;
	CallbackNoArgs onStart;
	CallbackNoArgs onDraw;
} initializeGraphics_args;


/*--------------------------------------------------------------------------------------------------------------------*/
static gboolean _onRedraw ( GtkWidget* widget ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	if ( widget == cg->widget && GTK_IS_WIDGET( widget )) {
		gtk_widget_queue_draw( widget );
		fflush( stdout );
	}
	return TRUE;
}


/*--------------------------------------------------------------------------------------------------------------------*/
static gint _onMouseDown ( GtkWidget* widget, GdkEventButton* event ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	
	if ( widget != cg->widget ) { return FALSE; }
	
	cg->mouseX = ( int ) event->x;
	cg->mouseY = ( int ) event->y;
	cg->mouseClicked = event->button == 1;
	
	return TRUE;
}


/*--------------------------------------------------------------------------------------------------------------------*/
static gint _onMouseUp ( GtkWidget* widget, GdkEventButton* event ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	
	if ( widget != cg->widget ) { return FALSE; }
	
	cg->mouseX = ( int ) event->x;
	cg->mouseY = ( int ) event->y;
	cg->mouseClicked = 0;
	
	if ( cg->onMouseClicked ) { cg->onMouseClicked( ); }
	
	return TRUE;
}

/*--------------------------------------------------------------------------------------------------------------------*/
static KeyCode gdk_keyval_to_keycode(guint keyval) {
	uint32_t unicode = gdk_keyval_to_unicode(keyval);

	if ((unicode == 0x000A || unicode == 0x000D)|| // returns
		(0x0020 <= unicode && unicode <= 0x007E) || // Basic Latin
		(0x00A0 <= unicode && unicode <= 0x00FF) ){ // Latin-1 Supplement
		return KeyCode_latinMask | unicode;
	}

	switch(keyval) {
		case GDK_KEY_Left      : return KeyCode_Left;
		case GDK_KEY_Up        : return KeyCode_Up;
		case GDK_KEY_Right     : return KeyCode_Right;
		case GDK_KEY_Down      : return KeyCode_Down;
		case GDK_KEY_Escape    : return KeyCode_Escape;
		case GDK_KEY_Delete    : return KeyCode_Delete;
		case GDK_KEY_BackSpace : return KeyCode_BackSpace;
		case GDK_KEY_Return    : return KeyCode_Return;
		case GDK_KEY_Tab       : return KeyCode_Tab;
		case GDK_KEY_Shift_L   : return KeyCode_ShiftLeft;
		case GDK_KEY_Shift_R   : return KeyCode_ShiftRight;
		case GDK_KEY_Control_L : return KeyCode_ControlLeft;
		case GDK_KEY_Control_R : return KeyCode_ControlRight;
		case GDK_KEY_Meta_L    : return KeyCode_MetaLeft;
		case GDK_KEY_Meta_R    : return KeyCode_MetaRight;
		case GDK_KEY_Alt_L     : return KeyCode_AltLeft;
		case GDK_KEY_Alt_R     : return KeyCode_AltRight;
		default                : return KeyCode_None;
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/
static gint _onKeyPressed ( GtkWidget* widget, GdkEventKey* event ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	
	cg->keyPressed = 1;
	cg->keyUnicode = gdk_keyval_to_unicode(event->keyval);
	cg->keyCode = gdk_keyval_to_keycode(event->keyval);
	cg->keyRawCode = event->keyval;
	if ( cg->onKeyDown ) { cg->onKeyDown( ); }
	
	return TRUE;
}


/*--------------------------------------------------------------------------------------------------------------------*/
static gint _onKeyReleased ( GtkWidget* widget, GdkEventKey* event ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	
	cg->keyPressed = 0;
	cg->keyUnicode = gdk_keyval_to_unicode(event->keyval);
	cg->keyCode = gdk_keyval_to_keycode(event->keyval);
	cg->keyRawCode = event->keyval;
	if ( cg->onKeyUp ) { cg->onKeyUp( ); }
	
	return TRUE;
}


/*--------------------------------------------------------------------------------------------------------------------*/
static gint _onMouseMoved ( GtkWidget* widget, GdkEventMotion* event ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	
	if ( widget != cg->widget ) { return FALSE; }
	
	cg->mouseX = ( int ) event->x;
	cg->mouseY = ( int ) event->y;
	cg->mouseClicked =
			(( event->state & GDK_BUTTON1_MASK ) != 0 ) || (( event->state & GDK_BUTTON1_MOTION_MASK ) != 0 );
	
	if ( cg->onMouseMoved ) { cg->onMouseMoved( ); }
	
	return TRUE;
}


/*--------------------------------------------------------------------------------------------------------------------*/
_Bool renderer_fill ( _Bool shouldPaint ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	
	if ( cg->noFill ) {
		return 0;
	}
	
	if ( shouldPaint ) {
		cairo_t* cr = cg->cairoContext;
		
		cairo_set_source_rgba(
				cr,
				cg->fill_r,
				cg->fill_g,
				cg->fill_b,
				cg->fill_a
		);
		cairo_fill( cr );
	}
	
	return 1;
}


/*--------------------------------------------------------------------------------------------------------------------*/
_Bool renderer_stroke ( _Bool shouldProceed ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	
	if ( cg->noStroke || ( cg->strokeWidth == 0.0 )) {
		return 0;
	}
	
	if ( shouldProceed ) {
		cairo_t* cr = cg->cairoContext;
		
		cairo_set_source_rgba(
				cr,
				cg->stroke_r,
				cg->stroke_g,
				cg->stroke_b,
				cg->stroke_a
		);
		
		cairo_set_line_width( cr, cg->strokeWidth );
		cairo_stroke( cr );
	}
	
	return 1;
}


/*--------------------------------------------------------------------------------------------------------------------*/
_Bool renderer_text ( _Bool shouldProceed ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	
	if ( cg->noStroke && cg->noFill ) {
		return 0;
	}
	
	if ( shouldProceed ) {
		cairo_t* cr = cg->cairoContext;
		
		if ( !cg->noFill ) {
			
			cairo_set_source_rgba(
					cr,
					cg->fill_r,
					cg->fill_g,
					cg->fill_b,
					cg->fill_a
			);
			if (cg->noStroke) {
				cairo_fill( cr );
			} else {
				cairo_fill_preserve( cr );
			}
		}
		
		if ( !cg->noStroke ) {
			cairo_set_source_rgba(
					cr,
					cg->stroke_r,
					cg->stroke_g,
					cg->stroke_b,
					cg->stroke_a
			);
			cairo_set_line_width( cr, cg->strokeWidth );
			cairo_stroke( cr );
		}
	}
	
	return 1;
}


/*--------------------------------------------------------------------------------------------------------------------*/
static gboolean repaint ( GtkWidget* widget, cairo_t* cr, gpointer data ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	
	if ( widget != cg->widget ) {
		return FALSE;
	}
	
	cairo_set_source_rgb( cr, 1, 1, 1 );
	cairo_paint( cr );
	
	if ( cg->onDraw ) {
		cg->onDraw( );
		cairo_set_source_surface( cr, cg->cairoContextSurface, 0, 0 );
		cairo_paint( cr );
	}
	
	return TRUE;
}


/*--------------------------------------------------------------------------------------------------------------------*/
void _runStart ( GtkWidget* widget, gpointer user_data ) {
	
	CallbackNoArgs setup = ( CallbackNoArgs ) user_data;
	
	if ( setup != NULL) {
		setup( );
	}
}


/*--------------------------------------------------------------------------------------------------------------------*/
void _onWindowActivate ( GtkApplication* app, gpointer user_data ) {
	
	GtkWidget* window;
	initializeGraphics_args* args = ( initializeGraphics_args* ) user_data;
	
	window = gtk_application_window_new( app );
	
	GraphicContext* cg = GraphicContext_new( args->onDraw, args->width, args->height );
	cg->window = GTK_WINDOW(window);
	_setCurrentGraphicContext( cg );
	
	gtk_widget_set_size_request( cg->widget, args->width, args->height );
	gtk_container_add(GTK_CONTAINER( window ), cg->widget );
	g_signal_connect ( G_OBJECT( cg->widget ), "draw", G_CALLBACK( repaint ), NULL );
	
	gtk_window_set_title(GTK_WINDOW( window ), "" );
	gtk_window_set_position(GTK_WINDOW( window ), GTK_WIN_POS_CENTER );
	gtk_window_set_default_size(GTK_WINDOW( window ), args->width, args->height );
	
	g_signal_connect ( G_OBJECT( cg->widget ), "motion_notify_event", G_CALLBACK( _onMouseMoved ), NULL );
	g_signal_connect ( G_OBJECT( cg->widget ), "button_press_event", G_CALLBACK( _onMouseDown ), NULL );
	g_signal_connect ( G_OBJECT( cg->widget ), "button_release_event", G_CALLBACK( _onMouseUp ), NULL );
	g_signal_connect ( G_OBJECT( window ), "key_press_event", G_CALLBACK( _onKeyPressed ), NULL );
	g_signal_connect ( G_OBJECT( window ), "key_release_event", G_CALLBACK( _onKeyReleased ), NULL );
	g_signal_connect ( G_OBJECT( cg->widget ), "realize", G_CALLBACK( _runStart ), ( gpointer ) args->onStart );
	
	gtk_widget_set_events(GTK_WIDGET( cg->widget ), GDK_EXPOSURE_MASK
	                                                | GDK_LEAVE_NOTIFY_MASK
	                                                | GDK_BUTTON_PRESS_MASK
	                                                | GDK_BUTTON_RELEASE_MASK
	                                                | GDK_POINTER_MOTION_MASK
	                                                | GDK_POINTER_MOTION_HINT_MASK
	                                                | GDK_KEY_PRESS_MASK
	                                                | GDK_KEY_RELEASE_MASK
	);
	gtk_widget_show_all( window );
    gtk_window_present( GTK_WINDOW(window) );
	
#ifdef __APPLE__
	macos_force_foreground_level();
#endif
  
	g_timeout_add(( guint ) ( 1000.0 / frameRate ), ( GSourceFunc ) _onRedraw, ( gpointer ) cg->widget );
}


/*--------------------------------------------------------------------------------------------------------------------*/
void _startGraphicsLoop ( initializeGraphics_args args ) {	
	currentApplication = gtk_application_new( "com.imerir.demo", G_APPLICATION_FLAGS_NONE );
	g_signal_connect( currentApplication, "activate", G_CALLBACK( _onWindowActivate ), ( gpointer ) &args );
	g_application_run(G_APPLICATION( currentApplication ), 0, NULL);
	g_object_unref( currentApplication );
}


/*--------------------------------------------------------------------------------------------------------------------*/
void startGraphicsLoop ( int width, int height, CallbackNoArgs onDraw ) {
	
	_startGraphicsLoop(( initializeGraphics_args ) {
			                   .width = width,
			                   .height = height,
			                   .onStart = NULL,
			                   .onDraw = onDraw
	                   }
	);
}


/*--------------------------------------------------------------------------------------------------------------------*/
void startGraphicsLoopWithSetup ( int width, int height, CallbackNoArgs onStart, CallbackNoArgs onDraw ) {
	
	_startGraphicsLoop(( initializeGraphics_args ) {
			                   .width = width,
			                   .height = height,
			                   .onStart = onStart,
			                   .onDraw = onDraw
	                   }
	);
}