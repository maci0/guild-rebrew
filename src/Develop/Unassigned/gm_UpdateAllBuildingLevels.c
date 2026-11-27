


// fcn_004f4d10 — for(i=0;i<0x300;i++) fcn_004f4970(i).

int __cdecl gm_CheckWealthRankMilestone(int);

void __cdecl gm_UpdateAllBuildingLevels(void)
{
	int i;
	for (i = 0; i < 0x300; i++) {
		gm_CheckWealthRankMilestone(i);
	}
}

