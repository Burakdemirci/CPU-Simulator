/************************/ 
/*	Burak Demirci       */
/*	141044091           */
/************************/

#include "CPU.h"

CPU::CPU(const int option) : option(option)
{
	//Isleme basladiginda butun registerlere 0 degerini atar 
	for (int i = 0; i < 5; ++i)
	{
		setRegister('=',i,0);
	}
}

void CPU::setPC(const int newPC)
{
	PC=newPC;
}

int CPU::getPC()const
{
	return PC;
}

void CPU::setRegister(const char key, const int regadres , const int eleman)
{
	//Gelen key harfine gore register degerini degistirir
	if(key=='=')
		R[regadres]=eleman;
	if(key=='+')
		R[regadres]+=eleman;
	if(key=='-')
		R[regadres]-=eleman;
}

int CPU::getRegister(const int adress)const
{
	//Adresi verilen registerin degerini dondurur
	return R[adress];
}

const void CPU::print()
{
	// Terminalden gelen 0 ve 1 sayisinin geldigi duruma gore islem yapma
	//Registerlerin icerisindeki degerleri yazdirma
	for (int i = 0; i < 5; ++i)
	{
		cout<<"["<<i<<"]"<<" --> "<<getRegister(i)<<endl;
	}
}

// Program halt oldugunda degeri dondurur
int CPU::halted()
{
	return getHlt();
}
void CPU::execute(string Str,Memory &myMemory)
{
	// Text'teki kodun calistirilmasi icin yazilan fonksiyon
    int i=0,j,k;
    string Temp,Temp2;
    int index1,index2;
    string Register[5]={"R1","R2","R3","R4","R5"};
    index1=Str.find_first_of(',');
    if(index1!=-1)
    	Str.replace(index1,0," ");

    //Optiona gore yazdirma islemleri 
    if(getOption()==1 || getOption()==2)
	{
		cout<<Str<<endl;
		print();
	}
	if(getOption()==2)
		myMemory.printAll();
    index1=Str.find_first_not_of(' ',0);
    index2=Str.find_first_of(' ',index1);
    Temp=Str.substr(index1,index2-index1);
    // PRN islemi
    if(Temp=="PRN")
    {
        index1=Str.find_first_not_of(' ',3);
        index2=Str.find_first_of(' ',index1);
        Temp=Str.substr(index1,index2-index1);
        j=0;
        index1=Temp.find_first_of('#',0);
        //Adressin icerisindeki bilgi yazdirilacaksa 
        if(index1!=-1)
        {
        	if(NumberCheck(Temp)!=-1)
        	{
        	    cout<<myMemory.getMem(NumberCheck(Temp))<<endl;
        	}
        }
        else
        {	
        	while(j<5)
        	{
        		// Registerin belirlenmesi icin gereken dongu
        	    if(Temp==Register[j])
        	    {
        	        cout<<getRegister(j)<<endl;
        	    }
        	    j++;
        	}
        	// Sayi yazdirilacak ise onun belirlenmesi
        	if(NumberCheck(Temp)!=-1)
        	{
        	    cout<<NumberCheck(Temp)<<endl;
        	}
        }		
    }
    if(Temp=="HLT")
    {
        // Bu ifade geldiginde program sonlanir
        setHlt();
    }
    // MOV islemi
    if(Temp=="MOV")
    {
        // Registerin belirlenmesi
        index1=Str.find_first_not_of(' ',3);
        index2=Str.find_first_of(' ',index1);
        Temp=Str.substr(index1,index2-index1);
        // Registere atanacak olan sayi veya diger registerin belirlenmesi
        index1=Str.find_first_of(',',3);
        index1=Str.find_first_not_of(' ',index1+1);
        index2=Str.find_first_of(' ',index1);
        Temp2=Str.substr(index1,index2-index1);
        j=0;
        k=0;
        //Virgülden onceki stringin icınde # aranmasi 
        index1=Temp.find_first_of('#',0);
        //Virgülden sonraki stringin icınde # aranmasi 
        index2=Temp2.find_first_of('#',0);
        //Virgulden once # varsa adres atamasi
        if(index1!=-1)
        {
        	//Eger ilk deger adres ise adrese registerin degeri veya 
        	//constant bir sayi degereinin atanmasi
        	while(k<5)
            {
                // Bilginin nereden atanacagi ve bilgi atama islemi
                if(Temp2==Register[k])
                {
                    setRegister('=',k,myMemory.getMem(NumberCheck(Temp)));
                }
                k++;
            }

            if(NumberCheck(Temp2)!=-1)
            {
                myMemory.setMem(NumberCheck(Temp),NumberCheck(Temp2));
            }	
        }
        if(index2!=-1)
        {
        	while(k<5)
            {
                // Bilginin nereden atanacagi ve bilgi atama islemi
                if(Temp==Register[k])
                {
                    myMemory.setMem(NumberCheck(Temp2),getRegister(k));
                }
                k++;
            }
        }	
        //Eger atanacak degerlerden ikiside adres bilgisi icermiyorsa yapilacak atama(Mov) 
        if(index1==-1 && index2==-1)
        {
            while(j<5)
            {
                // Icerisine bilgi atanacak registerin bulunmasi
                if(Temp==Register[j])
                {
                    while(k<5)
                    {
                        // Bilginin nereden atanacagi ve bilgi atama islemi
                        if(Temp2==Register[k])
                        {
                            setRegister('=',j,getRegister(k));
                        }
                        k++;
                    }
                    if(NumberCheck(Temp2)!=-1)
                    {
                        setRegister('=',j,NumberCheck(Temp2));
                    }
                }
                j++;
            }
        }   
    }
    // ADD ve SUB islemi
    if(Temp=="ADD" || Temp=="SUB")
    {
    	string Temp3=Temp;
        // Registerin belirlenmesi
        index1=Str.find_first_not_of(' ',3);
        index2=Str.find_first_of(' ',index1);
        Temp=Str.substr(index1,index2-index1);
        // Registere eklenecek olan sayi veya diger registerin belirlenmesi
        index1=Str.find_first_of(',',3);
        index1=Str.find_first_not_of(' ',index1+1);
        index2=Str.find_first_of(' ',index1);
        Temp2=Str.substr(index1,index2-index1);
        j=0;
        k=0;
        while(j<5)
        {
            // Icerisine ekleme yapilacak registerin bulunmasi
            if(Temp==Register[j])
            {
                while(k<5)
                {
                    // Bilginin nereden atanacagi ve bilgi atama islemi
                    if(Temp2==Register[k])
                    {
                    	if(Temp3=="ADD")
                        	setRegister('+',j,getRegister(k));
                        else
                        	setRegister('-',j,getRegister(k));
                    }	
                    index1=Temp2.find_first_of('#',0);
                    if(index1!=-1)
                    {
                    	if(Temp3=="ADD")
                    	{
                    		if(NumberCheck(Temp2)!=-1)
                        	{
                        	    setRegister('+',j,myMemory.getMem(NumberCheck(Temp2)));
                        	    k=10;
                        	}
                    	}
                    	else
                    	{
                    		if(NumberCheck(Temp2)!=-1)
                        	{
                        	   setRegister('-',j,myMemory.getMem(NumberCheck(Temp2)));
                        	    k=10;
                        	}	
                    	}	
                    }
                    else
                    {
                    	if(Temp3=="ADD")
                    	{
                    		if(NumberCheck(Temp2)!=-1)
                        	{
                        	    setRegister('+',j,NumberCheck(Temp2));
                        	    k=10;
                        	}
                    	}
                    	else
                    	{
                    		if(NumberCheck(Temp2)!=-1)
                        	{
                        	    setRegister('-',j,NumberCheck(Temp2));
                        	    k=10;
                        	}	
                    	}	
                    }
                    k++;
                }
            }
            j++;
        }
    }
    // JMP ve JPN islemleri
    if(Temp=="JMP" || Temp=="JPN")
    {
        string Temp2=Temp;
        index1=Str.find_first_of(',',0);
        if(index1!=-1)
        {
            // Registerin ismini bulma
            index1=Str.find_first_not_of(' ',3);
            index2=Str.find_first_of(' ',index1);
            Temp=Str.substr(index1,index2-index1);
            // Sicrayacagi indeksi bulma
            index1=Str.find_first_of(',',3);
            index1=Str.find_first_not_of(' ',index1+1);
            index2=Str.find_first_of(' ',index1);
            j=0;
            // Dongu ile registerleri belirleme
            if(Temp2=="JMP")
            {	
                while(j<5)
                {
                    if(Temp==Register[j])
                    {
                        if(R[j]==0)
                        {
                            Temp2=Str.substr(index1,index2-index1);
                            setPC(NumberCheck(Temp2)-1);
                        }
                    }
                    j++;
                }
            }
            else
            {
            	while(j<5)
                {
                    if(Temp==Register[j])
                    {
                        if(R[j]<=0)
                        {
                            Temp2=Str.substr(index1,index2-index1);
                            setPC(NumberCheck(Temp2)-1);
                        }
                    }
                    j++;
                }
            }    
        }
        else
        {
            // Eger direkt atlayacagi satirin adresi verilmisse o adresi belirleme ve atama
            index1=Str.find_first_not_of(' ',3);
            index2=Str.find_first_of(' ',index1);
            Temp=Str.substr(index1,index2-index1);
            setPC(NumberCheck(Temp)-1);
        }   
    }
}

int CPU::NumberCheck(string Temp)
{
    // Bir strinkteki ifadenin sayi olup olmadigini ve sayi ise o sayiyi integer haline getirme
    int Degisken,tempNum=0,Num=0,pow,i=0;
    char ch;
    int check;
    check=Temp.find_first_of("#",0);
    Degisken=Temp.size();
    if(check==0)
    {
    	Temp=Temp.substr(1,Degisken-1);
    	Degisken--;
    }
    if(check>0)
    {
    	return -1;
    }	
    pow=Degisken;
    while(i<Degisken)
    {
       // ASCII tablosundaki karekter halinde bulunan sayilarin decimal degerinden yaralanip
       //Sayiya cevirme islemi
       if(Temp[i]<='9' && Temp[i]>='0')
       {
            tempNum=Temp[i]%48;
            Num+=Power(tempNum,pow);
       }
       else
       {
           return -1;
       }
       pow--;
       i++;
    }
    return Num;
}

int CPU::Power(int num,const int pow)
{
    // Bir sayinin basamak deðerini bulmak icin kullanilan fonksiyon
    int i=1;
    while(i<pow)
    {
        num*=10;
        i++;
    }
    return num;
}