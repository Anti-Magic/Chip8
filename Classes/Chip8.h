#ifndef __CHIP8_H__
#define __CHIP8_H__

#include <string>

class Chip8
{
public:
	void emulateCycle();
	bool loadRom(const std::string& fileName);
	
	bool getIsDraw();
	bool getIsSound();

	bool getVideo(int x, int y);
	void setKey(int k, unsigned char press);

private:
	unsigned char video_memory[64 * 32];
	unsigned char keys[16];
	
	bool _drawflag;
	bool _soundflag;

	unsigned short opcode;
	unsigned short reg_pc;
	unsigned short reg_i;
	unsigned short reg_sp;

	unsigned char reg[16];
	unsigned short stack[16];
	unsigned char memory[4096];

	unsigned char delay_timer;
	unsigned char sound_timer;
	
	void reset();
	// opcodes
	inline void op_0NNN();
	inline void op_00E0();
	inline void op_00EE();
	inline void op_1NNN();
	inline void op_2NNN();
	inline void op_3XNN();
	inline void op_4XNN();
	inline void op_5XY0();
	inline void op_6XNN();
	inline void op_7XNN();
	inline void op_8XY0();
	inline void op_8XY1();
	inline void op_8XY2();
	inline void op_8XY3();
	inline void op_8XY4();
	inline void op_8XY5();
	inline void op_8XY6();
	inline void op_8XY7();
	inline void op_8XYE();
	inline void op_9XY0();
	inline void op_ANNN();
	inline void op_BNNN();
	inline void op_CXNN();
	inline void op_DXYN();
	inline void op_EX9E();
	inline void op_EXA1();
	inline void op_FX07();
	inline void op_FX0A();
	inline void op_FX15();
	inline void op_FX18();
	inline void op_FX1E();
	inline void op_FX29();
	inline void op_FX33();
	inline void op_FX55();
	inline void op_FX65();
};

#endif