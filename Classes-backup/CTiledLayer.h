/************************************************************************/
/* code by ����
/* create 2013/06/25
/* updata 2013/06/26
/* version v1.0.1
/* ʹ�����ֿռ�common
/* use namespace common
/* ����Tiled��ͼ����ʱ��CTiledLayer������CCTMXTiledMap
/* use CTiledLayer to replace CCTMXTiledMap
/************************************************************************/

#ifndef _CTILEDLAYER_H_
#define _CTILEDLAYER_H_

#include "cocos2d.h"

namespace common
{
	class CTiledLayer : public cocos2d::CCTMXTiledMap
	{
	public:
		CTiledLayer();

		static CTiledLayer* create(const char* _filePath);
		static CTiledLayer* createWithSize(const char* _filePath, cocos2d::CCSize _size); 
		virtual void visit();

	protected:
		bool InVisible(cocos2d::CCNode* pNode);

	private:
		cocos2d::CCSize m_size;
	};
}

#endif
