#ifndef		__WARES_INFO_H
#define		__WARES_INFO_H

#include <stdio.h>
#include <stdint.h>
#include "GUI.h"


class WaresInfo
{
	public:
		uint32_t Inventory; // 库存
		uint32_t Price; // 价格
		
		uint32_t SelectNumber; // 选择的数量

		uint32_t SalesVolume; // 销量
};




#endif
