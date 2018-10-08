#ifndef		__UI_POLYGON_H
#define		__UI_POLYGON_H

#include "GUI.h"
#include <stdint.h>

class UiPolygon
{
	public:
		static UiPolygon &instance(void)
		{
			static UiPolygon p;
			return p;
		}
		
		inline UiPolygon &begin(void) { nCount = 0; return *this; }
		
		inline UiPolygon &append(int16_t x, int16_t y)
		{
			mPoints[nCount].x = x;
			mPoints[nCount].y = y;
			nCount ++;
			return *this;
		}
		
		inline void draw(int x, int y) { GUI_DrawPolygon(mPoints, nCount, x, y);}
		
		inline void fill(int x, int y) { GUI_FillPolygon(mPoints, nCount, x, y); }
		
	private:
		UiPolygon(void);
	
	private:
		GUI_POINT mPoints[10];
		int nCount;
};


#endif
