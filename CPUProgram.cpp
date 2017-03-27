/************************/ 
/*  Burak Demirci       */
/*  141044091           */
/************************/
#include "CPUProgram.h"

CPUProgram::CPUProgram()
{
    //constructor
}
CPUProgram::~CPUProgram()
{
    //Destructor
}

void CPUProgram::ReadFile(const string fileName)
{
	ifstream input;
	input.open(fileName.c_str());
    if(input.is_open()!=1)
    {
        cerr<<"Error opening file"<<endl;
        return ;
    }
    int i=0;
    //Bilginin text'ten satir satir okunmasi
    string Temp;
    while(getline(input,Temp))
    {
    	originaLine.push_back(Temp);
        i++;
    }
    if(i==0)
    {
        //Verilen text bossa
        cerr<<"The text file is empty!"<<endl;
        return ;
    }
    SetSize(i);
    input.close();
    //Dosyadaki bilgileri buyuk harf yapar 
    UpperCase();
    // Dosyadaki bilgileri duzenler 
    Organize();
    
    //Eror Check
    //CheckError();
}

CPUProgram::CPUProgram(const int option) : option(option)  
{   
    // CPUProgram constructoru 
    if(option!=0 && option!=1 && option!=2)
    {
    	cerr<<"Wrong input parameter"<<endl;
    	return;
    }	
}

void CPUProgram::UpperCase()
{
    bool check=true;
    int i=0, j=0;
    while(i<size())
    {
        //Butun karekterlerin buyuk harfe cevrilme islemi
        while(check)
        {
            //Cevirme islemi icin ASCII tablosundan yararlanma
            if(originaLine[i][j]>='a' && originaLine[i][j]<='z')
            {
                originaLine[i][j]-=32;
            }
            if(originaLine[i].length()==j+1)
            {
                check=false;
                j=0;
            }
            else
            {
                j++;
            }
        }
        i++;
        check=true;
    }
}

void CPUProgram::Organize()
{
    int found;
    int index1=0,index2=0,index3;
    int i=0, j;
    while(i<size())
    {
        Line.push_back("");
        //Ana string arreyindeki satirlardaki yorum ifadelerinin ';' referans alinarak silinmesi
        found=originaLine[i].find_first_of(";");
        if(found!=-1)
        {
            originaLine[i].erase(found);
            originaLine[i]+=" ";
        }
        //Ana string arreyindeki ifadelerin sirali sekilde yeni string arreyine doldurulmasi
        for(j=0; j<=9; j++)
        {
            index1=originaLine[i].find_first_not_of(' ',index2);
            index2=originaLine[i].find_first_of(' ',index1);
            if(index1!=-1 && index2==-1)
            {
                Line[i]+=originaLine[i].substr(index1,originaLine[i].length()-index1);
            }
            if(index1==-1 || index2==-1)
            {
                j=10;
            }
            else
            {
                Line[i]+=originaLine[i].substr(index1,index2-index1);
                Line[i]+=" ";
            }
        }
        found=Line[i].find_first_of(',',0);
        if(found!=-1)
        {
            if(Line[i][found-1]==' ')
            {
               Line[i].replace(found,0,"");
            }
            index3=Line[i].find_first_of(',',0);
            if(Line[i][index3+1]!=' ')
            {
                Line[i].replace(index3+1,0," ");
            }
        }
        index2=0;
        i++;
    }    
}

