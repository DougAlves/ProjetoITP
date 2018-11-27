#include "meufiltro.h"

void inicializarWidgetsMeuFiltro() {
	//widgets das opcoes de filtro
	WidComprimento = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,1, 20, 1);
	label_comp = gtk_label_new("Comprimento das pinceladas");
	label_espe = gtk_label_new("Espessura das pinceladas");
	WidEspessura = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,1, 20, 1);
	angulo = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,1, 6, 1);
}
void adicionarWidgetsMeuFiltro(GtkWidget *container) {

	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);
	gtk_container_add(GTK_CONTAINER(container), vbox);
	gtk_container_add(GTK_CONTAINER(vbox),label_comp);
	gtk_container_add(GTK_CONTAINER(vbox), WidComprimento);
	gtk_container_add(GTK_CONTAINER(vbox),label_espe);
	gtk_container_add(GTK_CONTAINER(vbox), WidEspessura);
	gtk_container_add(GTK_CONTAINER(vbox), angulo);
}

Imagem meuFiltro(Imagem origem) {

}
Imagem filtroPintura (Imagem original){
	Imagem resultado = alocarImagem(original);
	long *contIntensidade, *sumR, *sumG, *sumB;
	contIntensidade = calloc(256,sizeof(int));
	sumR = calloc(256,sizeof(int));
	sumG = calloc(256,sizeof(int));
	sumB = calloc(256,sizeof(int));
	int raio= (int) gtk_range_get_value(GTK_RANGE(WidComprimento));
	float intens = (float) gtk_range_get_value(GTK_RANGE(WidEspessura));
	printf("askudhf");
	for(int y =raio; y<original.h-raio; y++){
		for (int x = raio; x < original.w-raio; x++){
			for (int y_0 =-raio; y_0<=raio;y_0++ ){
				for (int x_0 =-raio; x_0<=raio;x_0++ ){
					if(x+x_0<original.w && y+y_0<original.h){
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
				printf("");
				if(contIntensidade[i]>curMax){
					curMax = contIntensidade[i];
					maxIndex = i;
				}
			}
			resultado.m[x][y][0] =  sumR[maxIndex]/curMax;
			resultado.m[x][y][1] =  sumG[maxIndex]/curMax;
			resultado.m[x][y][2] =  sumB[maxIndex]/curMax;
		}
	}
	return resultado;
}
//  int bordah(Imagem original, int i, int j){
//  	int resultd = 0;
//  	for(int l =i; l < i+3; l++){
//  		for(int k =j; k < j+3; k++){
//  			if(l ==i){
//  				resultd += (original.m[l][k][0] + original.m[l][k][1] +original.m[l][k][2] )/(-3);
//  			}
//  			else if(l == i+1){
//  				resultd += original.m[l][k][0]*0;
//  			}
//  			else{
//  				resultd += (original.m[l][k][0] + original.m[l][k][1]+ original.m[l][k][2])/3;
//  			}
//  		}
//  	}
//  	resultd = resultd/9;
//  	return resultd;
//  }
//  int bordav(Imagem original, int i, int j){
//  	int resultd = 0;
//  	for(int l =i; l < i+3; l++){
//  		for(int k =j; k < j+3; k++){
//  			if(k ==j){
// 				 if(l==i+1){
// 					resultd += original.m[l][k][0]*(-2);
// 				 }
//  			resultd += original.m[l][k][0]*(-1);
//  			}
//  			else if(k == j+1){
//  				resultd += original.m[l][k][0]*0;
//  			}
//  			else{
// 				if(l==i+1){
// 					resultd += original.m[l][k][0]*(2);
// 				}
//  				resultd += original.m[l][k][0]*1;
//  			}
//  		}
//  	}
//  	resultd = resultd/9;
//  	return resultd;
// }
// Imagem pintar(Imagem original,int i, int j, Imagem resultado){
// 	int comp, espe, ale, ret, dens;
// 	comp = (int) gtk_range_get_value(GTK_RANGE(comprimento));
// 	espe = (int) gtk_range_get_value(GTK_RANGE(espessura));
// 	int x =abs( i - comp), y = abs(j - espe);
// 	int nsei = x+i, nsei1 = y+j;
// 	//pinta matriz aux
// 	for (;i<nsei; i++){
// 		for (;j<nsei1;j++){
// 			int* result = rotacionar(original, i,j);
// 			if(result[0]<= resultado.w && result[1]<= resultado.h && result[0]>=0 && result[1]>= 0){
// 				resultado.m[result[0]][result[1]][0] = original.m[i][j][0];
// 				resultado.m[result[0]][result[1]][1] = original.m[i][j][1];
// 				resultado.m[result[0]][result[1]][2] = original.m[i][j][2];
// 			}
// 		}
// 	}
// 	return resultado;
// }
// int* rotacionar(Imagem original,int i,int j){
// 	int  *result;
// 	result = malloc(2*(sizeof(int)));
// 	int alfa = (int) gtk_range_get_value(GTK_RANGE(angulo));
// 	result[0] = (original.w-i)*cos(alfa) + (original.h-j)*sin(alfa)*(-1);
// 	result[1] = (original.w-i)*sin(alfa) + (original.h-j)*cos(alfa);
// 	return result;
// }make