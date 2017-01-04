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
_Bool isMousePressed ( ) {
	
	return _getCurrentGraphicContext( )->mouseClicked;
}


/*--------------------------------------------------------------------------------------------------------------------*/
_Bool isKeyPressed ( ) {
	
	return _getCurrentGraphicContext( )->keyPressed;
}


/*--------------------------------------------------------------------------------------------------------------------*/
unsigned long getKeyPressed ( ) {
	
	return _getCurrentGraphicContext( )->keyUnicode;
}


/*--------------------------------------------------------------------------------------------------------------------*/
void setMouseMoveHandler ( CallbackNoArgs callback ) {
	
	_getCurrentGraphicContext( )->onMouseMoved = callback;
}


/*--------------------------------------------------------------------------------------------------------------------*/
void setMouseClickHandler ( CallbackNoArgs callback ) {
	
	_getCurrentGraphicContext( )->onMouseClicked = callback;
}


/*--------------------------------------------------------------------------------------------------------------------*/
void setKeyUpHandler ( CallbackNoArgs callback ) {
	
	_getCurrentGraphicContext( )->onKeyUp = callback;
}


/*--------------------------------------------------------------------------------------------------------------------*/
void setKeyDownHandler ( CallbackNoArgs callback ) {
	
	_getCurrentGraphicContext( )->onKeyDown = callback;
}


/*--------------------------------------------------------------------------------------------------------------------*/
void setDrawHandler ( CallbackNoArgs callback ) {
	
	if ( callback != NULL) {
		_getCurrentGraphicContext( )->onDraw = callback;
	}
}


/*--------------------------------------------------------------------------------------------------------------------*/
void clearAllHandlers ( ) {
	
	GraphicContext* gc = _getCurrentGraphicContext( );
	
	gc->onKeyDown = ( CallbackNoArgs ) NULL;
	gc->onKeyUp = ( CallbackNoArgs ) NULL;
	gc->onMouseClicked = ( CallbackNoArgs ) NULL;
	gc->onMouseMoved = ( CallbackNoArgs ) NULL;
}