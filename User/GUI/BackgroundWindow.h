#ifndef		__BACK_GROUND_WINDOW_H
#define		__BACK_GROUND_WINDOW_H

#include "GUI/BaseWindow.h"
#include "GUI/UiProgBar.h"

class BackgroundWindow : public BaseWindow, public UiProgBarTimeOutListener
{
	public:
		static BackgroundWindow &instance(void)
		{
			static BackgroundWindow win;
			return win;
		}
		
		virtual void onKeyClick(uint16_t keyValue);
		
		virtual bool isShowing(void);
		
		virtual void onProgBarTimeOut(void);
		
		void onCallback(WM_MESSAGE *msg);
		
		void draw(void);
		
		void drawForAndTo(uint16_t from, uint16_t to, uint32_t color);
		
		inline void invaliate(void) {
			WM_InvalidateWindow(WM_HBKWIN);
		}
		
		inline uint16_t getAllCount(void) 
		{
			uint16_t s = 0;
			for (uint16_t i = 0; i < GUI_COUNTOF(mCountArray); i ++) {
				s += mCountArray[i];
			}
			return s;
		}
		
		inline void clearAllCount(void) 
		{
			for (uint16_t i = 0; i < GUI_COUNTOF(mCountArray); i ++) {
				mCountArray[i] = 0;
			}
		}
		
		uint32_t getAllPrice(void);
		
		void deliver(void);
		
	private:
		BackgroundWindow(void);
	
		uint16_t mCountArray[5];
	
		char mTextBuffer[32];
	
		WM_HMEM hTimer;
};

#define ID_MESSAGE_1	(WM_USER + 0x01)

#define COLORT			0xFFC9CBCB
#define COLOR1			0xFF22AC38
#define COLOR2			0xFFFF0000
#define COLOR3			0xFFF39800
#define COLOR4			0xFFFF00FF
#define COLOR5			0xFF0000FF

#define CIRCLE_R		26

/**
 * @brief 圆1坐标
 */
#define	CIRCLE1_X		46
#define CIRCLE1_Y		46

/**
 * @brief 圆2坐标
 */
#define	CIRCLE2_X		46
#define CIRCLE2_Y		103

/**
 * @brief 圆3坐标
 */
#define	CIRCLE3_X		46
#define CIRCLE3_Y		160

/**
 * @brief 圆4坐标
 */
#define	CIRCLE4_X		46
#define CIRCLE4_Y		217

/**
 * @brief 圆5坐标
 */
#define	CIRCLE5_X		46
#define CIRCLE5_Y		274

/**
 * @brief 梯形1坐标
 */
#define TRAP1_LTX		160
#define TRAP1_LTY		62

#define TRAP1_RTX		321
#define TRAP1_RTY		62

#define TRAP1_RBX		316
#define TRAP1_RBY		99

#define TRAP1_LBX		164
#define TRAP1_LBY		99

/**
 * @brief 梯形2坐标
 */
#define TRAP2_LTX		165
#define TRAP2_LTY		104

#define TRAP2_RTX		315
#define TRAP2_RTY		104

#define TRAP2_RBX		311
#define TRAP2_RBY		141

#define TRAP2_LBX		169
#define TRAP2_LBY		141

/**
 * @brief 梯形3坐标
 */
#define TRAP3_LTX		170
#define TRAP3_LTY		146

#define TRAP3_RTX		310
#define TRAP3_RTY		146

#define TRAP3_RBX		306
#define TRAP3_RBY		183

#define TRAP3_LBX		174
#define TRAP3_LBY		183

/**
 * @brief 梯形4坐标
 */
#define TRAP4_LTX		175
#define TRAP4_LTY		188

#define TRAP4_RTX		305
#define TRAP4_RTY		188

#define TRAP4_RBX		300
#define TRAP4_RBY		225

#define TRAP4_LBX		179
#define TRAP4_LBY		225

/**
 * @brief 梯形5坐标
 */
#define TRAP5_LTX		180
#define TRAP5_LTY		230

#define TRAP5_RTX		300
#define TRAP5_RTY		230

#define TRAP5_RBX		296
#define TRAP5_RBY		267

#define TRAP5_LBX		185
#define TRAP5_LBY		267



#endif
