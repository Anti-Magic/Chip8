#Chip8模拟器
Chip8只有35条指令，属于RISC指令集[维基百科](http://zh.wikipedia.org/wiki/精简指令集)，4k内存，2k显存，19个寄存器，支持16个按键，没有中断，但是有两个计时器。

模拟器需要大量的位运算，所以用Java做android原生应用不太方便，所以选择支持C++的Cocos2d-x。
