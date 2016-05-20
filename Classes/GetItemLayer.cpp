#include "GetItemLayer.h"
#include "AppDelegate.h"
#include "Common.h"
#include "ShopMenu.h"
#include "baseRes.h"
#include "GameControler.h"
#include "GameoverBtnMenu.h"
#include "AchieveAdd.h"
#include "PayService.h"

using namespace cocos2d;
using namespace cocos2d::extension;

static int _Type[] =
{
	1, 1, 1, 1, 1, 1, 1, 1, 
	2, 2, 2, 2, 2, 2, 2, 2, 2, 
	3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6,
	7, 8, 9 ,10, 11, 6, 6, 6,
};
static int _Num[] =
{
	10, 50, 100, 200, 500, 1000, 2000, 5000,
	1, 2, 3, 5, 10, 20, 30, 50, 100,
	5, 10, 1, 2, 3, 1, 2, 5, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
};
static int _Probability[] =
{
	100, 100, 40, 30, 20, 10, 1, 1,
	100, 100, 40, 30, 20, 10, 5, 1, 1,
	5, 1, 100, 20, 10, 5, 1, 0, 0, 0, 0,
	0, 0, 0, 0, 100, 0, 0, 0,
};

#define d_fGameOverNumLocate1	654, 388
#define d_fGameOverNumLocate2	619, 301
#define d_fGameOverNumLocate4	573, 205
#define d_fGameOverNumLocate31	639, 280
#define d_fGameOverNumLocate32	660, 280
#define d_fGameOverNumLocate33	681, 280

ccbGetItemLayer* ccbGetItemLayer::s_pccbGetItemLayer = NULL;

ccbGetItemLayer::ccbGetItemLayer()
	: m_AnimationManager(NULL)
{
	m_bOnSell		= false;
	m_bWin			= false;
	m_iWeapon		= 0;
	m_pSprite		= NULL;
	m_bCanPress		= false;
	m_bIsWeapon		= true;
	s_pccbGetItemLayer = this;
}

ccbGetItemLayer::~ccbGetItemLayer()
{
	s_pccbGetItemLayer = NULL;
	CC_SAFE_RELEASE_NULL(m_AnimationManager);
}

void ccbGetItemLayer::onNodeLoaded(cocos2d::CCNode * _pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) 
{	
	m_pNode = _pNode;
	bool bAchieve = false;
	CCNode* pNode = _pNode->getChildByTag(7);
}

SEL_MenuHandler ccbGetItemLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "On1", ccbGetItemLayer::OnBuy1 );
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "On2", ccbGetItemLayer::OnBuy2 );
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "On3", ccbGetItemLayer::OnBuy3 );
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "On4", ccbGetItemLayer::OnBuy4 );
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "On5", ccbGetItemLayer::DisAppear );
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "On6", ccbGetItemLayer::OnShop );
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "On7", ccbGetItemLayer::OnContinue );
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "On8", ccbGetItemLayer::OnReturn );
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "On9", ccbGetItemLayer::OnReplay );
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "On10", ccbGetItemLayer::OnRechoseHero );
	return NULL;    
}

SEL_CCControlHandler ccbGetItemLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{
	return NULL;
}

bool ccbGetItemLayer::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) 
{
	return false;
}

bool ccbGetItemLayer::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
	bool bRet = false;
	return bRet;
}

void ccbGetItemLayer::setAnimationManager(CCBAnimationManager *pAnimationManager, cocos2d::CCNode* _pNode)
{
	CC_SAFE_RELEASE_NULL(m_AnimationManager);
	m_AnimationManager = pAnimationManager;
	CC_SAFE_RETAIN(m_AnimationManager);
	m_pGameControler = _pNode;
}

//void ccbGetItemLayer::SetGame( CGameControler* p )
//{
//	m_pGameControler = p;
//}

void ccbGetItemLayer::StartBtn()
{
	m_AnimationManager->runAnimationsForSequenceNamedTweenDuration("Default Timeline2 copy", 0.0f);
}

