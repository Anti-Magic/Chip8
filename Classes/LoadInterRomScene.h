#ifndef __LOADINTERROMSCENE_H__
#define __LOADINTERROMSCENE_H__

#include "cocos2d.h"
#include "BaseLayer.h"
#include "extensions/cocos-ext.h"

class LoadInterRomScene :
	public BaseLayer,
	public cocos2d::extension::TableViewDataSource,
	public cocos2d::extension::TableViewDelegate
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	CREATE_FUNC(LoadInterRomScene);

	virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell) override;
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView* table, ssize_t index) override;
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView* table, ssize_t index) override;
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table) override;

private:
	std::vector<std::string> _interRomsName;
	cocos2d::Size _cellSize;
};

#endif