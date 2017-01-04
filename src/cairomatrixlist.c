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
#include <private_headers/cairomatrixlist.h>
#include <stdlib.h>

CairoMatrixList* CairoMatrixList_new ( ) {
	CairoMatrixList* n = malloc( sizeof( CairoMatrixList ));
	cairo_matrix_init_identity( &n->matrix );
	n->prev = NULL;
	n->next = NULL;
  return n;
}

CairoMatrixList* CairoMatrixList_last ( CairoMatrixList* list ) {
	CairoMatrixList* c;
	for ( c = list; c->next != NULL; c = c->next ) { }
	return c;
}

CairoMatrixList* CairoMatrixList_pop ( CairoMatrixList* list ) {
	CairoMatrixList* last = CairoMatrixList_last( list );
	if ( last->prev != NULL) {
		CairoMatrixList* prev = last->prev;
		prev->next = NULL;
		free( last );
		return prev;
	} else {
		// if poping the first matrix, reset it to identity
		cairo_matrix_init_identity( &last->matrix );
		return last;
	}
}

CairoMatrixList* CairoMatrixList_push ( CairoMatrixList* list ) {
	CairoMatrixList* last = CairoMatrixList_last( list );
	CairoMatrixList* n = CairoMatrixList_new( );
	n->prev = last;
	last->next = n;
	n->matrix = last->matrix;
	return n;
}

void CairoMatrixList_rotate ( CairoMatrixList* list, double radians ) {
	CairoMatrixList* last = CairoMatrixList_last( list );
	cairo_matrix_rotate( &last->matrix, radians );
}

void CairoMatrixList_scale ( CairoMatrixList* list, double x, double y ) {
	CairoMatrixList* last = CairoMatrixList_last( list );
	cairo_matrix_scale( &last->matrix, x, y );
}

void CairoMatrixList_translate ( CairoMatrixList* list, double x, double y ) {
	CairoMatrixList* last = CairoMatrixList_last( list );
	cairo_matrix_translate( &last->matrix, x, y );
}

void CairoMatrixList_set ( CairoMatrixList* list, cairo_t* ct ) {
	cairo_set_matrix( ct, &CairoMatrixList_last( list )->matrix );
}