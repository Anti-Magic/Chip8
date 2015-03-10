#ifndef __SETTINGSCENE_H__
#define __SETTINGSCENE_H__

#include "cocos2d.h"
#include "BaseLayer.h"
#include "extensions/cocos-ext.h"

class SettingScene : public BaseLayer
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;
	CREATE_FUNC(SettingScene);
private:
	void rateSliderValueChanged(cocos2d::Ref *sender, 
		cocos2d::extension::Control::EventType controlEvent);

	void soundSwitchValueChanged(cocos2d::Ref *sender,
		cocos2d::extension::Control::EventType controlEvent);

	cocos2d::Label* _rateLabel;
	cocos2d::Label* _soundLabel;
};

#endif