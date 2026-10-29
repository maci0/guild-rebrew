extern char g_7f4ca0[];
extern int g_14ce8e0;
extern int g_774654;

int __cdecl fcn_00502cd0(int container_id, int arg_count, ...);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190();
int __cdecl fcn_00510170(char*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x005aceb0 */
void __cdecl fcn_005aceb0(char* obj)
{
	char* entry;
	int h;
	int count;
	int next;

	count = 0;
	if (fcn_00502cd0(*(int*) (obj + 0x5d), 1, 0, 0xba) == 0) {
		return;
	}
	h = fcn_00470820(0, 0, "locations\\kerker\\kerkerplan.ob");
	fcn_00471b60(h);
	d2_SetForm(h, 1);
	fcn_00519190(0x19ad);
	d2_SetForm(h, 1);
	entry = g_7f4ca0;
	do {
		if (fcn_00510170(entry) != 0) {
			fcn_00519190(0x19ae, count + 1, *(unsigned short*) entry);
			count++;
		}
		entry += 0x21c;
	} while ((int) entry < 0x85a0a0);
	if (count == 0) {
		fcn_00519190(0x19af);
	}
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0(fcn_005aceb0, 0x677c7) != 0);
	fcn_00532ef0();
	fcn_00471e30(h);
}
