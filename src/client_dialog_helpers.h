/* Declarations shared by the reconstructed TL client dialog and graph
 * helpers. Each entry names the source of its evidence. Sibling functions
 * are reconstructed and RELOC on Europa1400Gold_TL.exe; entries marked
 * "inferred" come from call sites inside one large row and still need
 * body-level confirmation.
 *
 * Conflicting declarations found while collecting this list:
 *  - fcn_0051af00 is variadic at every TL call site (buffer, id, then
 *    format arguments), but src/GOLD.fcn_0051af00.c declares it with no
 *    parameters. The call sites govern the TL target; the GOLD stub is
 *    not authoritative here.
 *  - fcn_00471f80 appears with one argument in several files and with
 *    two in fcn_005a4bb0.c. The two-argument form is kept and marked
 *    inferred.
 *  - fcn_004c51a0 is declared returning int in some files and void in
 *    others; int is kept.
 *  - fcn_0050d320 is defined as (char* entity, char season) in
 *    GOLDTL.fcn_0050d320.c:7 and declared (char*, char) in
 *    GOLDTL.PrepareBuergerrecht.c:3 and GOLDTL.fcn_004c0460.c:21, but
 *    call sites treat the entity as a short* record and the season as
 *    an unsigned char (GOLDTL.fcn_004976e0.c:6, GOLDTL.fcn_0049c310.c:11).
 *    The short pointer form with unsigned char is kept.
 *  - fcn_0049e900 is defined (int, short*, char*, char*, char*) in
 *    GOLDTL.fcn_0049e900.c:10 and declared with other shapes at
 *    GOLDTL.fcn_0048d6c0.c:11, GOLDTL.fcn_00497990.c:15,
 *    GOLDTL.fcn_0048e850.c:7, and with no arguments in
 *    GOLDTL.fcn_004a1130.c:124. The definition is kept.
 *  - fcn_004a4bb0 is defined (char*, char*, char*, char*, char*, int) in
 *    GOLDTL.fcn_004a4bb0.c:18 and declared with Cmd pointers, Blk24
 *    pointers, or int pointers at GOLDTL.fcn_0049e1e0.c:26,
 *    GOLDTL.fcn_0048d6c0.c:10 and GOLDTL.fcn_0048e850.c:6. The Cmd
 *    pointer form matches the row 0x00498670 call sites and is kept;
 *    the middle argument may be an int mode.
 *  - fcn_00497ec0 is defined (int, short*, int, Cmd*, Cmd*) in
 *    GOLDTL.fcn_00497ec0.c:22 and declared (void) in
 *    GOLDTL.fcn_004a1130.c:42. The definition is kept.
 *  - g_868050 and g_90e094 appear as both char* and unsigned char*
 *    across files. unsigned char* is the majority form and is kept.
 *
 * Sample_99ec20 and g_99ec20[16] belong to client_types.h and are not
 * declared here: this header deliberately includes nothing yet.
 */
#ifndef CLIENT_DIALOG_HELPERS_H
#define CLIENT_DIALOG_HELPERS_H

/* Graph value passed by value to the graph drawers, SIZE 0x28.
 * Matched siblings 0x005d3980, 0x005d3ad0 and 0x005d3c20. */
typedef struct {
	int id;
	float a;
	float b;
	float c;
	char pad10[0x18];
} Cur;

/* Action packet passed between the AI selectors and the action runners,
 * SIZE 0x18. Same layout in GOLDTL.fcn_00497ec0.c, GOLDTL.fcn_0049e900.c
 * and GOLDTL.fcn_004a4bb0.c (there called Blk24). */
typedef struct Cmd {
	char kind;
	int f1;
	int f2;
	int f3;
	int f4;
	int f5;
} Cmd;

/* Lowest value drawn by the graph helpers, CLAMP0 bound.
 * Matched siblings 0x005d3ad0 and 0x005d3c20. */
extern double g_662950;

/* Initial maximum for the graph scaling loop.
 * Matched sibling 0x005d3c20. */
