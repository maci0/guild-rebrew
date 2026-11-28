#include <string.h>

extern float g_6629d0;

extern unsigned char gm_ActiveTownIndex;
extern void* txt_TargetBuildingPrompt;

int __cdecl fcn_005015e0(int* out, int a, int b, int c);
int __cdecl d2_RunCityScrollMapDialog(int a, int* b, void* c, int d, int e);
int __cdecl gm_QueryEntities(int a, int b, ...);
int __cdecl fcn_00502850(void);
float __cdecl fcn_0042e450(void);
void __cdecl cm_SendSellObjekt(int a, int b, int c, int d, unsigned char e, int f);
void __cdecl io_FormatTextBuffer(char* buf, int id, ...);
void __cdecl he_PostEntityMessage(int a, int b, char* buf, int c, int d, int e);
void __cdecl d2_ShowUseObjDialog(char* buf);

/* ADDRESS: GOLDTL 0x005de420 */
int __cdecl gm_ObjForceSellBuildingStock(char* actor, char* action)
{
	int one;
	int recordAddr;
	int request[0x14];
	char detail[0x200];
	char text[0x800];
	char* base;
	int* rec;
	int* e;
	int* f;
	int quantity;

	one = 1;
	if (actor[2] == 6) {
		memset(request, 0, 0x50);
		memset(&request[7], -1, 0x20);
		request[0] = one;
		request[1] = -1;
		request[4] = 6;
		request[2] = 0xa0744300;
		request[3] = one;
		recordAddr = d2_RunCityScrollMapDialog(one, request, txt_TargetBuildingPrompt, 0, 0);
		if (recordAddr == 0)
			return 0;
	} else {
		fcn_005015e0(&recordAddr, 0, 0, *(int*) (action + 4));
		if (recordAddr == 0)
			return 0;
	}

	rec = (int*) recordAddr;
	base = (char*) ((int*) 0x7f4ca0
	    + (int) *(unsigned short*) ((char*) recordAddr + 0x27) * 135);
	e = (int*) gm_QueryEntities(*(int*) ((char*) rec + 0x5d), 2, 6, 0, 0x2a);
	if (e != 0) {
		gm_QueryEntities(*(int*) ((char*) e + 0x14), one, 5);	/* result unused */
		f = (int*) gm_QueryEntities(*(int*) ((char*) e + 0x14), one, 5);
		while (f != 0) {
			if (*(int*) ((char*) f + 0xe) > one) {
				quantity = (((int) ((fcn_0042e450() * g_6629d0 + 0.1f)
				    * *(int*) ((char*) f + 0xe))) < one) ? one
				    : (int) ((fcn_0042e450() * g_6629d0 + 0.1f)
				    * *(int*) ((char*) f + 0xe));
				cm_SendSellObjekt(-1, *(int*) ((char*) e + 2),
				    *(unsigned short*) f, quantity, gm_ActiveTownIndex, 0);
			}
			f = (int*) fcn_00502850();
		}
	}

	if (base[2] == 6 || base[2] == 7) {
		io_FormatTextBuffer(text, 0x100c, recordAddr);
		he_PostEntityMessage(*(int*) (base + 4), -1, text, 0, 0x5fb, 0);
	}
	if (actor[2] == 6) {
		io_FormatTextBuffer(detail, 0x109d,
		    *(unsigned short*) ((char*) recordAddr + 0x27), recordAddr);
		io_FormatTextBuffer(text, 0xfe8, detail);
		d2_ShowUseObjDialog(text);
	}
	*(int*) (action + 0x10) = one;
	return one;
}
