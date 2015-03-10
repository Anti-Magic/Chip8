#include "PlayScene.h"
#include "Config.h"

USING_NS_CC;

Scene* PlayScene::createScene(const std::string& rom)
{
	auto scene = Scene::create();
	auto layer = PlayScene::create(rom);
	scene->addChild(layer);
	return scene;
}

PlayScene* PlayScene::create(const std::string& rom)
{
	PlayScene *pRet = new PlayScene();
	if (pRet && pRet->initWithRom(rom)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool PlayScene::initWithRom(const std::string& rom)
{
	if(!Layer::init()) {
		return false;
	}

	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyReleased = [](EventKeyboard::KeyCode keycode, Event* event) {
		if (keycode == EventKeyboard::KeyCode::KEY_BACKSPACE || keycode == EventKeyboard::KeyCode::KEY_ESCAPE) {
			Director::getInstance()->popScene();
		}
	};
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

	if (!_chip8.loadRom(rom)) {
		auto strings = FileUtils::getInstance()->getValueMapFromFile("strings.xml");
		auto visSize = Director::getInstance()->getVisibleSize();
		auto rom_error = Label::createWithSystemFont(strings["rom_error"].asString(), "Consolas", 30);
		rom_error->setPosition(visSize.width / 2, visSize.height / 2);
		rom_error->setLineBreakWithoutSpace(true);
		rom_error->setWidth(400);
		addChild(rom_error, 1);
		return true;
	}
	_rate = Config::getInstance()->getRate();
	_hassound = Config::getInstance()->getSound();

	/*auto bg = Sprite::create("bg.png");
	auto size = bg->getContentSize();
	bg->setScale(480.0f / size.width, 800.0f / size.height);
	bg->setPosition(240, 400);
	addChild(bg, 1);*/

	auto blackFrame = SpriteFrame::create("black.png", Rect(0, 0, 64, 64));
	SpriteFrameCache::getInstance()->addSpriteFrame(blackFrame, "black");
	for(int i = 0; i < 32; ++i) {
		for(int j = 0; j < 64; ++j) {
			_block[i][j] = Sprite::createWithSpriteFrameName("black");
			_block[i][j]->setScale(7.5f / 64);
			_block[i][j]->setAnchorPoint(Vec2(0, 1));
			_block[i][j]->setPosition(j*7.5, 700.0f - i*7.5);
			_block[i][j]->setVisible(false);
			addChild(_block[i][j], 10);
		}
	}

	initKeys();
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [=](Touch* touch, Event* event) {
		auto pos = touch->getLocation();
		for(int i = 0; i < 16; i++) {
			if(_keys[i]->getBoundingBox().containsPoint(pos)) {
				_chip8.setKey(i, 1);
				break;
			}
		}
		return true;
	};
	touchListener->onTouchEnded = [=](Touch* touch, Event* event) {
		auto pos = touch->getLocation();
		for(int i = 0; i < 16; i++) {
			if(_keys[i]->getBoundingBox().containsPoint(pos)) {
				_chip8.setKey(i, 0);
				break;
			}
		}
	};

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	scheduleUpdate();
	return true;
}

void PlayScene::addOneKey(int index, const std::string& content, const Vec2& pos)
{
	_keys[index] = Sprite::create("button_n.png");
	_keys[index]->setPosition(pos);
	addChild(_keys[index], 20);
	auto label = Label::createWithSystemFont(
		content, "Consolas", 30);
	label->setPosition(_keys[index]->getPosition());
	addChild(label, 25);
}

void PlayScene::initKeys()
{
	// 0x0
	addOneKey(0, "0", Vec2(171, 70));
	// 0x1 ~ 0x9
	for(int i = 0; i < 3; i++) {
		int y = 200 - i * 50 + 20;
		for(int j = 0; j < 3; j++) {
			int x = j * 120 + 51;
			int index = i * 3 + j + 1;
			addOneKey(index, Value(index).asString(), Vec2(x, y));
		}
	}
	// 0xA
	addOneKey(0xA, "A", Vec2(51, 70));
	// 0xB
	addOneKey(0xB, "B", Vec2(291, 70));
	// 0xC ~ 0xF
	for(int i = 0; i < 4; i++) {
		int x = 3 * 120 + 51;
		int y = 200 - i * 50 + 20;
		int index = 0xC + i;
		char content[2] = {static_cast<char>('C' + i), '\0'};
		addOneKey(index, content, Vec2(x, y));
	}
}

void PlayScene::update(float dlt)
{
	for(int i = 0; i < _rate; i++) {
		_chip8.emulateCycle();
		if(_chip8.getIsDraw()) {
			drawDisplay();
		}
		if (_hassound && _chip8.getIsSound()) {
			// sound
		}
	}
}

void PlayScene::drawDisplay()
{
	for(int i = 0; i < 32; ++i) {
		for(int j = 0; j < 64; ++j) {
			_block[i][j]->setVisible(_chip8.getVideo(i, j));
		}
	}
}
