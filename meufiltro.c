#include "meufiltro.h"

void inicializarWidgetsMeuFiltro() {
	//widgets das opcoes de filtro
	comprimento = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,0, 20, 1);
	label_comp = gtk_label_new("Comprimento das pinceladas");
	label_espe = gtk_label_new("Espessura das pinceladas");
	espessura = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,0, 20, 1);
}
void adicionarWidgetsMeuFiltro(GtkWidget *container) {

	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);
	gtk_container_add(GTK_CONTAINER(container), vbox);
	gtk_container_add(GTK_CONTAINER(vbox),label_comp);
	gtk_container_add(GTK_CONTAINER(vbox), comprimento);
	gtk_container_add(GTK_CONTAINER(vbox),label_espe);
	gtk_container_add(GTK_CONTAINER(vbox), espessura);

}

Imagem meuFiltro(Imagem origem) {
	int i, j;
	Imagem destino = alocarImagem(origem);
	int nivel = (int) gtk_range_get_value(GTK_RANGE(widgetControleNivel));
	int ch1, ch2, ch3;

	ch1 = 0;
	ch2 = 1;
	ch3 = 2;
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widgetMisturarCanais))) {
		ch1 = rand()%3;
		ch2 = (ch1+1+rand()%2)%3;
		ch3 = 3 - ch2 - ch1;
	}

	for(j = 0; j < destino.w; j++) {
		for(i = 0; i < destino.h; i++) {
			int x = j - nivel + rand()%(2*nivel+1);
			int y = i - nivel + rand()%(2*nivel+1);
			if(x < 0)
				x = 0;
			if(y < 0)
				y = 0;
			if(x >= destino.w)
				x = destino.w - 1;
			if(y >= destino.h)
				y = destino.h - 1;
			destino.m[i][j][0] = origem.m[y][x][ch1];
			destino.m[i][j][1] = origem.m[y][x][ch2];
			destino.m[i][j][2] = origem.m[y][x][ch3];
		}
	}
	return destino;
}
Imagem filtroPintura (Imagem original){
	Imagem resultado = alocarImagem(original);
	int comp= (int) gtk_range_get_value(GTK_RANGE(comprimento)), espe = (int) gtk_range_get_value(GTK_RANGE(espessura));
	int bordaH = 0, bordaV = 0;
	if(comp == 0 || espe == 0){
		return original;
	}
	for(int i =1; i<original.h-1; i++){
		for (int j = 1; j < original.w-1; j++){
			bordaH= bordah(original, i-1, j-1);
			bordaV = bordav(original, i-1, j-1);
			if (bordaH>1 || bordaV >1 || bordaH<-1 ||bordaV<-1){
				resultado =	pintar(original,i,j,resultado);
			}
		}
	}
	return resultado;
}
 int bordah(Imagem original, int i, int j){
 	int resultd = 0;
 	for(int l =i; l < i+3; l++){
 		for(int k =j; k < j+3; k++){
 			if(l ==i){
 				resultd += (original.m[l][k][0] + original.m[l][k][1] +original.m[l][k][2] )/(-3);
 			}
 			else if(l == i+1){
 				resultd += original.m[l][k][0]*0;
 			}
 			else{
 				resultd += (original.m[l][k][0] + original.m[l][k][1]+ original.m[l][k][2])/3;
 			}
 		}
 	}
 	resultd = resultd/9;
 	return resultd;
 }
 int bordav(Imagem original, int i, int j){
 	int resultd = 0;
 	for(int l =i; l < i+3; l++){
 		for(int k =j; k < j+3; k++){
 			if(k ==j){
 			resultd += original.m[l][k][0]*(-1);
 			}
 			else if(k == j+1){
 				resultd += original.m[l][k][0]*0;
 			}
 			else{
 				resultd += original.m[l][k][0]*1;
 
 			}
 		}	
 	}
 	resultd = resultd/9;
 	return resultd;
 }
Imagem pintar(Imagem original,int i, int j, Imagem resultado){
	int comp, espe, ale, ret, dens;
	comp = (int) gtk_range_get_value(GTK_RANGE(comprimento));
	espe = (int) gtk_range_get_value(GTK_RANGE(espessura));
	int x = i - comp, y = j - espe;
	for (; x < i ; x++){
		if(x >= 0){
			for(; y < j; y++){
				if(y >= 0){
					resultado.m[x][y][0] = original.m[i][j][0];
					resultado.m[x][y][1] = original.m[i][j][1];
					resultado.m[x][y][2] = original.m[i][j][2];
				}
			}
		}
	}
	return resultado;
}