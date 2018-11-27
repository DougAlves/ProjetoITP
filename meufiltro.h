#ifndef MEUFILTRO_H
#define MEUFILTRO_H
#include <math.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <stdlib.h>
#include <time.h>
#include "imagem.h"

//declare aqui os seus widgets
GtkWidget *widgetControleNivel;
GtkWidget *widgetMisturarCanais;
GtkWidget *WidComprimento;
GtkWidget *WidEspessura;
GtkWidget *label_comp;
GtkWidget *label_espe;
GtkWidget *angulo;

Imagem filtroPintura(Imagem original);
Imagem meuFiltro(Imagem origem);

void inicializarWidgetsMeuFiltro();
void adicionarWidgetsMeuFiltro(GtkWidget *container);
int* rotacionar(Imagem original,int i,int j);
int bordah(Imagem original, int i, int j);
int bordav(Imagem original, int i, int j);
Imagem pintar(Imagem original,int i, int j, Imagem resultado);
Imagem filtroPintura (Imagem original);

//esta funcao esta implementada em filtroGtk.c, nao precisa alterar
void funcaoAplicar(GtkWidget *widget, gpointer data);
void testeWidget(GtkWidget *widget, gpointer data);
#endif


