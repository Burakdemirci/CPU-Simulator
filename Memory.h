/************************/ 
/*	Burak Demirci       */
/*	141044091           */
/************************/
#include <iostream>
#include <string>
using namespace std;

#ifndef Memory_H
#define Memory_H
//Memory clasi  ve fonksiyon tanimlamalari
class Memory 
{
public:
	//Memory constructoru 
	Memory(const int option);
	//adresi verilen memory'i gwtirir
	int getMem(const int adress)const;
	//Adresi verilen memory degerine yeni bir deger atar
	void setMem(const int adress , const int eleman);
	//Butun memory'i yazdirir
	void printAll()const;
private:
	//Adres arrayimiz 
	unsigned int Adress[50];
};

#endif // Memory_H