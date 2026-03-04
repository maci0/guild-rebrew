/* Auto-generated from Ghidra via rebrew sync --pull-structs */
/* 85 structures exported */

#ifndef TYPES_H
#define TYPES_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

/* size: 16 */
typedef struct _4i {
    int a;  /* offset 0x0 */
    int b;  /* offset 0x4 */
    int c;  /* offset 0x8 */
    int d;  /* offset 0xc */
} _4i;

/* _CONTEXT skipped */

/* _CONTEXT skipped */

/* size: 8 */
typedef struct _count_string {
    short Length;  /* offset 0x0 */
    short MaximumLength;  /* offset 0x2 */
    char * Buffer;  /* offset 0x4 */
} _count_string;

/* size: 20 */
typedef struct _cpinfo {
    UINT MaxCharSize;  /* offset 0x0 */
    BYTE DefaultChar[2];  /* offset 0x4 */
    BYTE LeadByte[12];  /* offset 0x6 */
} _cpinfo;

/* _EXCEPTION_POINTERS skipped */

/* _EXCEPTION_RECORD skipped */

/* _EXCEPTION_RECORD skipped */

/* _iobuf skipped */

/* _LIST_ENTRY skipped */

/* _OSVERSIONINFOA skipped */

/* _OVERLAPPED skipped */

/* _SECURITY_ATTRIBUTES skipped */

/* _STARTUPINFOA skipped */

/* size: 8 */
typedef struct _struct_3 {
    unsigned long was;  /* offset 0x0 */
    unsigned long need;  /* offset 0x4 */
} _struct_3;

/* size: 4 */
typedef struct _struct_4 {
    inflate_codes_statef * codes;  /* offset 0x0 */
} _struct_4;

/* size: 8 */
typedef struct _struct_519 {
    DWORD Offset;  /* offset 0x0 */
    DWORD OffsetHigh;  /* offset 0x4 */
} _struct_519;

/* _SYSTEMTIME skipped */

/* size: 2 */
typedef struct _union_2 {
    unsigned short freq;  /* offset 0x0 */
    unsigned short code;  /* offset 0x0 */
} _union_2;

/* size: 2 */
typedef struct _union_3 {
    unsigned short dad;  /* offset 0x0 */
    unsigned short len;  /* offset 0x0 */
} _union_3;

/* size: 8 */
typedef struct _union_518 {
    _struct_519 s;  /* offset 0x0 */
    PVOID Pointer;  /* offset 0x0 */
} _union_518;

/* size: 16 */
typedef struct ArrayItem {
    int field0;  /* offset 0x0 */
    int field4;  /* offset 0x4 */
    void * ptr8;  /* offset 0x8 */
    int fieldC;  /* offset 0xc */
} ArrayItem;

/* size: 16 */
typedef struct BlockNode {
    int count;  /* offset 0x0 */
    int max;  /* offset 0x4 */
    int size;  /* offset 0x8 */
    BlockNode * next;  /* offset 0xc */
} BlockNode;

/* size: 589 */
typedef struct BuildingPrototype {
    unsigned char type_byte;  /* offset 0x0 */
    char pad01[34];  /* offset 0x1 */
    char component_list;  /* offset 0x23 */
    char pad24[547];  /* offset 0x24 */
    unsigned char stat_count_lo;  /* offset 0x247 */
    unsigned char stat_count_hi;  /* offset 0x248 */
    char pad249[4];  /* offset 0x249 */
} BuildingPrototype;

/* size: 24 */
typedef struct CmdAllocateSlot {
    int padding0;  /* offset 0x0 */
    int padding4;  /* offset 0x4 */
    int item_id;  /* offset 0x8 */
    int paddingC;  /* offset 0xc */
    int amount;  /* offset 0x10 */
    int out_entity_id;  /* offset 0x14 */
} CmdAllocateSlot;

