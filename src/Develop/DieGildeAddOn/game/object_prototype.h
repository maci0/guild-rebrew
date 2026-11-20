#ifndef OBJECT_PROTOTYPE_H
#define OBJECT_PROTOTYPE_H

/*
 * Shared record view intended for GoldTL, Gold and server contexts. It can
 * replace fcn_0050b980_Rec in GOLDTL.eval_ObjektPreis2Credits.c and other
 * compatible partial views after migrating their callers.
 *
 * The name begins at +0x01; its original extent and termination are not
 * established. Preserve whole-record byte views for unbounded string and
 * indexed accesses. Signed and unsigned interpretations of value_022 occur.
 *
 * Resolved:
 * - Pointer declarations are opt-in: each existing char *, unsigned char *,
 *   or int lpObjektePROT declaration can include the default header.
 *   Select a char * declaration only after reviewing that compilation context;
 *   the server and client symbols do not imply shared storage or contents.
 * - Existing fcn_0050b980_Rec callers use type, sub, cap, weight, child,
 *   div and cache. Migrate them respectively to kind, subtype, value_022,
 *   ingredient_amounts, ingredient_ids, value_036 and price_cache; this type
 *   does not silently rename the old members.
 * - The layout is proposed for all three targets, so no Gold-only exclusion
 *   is inferred. Validate target bindings and the pinned-compiler layout.
 */

#pragma pack(push, 1)
/* SIZE 0x41 */
typedef struct OBJECT_PROTOTYPE {
    unsigned char kind;                   /* 0x00: category/type */
    char name_bytes[0x20];                /* 0x01..0x20: name starts here */
    unsigned char subtype;                /* 0x21: subtype or selector */
    unsigned int value_022;               /* 0x22: price/production value */
    unsigned short ingredient_amounts[4]; /* 0x26..0x2d: paired quantities */
    unsigned short ingredient_ids[4];     /* 0x2e..0x35: object IDs */
    unsigned short value_036;             /* 0x36: quantity/divisor */
    int price_cache;                      /* 0x38: calculated-price cache */
    unsigned char unk_03c[4];             /* 0x3c..0x3f: unclassified */
    unsigned char value_040;              /* 0x40: requirement/display value */
} OBJECT_PROTOTYPE;
#pragma pack(pop)

/* Opt in only in contexts whose existing declarations use char *. */
#if defined(OBJECT_PROTOTYPE_DECLARE_LPOBJEKTE_CHAR_POINTER)
extern char *lpObjektePROT;
#endif
#if defined(OBJECT_PROTOTYPE_DECLARE_ITEM_TABLE_CHAR_POINTER)
extern char *g_item_def_table;
#endif

#endif /* OBJECT_PROTOTYPE_H */
