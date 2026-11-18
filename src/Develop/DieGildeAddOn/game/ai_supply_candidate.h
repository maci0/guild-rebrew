#ifndef AI_SUPPLY_CANDIDATE_H
#define AI_SUPPLY_CANDIDATE_H

/* Native candidate stride is 0x18. */
typedef struct {
	char* entity;
	int unk_04;
	int unk_08;
	int limit;
	float score;
	int unk_14;
} AI_SUPPLY_CANDIDATE;

extern AI_SUPPLY_CANDIDATE g_868c40[];

#endif