/* size: 48 */
typedef struct code_page_info {
    int code_page;  /* offset 0x0 */
    unsigned short mbulinfo[6];  /* offset 0x4 */
    uint8_t[4][8] rgrange;  /* offset 0x10 */
} code_page_info;

/* size: 153 */
typedef struct CommandPacket {
    unsigned char command_type;  /* offset 0x0 */
    unsigned short total_length;  /* offset 0x1 */
    unsigned char player_slot_id;  /* offset 0x3 */
    unsigned int sequence_id;  /* offset 0x4 */
    unsigned char payload[137];  /* offset 0x8 */
    CommandPacket * prev;  /* offset 0x91 */
    CommandPacket * next;  /* offset 0x95 */
} CommandPacket;

/* size: 12 */
typedef struct config_s {
    unsigned short good_length;  /* offset 0x0 */
    unsigned short max_lazy;  /* offset 0x2 */
    unsigned short nice_length;  /* offset 0x4 */
    unsigned short max_chain;  /* offset 0x6 */
    compress_func func;  /* offset 0x8 */
} config_s;

/* CPINFO skipped */

/* size: 28 */
typedef struct CrashStackWalkState {
    unsigned int * dbgImageBase;  /* offset 0x0 */
    void * crashLogHandle;  /* offset 0x4 */
    unsigned int instructionPtr;  /* offset 0x8 */
    unsigned int lastInstructionPtr;  /* offset 0xc */
    unsigned int currentModuleBase;  /* offset 0x10 */
    unsigned int inlineHeuristicBudget;  /* offset 0x14 */
    unsigned int repeatedModuleCount;  /* offset 0x18 */
} CrashStackWalkState;

/* size: 28 */
typedef struct CRT_FILE {
    char * _ptr;  /* offset 0x0 */
    int _cnt;  /* offset 0x4 */
    char * _base;  /* offset 0x8 */
    int _flag;  /* offset 0xc */
    int _file;  /* offset 0x10 */
    int _charbuf;  /* offset 0x14 */
    int _bufsiz;  /* offset 0x18 */
} CRT_FILE;

/* size: 4 */
typedef struct ct_data_s {
    _union_2 fc;  /* offset 0x0 */
    _union_3 dl;  /* offset 0x2 */
} ct_data_s;

/* size: 24 */
typedef struct deflate_state_s {
    char pad0[8];  /* offset 0x0 */
    unsigned char * pending_buf;  /* offset 0x8 */
    char pad1[8];  /* offset 0xc */
    unsigned int pending;  /* offset 0x14 */
} deflate_state_s;

/* size: 44 */
typedef struct DISPATCH_OBJ {
    char pad[36];  /* offset 0x0 */
    _func_1 * func;  /* offset 0x24 */
    int field_28;  /* offset 0x28 */
} DISPATCH_OBJ;

/* size: 24 */
typedef struct ENT {
    int value;  /* offset 0x0 */
    char type;  /* offset 0x4 */
    char pad[19];  /* offset 0x5 */
} ENT;

/* size: 540 */
typedef struct EntityStruct {
    unsigned short word0;  /* offset 0x0 */
    unsigned char byte2;  /* offset 0x2 */
    unsigned char pad3;  /* offset 0x3 */
    int id;  /* offset 0x4 */
    char byte8;  /* offset 0x8 */
    char pad9[31];  /* offset 0x9 */
    unsigned short word28;  /* offset 0x28 */
    char pad2a[50];  /* offset 0x2a */
    int table5c[8];  /* offset 0x5c */
    char pad7c[252];  /* offset 0x7c */
    char field178;  /* offset 0x178 */
    char pad179[163];  /* offset 0x179 */
} EntityStruct;

/* size: 4 */
typedef struct ENTRYEND {
    int sizeBack;  /* offset 0x0 */
} ENTRYEND;

/* size: 8 */
typedef struct errmap {
    unsigned int dos_err;  /* offset 0x0 */
    int c_err;  /* offset 0x4 */
} errmap;

