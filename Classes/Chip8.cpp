#include "Chip8.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "cocos2d.h"

USING_NS_CC;

unsigned char fontset[80] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, //0
	0x20, 0x60, 0x20, 0x20, 0x70, //1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
	0x90, 0x90, 0xF0, 0x10, 0x10, //4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
	0xF0, 0x10, 0x20, 0x40, 0x40, //7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
	0xF0, 0x90, 0xF0, 0x90, 0x90, //A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
	0xF0, 0x80, 0x80, 0x80, 0xF0, //C
	0xE0, 0x90, 0x90, 0x90, 0xE0, //D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
	0xF0, 0x80, 0xF0, 0x80, 0x80  //F
};

void Chip8::reset()
{
	reg_pc = 0x200;
	opcode = 0;
	reg_i = 0;
	reg_sp = 0;
	delay_timer = 0;
	sound_timer = 0;
	_drawflag = true;

	memset(memory, 0, sizeof(memory));
	memset(reg, 0, sizeof(reg));
	memset(video_memory, 0, sizeof(video_memory));
	memset(stack, 0, sizeof(stack));
	memset(keys, 0, sizeof(keys));

	for(int i = 0; i < 80; i++) {
		memory[i] = fontset[i];
	}
	srand((unsigned int)time(NULL));
}

bool Chip8::loadRom(const std::string& fileName)
{
	reset();

	Data romData = FileUtils::getInstance()->getDataFromFile(fileName);
	unsigned char* buffer = romData.getBytes();
	ssize_t size = romData.getSize();

	if (0x200 + size > 4096) {
		return false;
	}
	for (int i = 0; i < size; i++) {
		memory[i + 0x200] = buffer[i];
	}
	return true;
}

bool Chip8::getIsDraw()
{
	if (_drawflag) {
		_drawflag = false;
		return true;
	}
	return false;
}

bool Chip8::getIsSound()
{
	if (_soundflag) {
		_soundflag = false;
		return true;
	}
	return false;
}

bool Chip8::getVideo(int x, int y)
{
	return static_cast<bool>(video_memory[x*64 + y]);
}

void Chip8::setKey(int k, unsigned char press)
{
	keys[k] = press;
}

void Chip8::emulateCycle()
{
	opcode = memory[reg_pc] << 8 | memory[reg_pc+1];
	switch(opcode & 0xF000) {
	case 0x0000:
		switch(opcode & 0x000F) {
		case 0x0000:
			op_00E0(); break;
		case 0x000E:
			op_00EE(); break;
		}
		break;
	case 0x1000:
		op_1NNN(); break;
	case 0x2000:
		op_2NNN(); break;
	case 0x3000:
		op_3XNN(); break;
	case 0x4000:
		op_4XNN(); break;
	case 0x5000:
		op_5XY0(); break;
	case 0x6000:
		op_6XNN(); break;
	case 0x7000:
		op_7XNN(); break;
	case 0x8000:
		switch(opcode & 0x000F) {
		case 0x0000:
			op_8XY0(); break;
		case 0x0001:
			op_8XY1(); break;
		case 0x0002:
			op_8XY2(); break;
		case 0x0003:
			op_8XY3(); break;
		case 0x0004:
			op_8XY4(); break;
		case 0x0005:
			op_8XY5(); break;
		case 0x0006:
			op_8XY6(); break;
		case 0x0007:
			op_8XY7(); break;
		case 0x000E:
			op_8XYE(); break;
		}
		break;
	case 0x9000:
		op_9XY0(); break;
	case 0xA000:
		op_ANNN(); break;
	case 0xB000:
		op_BNNN(); break;
	case 0xC000:
		op_CXNN(); break;
	case 0xD000:
		op_DXYN(); break;
	case 0xE000:
		switch(opcode & 0x000F) {
		case 0x000E:
			op_EX9E(); break;
		case 0x0001:
			op_EXA1(); break;
		}
		break;
	case 0xF000:
		switch(opcode & 0x00FF) {
		case 0x0007:
			op_FX07(); break;
		case 0x000A:
			op_FX0A(); break;
		case 0x0015:
			op_FX15(); break;
		case 0x0018:
			op_FX18(); break;
		case 0x001E:
			op_FX1E(); break;
		case 0x0029:
			op_FX29(); break;
		case 0x0033:
			op_FX33(); break;
		case 0x0055:
			op_FX55(); break;
		case 0x0065:
			op_FX65(); break;
		}
	}
	if(delay_timer > 0) {
		--delay_timer;
	}
	if(sound_timer > 0) {
		if(sound_timer == 1) {
			_soundflag = true;
		}
		--sound_timer;
	}
}

