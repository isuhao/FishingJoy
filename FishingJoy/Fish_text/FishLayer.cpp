//该层包含的唯一元素是带有动画效果的鱼

#include "FishLayer.h"
#include "Fish.h"

USING_NS_CC;

bool FishLayer::init()
{
	if (CCLayer::init())
	{
		int capacity = 50;
		_fishes = CCArray::createWithCapacity(capacity);//存储预先生成的鱼（预加载技术）；预先存储游戏者大量出现的物体，如子弹、一定时间后生成的怪物
		CC_SAFE_RETAIN(_fishes);                        //从而避免游戏过程中大量申请内存，给玩家带来不流畅感觉。

		for (int i = 0; i < capacity; i++)
		{
			int type = CCRANDOM_0_1() * 2;

			//创建鱼s
			Fish* fish = Fish::create((FishType)type);
			_fishes->addObject(fish);
		}
		this->schedule(schedule_selector(FishLayer::addFish), 3.0);
		return true;
	}
	return false;

}
void FishLayer::addFish(float dt)
{
	int countToAdd = CCRANDOM_0_1() * 10 + 1;
	int countHasAdded = 0;
	CCObject* iterator;
	CCARRAY_FOREACH(_fishes, iterator){
		Fish* fish = (Fish*)iterator;
		if (fish->getParent() == NULL){
			this->addChild(fish);
			this->resetFish(fish);
			countHasAdded++;
			if (countToAdd == countHasAdded){
				break;
			}
		}
	}

	//CCSize winSize = CCDirector::sharedDirector()->getWinSize();//返回OpenGL View的大小
	//int countToAdd = CCRANDOM_0_1() * 10 + 1;  //统计产生鱼的数量
	//int countHashAdded = 0;
	//CCObject* iterator;
	//CCARRAY_FOREACH(_fishes, iterator){
	//	Fish* fish = (Fish*)iterator;
	//	//只有在CCNode::onEnter()中isRunning（）才设置为true
	//	if (fish->isRunning() == false)	{
	//		this->addChild(fish);
	//		//todo后期应该重设Fish产生时的随机坐标
	//		int randomX = CCRANDOM_0_1() * winSize.width;
	//		int randomY = CCRANDOM_0_1() * winSize.height;
	//		fish->setPosition(CCPointMake(randomX,randomY));

	//		countHashAdded++;
	//		if (countToAdd == countHashAdded)
	//			break;
	//	}
	//}


}
FishLayer::~FishLayer()
{
	CC_SAFE_RELEASE(_fishes);
}

void FishLayer::resetFish(Fish* fish)
{
	fish->reset();
	CCPoint start, destination;
	float startX, startY, endX, endY;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize fishSize = fish->getFishSprite()->getContentSize();

	int direction = CCRANDOM_0_1() * 2;

	//随机产生鱼X的方向
	if (direction){
		fish->setRotation(180); //节点的方向
		startX = winSize.width + fishSize.width*0.5;
		endX = -fishSize.width*0.5;
	}
	else{
		fish->setRotation(0);
		startX = -fishSize.width*0.5;
		endX = winSize.width + fishSize.width*0.5;
	}
	startY = CCRANDOM_0_1()*(winSize.height-2*fishSize.height)+fishSize.height;
	endY = startY;

	start = CCPointMake(startX,startY);
	destination = CCPointMake(endX, endY);

	fish->setPosition(start);
	fish->moveTo(destination);
}