/* size: 516 */
typedef struct GROUP {
    int cntEntries;  /* offset 0x0 */
    LISTHEAD listHead[64];  /* offset 0x4 */
} GROUP;

/* size: 20 */
typedef struct HEADER {
    BITVEC bitvEntryHi;  /* offset 0x0 */
    BITVEC bitvEntryLo;  /* offset 0x4 */
    BITVEC bitvCommit;  /* offset 0x8 */
    void * pHeapData;  /* offset 0xc */
    PREGION pRegion;  /* offset 0x10 */
} HEADER;

/* size: 40 */
typedef struct IMAGE_DIRECTORY_ENTRY_EXPORT {
    unsigned int Characteristics;  /* offset 0x0 */
    unsigned int TimeDateStamp;  /* offset 0x4 */
    unsigned short MajorVersion;  /* offset 0x8 */
    unsigned short MinorVersion;  /* offset 0xa */
    ImageBaseOffset32 Name;  /* offset 0xc */
    unsigned int Base;  /* offset 0x10 */
    unsigned int NumberOfFunctions;  /* offset 0x14 */
    unsigned int NumberOfNames;  /* offset 0x18 */
    ImageBaseOffset32 AddressOfFunctions;  /* offset 0x1c */
    ImageBaseOffset32 AddressOfNames;  /* offset 0x20 */
    ImageBaseOffset32 AddressOfNameOrdinals;  /* offset 0x24 */
} IMAGE_DIRECTORY_ENTRY_EXPORT;

/* IMAGE_DOS_HEADER skipped */

/* size: 248 */
typedef struct IMAGE_NT_HEADERS32 {
    char Signature[4];  /* offset 0x0 */
    -BAD- FileHeader;  /* offset 0x4 */
    IMAGE_OPTIONAL_HEADER32 OptionalHeader;  /* offset 0x18 */
} IMAGE_NT_HEADERS32;

/* size: 224 */
typedef struct IMAGE_OPTIONAL_HEADER32 {
    unsigned short Magic;  /* offset 0x0 */
    unsigned char MajorLinkerVersion;  /* offset 0x2 */
    unsigned char MinorLinkerVersion;  /* offset 0x3 */
    unsigned int SizeOfCode;  /* offset 0x4 */
    unsigned int SizeOfInitializedData;  /* offset 0x8 */
    unsigned int SizeOfUninitializedData;  /* offset 0xc */
    ImageBaseOffset32 AddressOfEntryPoint;  /* offset 0x10 */
    ImageBaseOffset32 BaseOfCode;  /* offset 0x14 */
    ImageBaseOffset32 BaseOfData;  /* offset 0x18 */
    pointer32 ImageBase;  /* offset 0x1c */
    unsigned int SectionAlignment;  /* offset 0x20 */
    unsigned int FileAlignment;  /* offset 0x24 */
    unsigned short MajorOperatingSystemVersion;  /* offset 0x28 */
    unsigned short MinorOperatingSystemVersion;  /* offset 0x2a */
    unsigned short MajorImageVersion;  /* offset 0x2c */
    unsigned short MinorImageVersion;  /* offset 0x2e */
    unsigned short MajorSubsystemVersion;  /* offset 0x30 */
    unsigned short MinorSubsystemVersion;  /* offset 0x32 */
    unsigned int Win32VersionValue;  /* offset 0x34 */
    unsigned int SizeOfImage;  /* offset 0x38 */
    unsigned int SizeOfHeaders;  /* offset 0x3c */
    unsigned int CheckSum;  /* offset 0x40 */
    unsigned short Subsystem;  /* offset 0x44 */
    unsigned short DllCharacteristics;  /* offset 0x46 */
    unsigned int SizeOfStackReserve;  /* offset 0x48 */
    unsigned int SizeOfStackCommit;  /* offset 0x4c */
    unsigned int SizeOfHeapReserve;  /* offset 0x50 */
    unsigned int SizeOfHeapCommit;  /* offset 0x54 */
    unsigned int LoaderFlags;  /* offset 0x58 */
    unsigned int NumberOfRvaAndSizes;  /* offset 0x5c */
    -BAD- DataDirectory;  /* offset 0x60 */
} IMAGE_OPTIONAL_HEADER32;

