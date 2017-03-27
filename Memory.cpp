/************************/
/*	Burak Demirci       */
/*	141044091           */
/************************/

#include "Memory.h"
	
Memory::Memory(const int option)
{
	//Butun adreslere baslangic degeri olarak 0(Sifir) atar
	for(int i=0; i<50; i++)
	{
		setMem(i,0);
	}		
}
//Adreslerin getter fonksiyonu 
int Memory::getMem(const int adress)const 
{
	return Adress[adress];
}

//Adreslerin setter fonksiyonu
void Memory::setMem(const int adress , const int eleman)
{
	Adress[adress]=eleman;
}

//Butun adreslerin degerini yazdirir
void Memory::printAll()const
{
	for(int i=0; i<50; i++)
	{
		cout <<"["<<i<<"]"<<" --> "<<getMem(i)<<endl;
	}	
}
