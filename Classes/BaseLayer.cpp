#include "BaseLayer.h"

USING_NS_CC;

bool BaseLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	auto strings = FileUtils::getInstance()->getValueMapFromFile("strings.xml");
	//auto visSize = Director::getInstance()->getVisibleSize();

	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 10);

	auto btn_back = MenuItemImage::create(
		"button_n.png",
		"button_p.png",
		"button_p.png",
		[](Ref* sender) {
		Director::getInstance()->popScene();
	});
	Vec2 pos_back(330, 100);
	btn_back->setPosition(pos_back);
	btn_back->setScale(1.5f);
	auto lbl_back = Label::createWithSystemFont(strings["back"].asString(), "Consolas", 30);
	lbl_back->setPosition(pos_back);
	addChild(lbl_back, 10);
	menu->addChild(btn_back, 1);

	return true;
}