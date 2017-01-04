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

/**
 * @mainpage Welcome.
 * The library API documentation is within the public header file: GfxHelper-1.1.h
 *
 *
 *  @file      Public header functions for the graphic environment.
 *  @brief     Functions for the graphic environment.
 *  @details   These functions are meant to provide a Processing-like API for the C computer labs.
 *  @author    Pierre Grabolosa <pierre.grabolosa@imerir.com>
 *  @version   1.1
 *  @date      09-Sept-2016 (created)
 *  @date      21-Sept-2016 (last edited)
 *  @bug       None known. Please report by sending emails to pierre.grabolosa@imerir.com
 *  @copyright (c) 2016, IMERIR - full rights reserved. Cannot be used or copied without permission.
 */

#ifndef GFXHELLOWORLD_GRAPHICS_H
#define GFXHELLOWORLD_GRAPHICS_H


/*--------------------------------------------------------------------------------------------------------------------*/
/** Function pointer type for a no-arguments void-returning function.
 *
 * @since 1.0
 * */
typedef void (*CallbackNoArgs) ( );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Starts the graphic environement for the drawing calls.
 * This function should be called in the main of the program.
 *
 * @param width The width of the Window to create, in pixels.
 * @param height The height of the Window to create, in pixels.
 * @param onDraw Pointer to a function which will be called 30 times per second (by default) to draw on the Window.
 *
 * @related startGraphicsLoopWithSetup
 *
 * @since 1.0
 * */
void startGraphicsLoop ( const int width, const int height, const CallbackNoArgs onDraw );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Starts the graphic environement but allows for an "onStart" parameter.
 * This function should be called in the main of the program.
 *
 * @param width The width of the Window to create, in pixels.
 * @param height The height of the Window to create, in pixels.
 * @param onStart Pointer to a function which will be called *ONCE* before `onDraw` is ever called.
 * @param onDraw Pointer to a function which will be called 30 times per second (by default) to draw on the Window.
 *
 * @related startGraphicsLoop
 *
 * @since 1.0
 * */
void startGraphicsLoopWithSetup (
		const int width, const int height, const CallbackNoArgs onStart, const CallbackNoArgs onDraw
);


/*--------------------------------------------------------------------------------------------------------------------*/
/** Paints the whole window with the specified color.
 *
 * @param r Red component, from 0.0 to 1.0 (for 0 to 100%)
 * @param g Green component, from 0.0 to 1.0 (for 0 to 100%)
 * @param b Blue component, from 0.0 to 1.0 (for 0 to 100%)
 *
 * @since 1.0
 *
 * @related backgroundAlpha
 *
 * */
void background ( const float r, const float g, const float b );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Paints the whole window with the specified color with a transparency channel (alpha).
 *
 * @param r Red component, from 0.0 to 1.0 (for 0 to 100%)
 * @param g Green component, from 0.0 to 1.0 (for 0 to 100%)
 * @param b Blue component, from 0.0 to 1.0 (for 0 to 100%)
 * @param a alpha component, from 0.0 to 1.0 (for 0 to 100%)
 *
 * @since 1.0
 *
 * @related background
 *
 * */
void backgroundAlpha ( const float r, const float g, const float b, const float a );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Sets the filling color for the subsequent drawing calls (such as `rect`, `disk`, etc).
 *
 * @param r Red component, from 0.0 to 1.0 (for 0 to 100%)
 * @param g Green component, from 0.0 to 1.0 (for 0 to 100%)
 * @param b Blue component, from 0.0 to 1.0 (for 0 to 100%)
 *
 * @related noFill, fillAlpha
 * @relatedalso stroke, noStroke
 *
 * @since 1.0
 * */
void fill ( const float r, const float g, const float b );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Sets the filling color for the subsequent drawing calls (such as `rect`, `disk`, etc).
 *
 * @param r Red component, from 0.0 to 1.0 (for 0 to 100%)
 * @param g Green component, from 0.0 to 1.0 (for 0 to 100%)
 * @param b Blue component, from 0.0 to 1.0 (for 0 to 100%)
 * @param a alpha component, from 0.0 to 1.0 (for 0 to 100%)
 *
 * @related noFill, fill
 * @relatedalso stroke, noStroke
 *
 * @since 1.0
 * */