/* size: 40 */
typedef struct IMAGE_SECTION_HEADER {
    char Name[8];  /* offset 0x0 */
    -BAD- Misc;  /* offset 0x8 */
    ImageBaseOffset32 VirtualAddress;  /* offset 0xc */
    unsigned int SizeOfRawData;  /* offset 0x10 */
    unsigned int PointerToRawData;  /* offset 0x14 */
    unsigned int PointerToRelocations;  /* offset 0x18 */
    unsigned int PointerToLinenumbers;  /* offset 0x1c */
    unsigned short NumberOfRelocations;  /* offset 0x20 */
    unsigned short NumberOfLinenumbers;  /* offset 0x22 */
    SectionFlags Characteristics;  /* offset 0x24 */
} IMAGE_SECTION_HEADER;

/* size: 48 */
typedef struct inflate_blocks_state {
    inflate_block_mode mode;  /* offset 0x0 */
    _union_2 sub;  /* offset 0x4 */
    unsigned int last;  /* offset 0x8 */
    unsigned int bitk;  /* offset 0xc */
    unsigned long bitb;  /* offset 0x10 */
    inflate_huft * hufts;  /* offset 0x14 */
    Bytef * window;  /* offset 0x18 */
    Bytef * end;  /* offset 0x1c */
    Bytef * read;  /* offset 0x20 */
    Bytef * write;  /* offset 0x24 */
    check_func checkfn;  /* offset 0x28 */
    unsigned long check;  /* offset 0x2c */
} inflate_blocks_state;

/* size: 4 */
typedef struct inflate_codes_state {
    int dummy;  /* offset 0x0 */
} inflate_codes_state;

/* size: 8 */
typedef struct inflate_huft_s {
    _union_2 unsigned short;  /* offset 0x0 */
    unsigned int base;  /* offset 0x4 */
} inflate_huft_s;

/* size: 16 */
typedef struct ioinfo {
    long osfhnd;  /* offset 0x0 */
    char osfile;  /* offset 0x4 */
    char pipech;  /* offset 0x5 */
    char pad[2];  /* offset 0x6 */
    int lockinitflag;  /* offset 0x8 */
    CRITICAL_SECTION lock;  /* offset 0xc */
} ioinfo;

/* size: 12 */
typedef struct LD12 {
    int w[3];  /* offset 0x0 */
} LD12;

/* size: 12 */
typedef struct LDOUBLE {
    unsigned int lo;  /* offset 0x0 */
    unsigned int hi;  /* offset 0x4 */
    unsigned short exp;  /* offset 0x8 */
} LDOUBLE;

/* size: 40 */
typedef struct LinkedListNode {
    char data[36];  /* offset 0x0 */
    LinkedListNode * next;  /* offset 0x24 */
} LinkedListNode;

/* size: 65 */
typedef struct ObjectPrototype {
    unsigned char item_category;  /* offset 0x0 */
    char pad01[35];  /* offset 0x1 */
    unsigned char recipe_type;  /* offset 0x24 */
    char pad25[17];  /* offset 0x25 */
    unsigned short base_quantity;  /* offset 0x36 */
    char pad38[9];  /* offset 0x38 */
} ObjectPrototype;

/* size: 24 */
typedef struct OfficeEntry {
    int holder_id;  /* offset 0x0 */
    char rank;  /* offset 0x4 */
    char pad_5[3];  /* offset 0x5 */
    int term_count;  /* offset 0x8 */
    char status;  /* offset 0xc */
    char pad_13[3];  /* offset 0xd */
    int applicant_id;  /* offset 0x10 */
    int unknown_20;  /* offset 0x14 */
} OfficeEntry;

