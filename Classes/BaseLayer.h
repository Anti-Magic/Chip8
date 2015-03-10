#ifndef __BASELAYER_H__
#define __BASELAYER_H__

#include "cocos2d.h"

class BaseLayer : public cocos2d::Layer
{
public:
	virtual bool init() override;
	virtual ~BaseLayer() {}
};

#endif