void fillAlpha ( const float r, const float g, const float b, const float a );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Disables the filling of subsequent drawing calls (such as `rect`, `disk`, etc).
 * Then no filling will occur, leaving the *inside* of a shape clear / transparent.
 *
 * @related fill
 * @relatedalso stroke, noStroke
 *
 * @since 1.0
 * */
void noFill ( );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Sets the outlining (stroke) color for the subsequent drawing calls (such as `rect`, `disk`, etc).
 *
 * @param r Red component, from 0.0 to 1.0 (for 0 to 100%)
 * @param g Green component, from 0.0 to 1.0 (for 0 to 100%)
 * @param b Blue component, from 0.0 to 1.0 (for 0 to 100%)
 *
 * @related noStroke, strokeAlpha
 * @relatedalso fill, noFill
 *
 * @since 1.0
 * */
void stroke ( const float r, const float g, const float b );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Sets the outlining (stroke) color for the subsequent drawing calls (such as `rect`, `disk`, etc).
 *
 * @param r Red component, from 0.0 to 1.0 (for 0 to 100%)
 * @param g Green component, from 0.0 to 1.0 (for 0 to 100%)
 * @param b Blue component, from 0.0 to 1.0 (for 0 to 100%)
 * @param a alpha component, from 0.0 to 1.0 (for 0 to 100%)
 *
 * @related noStroke, stroke
 * @relatedalso fill, noFill
 *
 * @since 1.0
 * */
void strokeAlpha ( const float r, const float g, const float b, const float a );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Disables the outlining (stroke) of subsequent drawing calls (such as `rect`, `disk`, etc).
 *
 * @related stroke, strokeWidth
 * @relatedalso fill, noFill
 * */
void noStroke ( );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Sets the width of the stroke when outlining subsequent drawing calls (such as `rect`, `disk`, etc).
 *
 * @param width Width in pixels. Must be positive. Setting it to 0 is equivalent to calling `noStroke`.
 *
 * @related stroke, noStroke
 * @relatedalso fill, noFill
 *
 * @since 1.0
 * */
void strokeWidth ( const float width );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Draws a rectangle shape with the current drawing style (filling and outlining).
 *
 * @param topLeftX x-coordinate in pixels of the top-left corner of the rectangle.
 * @param topLeftY y-coordinate in pixels of the top-left corner of the rectangle.
 * @param width Width of the rectangle.
 * @param height Height of the rectangle.
 *
 * @related fill, stroke, disc, line, triangle
 *
 * @since 1.0
 * */
void rect ( const int topLeftX, const int topLeftY, const int width, int const height );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Draws a line segment with the current outlining drawing style.
 *
 * @param x0 x-coordinate in pixels of the starting point
 * @param y0 y-coordinate in pixels of the starting point
 * @param x1 x-coordinate in pixels of the ending point
 * @param y1 y-coordinate in pixels of the ending point
 *
 * @related disc, line, point, stroke, strokeWidth, triangle
 * */
void line ( const int x0, const int y0, const int x1, const int y1 );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Draws a single 1x1 pixel point with the current outlining or filling color.
 * If you intend to draw many points, consider using `getPixels` and `setPixels` instead.
 *
 * @param x0 x-coordinate in pixels of the point
 * @param y0 y-coordinate in pixels of the point
 *
 * @related getPixels, setPixels
 * @relatedalso stroke, fill
 *
 * @since 1.0
 * */
void point ( const int x0, const int y0 );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Draws a disc (circle) shape with the current drawing style (filling and outlining).
 *
 * @param x x-coordinate in pixels of the center of the disc.
 * @param y y-coordinate in pixels of the center of the disc.
 * @param radius Radius of the disk.
 *
 * @related rect, line, point, triangle
 * @relatedalso fill, stroke, noFill, noStroke
 *
 * @since 1.0
 * */
