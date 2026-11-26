


typedef struct Small3i {
	int code;
	int a;
	int b;
} Small3i;
// SIZE 0xc

extern char g_67eb6c[];
extern char g_67eb54[];

void __cdecl cm_SendLogAction(char* s);
void __cdecl cm_SendTraceEnd(char* s);
void __cdecl fcn_004c6900(Small3i* a1);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);

int __cdecl ai_RunStammtisch(char* a1, char* a2)
{
	Small3i msg;

	if (*(int*) (a2 + 8) == 0x6a6f696e) {
		msg.code = *(int*) (a2 + 8);
		msg.a = *(int*) (a1 + 4);
		msg.b = *(int*) (a2 + 4);
		cm_SendLogAction(g_67eb6c);
		fcn_004c6900(&msg);
		cm_RequestChangeBits(*(int*) (a1 + 4), 0x1c8, 4, 0x2000000, 0);
		cm_SendTraceEnd(g_67eb6c);
		return 0x35;
	}
	if (*(int*) (a2 + 8) == 0x6c656176) {
		msg.code = *(int*) (a2 + 8);
		msg.a = *(int*) (a1 + 4);
		msg.b = *(int*) (a2 + 4);
		cm_SendLogAction(g_67eb54);
		fcn_004c6900(&msg);
		cm_RequestChangeBits(*(int*) (a1 + 4), 0x1c8, 4, 0x2000000, 0);
		cm_SendTraceEnd(g_67eb54);
		return 0x35;
	}
	if (*(int*) (a2 + 8) == 0x6e6f6f70) {
		cm_RequestChangeBits(*(int*) (a1 + 4), 0x1c8, 4, 0x2000000, 0);
		return 0x35;
	}
	return 0;
}
