extern char* g_774a34;
extern int g_779ce0;
extern int g_779c6c;
extern int g_6a9b9c;
extern int g_772514;
extern char* g_1015ea0;
extern int g_14a5774;
extern int g_14a579c;
extern int g_14a595c[];
extern int g_14a57e0[];
extern int g_14a6538[];
extern int g_14b5d40;
extern int g_14b5d44;
extern unsigned char g_779c70;
extern unsigned char g_779c6b;
extern unsigned char g_779c71;
extern char g_779c72[];
extern char g_779c82[];
extern char g_6811b0[];

int __cdecl fcn_004ce190(int);
int __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_0046fac0(int, int, char*, int);
int __cdecl fcn_0064d41a(char*, char*, ...);

/* ADDRESS: GOLDTL 0x00593360 */
void __cdecl fcn_00593360(void)
{
	char buf[0x100];
	char* rec;
	int v;
	int i;
	int x;
	int y;
	int z;

	rec = (char*) fcn_004ce190(*(int*) (g_774a34 + g_779ce0 * 4 + 4));
	if (rec != 0)
		g_779c6c = *(int*) (rec + 0xc);
	fcn_004727a0(g_6a9b9c, 3);
	fcn_00519190((int) g_6811b0);
	i = *(int*) (g_1015ea0 + fcn_0046f740(5, 10, g_779c6c + 0x59a, g_772514) * 0x2f4 + 0x18) + 0xf;
	v = g_779c70 ? g_14a579c : g_14a5774;
	fcn_0064d41a(buf, "%s %s %s", v, g_779c72, g_779c82);
	y = *(int*) (g_1015ea0 + fcn_0046fac0(i, 10, buf, g_772514) * 0x2f4 + 0x1c) + 2;
	z = y + 0xa;
	if (g_779c70 == 1)
		v = g_14a595c[g_779c6b];
	else
		v = g_14a57e0[g_779c6b];
	fcn_0064d41a(buf, "%s: %s", g_14b5d40, v);
	fcn_0046fac0(i, z, buf, g_772514);
	v = g_14a6538[g_779c71];
	fcn_0064d41a(buf, "%s: %s", g_14b5d44, v);
	fcn_0046fac0(i, y + z, buf, g_772514);
}
