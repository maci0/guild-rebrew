#include "Develop/DieGildeAddOn/game/game_data.h"
/* TOD cutscene setup handler, 0x4e2b70..0x4e301e (1199 bytes).  Registered
 * with id 8 through fcn_004e7160 at 0x4e7299; frame is a 0x23EC-byte local
 * block (single `add esp,0x23EC; ret` exit at 0x4e3018/0x4e301e). */

int __cdecl gm_LookupEntityRecordById(int);
void __cdecl msx_StartMusicIfAllowed(char* s);
int __cdecl sb_LoadLocalizedSampleBank(char* s, int a);
void __cdecl fcn_004e4730(char* s);
void __cdecl fcn_004e4b60(char* s);
void __cdecl fcn_00445f50(int a, int b, float f, int c);
void __cdecl fcn_004463f0(int a, int b, float f);
int __cdecl fcn_004e44b0(char* s, void* p);
int __cdecl cut_WaitForTimeoutOrInput(int a, int b, int c);
void __cdecl fcn_004e4b40(int a, int b, char* s, int c, int d);
void __cdecl main_RunFrameLoop(int a, int b);
void __cdecl sb_PlayVoice(int a, char* s, int b, int c, int d, int e, int f);
int __cdecl fcn_005095d0(void* p, void* buf);
void __cdecl io_FormatTextBuffer(char* buf, ...);
int __cdecl d2_ShowMessageBox(void* buf, int n);
void __cdecl fcn_005d0660(int a, int b, int c, int d);
void __cdecl cm_BeginPacketFieldDelta(void* a, int b);
void __cdecl cm_AppendPacketFieldDelta(int a, int b, int c, void* p);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl cm_RequestChangeBits(int a, int b, int c, int d, int e);
void __cdecl main_ExitToFrameHandler(int p);
void __cdecl fcn_00509fc0(void* a, void* b, int c);
void __cdecl fcn_004e48b0(void);
void __cdecl fcn_004e4610(void* h);
void __cdecl fcn_004e44f0(void* h);
void __cdecl fcn_004e4c00(void);
void __cdecl cut_CleanupCutscene(void);
void __cdecl d3snd_StopTrackedVoices(void);
void __cdecl fcn_004230e0(void* h);
void __cdecl fcn_004e4eb0(void);

