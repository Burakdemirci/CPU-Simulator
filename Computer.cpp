/************************/ 
/*	Burak Demirci       */
/*	141044091           */
/************************/

#include "Computer.h"
//Computer constructoru 
Computer::Computer(CPU myCPU, CPUProgram myCPUProgram, Memory myMemory,const int option) 
    //objelerin olusturulmasi
    :myCPU1(option),myCPUProgram1(option),myMemory1(option), option(option)
{	
	//Dosya isminin yer aldıgi objeyi kaybetmemek icin classin icindeki objeya atma islemi
	setCPUProgram(myCPUProgram);
}
//Computer constructoru 
Computer::Computer(const int option)
	:myCPU1(option),myCPUProgram1(option),myMemory1(option), option(option)
{
	//objelerin olusturulmasi 
}
// Dosyadan aldigi veriyi isleyen fonksiyon
void Computer::execute()
{
    //Eger hata yoksa verilen kodu calistirir
    if(myCPUProgram1.CheckError(myCPUProgram1.GetStr())==0)
    {
    	if(getOption()==0 || getOption()==1 || getOption()==2)
    	{
    		//gelen kod halt olana kadar doner
    		while(!myCPU1.halted())
    		{
    			string instruction = myCPUProgram1.getLine(myCPU1.getPC()-1);
                myCPU1.execute(instruction,myMemory1);
    			myCPU1.setPC(myCPU1.getPC()+1);
    		}	
 		}
    	else
      		cerr<<"Wrong input"<<endl;
    } 
}
//CPU objesini getirir
CPU Computer::getCPU()const
{
	return myCPU1;
}
//CPUProgram objesini getirir
CPUProgram Computer::getCPUProgram()const
{
	return myCPUProgram1;
}
//Memory objesini getirir
Memory Computer::getMemory()const
{
	return myMemory1;
}
// Optionu getirir
int Computer::getOption()const
{
	return option;
}
//CPU objesine yeni CPU objesi atar
void Computer::setCPU(CPU myCPU)
{
	myCPU1=myCPU;
}
//CPUProgram objesine yeni CPUProgram objesi atar
void Computer::setCPUProgram(CPUProgram myCPUProgram)
{
	myCPUProgram1=myCPUProgram;
}
//Memory objesine yeni Memory objesi atar
void Computer::setMemory(Memory myMemory)
{
	myMemory1=myMemory;
} 
