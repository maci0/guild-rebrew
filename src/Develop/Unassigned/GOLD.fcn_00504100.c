/* ADDRESS: GOLD 0x00504100 */
int __cdecl gm_MapJobClassToSkillPair(unsigned int jobClass, int* primarySkill, int* secondarySkill)
{
	switch (jobClass) {
	case 11: *primarySkill = 2; *secondarySkill = 3; return 1;
	case 9: *primarySkill = 0; *secondarySkill = 4; return 1;
	case 7: *primarySkill = 4; *secondarySkill = 1; return 1;
	case 6: *primarySkill = 0; *secondarySkill = 1; return 1;
	case 8: *primarySkill = 0; *secondarySkill = 3; return 1;
	case 1: *primarySkill = 1; *secondarySkill = 0; return 1;
	case 5: *primarySkill = 1; *secondarySkill = 0; return 1;
	case 12: *primarySkill = 3; *secondarySkill = 2; return 1;
	case 3: *primarySkill = 1; *secondarySkill = 0; return 1;
	case 10: *primarySkill = 3; *secondarySkill = 2; return 1;
	case 2: *primarySkill = 1; *secondarySkill = 0; return 1;
	case 16: *primarySkill = 1; *secondarySkill = 0; return 1;
	case 4: *primarySkill = 1; *secondarySkill = 2; return 1;
	case 13: *primarySkill = 2; *secondarySkill = 0; return 1;
	}
	*primarySkill = 1; *secondarySkill = 0; return 1;
}
