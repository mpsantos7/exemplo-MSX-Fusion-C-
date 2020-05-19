/*
Curva Cardioide
usando tabela de senos e cossenos

Table[Round[1000*Sin[i]], {i, 0, 2*Pi, 0.05}]
Tempo de execucao 0.38s
*/

#include "fusion-c/header/msx_fusion.h"
//#include "fusion-c/header/vdp_sprites.h"
#include "fusion-c/header/vdp_graph2.h"
#include <stdio.h>
//#include <math.h>

int sen_table[126] =
{0, 5, 10, 15, 20, 25, 30, 34, 39, 43, 48, 52, 56, 61, 64, 68, 72, 
75, 78, 81, 84, 87, 89, 91, 93, 95, 96, 98, 99, 99, 100, 100, 100, 
100, 99, 98, 97, 96, 95, 93, 91, 89, 86, 84, 81, 78, 75, 71, 68, 64, 
60, 56, 52, 47, 43, 38, 33, 29, 24, 19, 14, 9, 4, -1, -6, -11, -16, 
-21, -26, -30, -35, -40, -44, -49, -53, -57, -61, -65, -69, -72, -76, 
-79, -82, -85, -87, -89, -92, -94, -95, -97, -98, -99, -99, -100, 
-100, -100, -100, -99, -98, -97, -96, -94, -93, -91, -88, -86, -83, 
-80, -77, -74, -71, -67, -63, -59, -55, -51, -46, -42, -37, -33, -28, 
-23, -18, -13, -8, -3};

 int cos_table[126] =
{100, 100, 100, 99, 98, 97, 96, 94, 92, 90, 88, 85, 83, 80, 76, 73, 
70, 66, 62, 58, 54, 50, 45, 41, 36, 32, 27, 22, 17, 12, 7, 2, -3, -8, 
-13, -18, -23, -28, -32, -37, -42, -46, -50, -55, -59, -63, -67, -70, 
-74, -77, -80, -83, -86, -88, -90, -92, -94, -96, -97, -98, -99, 
-100, -100, -100, -100, -99, -99, -98, -97, -95, -94, -92, -90, -87, 
-85, -82, -79, -76, -73, -69, -65, -62, -57, -53, -49, -45, -40, -35, 
-31, -26, -21, -16, -11, -6, -1, 4, 9, 14, 19, 24, 28, 33, 38, 42, 
47, 51, 55, 60, 63, 67, 71, 74, 78, 81, 83, 86, 89, 91, 93, 95, 96, 
97, 98, 99, 100, 100};

int raiz_quad_abs_cos[126] =
{100, 100, 100, 99, 99, 98, 98, 97, 96, 95, 94, 92, 91, 89, 87, 86, 
83, 81, 79, 76, 74, 71, 67, 64, 60, 56, 52, 47, 41, 35, 27, 14, 17, 
28, 36, 42, 48, 52, 57, 61, 65, 68, 71, 74, 77, 79, 82, 84, 86, 88, 
90, 91, 93, 94, 95, 96, 97, 98, 99, 99, 99, 100, 100, 100, 100, 100, 
99, 99, 98, 98, 97, 96, 95, 93, 92, 91, 89, 87, 85, 83, 81, 78, 76, 
73, 70, 67, 63, 60, 55, 51, 46, 40, 33, 25, 11, 19, 30, 37, 43, 49, 
53, 58, 61, 65, 68, 72, 74, 77, 80, 82, 84, 86, 88, 90, 91, 93, 94, 
95, 96, 97, 98, 99, 99, 100, 100, 100};




unsigned int Raio_fun_theta(int valor_sen,int abs_sqcos) {
	int Raio = 32;
	int RaioTheta;
	RaioTheta = Raio*(valor_sen * abs_sqcos / (valor_sen + 140) -2* valor_sen +200 )/100;
	return RaioTheta;
}

void main(void){
	char i,x,y,Cor,CentroX,CentroY;
    int Raio,tempo_ini, tempo_fim, delta_t;
	int SinValor,CosValor;
    VDP60Hz();
	CentroX = 127, CentroY = 70; Cor = 6;
	Screen(5);
    KeySound(0);
    tempo_ini = RealTimer();
SetColors(Cor, 0, 0);
for (i = 0;i < 126;i++) {
    SinValor = sen_table[i];
    CosValor = cos_table[i];
    Raio = Raio_fun_theta(SinValor,raiz_quad_abs_cos[i] );
    x = (char)((Raio * CosValor)/100 + CentroX);
    y = (char)(CentroY - (Raio * SinValor)/100);
    Pset(x, y, Cor, 0);
	//Line(x, y, xn, yn, Cor, 0);
    //if (Inkey() == 27)
    //	break; // Emergencia
}

tempo_fim = RealTimer();
while (Inkey() != 27) {}
// Ending program, and return to DOS
Screen(0);
SetColors(15, 0, 0);
KeySound(1);
delta_t = tempo_fim - tempo_ini;
//printf("tempo exec.= %d.%d s",(delta_t)/60,100*(delta_t%60)/60);
Print("tempo exec. = ");
PrintNumber((delta_t) / 60);
Print(",");
PrintNumber(100 * (delta_t % 60) / 60);
Exit(0);

}
