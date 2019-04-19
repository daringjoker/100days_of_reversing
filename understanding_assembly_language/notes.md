# Understanding __Assembly__ language 

## 1. empty function 
* in *x86 or x64* the __ret__ keyword can serve for returning control flow to the parent or calling module which uses the return address saved on the stack.


* in *AVR* this is done by using the same __ret__ keyword however the control flow is diffrent as there is no diffrent main and entry function.  


* in *arm*  the simple return is used by jumping to the return address this is because unlike the above architectures it doesnot use stack to store the return address instread it is stored in lr register. The jump is done using branch instruction ie __bx__ command so the __ret__ equivalent for arm would be 


### for x86 ,x64 and AVR :
```assembly
 ret
```
### for ARM :
```assembly
 bx lr ; lr = link register and bx = branch and exchange
```
___
## 2. returning value
* In __x86 or x64__ Architectures the return value of the function is stored in the _EAX_ / _RAX_ register . hence to return some value the value is simply moved to this register before the _ret_ instruction.

* In __AVR__  the return value is stored in multiple register since they have only 8bit registers and for 
int in c they require 16 bits of space so the registers used are _r25_ and _r24_. Also the _lo8()_ and _hi8()_ are used to segregate the 16 bit no to 8 lower and 8 higher bits and _ldi_  (load immidiate) is used to copy values to the registers. then calling the _ret_ instruction does the job.

* In __ARM__ Architecture the _r0_ register is used to store the return value so to return the value the value is first moved into _r0_ and then the _bx lr_ is used to return the control flow.

> __NOTE:__   
whenever the value to be returned is larger than the size of the register used in that architecture the return value is stored in a set of registers.  
__for X86 arch__ :- _EDX_ : _EAX_ is used  
__for AVR arch__ :- _r18_ : _r19_ : _r20_ : _r21_ : _r22_ : _r23_ :_r24_ : _r25_ is used since they are each 8 bit registers.  
__for ARM arch__ :- _r0_ :_r1_ is used for 64 bit value and _r0_ is used for value upto 32 bits.

### for x86 architecture
```assembly
mov eax, 123 ; copy value 123 to eax
ret
```
### for x64 architecture
```assembly
mov rax, 123
ret
```
### for AVR architecture
```assembly
ldi r24, lo8(123) ;copy lower 8 bits to r24
ldi r25, hi8(123) ;copy higher 8 bits to r25
ret
```
### for ARM architecture
```assembly
mov r0, #123
bx  lr
```
___
## 3. Hello world
> __NOTE__:  
The argumernt for functions are passed as discussed in the [architecture details](arch_details.md) section.
* In x86 and x64 architecture function call are invoked by _call_ instruction . To print in x64 0r x86 architecture we can use libc printf function or we can use _write_ syscall to write into the _std out_  in linux or use _WriteConsole_ syscall in windows.  
* In avr the technique is same for using syscall but as the machine is 8 bit but uses the 16 bit addressing space the function argument is passed in 2 registers and _rcall_ (relative call) is used to call the subroutine.  There is no other better way to achive this since avr is not usually used with operating systems.

* In ARM architecture the argument is passed in the _r0_ using _ldr_( load register ) and to call the puts _b_ ( branch ) instruction is used.

### for x86 and x64 arch
```assembly
.LC0:
  .string "hello world"
main:
  mov edi, OFFSET FLAT:.LC0
  jmp puts  ;since string doesnot have any format characters gcc optimizes to use the puts instead of printf
  ```
### for AVR arch
```assembly
.LC0:
  .string "hello world"
main:
  ldi r24,lo8(.LC0)
  ldi r25,hi8(.LC0)
  rcall puts
  ret
```
### for ARM arch
```assembly
main:
  ldr r0, .L2
  b puts
.L2:
  .word .LC0
.LC0:
  .ascii "hello world\000"
 ```
___





