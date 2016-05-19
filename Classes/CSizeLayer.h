/************************************************************************/
/* code by ����
/* date 2013/06/21
/* version v1.0.0
/* ʹ�����ֿռ�common
/* use namespace common
/* ����ȫ����ʾ��Layerʱʹ�÷�����CCLayer��ȫһ��
/* use it as CCLayer if it is full of window
/* �����Զ���Χʱʹ��createWithSize(CCSize)�������Զ�����Ӵ�С��Layer
/* use createWithSize(CCSize) to create your Layer with custom visible rect
/* �������κ�ʱ��ʹ��initSize(CCSize)���ı���ӷ�Χ��С
/* use initSize(CCSize) to change visible rect in anytime
����
/************************************************************************/

#ifndef _CSIZELAYER_H_
#define _CSIZELAYER_H_

#include "cocos2d.h"

namespace common
{
	class CSizeLayer : public cocos2d::CCLayer
	{
	public:
		CSizeLayer();

		static CSizeLayer* createWithSize(cocos2d::CCSize _size);
		void initSize(cocos2d::CCSize _size);

		virtual void visit();
		virtual void addChild(CCNode * child, int zOrder, int tag);
		virtual void addChild(CCNode * child, int zOrder);
		virtual void addChild(CCNode * child);
	protected:
		void beforeDraw();
		void afterDraw();
		cocos2d::CCRect getViewRect();

		bool m_bScissorRestored;
		cocos2d::CCSize m_sizeView;
		cocos2d::CCRect m_tParentScissorRect;
	};
}

#endif
