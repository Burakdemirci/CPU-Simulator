/************************/ 
/*	Burak Demirci       */
/*	141044091           */
/************************/
//CPU Class tanimlanmasi
#include <iostream>
#include <string>
#include "Memory.h"

using namespace std;
#ifndef CPU_H
#define CPU_H

class CPU
{
public:
	//Constructor fonksiyon baslangicta register degerlerini sifirlar
	CPU(const int option);
	//PC'yi getirir
	int getPC()const;
	//Programin bitip bitmedigini kontroleder
	int halted();
	//PC degerini ve Registerlerin degerini yazdirir
	const void print();
	//Gelen kodu isleyen fonksiyon 
	void execute(string Str, Memory &myMemory);
	//PC degerini degistirmeye yarayan fonksiyon 
	void setPC(const int newPC);
	//Verilen adresli registerin degerini getirir
	int getRegister(const int adress)const;
	//Verilen keye gore regadres li registere islem yapar 
	void setRegister(const char key, const int regadres , const int eleman);
	//Gelen string icerisindeki bilginin integer bir sayi olup olmadigini kontrol eder	
	int NumberCheck(const string Temp);
	//Halt flag  degerini degistirir
	inline void setHlt()
	{
		hlt=1;
	}
	//Halt flag degerini dondurur
	inline int getHlt()
	{
		return hlt;
	}
	//Option icin getter 
	inline const int getOption()
	{
		return option;
	}
private:
	
	//NumberCheck fonksiyonuna yardimci fonksiyon 
	int Power(int num,const int pow);
	//HLT icin kullanilan flag
	int hlt= 0;
	//Mainde kullanilan dongudeki hangi satirda islem yaptigini tutar
	int PC = 1;
	//Registerlerimiz 
	int R[5];
	//Option degiskeni
	int option;
};

#endif //CPU_H
