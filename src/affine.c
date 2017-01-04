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
void pushMatrix ( ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	CairoMatrixList_push( cg->matrixList );
	CairoMatrixList_set( cg->matrixList, cg->cairoContext );
}


/*--------------------------------------------------------------------------------------------------------------------*/
void popMatrix ( ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	CairoMatrixList_pop( cg->matrixList );
	CairoMatrixList_set( cg->matrixList, cg->cairoContext );
}


/*--------------------------------------------------------------------------------------------------------------------*/
void rotate ( const double radians ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	CairoMatrixList_rotate( cg->matrixList, radians );
	CairoMatrixList_set( cg->matrixList, cg->cairoContext );
}


/*--------------------------------------------------------------------------------------------------------------------*/
void translate ( const double x, const double y ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	CairoMatrixList_translate( cg->matrixList, x, y );
	CairoMatrixList_set( cg->matrixList, cg->cairoContext );
}


/*--------------------------------------------------------------------------------------------------------------------*/
void scale ( const double x, const double y ) {
	
	GraphicContext* cg = _getCurrentGraphicContext( );
	CairoMatrixList_scale( cg->matrixList, x, y );
	CairoMatrixList_set( cg->matrixList, cg->cairoContext );
}