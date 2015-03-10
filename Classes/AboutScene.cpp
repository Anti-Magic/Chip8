#include "AboutScene.h"

USING_NS_CC;

Scene* AboutScene::createScene()
{
	auto scene = Scene::create();
	auto layer = AboutScene::create();
	scene->addChild(layer);
	return scene;
}

bool AboutScene::init()
{
	if (!BaseLayer::init()) {
		return false;
	}
	auto strings = FileUtils::getInstance()->getValueMapFromFile("strings.xml");
	auto visSize = Director::getInstance()->getVisibleSize();

	auto help_content = Label::createWithSystemFont(strings["help_content"].asString(), "Consolas", 30);
	help_content->setPosition(visSize.width / 2, visSize.height / 2 + 100);
	help_content->setLineBreakWithoutSpace(true);
	help_content->setWidth(400);
	addChild(help_content, 1);

	auto about_content = Label::createWithSystemFont(strings["about_content"].asString(), "Consolas", 30);
	about_content->setPosition(visSize.width / 2, visSize.height / 2);
	about_content->setLineBreakWithoutSpace(true);
	about_content->setWidth(400);
	addChild(about_content, 1);

	auto version = Label::createWithSystemFont(strings["version"].asString(), "Consolas", 30);
	version->setPosition(visSize.width / 2, visSize.height / 2 - 100);
	version->setLineBreakWithoutSpace(true);
	version->setWidth(400);
	addChild(version, 1);

	return true;
}