int CPUProgram::CheckError(vector <string> Line)
{
    //Text'ten gelen bilginin duzenlenmesi islemi ve hata bulma islemi
    bool check=true;
    int i=0,j=0,k=0,index1,index2=0;
    int LineSizeOfile=0;
    int flag=-1;
    int hltFlag=-1;
    int retrunFlag=0;
    string Temp;
    string lineStr;
    // Sintaks hatalarinin olup olmadigini arastirma islemi
    while(i<size())
    {
        lineStr=Line[i];
        index1=lineStr.find_first_of(',');
        if(index1!=-1)
        {
            lineStr.replace(index1,0," ");
        }   
        int errorFlag=0;
        index1=lineStr.find_first_of(' ',0);
        if(index1!=3 && index1!=-1)
        {
            // Ilk komutun uzunlugunun uc karekterden fazla veya az olmasi durumundaki hata
            errorFlag = -1;
        }
        Temp=lineStr.substr(0,index1);
        if(Temp=="JMP" || Temp=="JPN")
        {
            //JMP icin alacagi degerlerin dogru gelip gelmedigini inceleme
            flag=0;
            string Temp2=Temp;
            index1=lineStr.find_first_not_of(' ',3);
            index2=lineStr.find_first_of(' ',index1);
            Temp=lineStr.substr(index1,index2-index1);
            index1=lineStr.find_first_of(',',3);
            if(Temp2=="JPN")
            {
                if(index1==-1)
                {
                    //JPN icin virgul yoksa verilecek hata
                    errorFlag = -1;
                }   
            }   
            if(index1!=-1)
            {
                index1=lineStr.find_first_not_of(' ',index1+1);
                if(index1==-1)
                {
                    //Virgul kullanilan JMP ve JPN islemi icin son parametre yoksa verilen hata
                    errorFlag = -1;
                }
                else
                {    
                    if(Temp=="R1" ||Temp=="R2" || Temp=="R3" || Temp=="R4" || Temp=="R5")
                    {
                    //Virgulden oncekiparametrenin belirlenen registerler icerisinde olup olmadigini kontrol etme
                    }
                    else
                    {
                        errorFlag =-1;
                    }
                    index1=lineStr.find_first_of(',',3);
                    index1=lineStr.find_first_not_of(' ',index1+1);
                    index2=lineStr.find_first_of(' ',index1);
                    Temp=lineStr.substr(index1,index2-index1);
                    index1=lineStr.find_first_not_of(' ',index2);
                    if(index1!=-1)
                    {
                        errorFlag = -1;
                    }
                    if(Temp2=="JPN")
                    {
                        // 49 maksimum adresimiz 
                        if(NumberCheck(Temp)==-1 || NumberCheck(Temp)>size()+1)
                        {
                           errorFlag = -1;
                        }
                    }
                    else
                    {
                        index1=Temp.find_first_of('#',0);
                        if(index1!=-1)
                        {
                            errorFlag = -1;
                        }    
                        if(NumberCheck(Temp)==-1 || NumberCheck(Temp)>size()+1)
                        {
                           errorFlag = -1;
                        }
                    }    
                }
            }
            else
            {
                //Virgul kullanilmayan JMP islemi icin patrametrelerin dogrulugunu inceleme
                if(index1!=-1)
                {
                    //JMP'den sonra hicbirsey gelmiyorsa verilecek hata
                    errorFlag = -1;
                }
                if(NumberCheck(Temp)!=-1 && NumberCheck(Temp)<size()+1){
                }
                else
                {
                    //Virgulsuz JMP islemi,nde gelen bilginin sayi olmamasi
                    errorFlag = -1;
                }
            }
        }
        if(Temp=="HLT")
        {
            //Yazilan kodda HLT olup olmadigi ve eger var ise hatali kullanilip kullanilmadigini belirleme
            hltFlag=0;
            flag=0;
            index2=lineStr.find_first_not_of(' ',3);
            if(index2!=-1)
            {
                errorFlag = -1;
            }
        }
        if(Temp=="PRN")
        {
            //PRN icin alacagi degerlerin dogru gelip gelmedigini inceleme
            flag=0;
            index1=lineStr.find_first_not_of(' ',3);
            index2=lineStr.find_first_of(' ',index1);
            LineSizeOfile=lineStr.length();
            Temp=lineStr.substr(index1,index2-index1);
            index1=lineStr.find_first_not_of(' ',index2);
            if(index1!=-1)
            {
                errorFlag = -1;
            }
            if(Temp=="R1" ||Temp=="R2" || Temp=="R3" || Temp=="R4" || Temp=="R5" || NumberCheck(Temp)!=-1)
            {
                //Registerlere uygunlugu ve sayimi degilmi kontrolu
                index1=Temp.find_first_of('#',0);
                // 49 Maksimum adres indexi
                if(index1!=-1 && NumberCheck(Temp)>49)
                {
                    errorFlag = -1;
                }   
            }
            else
            {
                errorFlag = -1;
            }
        }
        if(Temp=="MOV" || Temp=="ADD" || Temp=="SUB")
        {
            flag=0;
            int mov =0;
            //Ayni tur parametreleri kullanan ifadeler icin hata arastirma islemi
            if(Temp=="MOV")
                mov=1;
            if(CheckErrorHelper(lineStr,mov)==-1)
            {
                errorFlag = -1;
            }
        }
        if(flag==-1)
        {
            //Belirlenen ilk parametreler disinda uc harfli bir parametre gelirse verilecek hata
           errorFlag = -1;
        }
        flag=-1;
        if(errorFlag==-1)
        {
           cerr<<"Wrong instruction in line : "<<i+1<<endl;
           retrunFlag=-1 ;
        }    
        i++;
    }
    if(hltFlag==-1)
    {
        //Eger kodumuzda HLT yoksa verilecek hata
        cerr<<"Your code does not have HLT instruction"<<endl;
        retrunFlag=-1 ;
    }
    if(retrunFlag==-1)
        return -1;
    return 0;
}

