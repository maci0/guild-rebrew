// FUNCTION: GOLD 0x4c3680
// SIZE: 160
// FUNCTION: GOLDTL 0x4c3ff0
// SIZE: 148

#pragma pack(1)
typedef struct node99 {
	char f0;
	char f1;
	char f2;
	char f3;
	int f4;
	int f8;
	int fc;
	unsigned short f10;
	char data[0x7f];
	struct node99* prev;
	struct node99* next;
} node99;
// SIZE 0x99
#pragma pack()

extern int g_1005760;
extern int g_14cbca0;
extern unsigned char* g_14cbca8;

int __cdecl fcn_004c49f0(node99*);
void __cdecl fcn_00421290(void);

int __cdecl fcn_004c3ff0(void)
{
	if ((*(node99**)&g_1005760) == 0)
		return 0;
	if (g_14cbca0 == -1) {
		while (1) {
			if (fcn_004c49f0((*(node99**)&g_1005760)) != 0)
				break;
			(*(node99**)&g_1005760) = (*(node99**)&g_1005760)->next;
			if ((*(node99**)&g_1005760) == 0)
				return 0;
			(*(node99**)&g_1005760)->prev = 0;
		}
		return 1;
	}
	do {
		if ((*(node99**)&g_14cbca8) != 0) {
			fcn_00421290();
			if ((*(node99**)&g_14cbca8) != 0)
				return 0;
		}
		(*(node99**)&g_14cbca8) = (*(node99**)&g_1005760);
		(*(node99**)&g_1005760) = (*(node99**)&g_1005760)->next;
		if ((*(node99**)&g_1005760) != 0)
			(*(node99**)&g_1005760)->prev = 0;
		fcn_00421290();
	} while ((*(node99**)&g_1005760) != 0);
	return 0;
}
