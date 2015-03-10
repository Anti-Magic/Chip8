#ifndef __PLAYSCENE_H__
#define __PLAYSCENE_H__

#include "cocos2d.h"
#include "Chip8.h"

class PlayScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(const std::string& rom);
	static PlayScene* create(const std::string& rom);
	bool initWithRom(const std::string& rom);
private:
	void update(float dlt) override;
	void drawDisplay();

	void initKeys();
	void addOneKey(int index, const std::string& content, const cocos2d::Vec2& pos);

	cocos2d::Sprite* _block[32][64];
	cocos2d::Sprite* _keys[16];

	Chip8 _chip8;
	int _rate;
	bool _hassound;
};

#endif