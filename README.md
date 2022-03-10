# The Grand Mystery

I have a backup of my work (as far as I'm aware) from every class I've ever taken at both Portland Community College and Willamette University... except, somehow, my very first semester at WU... What!? Where!? How!? 😑 *sigh*...

## What Probably Happened

My best guess: I must have deleted the original folder thinking it had been backed up already.

Around the time I entered university I got a new computer and moved all of my data from my old machine to the new one. I *also* cleaned up my backup drive and put in place new scripts for backing up and compressing my data to it. Unfortunately, I didn't find the gap in my data backup until more recently when I wanted to add the virtual machine and assembler I built in my Architecture and Compilers class to my Homework Graveyard repo. It's been years since that first class and only Past Me knows what happened to the originals. Too bad I don't have that guys number.

## What Now?

In trying to contact my university professor and adviser I found out that he "retired" just after I graduated. (I wonder what happened... 😬) Luckily, the vast majority of his assignments were online and could still be downloaded from the school. So, I've done just that, and I'd like to rebuild the VM I made for fun and practice. After that I think I'll build a better one, but I want a refresher first.

# The Project

## PC-231

Professor Fritz Ruehr came up with a number of virtual machines over the years and the one he picked for my class was the PC-231 (named after the class he was teaching when he first built it himself).

The PC-231 is a 12-bit computer with 16 fixed-width CPU instructions and 256 12-bit words of RAM. It is also a stored-program computer where programs instructions are also considered data and stored in RAM.

The CPU has 16 registers: 10 general purpose registers, 4 jump registers, a single data register, and a modifiable program counter.

| Register Name          	| Register Code 	| Hex   	| Mnemonic 	|
|------------------------	|---------------	|-------	|----------	|
| General Registers      	| 0000 - 1001   	| 0 - 9 	| R0 - R9  	|
| Address/Jump Registers 	| 1010 - 1101   	| A - D 	| J0 - J3  	|
| The Data Register      	| 1110          	| E     	| DR       	|
| The Program Counter    	| 1111          	| F     	| PC       	|


| Code  	| HEX 	| Mnemonic 	| Argument format 	| Description                                                             	|
|-------	|-----	|----------	|-----------------	|-------------------------------------------------------------------------	|
| 0000  	| 0   	| HALT     	| `---- ----`       	| Halts the machine                                                       	|
| 0001  	| 1   	| ZERO     	| `RRRR ----`       	| Zeroes (or "clears") out register RRRR                                  	|
| 0010  	| 2   	| SET      	| `RRRR BBBB`       	| Sets the 4 lowest-order bits of register RRRR to BBBB                   	|
| 0011  	| 3   	| DATA     	| `BBBB BBBB`       	| Clears the data register DR, then sets its 8 lowest-order bits          	|
| 0100  	| 4   	| INC      	| `RRRR sNNN`       	| Adds or subtracts from 1 to 8 from register RRRR                        	|
| 0101  	| 5   	| SHIFT    	| `RRRR sNNN`       	| Shifts register RRRR left (-) or right (+) by from 1 to 8 bits          	|
| 0110  	| 6   	| ADD      	| `RRR1 RRR2`       	| Adds the contents of register RRR1 to RRR2 (result in RRR2)             	|
| 0111  	| 7   	| SUB      	| `RRR1 RRR2`       	| Subtracts the contents of register RRR1 from RRR2 (result in RRR2)      	|
| 1000  	| 8   	| AND      	| `RRR1 RRR2`       	| Logically ANDs the contents of register RRR1 into RRR2 (result in RRR2) 	|
| 1001  	| 9   	| COPY     	| `RRR1 RRR2`       	| Copies the contents of register RRR1 to RRR2                            	|
| 1010  	| A   	| LOAD     	| `RRR1 RRR2`       	| Loads the contents of location addressed by RRR2 into register RRR1     	|
| 1011  	| B   	| STORE    	| `RRR1 RRR2`       	| Stores the contents of register RRR1 into location addressed by RRR2    	|
| 1100  	| C   	| READ     	| `RRRR DDDD`       	| Reads a value (up to 12 bits) into register RRRR from device DDDD       	|
| 1101  	| D   	| WRITE    	| `RRRR DDDD`       	| Writes a value (up to 12 bits) from register RRRR to device DDDD        	|
| 1110  	| E   	| JPIF     	| `RRRR CCJJ`       	| If contents of RRRR meet condition CC, jump to address in JJ            	|
| 1111  	| F   	| JUMP     	| `AAAA AAAA`       	| Jump directly to the location whose address is AAAA AAAA                	|