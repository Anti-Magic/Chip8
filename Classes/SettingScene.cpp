#include "SettingScene.h"
#include "Config.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* SettingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SettingScene::create();
	scene->addChild(layer);
	return scene;
}

bool SettingScene::init()
{
	if (!BaseLayer::init()) {
		return false;
	}

	auto strings = FileUtils::getInstance()->getValueMapFromFile("strings.xml");
	auto visSize = Director::getInstance()->getVisibleSize();
	
	auto rateTip = Label::createWithSystemFont(strings["rate"].asString(), "Consolas", 30);
	rateTip->setPosition(rateTip->getContentSize().width / 2 + 10, 600);
	addChild(rateTip, 1);

	auto rateString = String::createWithFormat("%d", Config::getInstance()->getRate());
	_rateLabel = Label::createWithSystemFont(rateString->getCString(), "Consolas", 30);
	_rateLabel->setPosition(visSize.width - _rateLabel->getContentSize().width / 2 - 10, 600);
	addChild(_rateLabel, 1);
	
	ControlSlider* rateSlider = ControlSlider::create(
		"sliderTrack.png", "sliderProgress.png", "sliderThumb.png");
	rateSlider->setPosition(visSize.width / 2, 500);
	rateSlider->setMinimumValue(1.0f);
	rateSlider->setMaximumValue(10.0f);
	rateSlider->setValue(Config::getInstance()->getRate());
	rateSlider->addTargetWithActionForControlEvents(this,
		cccontrol_selector(SettingScene::rateSliderValueChanged), 
		Control::EventType::VALUE_CHANGED);
	addChild(rateSlider, 1);
	
	auto soundTip = Label::createWithSystemFont(strings["issound"].asString(), "Consolas", 30);
	soundTip->setPosition(soundTip->getContentSize().width / 2 + 10, 400);
	addChild(soundTip, 1);
	
	/*ControlSwitch *soundSwitch = ControlSwitch::create(
		Sprite::create("switch-mask.png"),
		Sprite::create("switch-on.png"),
		Sprite::create("switch-off.png"),
		Sprite::create("switch-thumb.png"),
		Label::createWithSystemFont("On", "Consolas", 20),
		Label::createWithSystemFont("Off", "Consolas", 20));
	soundSwitch->setPosition(visSize.width - soundSwitch->getContentSize().width / 2 - 10, 400);
	soundSwitch->setOn(Config::getInstance()->getSound());
	addChild(soundSwitch, 0);*/

	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 10);

	auto btn_ok = MenuItemImage::create(
		"button_n.png",
		"button_p.png",
		"button_p.png",
		[=](Ref* sender) {
		Config::getInstance()->setRate(Value(_rateLabel->getString()).asInt());
		//Config::getInstance()->setSound(soundSwitch->isOn());
		Director::getInstance()->popScene();
	});
	Vec2 pos_ok(150, 100);
	btn_ok->setPosition(pos_ok);
	btn_ok->setScale(1.5f);
	auto lbl_ok = Label::createWithSystemFont(strings["ok"].asString(), "Consolas", 30);
	lbl_ok->setPosition(pos_ok);
	addChild(lbl_ok, 10);
	menu->addChild(btn_ok, 1);
	
	return true;
}

void SettingScene::rateSliderValueChanged(Ref *sender, Control::EventType controlEvent)
{
	ControlSlider* rateSlider = dynamic_cast<ControlSlider*>(sender);
	if (rateSlider != nullptr) {
		_rateLabel->setString(String::createWithFormat("%.0f", rateSlider->getValue())->getCString());
	}
}