void disc ( const int x, const int y, const int radius );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Draws a triangular shape with the current drawing style (filling and outlining).
 *
 * @param x0 x-coordinate in pixels of the first vertex
 * @param y0 y-coordinate in pixels of the first vertex
 * @param x1 x-coordinate in pixels of the second vertex
 * @param y1 y-coordinate in pixels of the second vertex
 * @param x2 x-coordinate in pixels of the third vertex
 * @param y2 y-coordinate in pixels of the third vertex
 *
 * @related rect, line, point, disc
 * @relatedalso fill, stroke, noFill, noStroke
 *
 * @since 1.0
 * */
void triangle ( const int x0, const int y0, const int x1, const int y1, const int x2, const int y2 );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Fetches the current x-coordinate of the cursor (or at worst the last known location within the Window).
 *
 * @returns The current x-coordinate of the cursor (or at worst the last known location within the Window).
 *
 * @since 1.0
 * */
int getMouseX ( );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Fetches the current y-coordinate of the cursor (or at worst the last known location within the Window).
 *
 * @returns The current y-coordinate of the cursor (or at worst the last known location within the Window).
 *
 * @since 1.0
 * */
int getMouseY ( );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Fetches the current pressed status of the mouse button (or at worst the last known status within the Window).
 *
 * @returns 1 (true) if the mouse button is pressed, 0 (false) otherwise.
 *
 * @since 1.0
 * */
_Bool isMousePressed ( );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Fetches the width of the drawable area within the Window.
 *
 * @returns The width of the drawable area within the Window.
 *
 * @since 1.0
 * */
int getWidth ( );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Fetches the height of the drawable area within the Window.
 *
 * @returns The height of the drawable area within the Window.
 *
 * @since 1.0
 * */
int getHeight ( );


/*--------------------------------------------------------------------------------------------------------------------*/
/** The number of milliseconds ellapsed (wallclock) since the program started.
 *
 * @returns The number of milliseconds ellapsed (wallclock) since the program started.
 *
 * @since 1.0
 * */
long millis ( );


/*--------------------------------------------------------------------------------------------------------------------*/
/** A randomly generated number between 0.0 and 1.0. Note: 1.0 is excluded, interval is [0.0, 1.0)
 *
 * @returns A randomly number within the interval [0.0, 1.0)
 *
 * @since 1.0
 * */
float randomUniform ( );

/*--------------------------------------------------------------------------------------------------------------------*/
/** Tests whether a key is currently being pressed down.
 *
 * @returns `true` or `false`, whether a key is curently being pressed.
 *
 * @since 1.1
 * */
_Bool isKeyPressed ( );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Fetches Unicode character for the key being pressed.
 *
 * @returns The Unicode character for the key being pressed.
 *
 * @since 1.0
 * */
unsigned long getKeyPressed ( );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Specifies which user-provided function to call npon a mouse move event. To set no handler (default), set the
 * handler to `NULL`. This function should be called within the setup function and not within the draw function.
 *
 * @param callback Pointer to the function to call upon a mouve mouve event.
 *
 * @related setMouseClickHandler
 * @relatedalso getMouseX, getMouseY
 *
 * @since 1.0
 * */
void setMouseMoveHandler ( const CallbackNoArgs callback );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Specifies which user-provided function to call upon a mouse click event (on mouse button release).
 * To set no handler (default), set the  handler to `NULL`. This function should be called within the setup function
 * and not within the draw function.
 *
 * @param callback Pointer to the function to call upon a mouve click event.
 *
 * @related setMouseMoveHandler
 * @relatedalso getMouseX, getMouseY
 *
 * @since 1.0
 * */
void setMouseClickHandler ( const CallbackNoArgs callback );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Specifies which user-provided function to call upon a key release event.
 * To set no handler (default), set the  handler to `NULL`. This function should be called within the setup function
 * and not within the draw function.
 *
 * @param callback Pointer to the function to call upon event.
 *
 * @related setKeyDownHandler
 * @relatedalso getKeyPressed
 *
 * @since 1.0
 * */
