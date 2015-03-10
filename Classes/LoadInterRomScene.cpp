#include "LoadInterRomScene.h"
#include "PlayScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

const int tag_lbl_name = 100;
const int tag_lbl_count = 101;

Scene* LoadInterRomScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadInterRomScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoadInterRomScene::init()
{
	if (!BaseLayer::init()) {
		return false;
	}

	_cellSize = Size(400, 100);

	_interRomsName.push_back("15PUZZLE");
	_interRomsName.push_back("ALIEN");
	_interRomsName.push_back("ANT");
	_interRomsName.push_back("BLINKY");
	_interRomsName.push_back("BLITZ");
	_interRomsName.push_back("BREAKOUT");
	_interRomsName.push_back("BRIX");
	_interRomsName.push_back("CAR");
	_interRomsName.push_back("CONNECT4");
	_interRomsName.push_back("FIELD");
	_interRomsName.push_back("GUESS");
	_interRomsName.push_back("HIDDEN");
	_interRomsName.push_back("INVADERS");
	_interRomsName.push_back("JOUST");
	_interRomsName.push_back("KALEID");
	_interRomsName.push_back("MAZE");
	_interRomsName.push_back("MERLIN");
	_interRomsName.push_back("MISSILE");
	_interRomsName.push_back("PIPER");
	_interRomsName.push_back("PONG");
	_interRomsName.push_back("PONG2");
	_interRomsName.push_back("PUZZLE");
	_interRomsName.push_back("RACE");
	_interRomsName.push_back("SPACEFIG");
	_interRomsName.push_back("SQUASH");
	_interRomsName.push_back("SYZYGY");
	_interRomsName.push_back("TANK");
	_interRomsName.push_back("TETRIS");
	_interRomsName.push_back("TICTAC");
	_interRomsName.push_back("UBOAT");
	_interRomsName.push_back("UFO");
	_interRomsName.push_back("VBRIX");
	_interRomsName.push_back("VERS");
	_interRomsName.push_back("WALL");
	_interRomsName.push_back("WIPEOFF");
	_interRomsName.push_back("WORM3");

	Size visSize = Director::getInstance()->getVisibleSize();
	TableView* tableView = TableView::create(this, visSize);
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	Size tabelSize = tableView->getContentSize();
	tableView->setPosition(Vec2((visSize.width - _cellSize.width) / 2, 150));
	tableView->setViewSize(Size(400, 500));
	tableView->setDelegate(this);
	this->addChild(tableView, 10);
	tableView->reloadData();

	return true;
}

void LoadInterRomScene::tableCellTouched(TableView* table, TableViewCell* cell)
{
	std::string rom = "Roms/" + _interRomsName[static_cast<int>(cell->getIdx())];
	std::string path = FileUtils::getInstance()->fullPathForFilename(rom);
	auto scene = PlayScene::createScene(path);
	Director::getInstance()->pushScene(scene);
}

Size LoadInterRomScene::tableCellSizeForIndex(TableView* table, ssize_t index)
{
	return _cellSize;
}

TableViewCell* LoadInterRomScene::tableCellAtIndex(TableView* table, ssize_t index)
{
	auto count = String::createWithFormat("%ld", index);
	TableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new TableViewCell();
		cell->autorelease();

		auto cellBackGround = Scale9Sprite::create("TableCell.png");
		cellBackGround->setContentSize(_cellSize);
		cellBackGround->setAnchorPoint(Vec2::ZERO);
		cellBackGround->setPosition(Vec2::ZERO);
		cell->addChild(cellBackGround);

		auto lbl_name = Label::createWithSystemFont(
			_interRomsName[static_cast<int>(index)], "Consolas", 30.0f);
		lbl_name->setPosition(_cellSize.width / 2, _cellSize.height / 2);
		lbl_name->setTag(tag_lbl_name);
		cell->addChild(lbl_name, 1);

		auto lbl_count = Label::createWithSystemFont(count->getCString(), "Consolas", 20.0f);
		lbl_count->setPosition(Vec2(20, 20));
		lbl_count->setAnchorPoint(Vec2::ZERO);
		lbl_count->setTag(tag_lbl_count);
		cell->addChild(lbl_count);
	}
	else {
		auto lbl_count = dynamic_cast<Label*>(cell->getChildByTag(tag_lbl_count));
		lbl_count->setString(count->getCString());
		auto lbl_name = dynamic_cast<Label*>(cell->getChildByTag(tag_lbl_name));
		lbl_name->setString(_interRomsName[static_cast<int>(index)]);
	}
	return cell;
}

ssize_t LoadInterRomScene::numberOfCellsInTableView(TableView *table)
{
	return _interRomsName.size();
}