int CPUProgram::CheckErrorHelper(const string &lineStr, const int mov)
{
    // Verilen text'tin syntex'e uygun olup olmadigini belirleme
    int index1,index2;
    string Temp;
    int movflag=0;
    index1=lineStr.find_first_of(',',3);
    if(index1==-1)
    {
        //Virgul yoksa
        return -1;
    }
    index1=lineStr.find_first_not_of(' ',index1+1);
    if(index1==-1)
    {
        // ',' virgulden sonra ifade yoksa
        return -1;
    }
    // Ilk ifadeden sonra gelen ifadeyi bulma
    index1=lineStr.find_first_not_of(' ',3);
    index2=lineStr.find_first_of(' ',index1);
    Temp=lineStr.substr(index1,index2-index1);
    if(mov==0)
    { //MOV komutundan farkli bir komutla gelmisse
        if(Temp=="R1" ||Temp=="R2" || Temp=="R3" || Temp=="R4" || Temp=="R5")
        {
            //Bulunan ifade bizim belirledigimiz kriterlere uygunlugunu belirleme
        }
        else
        {
            return -1;
        }
    }
    if(mov==1)
    {
        //Mov komutuyla geldiyse
        if(Temp=="R1" ||Temp=="R2" || Temp=="R3" || Temp=="R4" || Temp=="R5"|| NumberCheck(Temp)!=-1)
        {
            // Bulunan ifade bizim belirledigimiz kriterlere uygunlugunu belirleme
            if(NumberCheck(Temp)!=-1)
            {
                index1=Temp.find_first_of('#',0);
                if(index1==-1)
                {
                    return -1;
                }
                else
                    movflag=1;
                if(NumberCheck(Temp)>49)
                {
                    return -1;
                }   
            }   
        }
        else
        {
            return -1;
        }
    }   
    // Virgulden sonraki ifadenin uygunluguna bakma
    index1=lineStr.find_first_of(',',3);
    index1=lineStr.find_first_not_of(' ',index1+1);
    index2=lineStr.find_first_of(' ',index1);
    Temp=lineStr.substr(index1,index2-index1);
    index1=lineStr.find_first_not_of(' ',index2);
    if(index1!=-1)
    {
        return -1;
    }
    if(Temp=="R1" ||Temp=="R2" || Temp=="R3" || Temp=="R4" || Temp=="R5" || NumberCheck(Temp)!=-1)
    {
        //Bulunan ifade bizim belirledigimiz kriterlere uygunlugunu belirleme
        //Eger mov'un ilk ifadesinde adres varsa 2. ifade adres olamaz 
        index1=Temp.find_first_of('#',0);
        if(index1!=-1 && movflag==1 && mov==1)
        {
            return -1;
        }
        //Eger gelen adres numarasi 49(maksimum adres sayisi) den buyukse verilen hata  
        if(index1!=-1 && NumberCheck(Temp)>49)
        {
            return -1;
        }   
    }  
    else
    {
    	
        return -1;
    }
    return 0; 
}

