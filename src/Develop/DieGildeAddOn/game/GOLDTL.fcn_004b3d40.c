extern char g_10069a0[];
extern int g_10069a4;
extern int g_10069a8;
extern char g_10069c0;


void __cdecl sim_SetSyncParams(void*, int, int, int);

void __cdecl gm_SetFirstMissionJob(int entityId, int missionOp)
{
	(*(int*)g_10069a0) = missionOp;
	g_10069a4 = entityId;
	g_10069a8 = 0;
	sim_SetSyncParams(&g_10069a8, 0, 0, 0);
	g_10069c0 = 0;
}
