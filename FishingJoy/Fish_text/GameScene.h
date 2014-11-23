#ifndef __FishJoying__GameScene__
#define __FishJoying__GameScene__


#include "cocos2d.h"
#include "FishLayer.h"
#include "PanelLayer.h"
#include "MenuLayer.h"
#include "BackgroundLayer.h"
#include "CannonLayer.h"
#include "TouchLayer.h"

typedef enum{
	k_Operate_Pause = 0,
	k_Operate_Resume
}OperateFlag;

class GameScene :public cocos2d::CCScene
{
public:
	CREATE_FUNC(GameScene);
	bool init();
	~GameScene();

	//�˵�ҳ����صĺ���
	void pause();
	void resume();
	void sound();
	void music();
	void reset();
	void transToMainMenu();


	//����ҳ����صĺ���
	void cannonAimAt(cocos2d::CCPoint target);
	void cannonShootTo(cocos2d::CCPoint target);

protected:


	BackgroundLayer* _backgroundLayer;
	FishLayer* _fishLayer;
	CannonLayer* _cannonLayer;
	PanelLayer* _panelLayer;
	MenuLayer* _menuLayer;
	TouchLayer* _touchLayer;

	//todo Ԥ������Դ��ʵ��StartScene����ɾ��
	void preloadResources();

	//��ͣ��ָ����������е����нڵ�
	void operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag);
};

#endif