int CPUProgram::NumberCheck(string Temp)
{
    // Bir strinkteki ifadenin sayi olup olmadigini ve sayi ise o sayiyi integer haline getirme
    int Degisken,tempNum=0,Num=0,pow,i=0;
    char ch;
    int check;
    check=Temp.find_first_of("#",0);
    Degisken=Temp.length();
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

int CPUProgram::Power(int num, const int pow)
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

const string CPUProgram::operator[](const int index)const
{   
    //gelen index negatif ise 
    if(index<0)
    {
        cerr <<"Out of index! Returning first index"<<endl;
        return Line[0];
    }    
	if(index <size())
		return Line[index];
	else
	{	
		cerr <<"Out of index! Returning last index"<<endl;
		return Line[size()-1];
	}				
}

CPUProgram & CPUProgram::operator+=(string instruction)
{   
    if(instruction!="")
    {    
        Line.push_back(instruction);
        SetSize(size()+1);
    }
    else
        cerr <<"Warning! Empty instruction"<<endl;   
    return *this;
}
// OP + For : myCPUProgram + "MOV R1, R2"
const CPUProgram CPUProgram::operator+(string instruction)
{
    CPUProgram newObje;
    newObje=*this;
    newObje.Line.push_back(instruction);
    newObje.SetSize(newObje.size()+1);
    return newObje;
}
// OP + For: ( myCPUProgram1 + myCPUProgram2 )
const CPUProgram CPUProgram::operator+ (CPUProgram newCPUProgram)
{
    CPUProgram newObje;
    newObje=*this;
    newObje.Line.insert(newObje.Line.end(),newCPUProgram.Line.begin(),newCPUProgram.Line.end());
    newObje.SetSize(newObje.size()+newCPUProgram.size());
    return newObje;
}
// OP <<  For: cout << myCPUProgram << endl;
ostream& operator<< (ostream &ostr,const CPUProgram & myCPUProgram)
{
    int i=0;
    while(i < myCPUProgram.size())
    {
        ostr << myCPUProgram.getLine(i);
        if(i < myCPUProgram.size()-1)
            ostr << endl;
        ++i;
    } 
    return ostr;   
}
// OP () For : myCPUProgram(5,9) 
const CPUProgram CPUProgram::operator() (int begin , int end)
{
    CPUProgram newObje;
    if(begin > size() || begin>end || begin<0 || end<0 || end>size())
    {
        cerr << "Warning : Out of size !" <<endl;
        return newObje;
    }  
    for (int i = begin; i<=end; ++i)
    {
        newObje.Line.push_back(getLine(i));
    }
    newObje.SetSize(end-begin+1);
    return newObje;
}

// OP ==
const bool CPUProgram::operator ==(const CPUProgram & myCPUProgram1) const
{
    if(size()==myCPUProgram1.size())
        return true;
    else
        return false;
}
// OP !=
const bool CPUProgram::operator !=(const CPUProgram & myCPUProgram1) const
{
    if(size()!=myCPUProgram1.size())
        return true;
    else
        return false;
}
// OP <
const bool CPUProgram::operator <(const CPUProgram & myCPUProgram1) const
{
    if(size() < myCPUProgram1.size())
        return true;
    else
        return false;
}
// OP >=
const bool CPUProgram::operator >=(const CPUProgram & myCPUProgram1) const
{
    if(size()>=myCPUProgram1.size())
        return true;
    else
        return false;
}
// OP <=
const bool CPUProgram::operator <=(const CPUProgram & myCPUProgram1) const
{
    if(size()<=myCPUProgram1.size())
        return true;
    else
        return false;
}
// OP >
const bool CPUProgram::operator >(const CPUProgram & myCPUProgram1) const
{
    if(size()>myCPUProgram1.size())
        return true;
    else
        return false;
}

// OP i-- Postfix
const CPUProgram CPUProgram::operator--(int ignorMe)
{
    CPUProgram newObje;
    newObje=*this;
    Line.pop_back();
    SetSize(size()-1);
    return newObje;
}
// OP --i Prefix
const CPUProgram CPUProgram::operator--()
{
    Line.pop_back();
    SetSize(size()-1);
    return *this;
}