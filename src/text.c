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
#include <cairo.h>

/*--------------------------------------------------------------------------------------------------------------------*/
void drawText ( const int x, const int y, const char* restrict text ) {
	
	GraphicContext* gc = _getCurrentGraphicContext( );
	cairo_t* cr = gc->cairoContext;
	
	Renderer renderPasses[] = { renderer_fill, renderer_stroke, NULL };
	for ( Renderer* renderCall = renderPasses; ( *renderCall ) != NULL; renderCall++ ) {
		if (( *renderCall )(FALSE)) {
			
			cairo_font_slant_t slant = gc->fontItalics ? CAIRO_FONT_SLANT_ITALIC : CAIRO_FONT_SLANT_NORMAL;
			cairo_font_weight_t weight = gc->fontBold ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL;
			
			cairo_select_font_face (cr, gc->fontName, slant, weight);
			cairo_set_font_size (cr, gc->fontSize);
			cairo_move_to (cr, x, y);
			cairo_text_path (cr, text);
			
			( *renderCall )(TRUE);
		}
	}
}


/*--------------------------------------------------------------------------------------------------------------------*/

void fontSize ( const float newSize ) {
	const float defaultSize = 30;
	GraphicContext* gc = _getCurrentGraphicContext( );
	
	if ( newSize <= 0 ) {
		gc->fontSize = defaultSize;
	} else {
		gc->fontSize = newSize;
	}
}


/*--------------------------------------------------------------------------------------------------------------------*/
void textBounds ( const char* restrict text, float* textBoxWidth, float* textBoxHeight ) {
	GraphicContext* gc = _getCurrentGraphicContext( );
	cairo_t* cr = gc->cairoContext;
	cairo_text_extents_t boundingBox;
			
	cairo_font_slant_t slant = gc->fontItalics ? CAIRO_FONT_SLANT_ITALIC : CAIRO_FONT_SLANT_NORMAL;
	cairo_font_weight_t weight = gc->fontBold ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL;
	
	cairo_select_font_face (cr, gc->fontName, slant, weight);
	cairo_set_font_size (cr, gc->fontSize);
	
	cairo_text_extents (cr, text, &boundingBox);
	if (textBoxHeight) *textBoxHeight = boundingBox.height;
	if (textBoxWidth) *textBoxWidth = boundingBox.width;
}