void ccbGetItemLayer::OnBuy1( cocos2d::CCObject *pSender )
{
	if ( ccbGameoverBtnMenu::s_pccbGameoverBtnMenu->m_bOnSell )
		return;
	/*if ( m_bOnSell || !m_pGetPrize->m_bOver )
		return;*/
	if ( !m_bCanPress )
		return;
	if ( m_iWeapon == 0 && !m_bIsWeapon )
	{
		if ( AppDelegate::s_Medal < 30 )
		{
			GetMedal();
			return;
		}
		AppDelegate::s_Medal -= 30;
		m_iGetPrize = 0;
		int num = rand()%50+1;
		while ( num )
		{
			for ( int i = 0; i < 25; i++ )
			{
				if ( _Probability[i] != 0 )
				{
					m_iGetPrize = i;
					num--;
					if ( !num )
						break;
				}
			}
		}
		/*m_pGetPrize->initPrize(m_iGetPrize);
		m_pGetPrize->Appear();*/
		schedule(schedule_selector(ccbGetItemLayer::GetPrizeCheck), 0.02f);
	}
	else if ( m_iWeapon )
	{
		bool successd = false;
		if ( m_iType == 0 )
		{
#ifdef Plat_Telecom_Demo
		/*	AppDelegate::s_VIP = 1;
			AppDelegate::SaveVIP();*/
			successd = true;
#else
			if ( pSender )
			{
				PayService::pay(11);
			}
			else
			{
				successd = true;
			}
#endif
		}
		else if ( m_iType == 1 )
		{
			int sell1 = 1;
			int sell2 = 1;
			if ( ccbShopMenu::WeaponOnSell(m_iWeapon) )
			{
				sell1 = 5;
				sell2 = 4;
			}
			int cost = g_priceUpgrade[m_iWeapon]*sell2/sell1;
			if ( g_weaponUseMedal[m_iWeapon] )
			{
				if ( AppDelegate::s_Money >= cost )
				{
					AppDelegate::s_Money -= cost;
					successd = true;
				}
				else
				{
					GetMoney();
					return;
				}
			}
			else
			{
				if ( AppDelegate::s_Medal >= cost )
				{
					AppDelegate::s_Medal -= cost;
					successd = true;
				}
				else
				{
					GetMedal();
					return;
				}
			}
			if ( successd )
			{
				AppDelegate::s_WeaponUse[1] = m_iWeapon;
				CCNode* pNode = m_pNode->getChildByTag(3);
				common::ShowNumber(pNode, AppDelegate::s_BulletNum[AppDelegate::s_WeaponUse[1]], 19, 24, 78, 57, "tu3/zidansuzi.png", 888, 0, 0.7f);
				common::ShowNumber(pNode, g_priceBullet[AppDelegate::s_WeaponUse[1]], 19, 24, 70, 24, "tu3/zidansuzi.png", 889, 0, 0.8f);
				AppDelegate::AudioPlayEffect("MS2/buy.mp3");
				AppDelegate::s_WeaponOwn[m_iWeapon] = 1;
				CCNode* pSprite = m_pNode->getChildByTag(1)->getChildByTag(1);
				pSprite->removeFromParentAndCleanup(true);
				pSprite->stopAllActions();
				pSprite->setScale(1.5f);
				m_iWeapon = 0;
			}
			else
			{//Ê§°ÜÌáÊ¾

			}
		}
		if ( successd )
		{
			m_pNode->getChildByTag(5)->setVisible(false);
		}
	}

}

void ccbGetItemLayer::OnBuy2( cocos2d::CCObject *pSender )
{
	if ( ccbGameoverBtnMenu::s_pccbGameoverBtnMenu->m_bOnSell )
		return;
	/*if ( m_bOnSell || !m_pGetPrize->m_bOver )
		return;*/
	if ( AppDelegate::s_Healbox > 2 || !m_bCanPress )
		return;
	if ( AppDelegate::s_Money < 300 )
	{
		GetMoney();
		return;
	}
	AppDelegate::AudioPlayEffect("MS2/buy.mp3");
	AppDelegate::s_Healbox ++;
	AppDelegate::s_Money -= 300;
	common::ShowNumberUpdate(m_pNode->getChildByTag(2), AppDelegate::s_Healbox, 888);
	CCNode* pNode = m_pNode->getChildByTag(2)->getChildByTag(888);
	pNode->stopAllActions();
	pNode->setScale(1.5f);
	CCActionInterval* pAction2 = CCScaleTo::create(0.2f, 1.0f);
	pNode->runAction( pAction2 );
}