void Chip8::op_0NNN()
{
	// Calls RCA 1802 program at address NNN.
}

void Chip8::op_00E0()
{
	memset(video_memory, 0, sizeof(video_memory));
	_drawflag = true;
	reg_pc += 2;
}

void Chip8::op_00EE()
{
	reg_pc = stack[--reg_sp] + 2;
}

void Chip8::op_1NNN()
{
	reg_pc = opcode & 0x0FFF;
}

void Chip8::op_2NNN()
{
	stack[reg_sp++] = reg_pc;
	reg_pc = opcode & 0x0FFF;
}

void Chip8::op_3XNN()
{
	reg_pc += (reg[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF)) ? 4 : 2;
}

void Chip8::op_4XNN()
{
	reg_pc += (reg[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF)) ? 4 : 2;
}

void Chip8::op_5XY0()
{
	reg_pc += (reg[(opcode & 0x0F00) >> 8] == reg[(opcode & 0x00F0) >> 4]) ? 4 : 2;
}

void Chip8::op_6XNN()
{
	reg[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
	reg_pc += 2;
}

void Chip8::op_7XNN()
{
	reg[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
	reg_pc += 2;
}

void Chip8::op_8XY0()
{
	reg[(opcode & 0x0F00) >> 8] = reg[(opcode & 0x00F0) >> 4];
	reg_pc += 2;
}

void Chip8::op_8XY1()
{
	reg[(opcode & 0x0F00) >> 8] |= reg[(opcode & 0x00F0) >> 4];
	reg_pc += 2;
}

void Chip8::op_8XY2()
{
	reg[(opcode & 0x0F00) >> 8] &= reg[(opcode & 0x00F0) >> 4];
	reg_pc += 2;
}

void Chip8::op_8XY3()
{
	reg[(opcode & 0x0F00) >> 8] ^= reg[(opcode & 0x00F0) >> 4];
	reg_pc += 2;
}

void Chip8::op_8XY4()
{
	reg[0xF] = reg[(opcode & 0x00F0) >> 4] > (0xFF - reg[(opcode & 0x0F00) >> 8]);
	reg[(opcode & 0x0F00) >> 8] += reg[(opcode & 0x00F0) >> 4];
	reg_pc += 2;
}

void Chip8::op_8XY5()
{
	reg[0xF] = !(reg[(opcode & 0x00F0) >> 4] > reg[(opcode & 0x0F00) >> 8]);
	reg[(opcode & 0x0F00) >> 8] -= reg[(opcode & 0x00F0) >> 4];
	reg_pc += 2;
}

void Chip8::op_8XY6()
{
	reg[0xF] = reg[(opcode & 0x0F00) >> 8] & 0x1;
	reg[(opcode & 0x0F00) >> 8] >>= 1;
	reg_pc += 2;
}

void Chip8::op_8XY7()
{
	reg[0xF] = !(reg[(opcode & 0x0F00) >> 8] > reg[(opcode & 0x00F0) >> 4]);
	reg[(opcode & 0x0F00) >> 8] = reg[(opcode & 0x00F0) >> 4] - reg[(opcode & 0x0F00) >> 8];
	reg_pc += 2;
}

void Chip8::op_8XYE()
{
	reg[0xF] = reg[(opcode & 0x0F00) >> 8] >> 7;
	reg[(opcode & 0x0F00) >> 8] <<= 1;
	reg_pc += 2; 
}

void Chip8::op_9XY0()
{
	reg_pc += (reg[(opcode & 0x0F00) >> 8] != reg[(opcode & 0x00F0) >> 4]) ? 4 : 2;
}

void Chip8::op_ANNN()
{
	reg_i = opcode & 0x0FFF;
	reg_pc += 2;
}

void Chip8::op_BNNN()
{
	reg_pc = (opcode & 0x0FFF) + reg[0];
}

void Chip8::op_CXNN()
{
	reg[(opcode & 0x0F00) >> 8] = (rand() % 0xFF) & (opcode & 0x00FF);
	reg_pc += 2;
}

void Chip8::op_DXYN()
{
	unsigned short x = reg[(opcode & 0x0F00) >> 8];
	unsigned short y = reg[(opcode & 0x00F0) >> 4];
	unsigned short height = opcode & 0x000F;
	unsigned short pixel = 0;
	reg[0xF] = 0;
	for(int yline = 0; yline < height; yline++) {
		pixel = memory[reg_i+yline];
		for(int xline = 0; xline < 8; xline++) {
			if((pixel & (0x80 >> xline)) != 0) {
				if(video_memory[(x + xline + ((y + yline) * 64))] == 1) {
					reg[0xF] = 1;
				}
				video_memory[x + xline + ((y + yline) * 64)] ^= 1;
			}
		}
	}
	_drawflag = true;
	reg_pc += 2;
}

void Chip8::op_EX9E()
{
	reg_pc += (keys[reg[(opcode & 0x0F00) >> 8]]) ? 4 : 2;
}

void Chip8::op_EXA1()
{
	reg_pc += (keys[reg[(opcode & 0x0F00) >> 8]]) ? 2 : 4;
}

void Chip8::op_FX07()
{
	reg[(opcode & 0x0F00) >> 8] = delay_timer;
	reg_pc += 2;
}

void Chip8::op_FX0A()
{
	bool keyPress = false;

	for(int i = 0; i < 16; i++) {
		if(keys[i] != 0) {
			reg[(opcode & 0x0F00) >> 8] = i;
			keyPress = true;
		}
	}

	if(!keyPress) {
		return;
	}
	reg_pc += 2;
}

void Chip8::op_FX15()
{
	delay_timer = reg[(opcode & 0x0F00) >> 8];
	reg_pc += 2;
}

void Chip8::op_FX18()
{
	sound_timer = reg[(opcode & 0x0F00) >> 8];
	reg_pc += 2;
}

void Chip8::op_FX1E()
{
	reg[0xF] = (reg_i + reg[(opcode & 0x0F00) >> 8]) > 0xFFF;
	reg_i += reg[(opcode & 0x0F00) >> 8];
	reg_pc += 2;
}

void Chip8::op_FX29()
{
	reg_i = reg[(opcode & 0x0F00) >> 8] * 0x5;
	reg_pc += 2;
}

void Chip8::op_FX33()
{
	unsigned short vx = reg[(opcode & 0x0F00) >> 8];
	memory[reg_i] = vx / 100;
	memory[reg_i+1] = vx / 10 % 10;
	memory[reg_i+2] = vx % 10;
	reg_pc += 2;
}

void Chip8::op_FX55()
{
	unsigned short x = (opcode & 0x0F00) >> 8;
	for(int i = 0; i <= x; i++) {
		memory[reg_i+i] = reg[i];
	}
	reg_i += ((opcode & 0x0F00) >> 8) + 1;
	reg_pc += 2;
}

void Chip8::op_FX65()
{
	unsigned short x = (opcode & 0x0F00) >> 8;
	for(int i = 0; i <= x; i++) {
		reg[i] = memory[reg_i+i];
	}
	reg_i += ((opcode & 0x0F00) >> 8) + 1;
	reg_pc += 2;
}