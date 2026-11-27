
// SIZE 0x30
typedef struct {
	char pad[0x24];
	int n;
	char pad2[0x30 - 0x28];
} EVT_VAR_INFO;

// SIZE 0x124
typedef struct {
	char pad[0x108];
	EVT_VAR_INFO* recs;
	int f10c;
	int a;
	int b;
	int f118;
	int f11c;
	int c;
} EVT_SCRIPT_SIZE_INFO;

int __cdecl evt_CalcScriptMemSize(EVT_SCRIPT_SIZE_INFO* s)
{
	int n;
	int i;

	n = s->a * 0x14c + s->b * 0x30 + s->c + 0xc98;
	for (i = 0; i < s->b; i++) {
		n += s->recs[i].n * 4;
	}
	return n;
}