void setKeyUpHandler ( const CallbackNoArgs callback );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Specifies which user-provided function to call upon a key press event.
 * To set no handler (default), set the  handler to `NULL`. This function should be called within the setup function
 * and not within the draw function.
 *
 * @param callback Pointer to the function to call upon event.
 *
 * @related setKeyUpHandler
 * @relatedalso getKeyPressed
 *
 * @since 1.0
 * */
void setKeyDownHandler ( const CallbackNoArgs callback );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Changes the drawing function handler. This can be useful to change the scene to draw while the program
 * is running. You cannot set this to `NULL` (the call would be ignored).
 *
 * @param callback Pointer to the function to call upon event. Must not be NULL.
 *
 * @related startGraphicsLoop, startGraphicsLoopWithSetup
 *
 * @since 1.0
 * */
void setDrawHandler ( const CallbackNoArgs callback );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Cancels any registered handler for the key and mouse events.
 *
 * @related setKeyDownHandler, setKeyUpHandler, setMouseMoveHandler, setMouseClickHandler
 *
 * @since 1.0
 * */
void clearAllHandlers ( );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Pushes a new working-copy on affine transform matrix stack. The stacks eases the process of reversing
 * transforms while maitaining a context.
 *
 * @related popMatrix
 * @relatedalso rotate, translate, scale
 *
 * @since 1.1
 * */
void pushMatrix ( );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Pop from the stack the current affine transform matrix and restores the previous one. When popping the original
 * matrix, it is replaced with an identity matrix, de facto clearing any transform.
 * The stacks eases the process of reversing transforms while maitaining a context.
 *
 * @related pushMatrix
 * @relatedalso rotate, translate, scale
 *
 * @since 1.1
 * */
void popMatrix ( );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Rotates the coordinate system used for drawing in reference to the Window's drawable area.
 * Consider `pushMatrix` and `popMatrix` when chaining transforms.
 *
 * @param radians The angle amount by which to rotate, in radians.
 *
 * @related translate, scale
 * @relatedalso popMatrix, pushMatrix
 *
 * @since 1.1
 * */
void rotate ( const double radians );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Translates the coordinate system used for drawing in reference to the Window's drawable area.
 * Consider `pushMatrix` and `popMatrix` when chaining transforms.
 *
 * @param dx The x-coordinate shift to apply
 * @param dy The y-coordinate shift to apply
 *
 * @related rotate, scale
 * @relatedalso popMatrix, pushMatrix
 *
 * @since 1.1
 * */
void translate ( const double dx, const double dy );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Scales the coordinate system used for drawing in reference to the Window's drawable area.
 * Consider `pushMatrix` and `popMatrix` when chaining transforms.
 *
 * @related rotate, translate
 * @relatedalso popMatrix, pushMatrix
 *
 * @since 1.1
 * */
void scale ( const double x, const double y );


/*--------------------------------------------------------------------------------------------------------------------*/
/** The `PixelColor` type is used to describe a color using RGB components with values belonging to the [0.0, 1.0]
 * interval.
 *
 * @since 1.1
 * */
typedef struct {
	float red;   //  0.0 to 1.0
	float green; //  0.0 to 1.0
	float blue;  //  0.0 to 1.0
} PixelColor_t;


/*--------------------------------------------------------------------------------------------------------------------*/
/** Generates a 1D array of the pixels as currently displayed by the Window. If parameters are non-NULL then the
 * width and height are returned. Use `x + y * width` as index.
 *
 * @warning This function allocates memory. You MUST call freePixels on the resulting array.
 *
 * @related setPixels, freePixels, getImagePixels
 * @relatedalso getPixels_2D, setPixels_2D, freePixels_2D, getImagePixels_2D
 *
 * @since 1.1
 * */