/* ADDRESS: GOLDTL 0x004e2b70 */
void __cdecl cut_PlayDeathCutscene(void* arg)
{
	float f10;
	int yslot;
	int xslot;
	int w[6];
	char buf1[0x400];
	char buf2[0x1fb8];
	void* obj;
	int handle;
	int i;
	int state;
	int start;
	int r;
	int idxval;
	unsigned int mask;

	obj = (void*) gm_LookupEntityRecordById(*(int*) ((char*) arg + 0x34));
	mask = *(unsigned int*) 0x7f4c04;
	i = 0;
	w[0] = 8;
	w[1] = 0xa;
	w[2] = 0xc;
	w[3] = 0xf;
	w[4] = 0x12;
	w[5] = 0x14;
	state = 6;
	cut_EventLoopFlags = 0x702c6;
	*(int*) 0x7725c8 = 1;
	mask &= 0xffff;
	while (i < 6) {
		if ((int) mask < w[i]) {
			state = i;
			break;
		}
		i++;
	}
	msx_StartMusicIfAllowed((char*) 0x68bd14);
	handle = sb_LoadLocalizedSampleBank((char*) 0x68d2d0, 1);
	fcn_004e4730((char*) 0x68d2c8);
	fcn_004e4b60((char*) 0x68d2b8);
	fcn_00445f50(state, 0, 1.0f, 1);
	fcn_004463f0(0, 0, 0.0f);
	xslot = fcn_004e44b0((char*) 0x68d29c, (void*) 0x6b5c60);
	r = cut_WaitForTimeoutOrInput(3000, 0, 0);
	if (r == 0) {
		fcn_004e4b40(-8, handle, (char*) 0x68d294, 0, 0);
		fcn_004e4b40(-8, handle, (char*) 0x68d294, 2, 4000);
		fcn_004e4b40(-8, handle, (char*) 0x68d294, 3, 3000);
		fcn_004e4b40(-8, handle, (char*) 0x68d294, 4, 2000);
		fcn_004e4b40(-8, handle, (char*) 0x68d294, 5, 4000);
		fcn_004e4b40(-8, handle, (char*) 0x68d294, 6, 500);
		state = cut_WaitForTimeoutOrInput(0x2af8, 0, 0);
		if (state == 0) {
			start = *(int*) 0x6b7fac;
			while (*(volatile unsigned int*) 0x6b7fac < (unsigned int) (start + 0x339) && state == 0) {
				main_RunFrameLoop(0, cut_EventLoopFlags);
				if (g_14ce8e0 != 0) {
					state = 1;
				}
				if ((float) (unsigned int) (*(int*) 0x6b7fac - start) * (1.0f / 825.0f) < 1.0f) {
					f10 = (float) (unsigned int) (*(int*) 0x6b7fac - start) * (1.0f / 825.0f);
				} else {
					f10 = 1.0f;
				}
				fcn_004463f0(0, 1, f10);
			}
			fcn_004463f0(0, 1, 1.0f);
			cut_WaitForTimeoutOrInput(0x2cec, 0, 0);
		}
	}
	sb_PlayVoice(0, (char*) 0x68d288, 1, 0x3f, 0x7f, 0, 0);
	*(int*) 0x7725c8 = 0;
	r = fcn_005095d0(obj, &yslot);
	if (r != 0) {
		if ((*(int*) ((char*) obj + 0x1cc) & 1) == 0)
			goto dialog_fallback;
		if ((*(int*) ((char*) obj + 0x1cc) & 2) != 0)
			goto dialog_fallback;
		idxval = *(unsigned short*) obj;
		io_FormatTextBuffer(buf1, 0x40fb, 0x40f5, idxval);
		if (d2_ShowMessageBox(buf1, 0x10) == 0) {
		dialog_fallback:
			fcn_005d0660(*(int*) (0x7f4ca4 + 540 * (unsigned short) *(unsigned short*) 0x774970), 0xa, *(int*) 0x14abde8, cut_EventLoopFlags);
		} else {
			int alo;
			alo = 0;
			r = *(int*) ((char*) obj + 4);
			cm_BeginPacketFieldDelta(obj, r);
			f10 = 100.0f;
			cm_AppendPacketFieldDelta(4, 1, 0x1c, &f10);
			cm_AppendPacketFieldDelta(4, 1, 0x24, &alo);
			*(char*) ((char*) obj + 8) = 100;
			cm_RequestChangeAttribute();
			cm_RequestChangeBits(*(int*) ((char*) obj + 4), 0x1cc, 4, 2, 0);
		}
	} else {
		if ((*(int*) ((char*) obj + 0x1cc) & 1) != 0 && (*(int*) ((char*) obj + 0x1cc) & 2) == 0) {
			float alo;
			idxval = *(unsigned short*) obj;
			*(int*) &f10 = 0;
			alo = 100.0f;
			io_FormatTextBuffer(buf1, 0x40fc, 0x40f5, idxval);
			d2_ShowMessageBox(buf1, 0x10);
			cm_BeginPacketFieldDelta(obj, *(int*) ((char*) obj + 4));
			cm_AppendPacketFieldDelta(4, 1, 0x1c, &alo);
			cm_AppendPacketFieldDelta(4, 1, 0x24, &f10);
			cm_RequestChangeAttribute();
			cm_RequestChangeBits(*(int*) ((char*) obj + 4), 0x1cc, 4, 2, 0);
			*(char*) ((char*) obj + 8) = 100;
		} else if ((g_7747b0 & 8) != 0) {
			*(char*) ((char*) obj + 8) = 0;
			idxval = yslot;
			g_774954 = 1;
			if (idxval != 0) {
				io_FormatTextBuffer(buf1, 0x1ab4);
			} else {
				io_FormatTextBuffer(buf1, 0x1ab3, *(unsigned short*) obj);
			}
			d2_ShowMessageBox(buf1, 0);
			main_ExitToFrameHandler(0x5438c0);
		} else {
			fcn_00509fc0(obj, buf2, 1);
			d2_ShowMessageBox(buf2, 0x10);
		}
	}
	fcn_004e48b0();
	fcn_004e4610((void*) xslot);
	fcn_004e44f0((void*) xslot);
	fcn_004e4c00();
	cut_CleanupCutscene();
	d3snd_StopTrackedVoices();
	fcn_004230e0((void*) handle);
	fcn_004e4eb0();
	g_772f54 = 0;
}
