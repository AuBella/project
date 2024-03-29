/*
 * Copyright (c) 2012 Chukong Technologies, Inc.
 *
 * http://www.cocostudio.com
 * http://tools.cocoachina.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef COCOSTUDIO_DISPLAYMANAGER_H
#define COCOSTUDIO_DISPLAYMANAGER_H

#include "cocos2d.h"
#include "CSDecorativeDisplay.h"
#include "CSDatas.h"


namespace cs {
    
class Bone;

//! DisplayManager manages Bone's display
class CS_EXTERN DisplayManager : public cocos2d::CCObject
{
public:
    static DisplayManager *create(Bone *bone);
    
public:
    DisplayManager();
    ~DisplayManager();
    
    bool init(Bone *bone);
    
    /**
	 * Use BoneData to init the display list.
     * If display is a sprite, and it have texture info in the TexutreData, then use TexutreData to init the display's anchor point
     * If the display is a Armature, then create a new Armature
     */
	void initDisplayList(BoneData *_boneData);
    
    /**
	 * Add display and use  _DisplayData init the display.
     * If _index already have a display, then replace it.
     * If _index is current display index, then also change display to _index
     *
	 *	@param 	displayData it include the display information, like DisplayType.
     *					If you want to create a sprite display, then create a SpriteDisplayData param
     *
	 *	@param 	index the index of the display you want to replace or add to
     *					-1 : append display from back
     */
    void addDisplay(DisplayData *displayData, int index);
    
    void removeDisplay(int index);
    
    cocos2d::CCArray *getDecorativeDisplayList();
    
    /**
	 * Change display by index. You can just use this method to change display in the display list. 
     * The display list is just used for this bone, and it is the displays you may use in every frame.
     *
     * Note : if index is the same with prev index, the method will not effect
     *
	 * @param index The index of the display you want to change
     * @param force If true, then force change display to specified display, or current display will set to  display index edit in the flash every key frame.
     */
	void changeDisplayByIndex(int index, bool force);
    
    
    void setDisplayRenderNode(cocos2d::CCNode *displayRenderNode);
    cocos2d::CCNode *getDisplayRenderNode();
    
    int getCurrentDisplayIndex();
	DecorativeDisplay *getCurrentDecorativeDisplay();
    DecorativeDisplay *getDecorativeDisplayByIndex( int index);
    
    /**
     * Sets whether the display is visible
     * The default value is true, a node is default to visible
     *
     * @param visible   true if the node is visible, false if the node is hidden.
     */
    virtual void setVisible(bool visible);
    /**
     * Determines if the display is visible
	 *
     * @see setVisible(bool)
     * @return true if the node is visible, false if the node is hidden.
     */
    virtual bool isVisible();
    
	cocos2d::CCSize getContentSize();
	cocos2d::CCRect getBoundingBox();
    
    cocos2d::CCPoint getAnchorPoint();
    cocos2d::CCPoint getAnchorPointInPoints();

	/**
     * Check if the position is inside the bone.
     */
    virtual bool containPoint(cocos2d::CCPoint &_point);
    
    /**
     * Check if the position is inside the bone.
     */
    virtual bool containPoint(float _x, float _y);

protected:
    //! Display render node.
	cocos2d::CCNode *m_pDisplayRenderNode;
    
    cocos2d::CCArray *m_pDecoDisplayList;
    //! Include current display information, like contour sprite, etc.
    DecorativeDisplay *m_pCurrentDecoDisplay;
    //! Current display index
	int m_iDisplayIndex;
    
    CC_SYNTHESIZE_PASS_BY_REF(bool, m_bForceChangeDisplay, ForceChangeDisplay)
    
    //! Whether of not the bone is visible. Default is true
    bool m_bVisible;
    
    Bone *m_pBone;
};
		
}

#endif
