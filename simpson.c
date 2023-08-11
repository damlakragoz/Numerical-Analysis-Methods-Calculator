#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void polinomAl(double polinom[100][2], int terim) {

    printf(" Terimin katsayi ve kuvvetini sirasiyla giriniz:\n");
    for (int i = 0; i < terim; i++) {
        printf("Term %d: ", i + 1);
        scanf("%lf %lf", &polinom[i][0], &polinom[i][1]);
    }
}

//max 100 terimlik bir polinomunu türevini hesaplar
double polinomHesap(double polinom[100][2], double deger, int terim) {
    double sonuc = 0.0;
    
    for (int i = 0; i < terim; i++) {
        sonuc += polinom[i][0]*pow(deger,polinom[i][1]);

    }
    //printf("sonc %lf\n", sonuc);
    return sonuc;
}

// Polinom Türevi alır
double türevF(double p[100][2], double deger, int terim) {
    double p2[100][2];
    for (int i = 0; i < terim; i++) {
        for (int j = 0; j < 2; j++) {
            p2[i][j] = p[i][j];
        }
    }

    for (int i = 0; i < terim; i++) {
       p2[i][0] *= p2[i][1];
       p2[i][1]--;
    }

    return polinomHesap(p2, deger, terim);
}

// 8. Trapez Yöntemi
double trapezYontemi(double altlim, double üstlim, int n) {
    double aralikGenisligi = (üstlim - altlim) / n; // aralık genişliği
    //double kenar1 = f(altlim);
    //double kenar2 = f(üstlim);

    double birustlim =( altlim + aralikGenisligi);

    double yamukAlan = 0;
    for (int i = 1; i <=  n; i++) {
        
  //      yamukAlan += aralikGenisligi * ((f(altlim) + f(altlim+aralikGenisligi)) / 2) ;
        altlim += aralikGenisligi;
    }

    return yamukAlan;
}

// 9. Simpson
double simpsonYontemi(double altlim, double üstlim, int n) {
    double aralikGenisligi = (üstlim - altlim) / n; // aralık gneişliği
    double toplam ;//f(altlim) + f(üstlim); 

    for (int i = 1; i < n; i++) {
        double x = altlim + i * aralikGenisligi;

        if (i % 2 == 0) {
            toplam += 2 ;//*f(x); // çift sayılı x'lerde y'lerin toplamı
        } 
        else {
            toplam += 4 ; //*f(x); // tek sayılı x'lerde y'ler toplamı
        }
    }

    return (aralikGenisligi / 3) * toplam;
}

// 6. Gauss-Seidel
void gaussSeidel(double p[100][2], double p2[100][2], double p3[100][2]) {

}

// Gregory Newton
void gregoryNewton() {
    int size ;
    
    printf("Kaç x/y değeri gireceksiniz? ");
    scanf("%d", &size);
    
    double degerler[size][2]; 
    printf("x değerlerini giriniz: ");
	for (int i = 0; i < size; i++)
    {
        scanf("%lf", &degerler[i][0]);
    }
    printf("y değerlerini giriniz: ");
    for (int i = 0; i < size; i++)
    {
        scanf("%lf", &degerler[i][1]);
    }

    double ayrikFarklar[size-1][size-1];

    
    for (int j = 0; j < size-1; j++)
    {
        ayrikFarklar[0][j] = (degerler[j+1][1]-degerler[j][1]) / (degerler[j+1][0]-degerler[j][0]);
        printf("ayrik fark %d-%d: %lf\n", 0,j,ayrikFarklar[1][j]);
    }

    for (int i = 1; i < size-1; i++)
    {
        for (int j = 0; j < size-1; j++)
        {
            ayrikFarklar[i][j] = (ayrikFarklar[j+1][1]-ayrikFarklar[j][1]) / (degerler[j+1][0]-degerler[j][0]);
            printf("ayrik fark %d-%d: %lf\n", 1,j,ayrikFarklar[1][j]);
        }
        
    }
    
        

    
}

