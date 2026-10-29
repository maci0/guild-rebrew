typedef struct Handler {
	void(__cdecl* fn)(void);
	int arg;
} Handler;
/* SIZE 8 */

extern Handler g_7e35c0[];
extern int g_774650;
extern volatile unsigned int g_6b7fac;
int g_6a2c1c = 0xffffffff;
extern int g_6a2c20;
extern char g_6811b0[];
extern char g_7e3a60[];

void __cdecl fcn_00536810(void);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471d80(int, int);
void __cdecl fcn_00471e30(int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190(int, ...);

/* ADDRESS: GOLDTL 0x00536b10 */
void __cdecl fcn_00536b10(void)
{
	if (g_7e35c0[g_774650].fn != fcn_00536810 &&
	    g_6a2c1c > g_6b7fac - 0x23a &&
	    g_6a2c1c != -1) {
		if (g_6a2c20 == -1) {
			g_6a2c20 = fcn_00470820(0, 0, "misc\\quickchat");
			fcn_00471d80(g_6a2c20, 3);
			if (g_6a2c20 == -1) {
				return;
			}
		}
		d2_SetForm(g_6a2c20, 0);
		fcn_00519190((int) g_6811b0);
		fcn_00519190((int) g_7e3a60);
		return;
	}
	if (g_6a2c20 == -1) {
		return;
	}
	fcn_00471e30(g_6a2c20);
	g_6a2c20 = -1;
}
