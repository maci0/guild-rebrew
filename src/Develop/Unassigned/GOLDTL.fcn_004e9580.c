


// SIZE 0x1c
typedef struct {
	short lo;
	short hi;
	int min_cost;
	int max_cost;
	int a;
	int b;
	int c;
	int d;
} TierInfo;

// SIZE 0x18
typedef struct {
	int f0;
	int f4;
	unsigned char tier;
	char pad[15];
} TierSrc;

int __cdecl fcn_004e8b40(int id, TierSrc* src);

int __cdecl fcn_004e9580(int id, TierInfo* out)
{
	TierSrc src;

	if (fcn_004e8b40(id, &src) == 0) {
		return 0;
	}
	switch (src.tier) {
	case 1:
	case 2:
		out->lo = 0x10;
		out->hi = 0x14;
		out->min_cost = 0x9c400;
		out->max_cost = 0x138800;
		out->a = 3;
		out->b = 4;
		out->c = 2;
		out->d = 3;
		return 1;
	case 3:
	case 4:
		out->lo = 0x14;
		out->hi = 0x18;
		out->min_cost = 0x138800;
		out->max_cost = 0x1d4c00;
		out->a = 4;
		out->b = 5;
		out->c = 3;
		out->d = 4;
		return 1;
	case 5:
		out->lo = 0x18;
		out->hi = 0x1c;
		out->min_cost = 0x1d4c00;
		out->max_cost = 0x271000;
		out->a = 5;
		out->b = 6;
		out->c = 3;
		out->d = 4;
		return 1;
	case 6:
		out->lo = 0x18;
		out->hi = 0x1c;
		out->min_cost = 0x222e00;
		out->max_cost = 0x30d400;
		out->a = 6;
		out->b = 7;
		out->c = 3;
		out->d = 5;
		return 1;
	case 7:
	case 8:
	case 9:
		out->lo = 0x1c;
		out->hi = 0x20;
		out->min_cost = 0x30d400;
		out->max_cost = 0x493e00;
		out->a = 7;
		out->b = 8;
		out->c = 5;
		out->d = 6;
		return 1;
	}
	return 0;
}
