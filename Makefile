.PHONY : all clean

all: 
	cd Assembler && make
	cd Processor && make
	cd Disassembler && make

clean:
	cd Assembler && make clean
	cd Processor && make clean
	cd Disassembler && make clean