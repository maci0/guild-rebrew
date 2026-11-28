#ifndef PRODUCTION_GOODS_H
#define PRODUCTION_GOODS_H

typedef struct {
	int goods_id;
	int building_indices[4];
	int unk_14;
	int unk_18;
	int min_1;
	int min_2;
	float value;
	float sum;
	float base;
	float price;
	float slope;
	int amount;
	int unk_3c;
	int unk_40;
	int unk_44;
	int unk_48;
	int unk_4c;
	int unk_50;
	int flags;
} PRODUCTION_GOODS_RECORD;
/* SIZE 0x58 */

extern PRODUCTION_GOODS_RECORD ai_ProductionGoodsPlans[];

#endif
