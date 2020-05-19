/*
http://marmsx.msxall.com/artigos/gravidade.pdf
Versao em C da rotina em BASIC do artigo
*/

#include "fusion-c/header/msx_fusion.h"
//#include "fusion-c/header/vdp_sprites.h"
#include "fusion-c/header/vdp_graph2.h"
#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>

float sen_table[63][2] =
{
 {0., 0.},
 {1., 0.0998334},
 {2., 0.198669},
 {3., 0.29552},
 {4., 0.389418},
 {5., 0.479426},
 {6., 0.564642},
 {7., 0.644218},
 {8., 0.717356},
 {9., 0.783327},
 {10., 0.841471},
 {11., 0.891207},
 {12., 0.932039},
 {13., 0.963558},
 {14., 0.98545},
 {15., 0.997495},
 {16., 0.999574},
 {17., 0.991665},
 {18., 0.973848},
 {19., 0.9463},
 {20., 0.909297},
 {21., 0.863209},
 {22., 0.808496},
 {23., 0.745705},
 {24., 0.675463},
 {25., 0.598472},
 {26., 0.515501},
 {27., 0.42738},
 {28., 0.334988},
 {29., 0.239249},
 {30., 0.14112},
 {31., 0.0415807},
 {32., -0.0583741},
 {33., -0.157746},
 {34., -0.255541},
 {35., -0.350783},
 {36., -0.44252},
 {37., -0.529836},
 {38., -0.611858},
 {39., -0.687766},
 {40., -0.756802},
 {41., -0.818277},
 {42., -0.871576},
 {43., -0.916166},
 {44., -0.951602},
 {45., -0.97753},
 {46., -0.993691},
 {47., -0.999923},
 {48., -0.996165},
 {49., -0.982453},
 {50., -0.958924},
 {51., -0.925815},
 {52., -0.883455},
 {53., -0.832267},
 {54., -0.772764},
 {55., -0.70554},
 {56., -0.631267},
 {57., -0.550686},
 {58., -0.464602},
 {59., -0.373877},
 {60., -0.279415},
 {61., -0.182163},
 {62., -0.0830894}
};

float cos_table[63][2] =
{
    {0, 1.},
    { 1,0.995004 },
    { 2,0.980067 },
    { 3,0.955336 },
    { 4,0.921061 },
    { 5,0.877583 },
    { 6,0.825336 },
    { 7,0.764842 },
    { 8,0.696707 },
    { 9,0.62161 },
    { 10,0.540302 },
    { 11,0.453596 },
    { 12,0.362358 },
    { 13,0.267499 },
    { 14,0.169967 },
    { 15,0.0707372 },
    { 16,-0.0291995 },
    { 17,-0.128844 },
    { 18,-0.227202 },
    { 19,-0.32329 },
    { 20,-0.416147 },
    { 21,-0.504846 },
    { 22,-0.588501 },
    { 23,-0.666276 },
    { 24,-0.737394 },
    { 25,-0.801144 },
    { 26,-0.856889 },
    { 27,-0.904072 },
    { 28,-0.942222 },
    { 29,-0.970958 },
    { 30,-0.989992 },
    { 31,-0.999135 },
    { 32,-0.998295 },
    { 33,-0.98748 },
    { 34,-0.966798 },
    { 35,-0.936457 },
    { 36,-0.896758 },
    { 37,-0.8481 },
    { 38,-0.790968 },
    { 39,-0.725932 },
    { 40,-0.653644 },
    { 41,-0.574824 },
    { 42,-0.490261 },
    { 43,-0.400799 },
    { 44,-0.307333 },
    { 45,-0.210796 },
    { 46,-0.112153 },
    { 47,-0.0123887 },
    { 48,0.087499 },
    { 49,0.186512 },
    { 50,0.283662 },
    { 51,0.377978 },
    { 52,0.468517 },
    { 53,0.554374 },
    { 54,0.634693 },
    { 55,0.70867 },
    { 56,0.775566 },
    { 57,0.834713 },
    { 58,0.88552 },
    { 59,0.927478 },
    { 60,0.96017 },
    { 61,0.983268 },
    { 62,0.996542 },
};

float raiz_quad_abs_cos[63][2] =
{ {0, 1.}, {1, 0.997499}, {2, 0.989983}, {3, 0.977413}, {4,
  0.959719}, {5, 0.936794}, {6, 0.90848}, {7, 0.874553}, {8,
  0.83469}, {9, 0.788422}, {10, 0.735053}, {11, 0.673495}, {12,
  0.601962}, {13, 0.517203}, {14, 0.412271}, {15, 0.265965}, {16,
  0.170879}, {17, 0.358949}, {18, 0.476657}, {19, 0.568586}, {20,
  0.645094}, {21, 0.710525}, {22, 0.767138}, {23, 0.816257}, {24,
  0.858716}, {25, 0.895066}, {26, 0.925683}, {27, 0.950827}, {28,
  0.970681}, {29, 0.985372}, {30, 0.994984}, {31, 0.999567}, {32,
  0.999147}, {33, 0.99372}, {34, 0.983259}, {35, 0.967707}, {36,
  0.946973}, {37, 0.920923}, {38, 0.889364}, {39, 0.852017}, {40,
  0.808482}, {41, 0.758171}, {42, 0.700186}, {43, 0.633087}, {44,
  0.554376}, {45, 0.459125}, {46, 0.334892}, {47, 0.111304}, {48,
  0.295802}, {49, 0.431871}, {50, 0.532599}, {51, 0.614799}, {52,
  0.684483}, {53, 0.744563}, {54, 0.796676}, {55, 0.841825}, {56,
  0.880662}, {57, 0.913626}, {58, 0.94102}, {59, 0.963057}, {60,
  0.979883}, {61, 0.991599}, {62, 0.99827} };

unsigned int Raio_fun_theta(int valor_sen,int abs_sqcos) {
	unsigned int Raio = 32;
	unsigned int RaioTheta;
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
for (i = 0;i < 63;i++) {
    SinValor = (int)(100*sen_table[i][1]);
    CosValor = (int)(100*cos_table[i][1]);
    Raio = Raio_fun_theta(SinValor, (int)(100*raiz_quad_abs_cos[i][1]) );
    x = (char)((Raio * CosValor)/100 + CentroX);
    y = (char)(CentroY - (Raio * SinValor)/100);
    //Line(x, y, xn, yn, Cor, 0);
    Pset(x, y, Cor, 0);
}
//
tempo_fim = RealTimer();
while (Inkey() != 27) {}
// Ending program, and return to DOS
Screen(0);
SetColors(15, 0, 0);
KeySound(1);
delta_t = tempo_fim - tempo_ini;
// stdio.h ativado.
//printf("tempo exec.= %d.%d s",(delta_t)/60,100*(delta_t%60)/60);
Print("tempo exec. = ");
PrintNumber((delta_t) / 60);
Print(",");
PrintNumber(100 * (delta_t % 60) / 60);
Exit(0);

}
