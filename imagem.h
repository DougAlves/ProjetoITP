#ifndef IMAGEM_H
#define IMAGEM_H

#include <gtk/gtk.h>
#include <glib.h>
#include <stdlib.h>

typedef struct Imagem {
	unsigned char ***m;
	int w;
	int h;
	int numCanais;
} Imagem;

Imagem original, resultado;
Imagem alocarImagem(Imagem referencia);
void desalocarImagem(Imagem referencia);
int derivada(unsigned char **numeros);
Imagem pintar(Imagem original,int i, int j, int borda);

#endif


