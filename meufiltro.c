#include "meufiltro.h"

void inicializarWidgetsMeuFiltro() {
	//widgets das opcoes de filtro
	WidComprimento = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,1, 5, 1);
	label_comp = gtk_label_new("Comprimento das pinceladas");
	label_espe = gtk_label_new("Espessura das pinceladas");
	WidEspessura = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,1, 20, 1);
}
void adicionarWidgetsMeuFiltro(GtkWidget *container) {

	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);
	gtk_container_add(GTK_CONTAINER(container), vbox);
	gtk_container_add(GTK_CONTAINER(vbox),label_comp);
	gtk_container_add(GTK_CONTAINER(vbox), WidComprimento);
	gtk_container_add(GTK_CONTAINER(vbox),label_espe);
	gtk_container_add(GTK_CONTAINER(vbox), WidEspessura);
}

Imagem filtroPintura (Imagem original){
	Imagem resultado = alocarImagem(original);
	int raio= (int) gtk_range_get_value(GTK_RANGE(WidComprimento));
	float intens = (float) gtk_range_get_value(GTK_RANGE(WidEspessura));
	for(int y =raio; y<original.w-raio; y++){
		for (int x = raio; x < original.h-raio; x++){
			int *contIntensidade;
			contIntensidade = calloc(256,sizeof(int));
			int *sumR, *sumG, *sumB;
			sumR = calloc(256,sizeof(int));
			sumG = calloc(256,sizeof(int));
			sumB = calloc(256,sizeof(int));
			for (int y_0 =-raio; y_0<=raio;y_0++ ){
				for (int x_0 =-raio; x_0<=raio;x_0++ ){
					if(x+x_0<original.h && y+y_0<original.w && x+x_0>=0 && y+y_0>=0){
						int r = original.m[x+x_0][y+y_0][0];
						int g = original.m[x+x_0][y+y_0][1];
						int b = original.m[x+x_0][y+y_0][2];
						int curIntensity = (int) (((r+g+b)/3) *intens)/255;
						if(curIntensity >255) curIntensity =255;
						int i = curIntensity;
						contIntensidade[i]++;
						sumR[i] += r;
						sumG[i] += g;
						sumB[i] += b;
					}
				}
			}
			int curMax = 0;
            int maxIndex = 0;
			for( int i = 0; i < 256; i++ ){
				if(contIntensidade[i]>curMax){
					curMax = contIntensidade[i];
					maxIndex = i;
				}
			}
			if(x < original.h && y < original.w){
				resultado.m[x][y][0] =  sumR[maxIndex]/curMax;
				resultado.m[x][y][1] =  sumG[maxIndex]/curMax;
				resultado.m[x][y][2] =  sumB[maxIndex]/curMax;
			}
			free(sumR);
			free(sumG);
			free(sumB);
			free(contIntensidade);
		}
	}
	for(int x=0; x<resultado.h; x++){
		for(int y=0; y<raio;y++){
			resultado.m[x][y][0] = 104;
			resultado.m[x][y][1] = 83;
			resultado.m[x][y][2] = 21;
		}
	}
	for(int x=0; x<raio; x++){
		for(int y=0; y<resultado.w;y++){
			resultado.m[x][y][0] = 104;
			resultado.m[x][y][1] = 83;
			resultado.m[x][y][2] = 21;
		}
	}
	for(int x=resultado.h-raio; x<resultado.h; x++){
		for(int y=0; y<resultado.w;y++){
			resultado.m[x][y][0] = 104;
			resultado.m[x][y][1] = 83;
			resultado.m[x][y][2] = 21;
		}
	}
	for(int x=0; x<resultado.h; x++){
		for(int y=resultado.w-raio; y<resultado.w;y++){
			resultado.m[x][y][0] = 104;
			resultado.m[x][y][1] = 83;
			resultado.m[x][y][2] = 21;
		}
	}
	return resultado;
}