PixelColor_t* getPixels ( int* width, int* height );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Replaces the drawing with the provided pixels.
 *
 * @warning The provided array must have a `width * height` length matching the Window size.
 * @warning This assumes indices of the form `x + y * width`.
 *
 * @related getPixels, freePixels, getImagePixels
 * @relatedalso getPixels_2D, setPixels_2D, freePixels_2D, getImagePixels_2D
 *
 * @since 1.1
 * */
void setPixels ( const PixelColor_t* pixels );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Frees the memory allocated by the `getPixels` function.
 *
 * @warning This will not set your variable value to NULL (not fool-proof)
 *
 * @related getPixels, setPixels, getImagePixels
 * @relatedalso getPixels_2D, setPixels_2D, freePixels_2D, getImagePixels_2D
 *
 * @since 1.1
 * */
void freePixels ( PixelColor_t* pixels );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Generates a 2D array of the pixels as currently displayed by the Window. If parameters are non-NULL then the
 * width and height are returned. Use `[x][y]` as index.
 *
 * @warning This function allocates memory. You MUST call freePixels on the resulting array.
 *
 * @related setPixels_2D, freePixels_2D, getImagePixels_2D
 * @relatedalso getPixels, setPixels, freePixels, getImagePixels
 *
 * @since 1.1
 * */
PixelColor_t** getPixels_2D ( int* width, int* height );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Replaces the drawing with the provided pixels.
 *
 * @warning The provided 2D array must have a width and a height matching the Window size.
 * @warning This assumes indices [x][y]
 *
 * @related getPixels_2D, freePixels_2D, getImagePixels_2D
 * @relatedalso getPixels, setPixels, freePixels, getImagePixels
 *
 * @since 1.1
 * */
void setPixels_2D ( const PixelColor_t** pixels );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Frees the memory allocated by the `getPixels_2D` function.
 *
 * @warning This will not set your variable value to NULL (not fool-proof)
 *
 * @related setPixels_2D, setPixels_2D, getImagePixels_2D
 * @relatedalso getPixels, setPixels, freePixels, getImagePixels
 *
 * @since 1.1
 * */
void freePixels_2D ( PixelColor_t** pixels );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Opaque type used to represent images. */
struct ImageOpaque_t;

/** Opaque type used to represent images. */
typedef struct ImageOpaque_t Image_t;


/*--------------------------------------------------------------------------------------------------------------------*/
/** Opens an image file (PNG only) and provides an (opaque) internal representation of the image for drawing.
 *
 * @param path The path to the image file.
 *
 * @warning The image must be removed from memory after use ; `freeImage` must be called.
 *
 * @related freeImage
 * @related paintImage, paintImageWithSize, getImageWidth, getImageHeight
 * @relatedalso getImagePixels, getImagePixels_2D, freeImagePixels, freeImagePixels_2D
 *
 * @since 1.1
 * */
Image_t* loadImage ( const char* path );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Paints an image at the provided location.
 *
 * @param image The image to draw.
 * @param x     The x-coordinate of the top-left corner where to draw the image.
 * @param y     The y-coordinate of the top-left corner where to draw the image.
 *
 * @related paintImageWithSize
 * @related loadImage, getImageWidth, getImageHeight, freeImage
 * @relatedalso getImagePixels, getImagePixels_2D, freeImagePixels, freeImagePixels_2D
 *
 * @since 1.1
 * */
void paintImage ( const Image_t* image, const int x, const int y );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Paints an image at the provided location with a specific size.
 *
 * @param image  The image to draw.
 * @param x      The x-coordinate of the top-left corner where to draw the image.
 * @param y      The y-coordinate of the top-left corner where to draw the image.
 * @param width  The width which to stretch the image when drawing. If 0, will be proportionnal to height.
 * @param height The height which to stretch the image when drawing. If 0, will be proportionnal to width.
 *
 * @note If both width and height are 0, then the image isn't scaled.
 *
 * @related paintImage
 * @related loadImage, getImageWidth, getImageHeight, freeImage
 * @relatedalso getImagePixels, getImagePixels_2D, freeImagePixels, freeImagePixels_2D
 *
 * @since 1.1
 * */
