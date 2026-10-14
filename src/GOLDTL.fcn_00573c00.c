


#include <string.h>

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

extern int g_6b8010;

char* __cdecl fcn_005463a0(int, int, int, ...);
char* __cdecl fcn_005462a0(void);
void __cdecl fcn_00500bb0(struct pos14*, int, int, int);
int __cdecl fcn_00597ff0(int, char*);
int __cdecl fcn_00598150(char*, char*);
int __cdecl fcn_005987c0(char*, char*);
void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_00573c00(char* u)
{
	char text[0x80];
	char list[0x400];
	char* e;
	int saved;
	int n;
	int i;

	for (e = fcn_005463a0(1, 0, 0xd); e != 0; e = fcn_005462a0()) {
		if (e != u && *(int*) (e + 0x70) < 5) {
			fcn_00546190(u);
			return;
		}
	}
	*(struct pos14*) (u + 0x52) = *(struct pos14*) (u + 0x44);
	*(struct pos14*) (u + 0x60) = *(struct pos14*) (u + 0x44);
	fcn_00500bb0((struct pos14*) (u + 0x52), 0, 1, 0);
	*(int*) (u + 0xc4) = 0;
	*(int*) (u + 0xc8) = 0;
	if (fcn_00597ff0(*(int*) (u + 0xb0), text) == 0) {
		fcn_00546190(u);
		return;
	}
	saved = g_6b8010;
	memset(list, 0, sizeof(list));
	fcn_004432d0(0, 1);
	n = fcn_00598150(text, list);
	if (n == 0) {
		fcn_004432d0(saved, 1);
		fcn_00546190(u);
		return;
	}
	for (i = 0; i < n; i++) {
		if (fcn_005987c0(u + 0xd4, list) == 0) {
			fcn_00546190(u);
			fcn_004432d0(saved, 1);
			return;
		}
	}
	fcn_0051af00(text, (int) "he_AllocGebaeudeBauen: %1N1", *(unsigned short*) (u + 8));
	fcn_004432d0(saved, 1);
	*(int*) (u + 0x84) = -1;
}
