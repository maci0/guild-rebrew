// FUNCTION: GOLDTL 0x0059c760
// SIZE: 152

extern int g_7746d8;
extern int g_7746a0;
extern int g_14ad230;
extern int g_14ad208;
extern char g_6aa39c[];
extern char g_6aa38c[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_0059b260(int);
void __cdecl fcn_0059ba40(int);

void __cdecl fcn_0059c760(int a)
{
	int x;
	int y;

	x = 0;
	y = 0;
	fcn_005338a0();
	while (fcn_005373e0(fcn_0059c760, 0x67fff) != 0) {
		if (g_7746d8 & 0x200) {
			x = fcn_005338d0(g_6aa39c, g_14ad230, 0x16);
			y = fcn_005338d0(g_6aa38c, g_14ad208, 0xa);
		}
		if (g_7746a0 != 0) {
			if (g_7746a0 == x) {
				fcn_0059b260(a);
			}
			else if (g_7746a0 == y) {
				fcn_0059ba40(a);
			}
		}
	}
}
