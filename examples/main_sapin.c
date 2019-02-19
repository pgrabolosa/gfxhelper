#include <GfxHelper.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
// Partie C

typedef struct {
	float rouge;
	float vert;
	float bleu;
} couleur;

typedef struct boule_s {
	couleur couleur;
	struct boule_s* gauche;
	struct boule_s* droite;
} boule;


////////////////////////////////////////////////////////////////////////////////
// Partie C - Exercice 1

int max(int a, int b) {
	if (a < b) return b;
	return a;
}

int calculProfondeur(boule* element) {
	if (element == NULL) {
		return 0;
	} else {
		return 1 + max(calculProfondeur(element->gauche), calculProfondeur(element->droite));
	}
}

////////////////////////////////////////////////////////////////////////////////
// Partie C - Exercice2

void calculCouleur(boule* element) {
	if (element == NULL) {
		return;
	}
	
	// mettre a jour les enfants
	calculCouleur(element->gauche);
	calculCouleur(element->droite);
	
	// determiner sa couleur a partir de celle des enfants
	if (element->gauche == NULL && element->droite == NULL) {
		// ne rien faire
	} else if (element->gauche == NULL && element->droite != NULL) {
		element->couleur = element->droite->couleur;
	} else if (element->gauche != NULL && element->droite == NULL) {
		element->couleur = element->gauche->couleur;
	} else {
		element->couleur.rouge = fmin(element->gauche->couleur.rouge + element->droite->couleur.rouge, 1.0);
		element->couleur.vert = fmin(element->gauche->couleur.vert + element->droite->couleur.vert, 1.0);
		element->couleur.bleu = fmin(element->gauche->couleur.bleu + element->droite->couleur.bleu, 1.0);
	}
}


////////////////////////////////////////////////////////////////////////////////
// Partie C - Exercice3 et 4

void freeBoule(boule* r) {
	if (r == NULL) return;
	
	freeBoule(r->gauche);
	freeBoule(r->droite);
	
	free(r);
}

boule* newBoule() {
	return calloc(1, sizeof(boule));
}

boule* newColoredBoule(float r, float g, float b) {
	boule* new = newBoule();
	
	new->couleur.rouge = r;
	new->couleur.vert = g;
	new->couleur.bleu = b;
	
	return new;
}

boule* newBouleWithChildren(boule* left, boule* right) {
	boule* new = newBoule();
	
	new->gauche = left;
	new->droite = right;
	
	return new;
}

void fillTree(boule* item, int depth) {
	if (depth) {
		item->gauche = newBoule();
		item->droite = newBoule();
		
		fillTree(item->gauche, depth-1);
		fillTree(item->droite, depth-1);
	}
}

boule* racine;

void onKeyUp() {
	switch(getKeyPressed()) {
		case '3':
			freeBoule(racine);
			racine = newBoule();
			fillTree(racine, 2);
			break;
		case '4':
			freeBoule(racine);
			racine = newBoule();
			fillTree(racine, 3);
			break;
		default:
			// do nothing
			break;
	}
}

void onClick() {
	const int hauteur = calculProfondeur(racine);
	int rowHeight = getHeight()/hauteur;
	
	int profondeur = getMouseY() / rowHeight;
	const int largeur = (int) powl(2, profondeur);
	int childrenCellWidth = getWidth()/largeur;
	
	int which = getMouseX() / childrenCellWidth;
	
	int mask = 1 << profondeur;
	boule* item = racine;
	boule* parent = NULL;
	for(int i = 0; item != NULL && i < profondeur; i++) {
		mask = mask >> 1;
		parent = item;
		if ((which & mask) == 0) {
			item = item->gauche;
		} else {
			item = item->droite;
		}
	}
	if (item) {
		switch(getKeyPressed()) {
			case 'R': case 'r':
				item->couleur = ( couleur ) { 1, 0, 0 };
				break;
			case 'V': case 'v':
				item->couleur = ( couleur ) { 0, 1, 0 };
				break;
			case 'B': case 'b':
				item->couleur = ( couleur ) { 0, 0, 1 };
				break;
			case 'J': case 'j':
				item->couleur = ( couleur ) { 1, 1, 0 };
				break;
			case ' ':
				item->couleur = ( couleur ) { 1, 1, 1 };
				break;
			case 'S': case 's':
				if (parent && parent->gauche == item) parent->gauche = NULL;
				if (parent && parent->droite == item) parent->droite = NULL;
				if (parent == NULL) racine = NULL;
				freeBoule(item);
			default:
				// do nothing
				break;
		}
	}
}

void setup() {
	
	racine = newBouleWithChildren(
			newBouleWithChildren(newColoredBoule(1, 0, 0), newBouleWithChildren(newColoredBoule(0, 1, 0), newColoredBoule(1, 0, 0.5))),
			newBouleWithChildren(NULL, newBouleWithChildren(newColoredBoule(0, 0, 1), NULL))
	);
	
	
	setKeyUpHandler(onKeyUp);
	setMouseClickHandler(onClick);
}

void dessinerBoule(boule* item, int profondeur, int rowHeight, int offset, int parentX, int parentY) {
	if (item == NULL) {
		return;
	}
	
	int y = profondeur * rowHeight + rowHeight/2;
	int x = offset;
	
	const int largeur = (int) powl(2, profondeur+1);
	int childrenCellWidth = getWidth()/largeur;
	
	dessinerBoule(item->gauche, profondeur+1, rowHeight, offset - childrenCellWidth/2, x, y);
	dessinerBoule(item->droite, profondeur+1, rowHeight, offset + childrenCellWidth/2, x, y);
	
	if (parentX != 0 && parentY != 0) {
		stroke(0, 0, 0);
		line(x, y, parentX, parentY);
	}
	
	fill(item->couleur.rouge, item->couleur.vert, item->couleur.bleu);
	stroke(0,0,0);
	disc(x, y, 20);
}

void draw() {
	background(1, 1, 1);
	
	const int hauteur = calculProfondeur(racine);
	const int largeur = (int) powl(2, hauteur-1);
	
	calculCouleur(racine);
	if (hauteur > 0) {
		dessinerBoule( racine, 0, getHeight( ) / hauteur, getWidth( ) / 2, 0, 0 );
	}
}

int main ( int argc, char** argv ) {
	startGraphicsLoopWithSetup( 500, 500, setup, draw );
	return 0;
}

