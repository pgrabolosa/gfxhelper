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
/** Opaque type used to represent images. */
struct ImageOpaque_t {
	cairo_surface_t* surface;
};


/*--------------------------------------------------------------------------------------------------------------------*/
Image_t* loadImage ( const char* path ) {
	
	cairo_surface_t* surface = cairo_image_surface_create_from_png( path );
	if ( surface == NULL || cairo_surface_get_reference_count( surface ) == 0 ) {
		return NULL;
	}
	
	Image_t* image = malloc( sizeof( Image_t ));
	image->surface = surface;
	
	return image;
}


/*--------------------------------------------------------------------------------------------------------------------*/
void paintImage ( const Image_t* image, const int x, const int y ) {
	
	paintImageWithSize( image, x, y, getImageWidth( image ), getImageHeight( image ));
}


/*--------------------------------------------------------------------------------------------------------------------*/
void paintImageWithSize ( const Image_t* image, const int x, const int y, const int width, const int height ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	
	const double w = width;
	const double h = height;
	
	
	pushMatrix();
		cairo_translate( cg->cairoContext, x, y);
		cairo_scale( cg->cairoContext, w / getImageWidth( image ), h / getImageHeight( image ));

		cairo_set_source_surface( cg->cairoContext, image->surface, 0, 0 );
		cairo_paint( cg->cairoContext );
	popMatrix();
}


/*--------------------------------------------------------------------------------------------------------------------*/
int getImageWidth ( const Image_t* image ) {
	
	return cairo_image_surface_get_width( image->surface );
}


/*--------------------------------------------------------------------------------------------------------------------*/
int getImageHeight ( const Image_t* image ) {
	
	return cairo_image_surface_get_height( image->surface );
}


/*--------------------------------------------------------------------------------------------------------------------*/
PixelColor_t* getImagePixels ( const Image_t* image ) {
	
	cairo_surface_t* surface = image->surface;
	if ( cairo_image_surface_get_format( surface ) != CAIRO_FORMAT_ARGB32 ) {
		fprintf(
				stderr, "GFX LIB INTERNAL ERROR: unexpected image format (expected=%d, got=%d)",
				CAIRO_FORMAT_ARGB32, cairo_image_surface_get_format( surface ));
		return NULL;
	}
	
	unsigned char* data = cairo_image_surface_get_data( surface ); // get the raw data
	
	int w = cairo_image_surface_get_width( surface );
	int h = cairo_image_surface_get_height( surface );
	int pixelSize = 4; // 32 bits : CAIRO_FORMAT_ARGB32
	
	PixelColor_t* pixels = malloc( sizeof( PixelColor_t ) * w * h );
	
	for ( int x = 0; x < w; x++ ) {
		for ( int y = 0; y < h; y++ ) {
			unsigned char* raw_pixel = data + ( pixelSize * ( x + y * w ));
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
void freeImagePixels ( PixelColor_t* pixels ) {
	
	free( pixels );
}


/*--------------------------------------------------------------------------------------------------------------------*/
void freeImage ( Image_t* image ) {
	
	cairo_surface_destroy( image->surface );
	free( image );
}