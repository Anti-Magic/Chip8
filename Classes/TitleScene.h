#ifndef __TITLESCENE_H__
#define __TITLESCENE_H__

#include "cocos2d.h"

class TitleScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;
	CREATE_FUNC(TitleScene);
private:
	void addOneButton(const char* key, const cocos2d::Vec2& pos, 
		const cocos2d::ccMenuCallback& callback);
	cocos2d::ValueMap _strings;
	cocos2d::Menu* _buttons;
};

#endif