void paintImageWithSize ( const Image_t* image, const int x, const int y, const int width, const int height );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Fetch the width of an image in pixels.
 *
 * @param image  The image.
 *
 * @returns The width of the image.
 *
 * @related getImageHeight
 * @related loadImage, getImageWidth, paintImage, freeImage
 * @relatedalso getImagePixels, getImagePixels_2D, freeImagePixels, freeImagePixels_2D
 *
 * @since 1.1
 * */
int getImageWidth ( const Image_t* image );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Fetch the height of an image in pixels.
 *
 * @param image  The image.
 *
 * @returns The height of the image.
 *
 * @related getImageWidth
 * @related loadImage, getImageWidth, paintImage, paintImageWithSize, freeImage
 * @relatedalso getImagePixels, getImagePixels_2D, freeImagePixels, freeImagePixels_2D
 *
 * @since 1.1
 * */
int getImageHeight ( const Image_t* image );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Fetches the individual pixels of the image as a 1D array of PixelColor. Indices are of the form `x + y * width`.
 *
 * @param image  The image.
 *
 * @returns A dynamically allocated 1D array of pixel colors making up the image.
 *
 * @warning You must free the memory by calling `freeImagePixels`
 *
 * @related getPixels, freeImagePixels
 * @related loadImage, getImageWidth, getImageHeight, paintImage, paintImageWithSize, freeImage
 * @relatedalso getImagePixels, getImagePixels_2D, freeImagePixels, freeImagePixels_2D
 *
 * @since 1.1
 * */
PixelColor_t* getImagePixels ( const Image_t* image );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Frees the memory allocated for the pixels fetched using `getImagePixels`.
 *
 * @param pixels  The pixel array to be freed from memory.
 *
 * @related getImagePixels
 * @related loadImage, getImageWidth, getImageHeight, paintImage, paintImageWithSize, freeImage
 * @relatedalso getImagePixels, getImagePixels_2D, freeImagePixels, freeImagePixels_2D
 *
 * @since 1.1
 * */
void freeImagePixels ( PixelColor_t* pixels );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Frees the memory allocated for an image.
 *
 * @param image  The image to be freed from memory.
 *
 * @related loadImage
 *
 * @since 1.1
 * */
void freeImage ( Image_t *image );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Makes the mouse cursor invisible.
 *
 * @related showCursor
 *
 * @since 1.1
 * */
void hideCursor ( );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Makes the mouse cursor visible.
 *
 * @related hideCursor
 *
 * @since 1.1
 * */
void showCursor ( );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Sets the framerate.
 *
 * @warning Must be called before setup.
 *
 * @param rate the desired framerate. Caution should at most 30 for most computers.
 *
 * @since 1.1
 * */
void setFrameRate ( int rate );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Gets the framerate. By default it is 30.
 *
 * @since 1.1
 * */
int getFrameRate ( );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Draws text at the given location. The coloring is set through `fill`.
 *
 * @param x the x-axis coordinate in window pixel space
 * @param y the y-axis coordinate in window pixel space
 * @param text the text to draw
 *
 * @since 1.2
 * @sa fill, fontSize, textBounds
 * */
void drawText ( const int x, const int y, const char* restrict text );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Sets the font size.
 *
 * @param newSize The new font size. If 0 or negative, then the default value is used (30).
 *
 * @since 1.2
 * @sa drawText
 * */
void fontSize ( const float newSize );


/*--------------------------------------------------------------------------------------------------------------------*/
/** Retrieves the text boundaries
 *
 * @param text the text to be measured
 * @param textBoxWidth if not null, this will receive the required width to draw the text
 * @param textBoxHeight if not null, this will receive the required height to draw the text
 *
 * @since 1.2
 * @sa fill, fontSize
 * */
void textBounds ( const char* restrict text, float* textBoxWidth, float* textBoxHeight );



#endif //GFXHELLOWORLD_GRAPHICS_H
