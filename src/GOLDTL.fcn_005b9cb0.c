


typedef struct
{
	int x0;
	int x4;
	char pad8[0x214];
} Player;
// SIZE 0x21c

extern double g_662b20;
extern unsigned char g_773d75;
extern unsigned short g_774970;
extern char g_7f4ca0[];

float __cdecl fcn_0050b980(int, char);
int __cdecl fcn_0051e070(void);
void __cdecl fcn_0051af00(char*, int, ...);
int __cdecl fcn_00526120(char*, int);
void __cdecl fcn_00506300(char*);
void __cdecl fcn_004c5150(int, int, char, int);

void __cdecl fcn_005b9cb0(int n, char** items)
{
	char buf[0x400];
	int total;
	int i;
	int price;

	if (n > 0x20 || n == 0) {
		return;
	}
	total = 0;
	for (i = 0; i < n; i++) {
		total = (int)(total + (fcn_0050b980(*(unsigned short*) items[i], items[i][0x12])));
	}
	price = (int) (total * g_662b20);
	switch (fcn_0051e070()) {
	case 0:
		if (n > 1) {
			fcn_0051af00(buf, 0xdc, price, n, 0xc10);
		}
		else {
			fcn_0051af00(buf, 0xdc, price, n, *(unsigned short*) items[0] * 2 + 0x9a8);
		}
		break;
	case 1:
		if (n > 1) {
			fcn_0051af00(buf, 0xdc, n, 0xc10, price);
		}
		else {
			fcn_0051af00(buf, 0xdc, n, *(unsigned short*) items[0] * 2 + 0x9a8, price);
		}
		break;
	}
	if (fcn_00526120(buf, 0x101) != 0) {
		for (i = 0; i < n; i++) {
			fcn_00506300(items[i]);
		}
		fcn_004c5150(((Player*)g_7f4ca0)[g_774970].x4, -1, (*(char*)&g_773d75), price);
	}
}
