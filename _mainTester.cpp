/*--------------------------------------------------------------------------*/
/* HW_5									                                    */
/* Burak Demirci							                                */
/* 141044091                                								*/
/*--------------------------------------------------------------------------*/
/*                              Icerik  								    */
/*--------------------------------------------------------------------------*/
//Gerekli kutuphanenin cagrilmasi
#include "requiredIncs.h"

int main(int argc, char** argv){
//////////////////////////////////////////////////////////////////////////
	//command line parameters
	const char* filename = argv[1];
	int option = atoi(argv[2]);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
	//Testing class CPUProgram
	//op []
	CPUProgram myCPUProgram(option);
	myCPUProgram.ReadFile(filename);
	cout << myCPUProgram[0] << endl;
	cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
	//op +
	cout << ((myCPUProgram + "MOV R1, #45")[myCPUProgram.size() -1]) << endl;
	//op +=
	myCPUProgram += "MOV R2, #50";
	cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
	//op + <<
	CPUProgram myOtherCPUProgram(option);
	myOtherCPUProgram.ReadFile(filename);
	cout << (myCPUProgram + myOtherCPUProgram) << endl;
	//op COMP --
	cout << (myCPUProgram == myOtherCPUProgram ? "DONE" : "FAIL") << endl;
	cout << (myCPUProgram <= myOtherCPUProgram ? "DONE" : "FAIL") << endl;
	cout << (myCPUProgram > myOtherCPUProgram ? "FAIL" : "DONE") << endl;
	--myOtherCPUProgram;
	cout << (myCPUProgram != myOtherCPUProgram ? "DONE" : "FAIL") << endl;
	cout << (myCPUProgram >= myOtherCPUProgram ? "DONE" : "FAIL") << endl;
	cout << (myCPUProgram < myOtherCPUProgram ? "FAIL" : "DONE") << endl;
	myOtherCPUProgram--;
	myCPUProgram += "JMP R1, 10";
	cout<<myCPUProgram[myCPUProgram.size()-1]<<endl;
	//op ()
	cout << myCPUProgram(5, 500) << endl;
	//error check
	cout << myCPUProgram[myCPUProgram.size()] << endl;
	myCPUProgram += "";
	cout << myCPUProgram[myCPUProgram.size() - 1] << endl; 
	// Yeni bilgi ekleme
	CPUProgram myCPUProgram1(option);
	myCPUProgram1.ReadFile(filename);
	cout << (myCPUProgram + myCPUProgram1) << endl;
	cout << myCPUProgram(-5, 10) << endl;
	cout << (myCPUProgram == myCPUProgram1 ? "DONE" : "FAIL") << endl;
//////////////////////////////////////////////////////////////////////////
return 0;
}