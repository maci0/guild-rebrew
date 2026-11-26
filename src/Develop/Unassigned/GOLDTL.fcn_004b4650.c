


typedef struct {
	int f0;
	char pad4[0x18];
	int f1c;
} GM_ACTION_REC;
// SIZE 0x20

GM_ACTION_REC* __cdecl gm_FindMissionByEntityId(int);

int __cdecl gm_IncrementMissionActionCount(int entity_id, int kind)
{
	GM_ACTION_REC* p;

	p = gm_FindMissionByEntityId(entity_id);
	if (p == 0)
		return 0;
	switch (kind) {
	case 0xb:
	case 0x13:
	case 0x17:
	case 0x1c:
	case 0x28:
		if (p->f0 == kind)
			p->f1c++;
		return 1;
	case 0xc: case 0xd: case 0xe: case 0xf: case 0x10: case 0x11:
	case 0x12: case 0x14: case 0x15: case 0x16: case 0x18: case 0x19:
	case 0x1a: case 0x1b: case 0x1d: case 0x1e: case 0x1f: case 0x20:
	case 0x21: case 0x22: case 0x23: case 0x24: case 0x25:
	case 0x26: case 0x27:
		return 0;
	}
	return 0;
}
