/* cm_ChkMoveCredits - proper C */

extern int __cdecl gm_GetFieldByType(char*, int);
extern int __cdecl gm_ResolveEntityById(void**, void**, void**, int);
extern int __cdecl gm_QueryEntitySum(int, unsigned char);
extern void __cdecl LogMessageInternal(char*, int, char*, int);
// GLOBAL: SERVER 0x1002c748
extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
// GLOBAL: SERVER 0x1002c7a4
extern char s_cm_ChkMoveCredits____Invalid__qu_1002c7a4[];
// GLOBAL: SERVER 0x1002c774
extern char s_cm_ChkMoveCredits____Not_enough_m_1002c774[];

/* Validation handler: resolves the credit source entity and checks
 * that it has enough funds for the requested transfer.  Returns 1 on
 * invalid entity or insufficient balance, 0 when the move is allowed.
 *
 * Byte-match note: same Finding 7-family allocator fixed-point (docs/
 * msvc6-allocator.md Finding 33) — the reference hoists the arg3
 * address lea above the pre-resolve field store (esi-based, folded
 * `mov [esi+0x14],eax`); MSVC6 8168 emits the out-param leas after the
 * arg4 push and either reloads the param for the store or materializes
 * `lea esi,[eax+0x14]` with an extra push.  The -1 early return, the
 * entity selection, the raw-byte gm_QueryEntitySum call (unsigned-char
 * 2nd param stops zero-extension) and the sub/jns balance check all
 * match structurally. */

// FUNCTION: SERVER 0x1000cb20
// SIZE: 171

int __cdecl cm_ChkMoveCredits(int cmd, char* result)
{
	void* entity_or_node;
	void* ent_c;
	int field;
	int resolved;
	int* sum_src;

	(void) result;

	if (*(int*) (cmd + 0x14) == -1) {
		return 0;
	}
	field = gm_GetFieldByType((char*) cmd, *(int*) (cmd + 0x14));
	*(int*) (cmd + 0x14) = field;
	if (gm_ResolveEntityById((void**) &resolved, &entity_or_node, &ent_c, field) == 0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x22f9,
		                   s_cm_ChkMoveCredits____Invalid__qu_1002c7a4, 1);
		return 1;
	}
	if (resolved != 0)
		sum_src = (int*) (resolved + 0x5d);
	else if (entity_or_node != 0)
		sum_src = (int*) ((char*) entity_or_node + 0x14);
	else
		sum_src = (int*) ((char*) ent_c + 0x178);
	if (gm_QueryEntitySum(*sum_src, *(unsigned char*) (cmd + 0x1c)) - *(int*) (cmd + 0x1d) < 0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x231b,
		                   s_cm_ChkMoveCredits____Not_enough_m_1002c774, 1);
		return 1;
	}
	return 0;
}
