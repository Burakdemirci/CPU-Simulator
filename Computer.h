/************************/ 
/*	Burak Demirci       */
/*	141044091           */
/************************/

#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"

#ifndef Computer_H
#define Computer_H

class Computer
{
public:
	//Computer constructoru 
	Computer(CPU , CPUProgram , Memory ,const int );
	//Computer constructoru 
	Computer(const int);
	// Dosyadan aldigi veriyi isleyen fonksiyon
	void execute();
	//CPU objesini getirir
	CPU getCPU()const;
	//CPUProgram objesini getirir
    CPUProgram getCPUProgram()const;
    //Memory objesini getirir
	Memory getMemory()const;
	//Option'u getirir
	int getOption()const;
	//CPU objesine yeni CPU objesi atar
	void setCPU(CPU);
	//CPUProgram objesine yeni CPUProgram objesi atar
	void setCPUProgram(CPUProgram);
	//Memory objesine yeni Memory objesi atar
	void setMemory(Memory);
	
private:
	//option degiskeni
	int option;
	//CPU objesi
	CPU myCPU1;
	//CPUProgram objesi
	CPUProgram myCPUProgram1;
	//Memory objesi
	Memory myMemory1;
};

#endif //Computer_H