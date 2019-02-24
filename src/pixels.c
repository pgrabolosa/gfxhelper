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
void _getRawPixels ( GraphicContext* cg, unsigned char** data, int* pixelsWidth, int* pixelSize ) {
	
	cairo_surface_t* surface = cg->cairoContextSurface;
	if ( cairo_image_surface_get_format( surface ) != CAIRO_FORMAT_ARGB32 ) {
		fprintf(
				stderr, "GFX LIB INTERNAL ERROR: point() - unexpected image format (expected=%d, got=%d)",
				CAIRO_FORMAT_ARGB32, cairo_image_surface_get_format( surface ));
		return;
	}
	
	cairo_surface_flush( surface ); // make sure all pending drawings are applied
	if ( data ) { *data = cairo_image_surface_get_data( surface ); } // get the raw data
	
	if ( pixelsWidth ) { *pixelsWidth = cairo_image_surface_get_width( surface ); }
	if ( pixelSize ) { *pixelSize = 4; } // 32 bits : CAIRO_FORMAT_ARGB32
}


/*--------------------------------------------------------------------------------------------------------------------*/
void point ( const int x, const int y ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	
	unsigned char* data;
	int pixelsWidth;
	int pixelSize;
	_getRawPixels( cg, &data, &pixelsWidth, &pixelSize );
	
	unsigned char* pixel = data + ( pixelsWidth * y * pixelSize + x * pixelSize );
	
	unsigned char r = 0x00;
	unsigned char g = 0x00;
	unsigned char b = 0x00;
	unsigned char a = 0xff;
	
	if ( !cg->noFill ) {
		r = ( unsigned char ) ( 255 * cg->fill_r );
		g = ( unsigned char ) ( 255 * cg->fill_g );
		b = ( unsigned char ) ( 255 * cg->fill_b );
		a = ( unsigned char ) ( 255 * cg->fill_a );
	} else if ( !cg->noStroke ) {
		r = ( unsigned char ) ( 255 * cg->stroke_r );
		g = ( unsigned char ) ( 255 * cg->stroke_g );
		b = ( unsigned char ) ( 255 * cg->stroke_b );
		a = ( unsigned char ) ( 255 * cg->stroke_a );
	}
	
	pixel[ 0 ] = b; // B
	pixel[ 1 ] = g; // G
	pixel[ 2 ] = r; // R
	pixel[ 3 ] = a; // A
	
	cairo_surface_mark_dirty( cg->cairoContextSurface ); // redraw
}


/*--------------------------------------------------------------------------------------------------------------------*/
PixelColor_t* getPixels ( int* width, int* height ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	const int w = getWidth( );
	const int h = getHeight( );
	
	if ( width ) { *width = w; }
	if ( height ) { *height = h; }
	
	unsigned char* data;
	int pixelsWidth;
	int pixelSize;
	_getRawPixels( cg, &data, &pixelsWidth, &pixelSize );
	
	PixelColor_t* pixels = malloc( sizeof( PixelColor_t ) * w * h );
	
	for ( int x = 0; x < w; x++ ) {
		for ( int y = 0; y < h; y++ ) {
			unsigned char* raw_pixel = data + ( pixelsWidth * y * pixelSize + x * pixelSize );
			PixelColor_t* pixel = pixels + ( x + y * w );
			
			pixel->blue = raw_pixel[ 0 ] / 255.0f;
			pixel->green = raw_pixel[ 1 ] / 255.0f;
			pixel->red = raw_pixel[ 2 ] / 255.0f;
			// raw_pixel[3] : alpha
		}
	}
	
	return pixels;
}


/*--------------------------------------------------------------------------------------------------------------------*/
void setPixels ( const PixelColor_t* pixels ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	const int w = getWidth( );
	const int h = getHeight( );
	
	unsigned char* data;
	int pixelsWidth;
	int pixelSize;
	_getRawPixels( cg, &data, &pixelsWidth, &pixelSize );
	
	for ( int x = 0; x < w; x++ ) {
		for ( int y = 0; y < h; y++ ) {
			unsigned char* raw_pixel = data + ( pixelsWidth * y * pixelSize + x * pixelSize );
			const PixelColor_t* pixel = pixels + ( x + y * w );
			
			raw_pixel[ 0 ] = ( unsigned char ) ( pixel->blue * 255 );
			raw_pixel[ 1 ] = ( unsigned char ) ( pixel->green * 255 );
			raw_pixel[ 2 ] = ( unsigned char ) ( pixel->red * 255 );
			// raw_pixel[3] : alpha
		}
	}
	
	cairo_surface_mark_dirty( cg->cairoContextSurface ); // redraw
}


/*--------------------------------------------------------------------------------------------------------------------*/
void freePixels ( PixelColor_t* pixels ) {
	free( pixels );
}


/*--------------------------------------------------------------------------------------------------------------------*/
PixelColor_t** getPixels_2D ( int* width, int* height ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	const int w = getWidth( );
	const int h = getHeight( );
	
	if ( width ) { *width = w; }
	if ( height ) { *height = h; }
	
	unsigned char* data;
	int pixelsWidth;
	int pixelSize;
	_getRawPixels( cg, &data, &pixelsWidth, &pixelSize );
	
	PixelColor_t** pixels = malloc( sizeof( PixelColor_t* ) * w );
	
	for ( int x = 0; x < w; x++ ) {
		
		PixelColor_t* line = malloc( sizeof( PixelColor_t ) * h );
		pixels[ x ] = line;
		
		for ( int y = 0; y < h; y++ ) {
			unsigned char* raw_pixel = data + ( pixelsWidth * y * pixelSize + x * pixelSize );
			PixelColor_t* pixel = line + y;
			
			pixel->blue = raw_pixel[ 0 ] / 255.0f;
			pixel->green = raw_pixel[ 1 ] / 255.0f;
			pixel->red = raw_pixel[ 2 ] / 255.0f;
			// raw_pixel[3] : alpha
		}
	}
	
	return pixels;
}


/*--------------------------------------------------------------------------------------------------------------------*/
void setPixels_2D ( const PixelColor_t** pixels ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	const int w = getWidth( );
	const int h = getHeight( );
	
	unsigned char* data;
	int pixelsWidth;
	int pixelSize;
	_getRawPixels( cg, &data, &pixelsWidth, &pixelSize );
	
	for ( int x = 0; x < w; x++ ) {
		for ( int y = 0; y < h; y++ ) {
			unsigned char* raw_pixel = data + ( pixelsWidth * y * pixelSize + x * pixelSize );
			const PixelColor_t* pixel = pixels[ x ] + y;
			
			raw_pixel[ 0 ] = ( unsigned char ) ( pixel->blue * 255 );
			raw_pixel[ 1 ] = ( unsigned char ) ( pixel->green * 255 );
			raw_pixel[ 2 ] = ( unsigned char ) ( pixel->red * 255 );
			// raw_pixel[3] : alpha
		}
	}
	
	cairo_surface_mark_dirty( cg->cairoContextSurface ); // redraw
}


/*--------------------------------------------------------------------------------------------------------------------*/
void freePixels_2D ( PixelColor_t** pixels ) {
	
	const int w = getWidth( );
	for ( int x = 0; x < w; x++ ) {
		free( pixels[ x ] );
	}
	free( pixels );
}
