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

long signed int sen_table[126] =
{0, 50, 100, 149, 199, 247, 296, 343, 389, 435, 479, 523, 565, 605, 
644, 682, 717, 751, 783, 813, 841, 867, 891, 913, 932, 949, 964, 976, 
985, 993, 997, 1000, 1000, 997, 992, 984, 974, 961, 946, 929, 909, 
887, 863, 837, 808, 778, 746, 711, 675, 638, 598, 558, 516, 472, 427, 
382, 335, 287, 239, 190, 141, 91, 42, -8, -58, -108, -158, -207, 
-256, -304, -351, -397, -443, -487, -530, -572, -612, -651, -688, 
-723, -757, -789, -818, -846, -872, -895, -916, -935, -952, -966, 
-978, -987, -994, -998, -1000, -999, -996, -991, -982, -972, -959, 
-944, -926, -906, -883, -859, -832, -804, -773, -740, -706, -669, 
-631, -592, -551, -508, -465, -420, -374, -327, -279, -231, -182, 
-133, -83, -33};

 long signed int cos_table[126] =
{1000, 999, 995, 989, 980, 969, 955, 939, 921, 900, 878, 853, 825, 
796, 765, 732, 697, 660, 622, 582, 540, 498, 454, 408, 362, 315, 267, 
219, 170, 121, 71, 21, -29, -79, -129, -178, -227, -276, -323, -370, 
-416, -461, -505, -547, -589, -628, -666, -703, -737, -770, -801, 
-830, -857, -882, -904, -924, -942, -958, -971, -982, -990, -996, 
-999, -1000, -998, -994, -987, -978, -967, -953, -936, -918, -897, 
-874, -848, -821, -791, -759, -726, -691, -654, -615, -575, -533, 
-490, -446, -401, -355, -307, -259, -211, -162, -112, -62, -12, 38, 
87, 137, 187, 235, 284, 331, 378, 424, 469, 512, 554, 595, 635, 673, 
709, 743, 776, 806, 835, 861, 886, 908, 927, 945, 960, 973, 983, 991, 
997, 999};

long unsigned int raiz_quad_abs_cos[126] =
{1000, 999, 997, 994, 990, 984, 977, 969, 960, 949, 937, 923, 908, 
892, 875, 855, 835, 812, 788, 763, 735, 705, 673, 639, 602, 562, 517, 
468, 412, 347, 266, 144, 171, 281, 359, 422, 477, 525, 569, 608, 645, 
679, 711, 740, 767, 793, 816, 838, 859, 878, 895, 911, 926, 939, 951, 
961, 971, 979, 985, 991, 995, 998, 1000, 1000, 999, 997, 994, 989, 
983, 976, 968, 958, 947, 935, 921, 906, 889, 871, 852, 831, 808, 784, 
758, 730, 700, 668, 633, 595, 554, 509, 459, 402, 335, 250, 111, 194, 
296, 370, 432, 485, 533, 576, 615, 651, 684, 716, 745, 772, 797, 820, 
842, 862, 881, 898, 914, 928, 941, 953, 963, 972, 980, 986, 992, 996, 
998, 1000};




unsigned long int Raio_fun_theta(signed  int valor_sen,long int abs_sqcos) {
	int Raio = 28;
	unsigned long  int  RaioTheta;
	RaioTheta = Raio*(valor_sen * abs_sqcos /(valor_sen + 1400) -2*valor_sen +2000 )/1000;
	return RaioTheta;
}

void main(void){
	char i,x,y,Cor,CentroX,CentroY;
    unsigned int tempo_ini, tempo_fim, delta_t;
	signed long int SinValor,CosValor;
	int Raio;
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
    x = ((Raio * CosValor)/1000 + CentroX);
    y = (CentroY - (Raio * SinValor)/1000);
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