void ccbGetItemLayer::OnBuy3( cocos2d::CCObject *pSender )
{
	if ( ccbGameoverBtnMenu::s_pccbGameoverBtnMenu->m_bOnSell )
		return;
	//if ( m_bOnSell || !m_pGetPrize->m_bOver )
	//	return;
	if ( AppDelegate::s_BulletNum[AppDelegate::s_WeaponUse[1]] >= 999 || !m_bCanPress )
		return;
	if ( AppDelegate::s_Money < g_priceBullet[AppDelegate::s_WeaponUse[1]] )
	{
		GetMoney();
		return;
	}
	AppDelegate::AudioPlayEffect("MS2/buy.mp3");
	AppDelegate::s_BulletNum[AppDelegate::s_WeaponUse[1]] += g_iWeaponBulletOnce[AppDelegate::s_WeaponUse[1]];
	if ( AppDelegate::s_BulletNum[AppDelegate::s_WeaponUse[1]] > 999 )
		AppDelegate::s_BulletNum[AppDelegate::s_WeaponUse[1]] = 999;
	AppDelegate::s_Money -= g_priceBullet[AppDelegate::s_WeaponUse[1]];
	common::ShowNumberUpdate(m_pNode->getChildByTag(3), AppDelegate::s_BulletNum[AppDelegate::s_WeaponUse[1]], 888);
	CCNode* pNode = m_pNode->getChildByTag(3)->getChildByTag(888);
	pNode->stopAllActions();
	pNode->setScale(1.5f);
	CCActionInterval* pAction2 = CCScaleTo::create(0.2f, 1.0f);
	pNode->runAction( pAction2 );
}

void ccbGetItemLayer::OnBuy4( cocos2d::CCObject *pSender )
{
	if ( ccbGameoverBtnMenu::s_pccbGameoverBtnMenu->m_bOnSell )
		return;
	/*if ( m_bOnSell || !m_pGetPrize->m_bOver )
		return;*/
	if ( AppDelegate::s_GrenadeNum >= d_iGrenadeMax || !m_bCanPress )
		return;
	if ( AppDelegate::s_Money < 260 )
	{
		GetMoney();
		return;
	}
	AppDelegate::AudioPlayEffect("MS2/buy.mp3");
	AppDelegate::s_GrenadeNum ++;
	AppDelegate::s_Money -= 260;
	common::ShowNumberUpdate(m_pNode->getChildByTag(4), AppDelegate::s_GrenadeNum, 888);
	CCNode* pNode = m_pNode->getChildByTag(4)->getChildByTag(888);
	pNode->stopAllActions();
	pNode->setScale(1.5f);
	CCActionInterval* pAction2 = CCScaleTo::create(0.2f, 1.0f);
	pNode->runAction( pAction2 );
}

void ccbGetItemLayer::InitBtn(int _type){
	setVisible(true);
	m_bCanPress = true;
	if ( _type )
		m_AnimationManager->runAnimationsForSequenceNamedTweenDuration("Default Timeline", 0.0f);
	else
		m_AnimationManager->runAnimationsForSequenceNamedTweenDuration("Default Timeline3", 0.0f);
}

void ccbGetItemLayer::Appear1(int _type)
{
	m_iType = 0;
	m_iWeapon = 1;
	CCNode* pNode = m_pNode->getChildByTag(1);
	InitBtn(_type);
}

void ccbGetItemLayer::Appear2(int _type){
	InitBtn(_type);
}

