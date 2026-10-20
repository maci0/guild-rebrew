extern char* g_99ec10;
extern char g_7f4ca0[];
extern unsigned char g_773d75;
extern unsigned short g_7f3ee4;
extern int g_90d520[];

unsigned short __cdecl gm_RandomMod(unsigned short);
int __cdecl fcn_004c51f0(int, int, int, int, unsigned char, int);
void __cdecl fcn_00546190(char*);
int __cdecl fcn_00500cb0(char*, int);
int __cdecl gm_ResolveEntityById(void**, void**, void**, int);
char* __cdecl gm_NextEntityQueryMatch(void);
char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl fcn_005039e0(int);
void __cdecl fcn_0051af00(char*, int, int, int, int);
void __cdecl fcn_00529160(int, int, int, int);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);

/* ADDRESS: GOLDTL 0x00572a50 */

/* Advances a message action through its states, resolves the sender entity
 * and updates the message-table entry it belongs to. */
void __cdecl fcn_00572a50(char* obj)
{
	int ref1;
	int ref2;
	int count;
	char msg[0x200];
	char* ent;
	char* rec;
	unsigned short* p;
	int off;
	int more;
	int n;
	int total;

	switch (*(int*) (obj + 0x70)) {
	case 0:
		*(int*) (obj + 0x70) = *(int*) (obj + 0x70) + 1;
		return;
	case 1:
		if (*(int*) (obj + 0x14) != 0 || *(int*) (obj + 0x18) != 0) {
			if (fcn_00500cb0(obj + 0x52, 0x7f4c00) >= 0) {
				return;
			}
			gm_ResolveEntityById((void**) &ref1, 0, 0, *(int*) (obj + 0xac));
			if (ref1 == 0) {
				*(int*) (obj + 0x70) = -1;
				return;
			}
			gm_ResolveEntityById(0, (void**) &ref2, 0, *(int*) (obj + 0xb0));
			ent = fcn_00502cd0(*(int*) (ref2 + 0x14), 1, 4, 0x17);
			while (ent != 0) {
				if (*(int*) (ent + 0xe) == 1) {
					break;
				}
				ent = gm_NextEntityQueryMatch();
			}
			if (ent != 0) {
				fcn_004c51f0(*(int*) (ref2 + 2), -1, *(unsigned short*) ent,
					1, g_773d75, 0);
				fcn_005039e0(ref1);
				for (count = 0; count < (int) g_7f3ee4; count++) {
					n = g_90d520[count];
					rec = g_99ec10 + n * 0x40 + n;
					if (*rec == 0x17) {
						continue;
					}
					more = 1;
					off = 0;
					p = (unsigned short*) (rec + 0x2e);
					do {
						if (off >= 4) {
							if (more) {
								fcn_004c51f0(*(int*) (ref2 + 2), -1,
									g_90d520[count], 3, g_773d75, 0);
							}
							break;
						}
						if (*p != 0 && *p != *(unsigned short*) ent) {
							rec = fcn_00502cd0(*(int*) (ref2 + 0x14),
								1, 0, *p);
							if (rec == 0 || *(int*) (rec + 0xe) < 2) {
								more = 0;
							}
						}
						off++;
						p++;
					} while (more);
				}
				rec = g_99ec10 + *(unsigned short*) ent * 0x41;
				total = ((unsigned short) gm_RandomMod(*(unsigned short*) (rec + 0x36) * 0x1e) +
					*(unsigned short*) (rec + 0x36) * 0x1e) *
					(*(int*) (obj + 0x18) + *(int*) (obj + 0x14));
				fcn_004c51f0(*(int*) (obj + 0xb4), -1, *(unsigned short*) ent,
					total, g_773d75, 0);
				fcn_0051af00(msg, 0x1bb8, *(unsigned short*) ent * 2 + 0x9a8,
					ref1, total);
				he_MessageBoxQuickjump(
					*(int*) (g_7f4ca0 + *(unsigned short*) ((char*) ref1 + 0x27) * 0x21c + 4),
					-1, msg, 0, 0x5f1, *(int*) ((char*) ref1 + 1), -1, 0,
					"_NACHRICHTEN_HS_08");
			}
			for (p = (unsigned short*) 0x7f4ca0; (int) p < 0x85a0a0;
				p += 0x10e) {
				if (*(int*) ((char*) p + 0x17c) == (int) obj) {
					fcn_00529160(ref1, 0, *p, 0);
				}
			}
			fcn_00546190(obj);
			return;
		}
		break;
	case -2:
	case -1:
		for (p = (unsigned short*) 0x7f4ca0; (int) p < 0x85a0a0;
			p += 0x10e) {
			if (*(int*) ((char*) p + 0x17c) == (int) obj) {
				fcn_00529160(0, 0, *p, 0);
			}
		}
		break;
	default:
		return;
	}
	fcn_00546190(obj);
}
