#include "LoadSdcardRomScene.h"
#include "PlayScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

const int tag_lbl_name = 100;
const int tag_lbl_count = 101;

Scene* LoadSdcardRomScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadSdcardRomScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoadSdcardRomScene::init()
{
	if (!BaseLayer::init()) {
		return false;
	}

	//_interRomsName.push_back("15PUZZLE");
	//_interRomsName.push_back("ALIEN");
	//_interRomsName.push_back("ANT");

	if (_sdcardRomsName.empty()) {
		
	}
	else {
		_cellSize = Size(400, 100);
		Size visSize = Director::getInstance()->getVisibleSize();
		TableView* tableView = TableView::create(this, visSize);
		tableView->setDirection(ScrollView::Direction::VERTICAL);
		Size tabelSize = tableView->getContentSize();
		tableView->setPosition(Vec2((visSize.width - _cellSize.width) / 2, 150));
		tableView->setViewSize(Size(400, 500));
		tableView->setDelegate(this);
		this->addChild(tableView, 10);
		tableView->reloadData();
	}

	return true;
}

void LoadSdcardRomScene::tableCellTouched(TableView* table, TableViewCell* cell)
{
	std::string rom = "Roms/" + _sdcardRomsName[static_cast<int>(cell->getIdx())];
	auto scene = PlayScene::createScene(rom);
	Director::getInstance()->replaceScene(scene);
}

Size LoadSdcardRomScene::tableCellSizeForIndex(TableView* table, ssize_t index)
{
	return _cellSize;
}

TableViewCell* LoadSdcardRomScene::tableCellAtIndex(TableView* table, ssize_t index)
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
			_sdcardRomsName[static_cast<int>(index)], "Consolas", 30.0f);
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
		lbl_name->setString(_sdcardRomsName[static_cast<int>(index)]);
	}
	return cell;
}

ssize_t LoadSdcardRomScene::numberOfCellsInTableView(TableView *table)
{
	return _sdcardRomsName.size();
}