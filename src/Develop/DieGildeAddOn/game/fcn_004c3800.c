unsigned short __cdecl gm_RandomMod(int);
float __cdecl fcn_0050f980(int, int, int);
int __cdecl fcn_0050cce0(void *, void *, int);
int __cdecl fcn_0050ce20(void *, void *, int);
void __cdecl fcn_004c3030(int, int, int, int);

/* ADDRESS: GOLDTL 0x004c3800 */
void __cdecl fcn_004c3800(void *arg)
{
	volatile int flag;
	unsigned char slot[0xb8];
	int ret;
	void *obj;
	unsigned char *ent;
	int score;
	int r;

	flag = 0;
	r = gm_RandomMod(3);
	obj = *(void **) (*(int *) ((char *) arg + 0x34) + 0x204);
	if (obj == 0)
		return;
	ent = *(unsigned char **) ((char *) obj + 0x16c);
	score = (int) fcn_0050f980(*(unsigned short *) 0x774970, *(unsigned short *) (ent + 0x27), 1) / 33;
	if (*ent == 0x20 || *ent == 0x1f || *ent == 0x1e)
		ret = fcn_0050ce20(ent, slot, 0);
	else
		ret = fcn_0050cce0(ent, slot, 0);
	if (ret != 0) {
		if (*(int *) (slot + 4) == 0)
			flag = 1;
	}

	if (score == 0) {
		if (flag)
			fcn_004c3030(*(unsigned short *) obj, *(int *) 0x772e7c, (int) 0x68a994, 3);
		else
			fcn_004c3030(*(unsigned short *) obj, *(int *) 0x772e7c, (int) 0x68a994, r);
		return;
	}
	if (score == 1) {
		if (flag)
			fcn_004c3030(*(unsigned short *) obj, *(int *) 0x772e7c, (int) 0x68a984, 3);
		else
			fcn_004c3030(*(unsigned short *) obj, *(int *) 0x772e7c, (int) 0x68a984, r);
		return;
	}
	if (score < 2)
		return;
	if (flag)
		fcn_004c3030(*(unsigned short *) obj, *(int *) 0x772e7c, (int) 0x68a978, 3);
	else
		fcn_004c3030(*(unsigned short *) obj, *(int *) 0x772e7c, (int) 0x68a978, r);
}
