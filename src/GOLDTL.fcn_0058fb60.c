/* ADDRESS: GOLDTL 0x014b5798 */
extern int g_14b5798;
/* ADDRESS: GOLD 0x0144a638 */
extern int g_14b5798;



int __cdecl fcn_00525fb0(int);
void __cdecl fcn_0058bb10(int, int, int, int, void*);
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_0058d180(void);

void __cdecl fcn_0058fb60(int a)
{
	if (fcn_00525fb0(a) == 0) {
		fcn_0058bb10(0, a, g_14b5798, 1, fcn_0058d180);
		fcn_00532ef0();
	}
}
