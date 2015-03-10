#ifndef __ABOUTSCENE_H__
#define __ABOUTSCENE_H__

#include "cocos2d.h"
#include "BaseLayer.h"

class AboutScene : public BaseLayer
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;
	CREATE_FUNC(AboutScene);
private:
};

#endif