extern float g_662a94;

/* Current screen or menu mode, compared against 0x15..0x18. */
extern int g_14ce86c;

/* Dialog busy flag written while a modal dialog runs.
 * Used by fcn_005a4bb0 and row 0x00589d00. */
extern int g_774654;

/* Active player or team index byte. */
extern unsigned char g_773d75;

/* Entity table base, walked with a 0x21c stride. */
extern char g_7f4ca0[];

/* Current cursor or selection triple. Seen in row 0x00589d00. */
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;

/* Unit type table, indexed by the type byte of an entity record and
 * walked with a 0x24d stride. GOLDTL.fcn_004a4bb0.c. */
extern unsigned char* lpGebaeudePROT;

/* Entity record array walked with a 0xa9 stride (0xa900 bytes total).
 * GOLDTL.fcn_00497990.c and row 0x00498670. */
extern unsigned char* lpGebaeudeINST;

/* Graph and frame drawing. fcn_00472c30 draws one line segment.
 * Matched sibling 0x005d3c20. */
void __cdecl fcn_00472c30(int x0, int y0, int x1, int y1, int r, int g, int b);

/* Graph drawers, all matched RELOC. */
void __cdecl fcn_005d3980(Cur cur, int w, int h);
void __cdecl fcn_005d3ad0(Cur cur, int w, int h);
void __cdecl fcn_005d3c20(Cur cur, int w, int h);

/* Panel begin and window selection. */
void __cdecl fcn_00472e50(void);
int __cdecl fcn_0046f2c0(int win, int keep);

/* Dialog construction, from fcn_005a4bb0. */
void* __cdecl fcn_00470820(short a, short b, char* name);
void __cdecl d2_SetForm(int dlg, int stage);
int __cdecl fcn_00472250(int dlg, int a, int b);
void __cdecl fcn_00472380(int a, int b, int c, int d, int e);
int __cdecl io_AppendText(void* id, ...);
int __cdecl fcn_005373e0(void* fn, int message);
void __cdecl fcn_00471e30(int handle);
/* inferred: two-argument form from fcn_005a4bb0 */
int __cdecl fcn_00471f80(int handle, int player);

/* Entity value accessors. fcn_004c51a0 additionally returns int. */
void __cdecl fcn_004c4510(char* base, int entity_id);
void __cdecl fcn_004c4570(int a, int b, int off, void* value);
void __cdecl fcn_004c4670(int a, int b, int off, void* value);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c54c0(int a, int b, int value, int flag);
int __cdecl fcn_004c51a0(int a, int b, unsigned char kind, int amount);

/* Dialog text output. Variadic at every TL call site; see the conflict
 * note above. */
void __cdecl io_FormatTextBuffer(char* out, int id, ...);

/* inferred: seven stack arguments counted at row 0x00549c50 */
void __cdecl fcn_00545e80(int handle, int arg, char* text, int a, int b,
    int c, int d);

/* Dialog line with two text slots. */
int __cdecl fcn_00545d40(int id, int arg, char* text1, int flags, int value,
    char* text2);

/* Entity float value. */
float __cdecl fcn_0050bb50(int id, unsigned char kind);

/* AI action selection and scoring. fcn_00497ec0 picks the records for one
 * action code; fcn_0049e900 rates them and fills the two action packets;
 * fcn_004a4bb0 checks whether the unit can start the action. Types and
 * argument shapes come from their own definitions; see conflicts above. */
int __cdecl fcn_00497ec0(int action, short* target, int a2, Cmd* out1,
    Cmd* out2);
int __cdecl fcn_0049e900(int code, short* target, char* ent, char* out1,
    char* out2);
int __cdecl fcn_004a4bb0(int action, short* ent, int mode, Cmd* cmd,
    Cmd* out, int want);

/* Entity season/kind value. The entity is a short* record and the second
 * argument is the active player byte. */
int __cdecl fcn_0050d320(short* ent, unsigned char player);

#endif /* CLIENT_DIALOG_HELPERS_H */
