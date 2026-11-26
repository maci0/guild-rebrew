/* Owned (both targets) by src/GOLDTL.fcn_00549330.c. */
extern char g_7f4ca4[];




void* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_004ae080(char*, char*, char**, int*);
int __cdecl atoi(char*);
int __cdecl fcn_004ae0f0(int);
int __cdecl fcn_004ae260(int);
void __cdecl io_FormatTextBuffer(void*, int, ...);

/* The reference builds a frame (push ebp; mov ebp,esp; sub esp,0x20c) and
 * addresses the 0x200 scratch buffer off ebp; section 13 of
 * archived docs/msvc6-c-shapes.md. */
#pragma optimize("y", off)
int __cdecl fcn_004afa10(int selectionMode, int a2, int a3, char* a4, int a5)
{
	char buf[0x200];
	char* entityRecord = 0;
	int v2 = 0;
	int n = 0x200;
	char* p = buf;
	char* slotCursor;
	int i;
	int parsedOption;
	int flag;

	/* The original's zero-fill is the 24-byte hand-written block-fill prelude
	 * (archived docs/msvc6-c-shapes.md section 11, archived docs/codegen-walls.md section 6b);
	 * recorded C probes did not emit it.  Reproduced as a block-fill with ordinary
	 * named operands. */
	__asm {
		mov edi, p
		mov ebx, n
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
	{
		int len;

		fcn_004ae080(a4, buf, &p, &len);
		if (len != 1) {
			return 0;
		}
		parsedOption = atoi(a4 + (int) p);
	}
	if (parsedOption < 0 || parsedOption > 2) {
		return 0;
	}
	flag = 1;
	if (parsedOption == 0) {
		flag = 0;
	} else {
		v2 = (parsedOption != 1);
	}
	if (selectionMode == 1) {
		entityRecord = (char*) gm_LookupEntityRecordById(*(int*) ((char*) a2 + a3 * 8 + 4));
		if (entityRecord == 0 || *(unsigned char*) (entityRecord + 8) <= 0) {
			return 0;
		}
	} else {
		i = 0;
		slotCursor = g_7f4ca4;
		while ((int) slotCursor < (int) (g_7f4ca4 + 0x65400)) {
			if (fcn_004ae0f0(*(int*) slotCursor) != 0) {
				entityRecord = slotCursor - 4;
				if (flag == 0 || *(unsigned char*) (slotCursor + 5) == v2) {
					if (fcn_004ae260(i) != 0) {
						break;
					}
					entityRecord = 0;
				}
			}
			slotCursor += 0x21c;
			i++;
		}
		if (entityRecord == 0) {
			return 0;
		}
	}
	if (selectionMode == 0) {
		*(int*) ((char*) a2 + a3 * 8 + 4) = *(int*) ((char*) entityRecord + 4);
	}
	io_FormatTextBuffer((void*) a5, (int) buf, *(unsigned short*) entityRecord);
	return 1;
}
