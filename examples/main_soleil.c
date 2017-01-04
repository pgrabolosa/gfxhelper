#include <GfxHelper.h>

int hauteurDuSoleil = 400;
const int pasDuSoleil = -2;
const int hauteurFinaleDuSoleil = 80;
const int horizon = 500-200;

void setup ( ) {
}

void draw ( ) {
	if (hauteurDuSoleil > horizon) { // sous l'horizon ... nuit
		background( 0, 0, 0.2 );
	} else if (hauteurDuSoleil > (horizon - 80)) { // a l'horizon ... lever
		background( 0.2, 0.1, 0.5 );
	} else if (hauteurDuSoleil > (horizon - 140)) { // matin
		background( 0.6, 0.7, 1.0 );
	} else { // journee
		background( 0.5, 0.4, 1.0 );
	}
	
	
	noStroke( );
	
	fill( 1, 0.9, 0 );
	disc( 80, hauteurDuSoleil, 30 );
	
	fill( 0.5, 1.0, 0.5 );
	rect( 0, horizon, 500, 200 );
	
	if (hauteurDuSoleil > hauteurFinaleDuSoleil ) {
		hauteurDuSoleil += pasDuSoleil;
	}
}

int main ( int argc, char** argv ) {
	// do not change the main. It is some kind of "magic".
	startGraphicsLoopWithSetup( 500, 500, setup, draw );
	return 0;
}
