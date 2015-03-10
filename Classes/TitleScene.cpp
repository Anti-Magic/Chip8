#include "TitleScene.h"
#include "LoadInterRomScene.h"
#include "LoadSdcardRomScene.h"
#include "SettingScene.h"
#include "AboutScene.h"

USING_NS_CC;

Scene* TitleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TitleScene::create();
	scene->addChild(layer);
	return scene;
}

bool TitleScene::init()
{
	if(!Layer::init()) {
		return false;
	}
	_strings = FileUtils::getInstance()->getValueMapFromFile("strings.xml");
	_buttons = Menu::create();
	_buttons->setPosition(Vec2::ZERO);
	addChild(_buttons, 10);
	auto visSize = Director::getInstance()->getVisibleSize();
	addOneButton("loadInterRom", Vec2(visSize.width / 2, 600), [](Ref* sender) {
		auto scene = LoadInterRomScene::createScene();
		Director::getInstance()->pushScene(scene);
	});
	addOneButton("loadSdcardRom", Vec2(visSize.width / 2, 500), [](Ref* sender) {
		auto scene = LoadSdcardRomScene::createScene();
		Director::getInstance()->pushScene(scene);
	});
	addOneButton("setting", Vec2(visSize.width / 2, 400), [](Ref* sender) {
		auto scene = SettingScene::createScene();
		Director::getInstance()->pushScene(scene);
	});
	addOneButton("about", Vec2(visSize.width / 2, 300), [](Ref* sender) {
		auto scene = AboutScene::createScene();
		Director::getInstance()->pushScene(scene);
	});
	addOneButton("exit", Vec2(visSize.width / 2, 200), [](Ref* sender) {
		Director::getInstance()->end();
	});
	return true;
}

void TitleScene::addOneButton(const char* key, const cocos2d::Vec2& pos,
	const cocos2d::ccMenuCallback& callback)
{
	auto button = MenuItemImage::create(
		"button_n.png",
		"button_p.png",
		"button_p.png",
		callback);
	button->setPosition(pos);
	button->setScale(2.5);
	auto label = Label::createWithSystemFont(_strings[key].asString(), "Consolas", 30);
	label->setPosition(pos);
	addChild(label, 20);
	_buttons->addChild(button, 1);
}