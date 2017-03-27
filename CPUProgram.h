/************************/ 
/*	Burak Demirci       */
/*	141044091           */
/************************/
//CPUProgram Class tanimlanmasi
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

#ifndef CPUProgram_H
#define CPUProgram_H
//CPUProgram sinifi tanimlamalari ve fonksiyonlari 
class CPUProgram
{
public:
	//Constructor fonksiyonu 
	CPUProgram(const int option);
	CPUProgram();
	~CPUProgram();
	//Gelen stringin icerisindeki bilginin integer deger olup olmadigini kontrol eder
	int NumberCheck(string Temp);
	//Gelen bilginin dogrulugunu kontol edenfonksiyon 
	int CheckError(vector <string> Line);
	//Dosyayi okur
	void ReadFile(const string fileName);
	inline vector<string> GetStr()
	{
		return Line;
	}
	//Verilen string arreyinin tek elemanini dondürür 
	inline string getLine(const int lineAdress)const
	{
		return Line[lineAdress];
	}
	//Dosyanin satir uzunlugunu alan fonksiyon
	inline void SetSize(const int size) 
	{
		sizeOfFile=size;
	}
	inline int size() const
	{
		return sizeOfFile;
	}
	//Dosyanin adini alan fonksiyon
	inline const string GetFileName(const string fileName)
	{
		return fileName;
	}
	// OP []
	const string operator[] (const int index) const;
	// OP +   
	const CPUProgram operator+ (string instruction);
	// OP += 
	CPUProgram & operator+= (string instruction);
	// OP +  : Takes two program return object
	const CPUProgram operator+ (CPUProgram newCPUProgram);
	// COUT <<
	friend ostream& operator<< (ostream &ostr, const CPUProgram & myCPUProgram);
	// OP ==
	const bool operator ==(const CPUProgram & myCPUProgram1) const;
	// OP !=
	const bool operator !=(const CPUProgram & myCPUProgram1) const;
	// OP <
	const bool operator <(const CPUProgram & myCPUProgram1) const;
	// OP >=
	const bool operator >=(const CPUProgram & myCPUProgram1) const;
	// OP <=
	const bool operator <=(const CPUProgram & myCPUProgram1) const;
	// OP >
	const bool operator >(const CPUProgram & myCPUProgram1) const;
	// OP ()
	const CPUProgram operator() (int begin , int end);
	// OP i-- Postfix
	const CPUProgram operator--(int ignorMe);
	// OP --i Prefix
	const CPUProgram operator--();
private:
	//Gelen bilginin kac satir oldugunu tutar 
	// Basta sifir atanmasinin sebebi bos objede yazdirma islemlerinde
	// core dumpt hatasini onleme 
	int sizeOfFile=0;
	//Gelen bilginin orjinalini tutar
	vector<string> originaLine;
	//Gelen bilginin düzenlenmis halini tutar 
	vector<string> Line;
	//Gelen bilgileri buyuk harf yapar
	void UpperCase();
	//Gelen bilgiyi istenilen sekilde duzenler
	void Organize();
	//Hata kontrolu icin yardimci fonksiyon
	int CheckErrorHelper(const string &lineStr, const int mov);
	//NumberCheck'e yardimci fonksiyon 
	int Power(int num, const int pow);
	//Option 
	int option;
};
 
#endif //CPUProgram_H