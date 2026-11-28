#include <stdio.h>

// SIZE 0x64
struct tok_4291c0 {
	int type;
	union {
		char text[0x60];
		int num;
	} u;
};

// SIZE 0x10
struct frame_4291c0 {
	int pos;
	int x4;
	int kind;
	unsigned char open;
	char padd[3];
};

// SIZE 0x40 (f[] runs on past the declared element)
struct stack_4291c0 {
	char pad0[8];
	int count;
	char padc[0x24];
	struct frame_4291c0 f[1];
};

extern int g_6b7ec4;
extern char* evt_MemberScopeScript;

void __cdecl evt_ReadToken(int lex, struct tok_4291c0* t);
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);
void __cdecl evt_RequestScriptExit(char* g);
int __cdecl evt_PopCallFrame(char* g);
void __cdecl evt_ParseWhile(void);
void __cdecl evt_ParseIfHead(void);
void __cdecl evt_IncludeScript(void);
void __cdecl evt_ReturnFromFunction(void);
void __cdecl evt_SetScriptFlowState1(void);
void __cdecl evt_SetScriptFlowState2(void);
void __cdecl evt_ClearScriptFlowState(void);
void __cdecl evt_TrySkipIfFalseBlock(void);
void __cdecl evt_ExecuteCommand(int);
void __cdecl evt_ParseVariableAssignment(int);
void __cdecl evt_EnterFunction(char*, int);
int __cdecl evt_ParseSymbolDeclaration(char*, int);


/* Runs script statements until a block end (keyword 10), token type 12, or
 * the running flag at g+0x124 clears. */
/* ADDRESS: GOLDTL 0x004291c0 */
/* ADDRESS: GOLDDE 0x00423be0 */
int __cdecl evt_ExecuteStatements(char* g)
{
	struct tok_4291c0 t;
	char msg[0x100];
	char msg2[0x100];
	struct stack_4291c0* s;
	int n;

	g_6b7ec4 = 0;
	do {
		evt_ReadToken(*(int*) (g + 0x118), &t);
		if (t.type == 1) {
			(*(int*)&evt_MemberScopeScript) = 0;
			if (t.u.num == 9) {
				s = *(struct stack_4291c0**) (g + 0xc28);
				if (s->count > 0) {
					s->count--;
					s = *(struct stack_4291c0**) (g + 0xc28);
					if (s->f[s->count].pos != 0 && s->f[s->count].kind == 1) {
						*(int*) (g + 0x118) = s->f[s->count].pos;
					}
					return 0;
				}
				if (evt_PopCallFrame(g) == 0) {
					evt_RequestScriptExit(g);
				}
				return 0;
			}
		} else if (t.type == 10) {
			(*(int*)&evt_MemberScopeScript) = 0;
			switch (t.u.num) {
			case 1:
				evt_ParseWhile();
				break;
			case 2:
				evt_ParseIfHead();
				break;
			case 4:
				evt_TrySkipIfFalseBlock();
				break;
			case 5:
				evt_IncludeScript();
				break;
			case 6:
				evt_SetScriptFlowState1();
				break;
			case 8:
				evt_SetScriptFlowState2();
				break;
			case 7:
				evt_ClearScriptFlowState();
				break;
			case 3:
				evt_ReturnFromFunction();
				break;
			default:
				sprintf(msg2, "Keyword is not surported!");
				evt_LogScriptError(g, *(int*) (g + 0x118), msg2);
				evt_RequestScriptExit(g);
				return 0;
			}
		} else if (t.type == 4) {
			evt_ExecuteCommand(t.u.num);
		} else if (t.type == 2) {
			evt_ParseVariableAssignment(t.u.num);
		} else if (t.type == 3) {
			evt_EnterFunction(g, t.u.num);
		} else if (t.type == 8) {
			evt_ParseSymbolDeclaration(g, t.u.num);
		} else if (t.type == 11) {
			(*(int*)&evt_MemberScopeScript) = t.u.num;
			(*(int*) (g + 0x118))++;
		} else if (t.type != 12) {
			sprintf(msg, "Unknown symbol : '%s'", t.u.text);
			evt_LogScriptError(g, *(int*) (g + 0x118), msg);
			evt_RequestScriptExit(g);
		}
	} while ((*(unsigned char*) (g + 0x124) & 1) && t.type != 12 && !(t.type == 1 && t.u.num == 10));
	if (t.type == 1 && t.u.num == 10) {
		s = *(struct stack_4291c0**) (g + 0xc28);
		n = s->count;
		if (n > 1 && s->f[n - 1].pos != 0 && s->f[n - 1].open != 0) {
			s->count = n - 1;
			s = *(struct stack_4291c0**) (g + 0xc28);
			if (s->f[s->count].kind == 1) {
				*(int*) (g + 0x118) = s->f[s->count].pos;
			}
		}
	}
	if (t.type == 12) {
		*(int*) (g + 0x124) &= ~1;
	}
	return 0;
}
