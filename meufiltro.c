#include "meufiltro.h"

void inicializarWidgetsMeuFiltro() {
	//widgets das opcoes de filtro
	widgetControleNivel = 	gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 30, 1);
	comprimento = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,0, 30, 1);
	espessura = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,0, 30, 1);
	aleatoria = gtk_radio_button_new_with_label(NULL,"Pinseladas aleatorias");
	retilinea = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(aleatoria),"Pinseladas aleatorias");
	densidade = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,0, 10, 1);
	widgetMisturarCanais = gtk_check_button_new_with_label("Misturar canais");
	g_signal_connect(G_OBJECT(widgetControleNivel), "value-changed", G_CALLBACK(funcaoAplicar), NULL);
}
void adicionarWidgetsMeuFiltro(GtkWidget *container) {

	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	GtkWidget *radioBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);
	gtk_container_add(GTK_CONTAINER(container), vbox);
	gtk_container_add(GTK_CONTAINER(vbox), widgetControleNivel);
	gtk_container_add(GTK_CONTAINER(vbox), widgetMisturarCanais);
	gtk_container_add(GTK_CONTAINER(vbox), comprimento);
	gtk_container_add(GTK_CONTAINER(vbox), espessura);
	gtk_container_add(GTK_CONTAINER(vbox), densidade);
	gtk_container_add(GTK_CONTAINER(radioBox), aleatoria);
	gtk_container_add(GTK_CONTAINER(radioBox), retilinea);
	gtk_container_add(GTK_CONTAINER(vbox),radioBox);

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
	int cont=0;
	for(int i =1; i<original.h-1; i++){
		for (int j =1; j<original.w-1;j++){
			//if (bordah(original, i-1, j-1)>0 || bordav(original, i-1, j-1) >0){
				resultado =	pintar(original,i,j,1);
			//}

		}
	}
	return resultado;
}
int bordah(Imagem original, int i, int j){
	int resultd = 0;
	for(int l =i; l < i+3; l++){
		for(int k =j; k < j+3; k++){
			if(l ==i){
			resultd += original.m[l][k][0]*(-1);
			}
			else if(l == i+1){
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

Imagem pintar(Imagem original,int i, int j, int borda){
	int comp, espe, ale, ret, dens, constI =i, constJ =j, aux=0;
	comp = (int) gtk_range_get_value(GTK_RANGE(comprimento));
	espe = (int) gtk_range_get_value(GTK_RANGE(espessura));
	dens = (int) gtk_range_get_value(GTK_RANGE(densidade));
	Imagem resultado = original;
	for (i; comp-i < constI ; i--){
		if(i >= 0){
			for(j; espe - j < constJ; j--){
				if(j >= 0){
					resultado.m[i][j][0] = original.m[constI][constJ][0];
					resultado.m[i][j][1] = original.m[constI][constJ][1];
					resultado.m[i][j][2] = original.m[constI][constJ][2];
				}
			}
		}
	}

		
	}
	return resultado;
}