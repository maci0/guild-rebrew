// FUNCTION: GOLD 0x532960

#include <string.h>

// SIZE 0x6a
struct netinfo {
	short a;
	short b;
	short size;
	char name[0x20];
	char mode;
	char pad;
	short port;
	char rest[0x40];
};

extern struct netinfo g_7e2520;
// SIZE 0x70
struct netslot {
	struct netinfo info;
	int x;
};

extern struct netslot g_9baa70;
extern char g_7e21a0[];
extern char g_7e2000[];
extern char g_7e1d00[];
extern char g_6a3a28[];
extern char g_6a3778[];
extern unsigned char g_7747b0;
extern unsigned char g_6a375c;
extern short g_7e2510;
extern int g_6a3764;
extern int g_6a3768;
extern int g_6a376c;
extern int g_6a3770;
extern float g_10529c8;
extern float g_10421a0;
extern float g_10432a4;
// SIZE 4
struct shortpair {
	short lo;
	short hi;
};

extern short g_fb9070;
extern int g_77250c;

int __cdecl fcn_00539380(void);
void __cdecl fcn_00469e70(void);
int __cdecl fcn_0053ed60(int, int);
int __cdecl sprintf(char*, const char*, ...);
void __cdecl fcn_00438da0(float, float, float, float, int, int, int, int, int);
void __cdecl fcn_00476970(int);
void __cdecl fcn_00469e30(int);

int __cdecl fcn_00532960(void)
{
	if (fcn_00539380() != 0) {
		fcn_00469e70();
		if (fcn_0053ed60(1, 1) != 0) {
			sprintf(g_7e21a0, g_6a3a28, g_6a3778, g_7e1d00);
			strcpy(g_7e2000, "127.0.0.1");
			(*(int*)&g_7747b0) |= 0x10;
			g_7e2520.mode = *(char*) &(*(int*)&g_6a375c);
			g_7e2520.size = 0x6a;
			g_7e2520.a = 1;
			g_7e2520.b = 1;
			g_7e2520.port = g_7e2510;
			strcpy(g_7e2520.name, g_7e1d00);
			g_9baa70.info = g_7e2520;
			g_9baa70.x = 0x3f;
			fcn_00438da0((float) (g_6a376c - g_6a3764), (float) (g_6a3770 - g_6a3768), (float) g_6a3764,
			    (float) g_6a3768, (*(int*)&g_10529c8), (*(int*)&g_10421a0), (*(int*)&g_10432a4), (*(struct shortpair*)&g_fb9070).hi, (*(struct shortpair*)&g_fb9070).lo);
			return 1;
		}
	}
	fcn_00476970(g_77250c);
	fcn_00469e30(0x797);
	return 0;
}
