extern int d3_ActiveScene;
extern char d3_SceneObjectSentinel[];
extern unsigned int tb_TimerDelay;
extern volatile int gm_GameTicks;
extern int d3_CurrentContextIndex;
extern int d3_ActiveCamera;
extern int d3_SceneRenderLock;
extern char g_6b8018;

void __cdecl d3_UpdateTextureScrollOffsets(unsigned int now);
char __cdecl d3_VisitSceneObjects(char* scene, char* node, unsigned int flags, char (__cdecl* cb)(char*, void*), void* ctx);
char __cdecl d3_UpdateSceneObjectAnimCallback(char* node, void* ctx);
void __cdecl d3_IncrementScenePass(int mode);


typedef struct {
	char* node;
	char pad[0x3d8];
} D3_SCENE_CTX_ENTRY;
// SIZE 0x3dc

/* Flushes cached timing and walks the scene tree, then refreshes both
 * frame-rate counters. Re-entrant calls only run the trailing mode hook. */
/* ADDRESS: GOLDTL 0x0043b170 */
/* ADDRESS: GOLDDE 0x00433f30 */
void __cdecl d3_UpdateScene(unsigned int flags, char force, unsigned int mode, char deep)
{
	if (d3_SceneRenderLock < 0) {
		d3_SceneRenderLock = 0;
	}
	if (!g_6b8018 || d3_SceneRenderLock != 0 || !d3_ActiveCamera) {
		return;
	}
	d3_SceneRenderLock = 1;
	if (force) {
		unsigned int now;
		unsigned int elapsed;
		unsigned int frames;
		unsigned int scale;
		unsigned int fl;
		int i;
		D3_SCENE_CTX_ENTRY* entry;
		char* node;

		now = gm_GameTicks;
		d3_UpdateTextureScrollOffsets(now);
		fl = flags | 0x181;
		d3_VisitSceneObjects((char*) d3_ActiveScene, 0, fl, d3_UpdateSceneObjectAnimCallback, (void*) now);
		if (deep) {
			i = 0;
			entry = (D3_SCENE_CTX_ENTRY*) 0x1043340;
			do {
				if (i != d3_CurrentContextIndex) {
					node = entry->node;
					if (node != 0 && node != d3_SceneObjectSentinel) {
						do {
							d3_VisitSceneObjects((char*) d3_ActiveScene, node, fl, d3_UpdateSceneObjectAnimCallback, (void*) (now | 0x80000000));
							node = *(char**) (node + 0x1f4);
						} while (node != d3_SceneObjectSentinel);
					}
				}
				i++;
				entry++;
			} while ((int) entry < (int) 0x1052a40);
		}
		scale = tb_TimerDelay;
		elapsed = now - *(unsigned int*) 0x6b806c;
		frames = ++*(unsigned int*) 0x6b8070;
		if (elapsed > 60 && elapsed > 0) {
			*(unsigned int*) 0x6b8070 = 0;
			*(unsigned int*) 0x6b806c = now;
			*(unsigned int*) 0x6b8048 = frames * 1000 / (elapsed * scale);
		}
		elapsed = now - *(unsigned int*) 0x6b8074;
		frames = ++*(unsigned int*) 0x6b8078;
		if (elapsed > 10 && elapsed > 0) {
			*(unsigned int*) 0x6b8078 = 0;
			*(unsigned int*) 0x6b8074 = now;
			*(unsigned int*) 0x6b804c = frames * 1000 / (elapsed * scale);
		}
	}
	d3_IncrementScenePass(mode);
	d3_SceneRenderLock--;
}