void ccbGetItemLayer::DisAppear(cocos2d::CCObject *pSender)
{
	if ( ccbGameoverBtnMenu::s_pccbGameoverBtnMenu->m_bOnSell )
		return;
	if ( !m_bCanPress )
		return;
	((CGameControler*)m_pGameControler)->m_bEndPress = false;
	m_bCanPress = false;
	removeChildByTag(10);
	m_AnimationManager->runAnimationsForSequenceNamedTweenDuration("Default Timeline2", 0.0f);
}

void ccbGetItemLayer::OnShop( cocos2d::CCObject *pSender )
{
	if ( ccbGameoverBtnMenu::s_pccbGameoverBtnMenu->m_bOnSell )
		return;
	((ccbGameoverBtnMenu*)((CGameControler*)m_pGameControler)->m_pGameoverBtnNode)->OnShop(NULL);
}

void ccbGetItemLayer::OnContinue( cocos2d::CCObject *pSender )
{
	if ( ccbGameoverBtnMenu::s_pccbGameoverBtnMenu->m_bOnSell )
		return;
	((ccbGameoverBtnMenu*)((CGameControler*)m_pGameControler)->m_pGameoverBtnNode)->OnContinue(NULL);
}

void ccbGetItemLayer::OnReturn( cocos2d::CCObject *pSender )
{
	if ( ccbGameoverBtnMenu::s_pccbGameoverBtnMenu->m_bOnSell )
		return;
	unschedule(schedule_selector(ccbGetItemLayer::Timer));
	((ccbGameoverBtnMenu*)((CGameControler*)m_pGameControler)->m_pGameoverBtnNode)->OnReturn(NULL);
}

void ccbGetItemLayer::OnReplay( cocos2d::CCObject *pSender )
{
	if ( ccbGameoverBtnMenu::s_pccbGameoverBtnMenu->m_bOnSell )
		return;
	((ccbGameoverBtnMenu*)((CGameControler*)m_pGameControler)->m_pGameoverBtnNode)->OnReplay(NULL);
}

void ccbGetItemLayer::Timer( float _t )
{

}

void ccbGetItemLayer::OnRechoseHero( cocos2d::CCObject *pSender )
{
	if ( ccbGameoverBtnMenu::s_pccbGameoverBtnMenu->m_bOnSell )
		return;
	m_bOnSell = true;
	((ccbGameoverBtnMenu*)((CGameControler*)m_pGameControler)->m_pGameoverBtnNode)->OnRechoseHero(NULL);
}

void ccbGetItemLayer::OnGetAchieve( cocos2d::CCObject *pSender /*= NULL*/ )
{
	if ( ccbGameoverBtnMenu::s_pccbGameoverBtnMenu->m_bOnSell )
		return;
	m_bOnSell = true;
	((ccbGameoverBtnMenu*)((CGameControler*)m_pGameControler)->m_pGameoverBtnNode)->OnGetAchieve(NULL);
}

void ccbGetItemLayer::GetMoney( cocos2d::CCObject* sender )
{
#ifdef NoGetMoney
	return;
#endif
	if ( ccbGameoverBtnMenu::s_pccbGameoverBtnMenu->m_bOnSell )
		return;
	/*CCMenuItem* pItem = CCMenuItemImage::create("sell/guan.png", "sell/guan.png", this, menu_selector(ccbGetItemLayer::GetRemove));
	pItem->setPosition(ccp(723,351));
	CCMenu* pMenu = CCMenu::create(pItem, NULL);
	pMenu->setPosition(ccp(0,0));
	addChild(pMenu, 31, 1196);*/

	//CCSprite* pSprite1 = CCSprite::create("sell/money/di.png");
	//pSprite1->setPosition(ccp(400, 240));
	//addChild(pSprite1, 31, 1199);
	//CCSprite* pSprite2 = CCSprite::create("sell/money/2.png");
	//pSprite2->setPosition(ccp(400, 240));
	//addChild(pSprite2, 33, 1198);

	//CCMenuItem* pItem2 = CCMenuItemImage::create("sell/money/goumia.png", "sell/money/goumia2.png", this, menu_selector(ccbGetItemLayer::GetMoneyBtn));
	//pItem2->setPosition(ccp(243,199));
	//pItem2->setTag(2);
	//CCMenuItem* pItem3 = CCMenuItemImage::create("sell/money/goumia.png", "sell/money/goumia2.png", this, menu_selector(ccbGetItemLayer::GetMoneyBtn));
	//pItem3->setPosition(ccp(556,199));
	//pItem3->setTag(3);

	//CCMenu* pMenu1 = CCMenu::create(/*pItem1, */pItem2, pItem3, /*pItem4, pItem5, */NULL);
	//pMenu1->setPosition(ccp(0,0));
	//addChild(pMenu1, 32, 1197);
}

