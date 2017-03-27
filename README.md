# CPU-Simulator
CPU Simulator written in C++
This project based on C++14

-This project contains some OOP techniques:
1)Objects and classes
2)Composition
3)Encapsulation
...

-Attributes
1)Vectors and operator overloading
2)Text based assembly Coding
3)Text parsing
4)Some basic CPU Instruction's Implementation


------------------
Move instructions
MOV reg, address
MOV address, reg
MOV address, constant
For example MOV R1, #45 copies the value of register 1 to memory location 45
-----------------
Addition and Subtraction insructions
ADD reg, address
SUB reg, address
For example, ADD R1, #45 adds the value of memory location 45 to register 1
-----------------
Print instructions
PRN address
For example, PRN #56 will print the value of the memory loacation 56 to the screen, after each print
a new line should be inserted.
-----------------
Jump instruction
JPN reg, lineAdress
JPN R1, 32 jumps to line 32 of the program if the value of R1 is zero or smaller.
New example for clarification
SUB R1, R2 subtracts the value of register 2 from register 1 and puts the result into register 1

HLT
halts the program and prints on the screen the contents of all registers as well as the the memory.Your program will run using the same command line parameters as HW1. However, we have a new
option

Operator[] that takes an integer and works like the getLine function. It returns the program
line as a string.
• Operator+ that takes a CPUProgram and an instruction line as a string. It returns a new
CPUProgram that has the original CPUProgram with appended last line from the parameter
string.
• Operator+= that takes an instruction line as a string and appends the instruction to the end of
the program.
• Operator+ that takes two programs and returns a new program that appends the second
programs to the first one
• All comparison operators ==, !=, <, >=, etc. All comparison operators compare the number of
lines of the programs.
• Operator>> that prints the program
• Post and pre decrement operators - - that delete the last line of the program.
• Function call operator() that takes two integers and returns a new program that contains the
instructions between the given integer

--------------------------------------------------
The format for the command line parameters is as follows
yourProg filename option
yourProg is the name of your executable file, file name is the text file that contains your simple CPU
instructions, option a number and the defines the how your program runs as follows
• if option is 0, your program will run and finish by executing each instruction
• if option is 1, your program will execute each instruction after displaying the instruction first.
It also will print the contents of all the registers.
• If option is 2, your program will execute each instruction just like the option 1. This option
will also print the contents of the memory after each intruction execution.
