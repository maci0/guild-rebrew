// FUNCTION: GOLDTL 0x0053f920
// SIZE: 337

extern int g_774714;
extern int g_774950;
extern int g_7f4c00;
extern int g_774954;
extern int g_774958;
extern char g_774965;
extern int g_68a9cc;
extern int g_7749cc;
extern int g_774934;
extern int g_7747bc;
extern int g_7e2470;
extern int g_7747c0;
extern int g_7747c4;
extern int g_7747c8;
extern int g_7747cc;
extern int g_6b5c2c;
extern int g_774978;
extern int g_7e2aa0;
extern int g_7746cc;
extern int g_7746c4;
extern int g_7746c8;

void __cdecl fcn_00545430(void);
void __cdecl fcn_00538060(void);
void __cdecl fcn_0042de90(void*, int);
void __cdecl fcn_0042df30(void*, int);
void __cdecl fcn_00546ed0(void);
void __cdecl fcn_004f6740(void);
void __cdecl fcn_004fa690(void);
int __cdecl fcn_0044c310(char*, char*);
int __cdecl fcn_00422dc0(char*, int);
void __cdecl fcn_00420200(int);
void __cdecl fcn_005458b0(void);
void __cdecl fcn_00533880(void);
void __cdecl fcn_005338a0(void);
void __cdecl fcn_005c80c0(void);
void __cdecl fcn_004bbd20(void);
void __cdecl fcn_0040bdc0(void);
void __cdecl fcn_00591c40(void);
void __cdecl fcn_00510900(void);
void __cdecl fcn_004e71a0(void);

void __cdecl fcn_0053f920(void)
{
	fcn_00545430();
	g_774714 = 1;
	g_774950 = 1;
	g_7f4c00 = 2;
	g_774954 = 0;
	g_774958 = 0;
	g_774965 = 0;
	g_68a9cc = 2;
	fcn_0042de90(fcn_00538060, 0x47);
	fcn_0042df30(fcn_00538060, 1);
	fcn_00546ed0();
	fcn_004f6740();
	fcn_004fa690();
	g_7749cc = fcn_0044c310("Buch", "Buch");
	if (g_774934 != 0) {
		g_7747bc = fcn_00422dc0("natur\\regen.sbf", 0);
		g_7e2470 = fcn_00422dc0("natur\\wind.sbf", 0);
		g_7747c0 = fcn_00422dc0("natur\\blitzunddonner.sbf", 0);
		g_7747c4 = fcn_00422dc0("objekte\\buecher.sbf", 0);
		g_7747c8 = fcn_00422dc0("objekte\\TuerenUndRaeume.sbf", 0);
		g_7747cc = fcn_00422dc0("objekte\\Transporter.sbf", 0);
		g_6b5c2c = fcn_00422dc0("Lebewesen\\schritte.sbf", 1);
	}
	fcn_00420200(3000);
	fcn_005458b0();
	fcn_00533880();
	fcn_005338a0();
	g_774978 = 0;
	g_7e2aa0 = 0;
	g_7746cc = 0;
	g_7746c4 = 0;
	g_7746c8 = 0;
	fcn_005c80c0();
	fcn_004bbd20();
	fcn_0040bdc0();
	fcn_00591c40();
	fcn_00510900();
	fcn_004e71a0();
}
