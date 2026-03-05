// FUNCTION: SERVER 0x1000e8d0
// STATUS: STUB
// ORIGIN: GAME
// SIZE: 239
// CFLAGS: /O2 /Gd
// SYMBOL: _ExWriteEntityFields

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

extern int __cdecl get_field_by_type(char*, int);
extern int __cdecl ResolveEntityById(void**, void**, void**, int);
extern void __cdecl LogMessageInternal(const char*, uint, const char*, int);

extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
extern char s_cm_ExSetAttribute___Invalid_Id_1002d0d4[];

int __cdecl ExWriteEntityFields(int param_1, char* param_2)
{
	char cVar1;
	int iVar5;
	char* pcVar7;
	char* pcVar8;
	uint uVar9;
	int iVar4;
	void* pvStack_8;
	void* pvStack_4;

	iVar4 = param_1;
	iVar5 = get_field_by_type((char*)param_1, *(int*)(param_1 + 0x10));
	*(int*)(iVar4 + 0x10) = iVar5;
	iVar5 = ResolveEntityById((void**)&param_1, &pvStack_8, &pvStack_4, iVar5);
	if (iVar5 == 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x32ed,
			s_cm_ExSetAttribute___Invalid_Id_1002d0d4,
			1
		);
		return 1;
	}
	if (param_1 != 0) {
		iVar5 = param_1;
	} else {
		iVar5 = (int)pvStack_8;
		if (pvStack_8 == (void*)0) {
			iVar5 = (int)pvStack_4;
		}
	}
	uVar9 = 0;
	pcVar7 = (char*)(iVar4 + 0x15);
	if (*(uchar*)(iVar4 + 0x14) != 0) {
		do {
			cVar1 = *pcVar7;
			iVar5 = (int)(signed char)pcVar7[1];
			pcVar7 = pcVar7 + 2;
			pcVar8 = (char*)((uint)*(ushort*)pcVar7 + iVar5);
			pcVar7 = pcVar7 + 2;
			pcVar8 = (char*)((uint)*(ushort*)(pcVar7 - 2) + iVar5);
			if (cVar1 == 1) {
				for (; iVar5 != 0; iVar5--) {
					*pcVar8 = *pcVar7;
					pcVar8++;
					pcVar7++;
				}
			} else if (cVar1 == 2) {
				for (; iVar5 != 0; iVar5--) {
					*(short*)pcVar8 = *(short*)pcVar7;
					pcVar7 += 2;
					pcVar8 += 2;
				}
			} else if (cVar1 == 4) {
				for (; iVar5 != 0; iVar5--) {
					*(int*)pcVar8 = *(int*)pcVar7;
					pcVar7 += 4;
					pcVar8 += 4;
				}
			}
			uVar9++;
		} while (uVar9 < *(uchar*)(iVar4 + 0x14));
	}
	if (param_2 != (char*)0) {
		*param_2 = '\x01';
	}
	return 0;
}