/* size: 8 */
typedef struct PAIR {
    int key;  /* offset 0x0 */
    int val;  /* offset 0x4 */
} PAIR;

/* size: 2507364 */
typedef struct PlayerSlot {
    unsigned int state_flags;  /* offset 0x0 */
    unsigned char unknown1[20];  /* offset 0x4 */
    CommandPacket receive_buffer;  /* offset 0x18 */
    CommandPacket send_buffer;  /* offset 0xb1 */
    unsigned short bytes_received;  /* offset 0x14a */
    unsigned char padding[2506916];  /* offset 0x14c */
    CommandPacket * incoming_cmd_queue;  /* offset 0x2641f0 */
    CommandPacket * outgoing_cmd_queue;  /* offset 0x2641f4 */
    CommandPacket * incoming_cmd_freelist;  /* offset 0x2641f8 */
    CommandPacket * outgoing_cmd_freelist;  /* offset 0x2641fc */
    unsigned char tail_padding[100];  /* offset 0x264200 */
} PlayerSlot;

/* size: 16 */
typedef struct pool_block_t {
    int alloc_count;  /* offset 0x0 */
    int max_count;  /* offset 0x4 */
    int element_size;  /* offset 0x8 */
    pool_block_t * next;  /* offset 0xc */
} pool_block_t;

/* size: 32 */
typedef struct QueryResult {
    char pad00[14];  /* offset 0x0 */
    int count;  /* offset 0xe */
    char pad12[2];  /* offset 0x12 */
    int entity_id;  /* offset 0x14 */
    char pad18[4];  /* offset 0x18 */
    int entries[1];  /* offset 0x1c */
} QueryResult;

/* size: 72 */
typedef struct Record {
    short active;  /* offset 0x0 */
    int id;  /* offset 0x4 */
    char pad[61];  /* offset 0x8 */
} Record;

/* size: 16836 */
typedef struct REGION {
    int indGroupUse;  /* offset 0x0 */
    char cntRegionSize[64];  /* offset 0x4 */
    BITVEC bitvGroupHi[32];  /* offset 0x44 */
    BITVEC bitvGroupLo[32];  /* offset 0xc4 */
    GROUP grpHeadList[32];  /* offset 0x144 */
} REGION;

/* size: 8 */
typedef struct rterrmsgs {
    int rterrno;  /* offset 0x0 */
    char * rterrtxt;  /* offset 0x4 */
} rterrmsgs;

/* size: 81 */
typedef struct SeasonSlot {
    char pad00[4];  /* offset 0x0 */
    int owner_id;  /* offset 0x4 */
    char pad08[8];  /* offset 0x8 */
    int production_count;  /* offset 0x10 */
    char pad14[4];  /* offset 0x14 */
    int material_count;  /* offset 0x18 */
    int product_count;  /* offset 0x1c */
    char pad20[4];  /* offset 0x20 */
    int xp_gained;  /* offset 0x24 */
    char pad28[37];  /* offset 0x28 */
    int total_xp;  /* offset 0x4d */
} SeasonSlot;

/* size: 156 */
typedef struct SlotData {
    char pad[12];  /* offset 0x0 */
    SlotEntry slots[6];  /* offset 0xc */
} SlotData;

/* size: 24 */
typedef struct SlotEntry {
    char key;  /* offset 0x0 */
    char pad[3];  /* offset 0x1 */
    int entityId;  /* offset 0x4 */
    char field8;  /* offset 0x8 */
    char rest[15];  /* offset 0x9 */
} SlotEntry;

/* size: 20 */
typedef struct SRC {
    char hdr[8];  /* offset 0x0 */
    int key;  /* offset 0x8 */
    char pad[4];  /* offset 0xc */
    int val;  /* offset 0x10 */
} SRC;

/* size: 20 */
typedef struct static_tree_desc_s {
    ct_data * static_tree;  /* offset 0x0 */
    int * extra_bits;  /* offset 0x4 */
    int extra_base;  /* offset 0x8 */
    int elems;  /* offset 0xc */
    int max_length;  /* offset 0x10 */
} static_tree_desc_s;