void ccbGetItemLayer::GetMedal( cocos2d::CCObject* sender ){
}

void ccbGetItemLayer::GetMoneyBtn( cocos2d::CCObject* _pNode )
{
	if ( _pNode )
	{
		int numAdd = 0;
		int numMid = 0;
		int index = ((CCNode*)_pNode)->getTag();
		switch ( index )
		{
		case 1:
			numAdd = 1080;
			numMid = 2;
			break;
		case 2:
			numAdd = 6480;
			numMid = 14;
			break;
		case 3:
			numAdd = 35280;
			numMid = 49;
			break;
		case 4:
			numAdd = 80190;
			numMid = 99;
			break;
		case 5:
			numAdd = 181440;
			numMid = 168;
			break;
		}
		AppDelegate::s_Money += numAdd;
		AppDelegate::SaveMoney();
	}
	else
		GetRemove();
}

void ccbGetItemLayer::GetMedalBtn( cocos2d::CCObject* _pNode )
{
	if ( _pNode )
	{
		int numAdd = 0;
		int numMid = 0;
		int index = ((CCNode*)_pNode)->getTag();

		switch ( index )
		{
		case 1:
			numAdd = 108;
			numMid = 2;
			break;
		case 2:
			numAdd = 648;
			numMid = 14;
			break;
		case 3:
			numAdd = 3528;
			numMid = 49;
			break;
		case 4:
			numAdd = 8019;
			numMid = 99;
			break;
		case 5:
			numAdd = 18144;
			numMid = 168;
			break;
		}
		AppDelegate::s_Medal += numAdd;
		AppDelegate::SaveMedal();
	}
	else
		GetRemove();
}

void ccbGetItemLayer::GetRemove(cocos2d::CCObject* _pNode)
{
	if ( !m_bOnSell )
		return;
	m_bOnSell = false;
	for ( int i = 1195; i < 1200; i++ )
	{
		if ( getChildByTag(i) )
			removeChildByTag(i);
	}
}

void ccbGetItemLayer::GetPrizeCheck( float _t ){
		switch ( _Type[m_iGetPrize] )
		{
		case 1:
			AppDelegate::s_Money += _Num[m_iGetPrize];
			break;
		case 2:
			AppDelegate::s_Medal += _Num[m_iGetPrize];
			if ( AppDelegate::s_Medal > 99999 )
				AppDelegate::s_Medal = 99999;
			break;
		case 3:
			AppDelegate::s_GrenadeNum += _Num[m_iGetPrize];
			if ( AppDelegate::s_GrenadeNum > 10 )
				AppDelegate::s_GrenadeNum = 10;
			common::ShowNumberUpdate(m_pNode->getChildByTag(4), AppDelegate::s_GrenadeNum, 888);
			break;
		case 4:
			AppDelegate::s_Healbox += _Num[m_iGetPrize];
			if ( AppDelegate::s_Healbox > 3 )
				AppDelegate::s_Healbox = 3;
			common::ShowNumberUpdate(m_pNode->getChildByTag(2), AppDelegate::s_Healbox, 888);
			break;
		case 5:
			{
				int num = _Num[m_iGetPrize];
				if ( AppDelegate::s_SkillEnergy[0] < 100 )
				{
					AppDelegate::s_SkillEnergy[0] = 100;
					num--;
				}
				AppDelegate::m_Sell2 += num;
			}
			break;
		case 11:
			break;
		AppDelegate::SaveStatus();
		unschedule(schedule_selector(ccbGetItemLayer::GetPrizeCheck));
	}
}


