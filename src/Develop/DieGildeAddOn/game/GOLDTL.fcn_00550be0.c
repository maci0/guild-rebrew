extern char g_7f4ca0[];
extern char g_7f4ca4[];
extern unsigned char g_773d75;

unsigned short __cdecl gm_RandomMod(int n);
int __cdecl io_FormatTextBuffer(char* dst, int id, ...);
int __cdecl fcn_00545d40(int id, int arg, char* text1, unsigned char flags, int value, char* text2);
void __cdecl fcn_004c5150(int a1, int a2, char a3, int a4);
int __cdecl fcn_00546190(char* entity);

/* ADDRESS: GOLDTL 0x00550be0 */
void __cdecl fcn_00550be0(char* entity)
{
	char buf[0x418];

	if (*(int*) (entity + 0x70) == -2)
		goto done;
	if (*(int*) (entity + 0x70) != 0)
		return;
	if (*(unsigned char*) (entity + 0xac) > 0) {
		*(unsigned char*) (entity + 0xac) = *(unsigned char*) (entity + 0xac) - 1;
		return;
	}
	if ((double) (gm_RandomMod(0x100) & 0xffff) <
	    (double) (*(unsigned char*) (g_7f4ca0 + 0x80 + *(unsigned short*) (entity + 8) * 0x21c)) *
	        0.5 + 64.0) {

		io_FormatTextBuffer(buf, 0x10b5, *(unsigned int*) (entity + 0xb0) * 2);
		fcn_00545d40(*(int*) (g_7f4ca4 + *(unsigned short*) (entity + 8) * 0x21c),
		             *(int*) (g_7f4ca4 + *(unsigned short*) (entity + 8) * 0x21c),
		             buf, 0, 0x5ff, 0);
		fcn_004c5150(*(int*) (g_7f4ca4 + *(unsigned short*) (entity + 8) * 0x21c),
		             -1, g_773d75, *(unsigned int*) (entity + 0xb0) * 2);
	} else {		io_FormatTextBuffer(buf, 0x10b6,
		             (int) (*(unsigned int*) (entity + 0xb0) * 0.5f));
		fcn_00545d40(*(int*) (g_7f4ca4 + *(unsigned short*) (entity + 8) * 0x21c),
		             *(int*) (g_7f4ca4 + *(unsigned short*) (entity + 8) * 0x21c),
		             buf, 0, 0x5ff, 0);
		fcn_004c5150(*(int*) (g_7f4ca4 + *(unsigned short*) (entity + 8) * 0x21c),
		             -1, g_773d75,
		             (int) (*(unsigned int*) (entity + 0xb0) * 0.5f));
	}
done:
	fcn_00546190(entity);
}
