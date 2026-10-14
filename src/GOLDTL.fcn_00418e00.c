extern int g_67a370;
extern int g_677680;

// SIZE 0x54
struct snd_418e00 {
	char pad0[0x34];
	char* voice;
	char* obj;
	int idle;
	char pad40[4];
	int fade;
	char pad48[8];
	int keep;
};

extern char* g_6b5d08;

void __cdecl fcn_004237f0(char*, int);
void __cdecl fcn_004225e0(char*, int);
void __cdecl fcn_004190d0(struct snd_418e00*);
void __cdecl fcn_00418fb0(struct snd_418e00*);
int __cdecl fcn_00423460(char*);
void __cdecl fcn_00418d70(struct snd_418e00*);

/* ADDRESS: GOLDTL 0x00418e00 */

/* Updates the positional sound sources: silences the ones outside the
 * current room, pans the others and releases finished voices. */
void __cdecl fcn_00418e00(void)
{
	int i;

	if (((struct snd_418e00*)g_6b5d08) == 0) {
		return;
	}
	for (i = 0; i < g_677680; i++) {
		if (((struct snd_418e00*)g_6b5d08)[i].obj == 0) {
			continue;
		}
		if (*(char**) (((struct snd_418e00*)g_6b5d08)[i].obj + 0x20c) != ((char*)g_67a370)) {
			if (((struct snd_418e00*)g_6b5d08)[i].voice == 0) {
				continue;
			}
			fcn_004237f0(((struct snd_418e00*)g_6b5d08)[i].voice, 0);
			*(unsigned int*) (((struct snd_418e00*)g_6b5d08)[i].voice + 0x14) |= 8;
			if (((struct snd_418e00*)g_6b5d08)[i].keep == 0) {
				fcn_004225e0(((struct snd_418e00*)g_6b5d08)[i].voice, 0);
				((struct snd_418e00*)g_6b5d08)[i].voice = 0;
			}
			continue;
		}
		fcn_004190d0(&((struct snd_418e00*)g_6b5d08)[i]);
		fcn_00418fb0(&((struct snd_418e00*)g_6b5d08)[i]);
		if (((struct snd_418e00*)g_6b5d08)[i].voice == 0 || fcn_00423460(((struct snd_418e00*)g_6b5d08)[i].voice) != 0) {
			continue;
		}
		((struct snd_418e00*)g_6b5d08)[i].idle++;
		if (((struct snd_418e00*)g_6b5d08)[i].idle > 500 && ((struct snd_418e00*)g_6b5d08)[i].keep == 0) {
			if (((struct snd_418e00*)g_6b5d08)[i].fade != 0) {
				fcn_00418d70(&((struct snd_418e00*)g_6b5d08)[i]);
			} else {
				fcn_004225e0(((struct snd_418e00*)g_6b5d08)[i].voice, 0);
				*(unsigned int*) (((struct snd_418e00*)g_6b5d08)[i].voice + 0x14) |= 8;
				((struct snd_418e00*)g_6b5d08)[i].voice = 0;
			}
		}
	}
}
