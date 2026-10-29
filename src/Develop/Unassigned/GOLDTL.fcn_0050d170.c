


extern unsigned char* lpGebaeudePROT;
extern char* lpObjektePROT;

float __cdecl eval_ObjektPreis2Credits(int k, int n);

int __cdecl fcn_0050d170(int k)
{
	unsigned char* t;
	int total;
	int i;
	unsigned short w;
	int rec;

	t = lpGebaeudePROT + k * 0x24d;
	total = *(int*) (t + 0x249) * 0xf00;
	for (i = 0; i < 0x40; i++) {
		w = ((unsigned short*) (t + 0x23))[i];
		if (w == 0) {
			break;
		}
		rec = (*(int*)&lpObjektePROT) + (w & 0x7fff) * 0x40 + (w & 0x7fff);
		if (w & 0x8000) {
			total = (int) (eval_ObjektPreis2Credits(*(unsigned char*) rec, 100) + total);
		}
	}
	return total;
}