//gregory newton içib helper method 
void hesaplaAyrikFark(double x[], double fx[], int n) {
    double ayrikFark[100][100]; // Ayrık farkları tutacak 2D matris
    int i, j;

    // Ayrık fark matrisini sıfırlarla başlatma
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            ayrikFark[i][j] = 0;
        }
    }

    // İlk sütunu, f(x) değerleriyle doldurma
    for (i = 0; i < n; i++) {
        ayrikFark[i][0] = fx[i];
    }

    // Ayrık farkları hesaplama
    for (j = 1; j < n; j++) {
        for (i = 0; i < n - j; i++) {
            ayrikFark[i][j] = ayrikFark[i + 1][j - 1] - ayrikFark[i][j - 1];
        }
    }

    // Ayrık farkları yazdırma
    printf("Ayrık Farklar:\n");
    for (i = 0; i < n; i++) {
        printf("%.2lf ", x[i]);
        for (j = 0; j < n - i; j++) {
            printf("%.2lf ", ayrikFark[i][j]);
        }
        printf("\n");
    }
}

// Gregory Newton
/*void gregoryNewton() {
    double x[100], fx[100];
    int n, i;

    printf("Veri noktası sayısını girin: ");
    scanf("%d", &n);

    printf("x ve f(x) değerlerini girin:\n");
    for (i = 0; i < n; i++) {
        printf("x%d: ", i);
        scanf("%lf", &x[i]);

        printf("f(x%d): ", i);
        scanf("%lf", &fx[i]);
    }

    hesaplaAyrikFark(x, fx, n);
}*/


// 3. Newton Raphson
double NewtonRaphson(double polinom[100][2], double x, double terim) {
 
    double lastX;
    double fark;
    do{
        double a = polinomHesap(polinom,x,terim);
        double b = türevF(polinom,x,terim);
        x -= a / b;
        fark = fabs(x-lastX);
        lastX = x;
    
    }
    while (fark>= 0.00001);
    return x;

}

int main() {
    double altLim = 0; 
    double üstLim = M_PI; 
    int n = 100; //reiman dikdörtgenleri sayısı

    double sonuc = simpsonYontemi(altLim, üstLim, n);
    printf("Simpson - Yaklasik integral: %f\n", sonuc);

    double sonuc2  = trapezYontemi(altLim,üstLim,n);
    printf("Trapez - Yaklasik integral: %f\n", sonuc2);

//polinom alma
    double polinom[100][2]; 
    int terim; // Number of terms in the polynomial

    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &terim);

    polinomAl(polinom,terim);
    
    double deger;
    printf("X değerini giriniz: ");
    scanf("%lf", &deger);

/* 
    int x = polinomHesap(polinom, deger, terim);
    int y = türevF(polinom, deger, terim);

    printf("Polinom: %d\n", x);
    printf("Türevi: %d\n", y);
*/

    //seçim
    int yontemSecimi;
	
	printf("Yapmak istediginiz hesaplama yontemini secin:\n");
    printf("1. Bisection yontemi\n");
    printf("2. Regula-Falsi yontemi\n");
    printf("3. Newton-Raphson yontemi\n");
    printf("4. NxN'lik bir matrisin tersi\n");
    printf("5. Gauss Eleminasyon yontemi\n");
    printf("6. Gauss Seidel yontemi\n");
    printf("7. Sayisal Turev\n");
    printf("8. Simpson yontemi\n");
    printf("9. Trapez yontemi\n");
    printf("10. Degisken Donusumsuz Gregory Newton Enterpolasyonu\n");
    printf("Seciminizi yapin: ");
	scanf("%d", &yontemSecimi);
	
	if(yontemSecimi == 1){
		//bisection();
	} else if(yontemSecimi == 2){
		//regulaFalsi();
	} else if(yontemSecimi == 3){
        int tahmin;
        printf("Tahmin yapin: ");
	    scanf("%d", &tahmin);
        printf("Toleransi girin: ");
	    scanf("%d", &tahmin);
		printf("Newton ile kök: %lf", NewtonRaphson(polinom, tahmin, deger));

	}  else if(yontemSecimi == 4){

	}  else if(yontemSecimi == 5){
		gregoryNewton();
	}  else if(yontemSecimi == 6){

		double polinom2[100][2]; 
        int terim2; //terim sayısı
        printf("Enter the number of terms in the polynomial: ");
        scanf("%d", &terim2);
        polinomAl(polinom2,terim2);
        
        double polinom3[100][2]; 
        int terim3; // terim sayısı
        printf("Enter the number of terms in the polynomial: ");
        scanf("%d", &terim3);
        polinomAl(polinom3,terim3);

        gaussSeidel(polinom, polinom2, polinom3);
        
	}
    
return 0;
}