/* size: 12 */
typedef struct Struct10 {
    void * ptr;  /* offset 0x0 */
    int val;  /* offset 0x4 */
    short sval;  /* offset 0x8 */
} Struct10;

/* size: 24 */
typedef struct Struct70 {
    void * field_30;  /* offset 0x0 */
    void * field_34;  /* offset 0x4 */
    void * field_38;  /* offset 0x8 */
    void * field_3C;  /* offset 0xc */
    int field_40;  /* offset 0x10 */
    int field_2C;  /* offset 0x14 */
} Struct70;

/* size: 12 */
typedef struct tagEntry {
    int sizeFront;  /* offset 0x0 */
    tagEntry * pEntryNext;  /* offset 0x4 */
    tagEntry * pEntryPrev;  /* offset 0x8 */
} tagEntry;

/* size: 4 */
typedef struct tagEntryEnd {
    int sizeBack;  /* offset 0x0 */
} tagEntryEnd;

/* size: 516 */
typedef struct tagGroup {
    int cntEntries;  /* offset 0x0 */
    LISTHEAD listHead[64];  /* offset 0x4 */
} tagGroup;

/* size: 20 */
typedef struct tagHeader {
    unsigned int bitvEntryHi;  /* offset 0x0 */
    unsigned int bitvEntryLo;  /* offset 0x4 */
    unsigned int bitvCommit;  /* offset 0x8 */
    void * pHeapData;  /* offset 0xc */
    void * pRegion;  /* offset 0x10 */
} tagHeader;

/* size: 8 */
typedef struct tagListHead {
    tagEntry * pEntryNext;  /* offset 0x0 */
    tagEntry * pEntryPrev;  /* offset 0x4 */
} tagListHead;

/* size: 16836 */
typedef struct tagRegion {
    int indGroupUse;  /* offset 0x0 */
    char cntRegionSize[64];  /* offset 0x4 */
    BITVEC bitvGroupHi[32];  /* offset 0x44 */
    BITVEC bitvGroupLo[32];  /* offset 0xc4 */
    GROUP grpHeadList[32];  /* offset 0x144 */
} tagRegion;

/* size: 60 */
typedef struct TGT {
    char hdr[12];  /* offset 0x0 */
    PAIR entries[6];  /* offset 0xc */
} TGT;

/* size: 16 */
typedef struct TimeStruct {
    int days;  /* offset 0x0 */
    short hours;  /* offset 0x4 */
    int minutes;  /* offset 0x8 */
    int seconds;  /* offset 0xc */
} TimeStruct;

/* size: 12 */
typedef struct transitiondate {
    int yr;  /* offset 0x0 */
    int yd;  /* offset 0x4 */
    long ms;  /* offset 0x8 */
} transitiondate;

/* size: 12 */
typedef struct tree_desc_s {
    ct_data * dyn_tree;  /* offset 0x0 */
    int max_code;  /* offset 0x4 */
    static_tree_desc * stat_desc;  /* offset 0x8 */
} tree_desc_s;

/* size: 56 */
typedef struct z_stream_s {
    unsigned char * next_in;  /* offset 0x0 */
    unsigned int avail_in;  /* offset 0x4 */
    unsigned long total_in;  /* offset 0x8 */
    unsigned char * next_out;  /* offset 0xc */
    unsigned int avail_out;  /* offset 0x10 */
    unsigned long total_out;  /* offset 0x14 */
    char * msg;  /* offset 0x18 */
    void * state;  /* offset 0x1c */
    alloc_func zalloc;  /* offset 0x20 */
    free_func zfree;  /* offset 0x24 */
    void * opaque;  /* offset 0x28 */
    int data_type;  /* offset 0x2c */
    unsigned long adler;  /* offset 0x30 */
    unsigned long reserved;  /* offset 0x34 */
} z_stream_s;

#endif /* TYPES_H */
