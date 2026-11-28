extern int g_772e7c;
extern unsigned short gm_LocalPlayerSlot;

unsigned short __cdecl gm_RandomMod(int);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);
int __cdecl gm_CollectBuildingStock(void *, void *, int);
int __cdecl gm_CollectStockEntries(void *, void *, int);
void __cdecl d3snd_PlaySoundEffect(int, int, int, int);

/* ADDRESS: GOLDTL 0x004c3800 */
void __cdecl d3snd_PlayShopFavorGreeting(void *arg)
{
	int flag;
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
	score = (int) gm_CalcEntityFavor(gm_LocalPlayerSlot, *(unsigned short *) (ent + 0x27), 1) / 33;
	if (*ent == 0x20 || *ent == 0x1f || *ent == 0x1e)
		ret = gm_CollectStockEntries(ent, slot, 0);
	else
		ret = gm_CollectBuildingStock(ent, slot, 0);
	if (ret != 0) {
		if (*(int *) (slot + 4) == 0)
			flag = 1;
	}

	if (score == 0) {
		if (flag)
			d3snd_PlaySoundEffect(*(unsigned short *) obj, g_772e7c, (int) 0x68a994, 3);
		else
			d3snd_PlaySoundEffect(*(unsigned short *) obj, g_772e7c, (int) 0x68a994, r);
		return;
	}
	if (score == 1) {
		if (flag)
			d3snd_PlaySoundEffect(*(unsigned short *) obj, g_772e7c, (int) 0x68a984, 3);
		else
			d3snd_PlaySoundEffect(*(unsigned short *) obj, g_772e7c, (int) 0x68a984, r);
		return;
	}
	if (score < 2)
		return;
	if (flag)
		d3snd_PlaySoundEffect(*(unsigned short *) obj, g_772e7c, (int) 0x68a978, 3);
	else
		d3snd_PlaySoundEffect(*(unsigned short *) obj, g_772e7c, (int) 0x68a978, r);
}
