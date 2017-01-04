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

#ifndef GFXHELLOWORLD_AFFINEMATRIX_H
#define GFXHELLOWORLD_AFFINEMATRIX_H

#include <cairo.h>

typedef struct CairoMatrixList_ {
    cairo_matrix_t matrix;
    struct CairoMatrixList_* prev;
    struct CairoMatrixList_* next;
} CairoMatrixList;

CairoMatrixList* CairoMatrixList_new();
CairoMatrixList* CairoMatrixList_last(CairoMatrixList* list);
CairoMatrixList* CairoMatrixList_pop(CairoMatrixList* list);
CairoMatrixList* CairoMatrixList_push(CairoMatrixList* list);
void CairoMatrixList_rotate(CairoMatrixList* list, double radians);
void CairoMatrixList_scale(CairoMatrixList* list, double x, double y);
void CairoMatrixList_translate(CairoMatrixList* list, double x, double y);
void CairoMatrixList_set(CairoMatrixList* list, cairo_t* ct);

#endif //GFXHELLOWORLD_AFFINEMATRIX_H
