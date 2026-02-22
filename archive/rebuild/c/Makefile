# Build a bit-identical server.dll by compiling C functions (MSVC6)
# and reusing the original DLL sections.

ROOT := ../..
BUILD := build

CL := wine $(ROOT)/tools/MSVC600/VC98/Bin/CL.EXE
CLFLAGS := /nologo /c /O2 /MT /Gd
WININC := $(ROOT)/tools/MSVC600/VC98/Include

# Per-file compiler flag overrides (CRT code uses /O1 /Oy-)
CLFLAGS_entry0 := /nologo /c /O1 /Oy- /MT /Gd

OBJCOPY := objcopy
NASM := nasm
DD := dd

ORIG_DLL := $(ROOT)/original/Server/server.dll

TEXT_RAW := $(ROOT)/rebuild/sections/text_raw.bin
TEXT_OUT := $(ROOT)/rebuild/sections/text_from_c.bin

OUT_DLL := $(ROOT)/rebuild/Server/server_from_c.dll

C_FILES := $(wildcard *.c)
OBJ_FILES := $(patsubst %.c,$(BUILD)/%.obj,$(C_FILES))
TEXT_FILES := $(patsubst %.c,$(BUILD)/%_text.bin,$(C_FILES))
PATCH_FILES := $(patsubst %.c,$(BUILD)/%_patch.bin,$(C_FILES))

SIZE_entry0 := 157
SIZE_init := 48
SIZE_exit := 68
SIZE_fcn_10003140 := 33

# Per-file COFF relocation targets (for functions with extern references)
# VA = base address where function is placed in the final DLL
# RELOCS = SYM=ADDR pairs for each unresolved external symbol
VA_entry0 := 0x1001B9D4
RELOCS_entry0 := ___proc_attached=0x100354FC __pRawDllMain=0x11767588 __CRT_INIT@12=0x1001B8FB _DllMain@12=0x10009310

ASM := server_from_c.asm

.PHONY: all dll verify clean

all: verify

$(BUILD):
	@mkdir -p $(BUILD)

$(BUILD)/%.obj: %.c | $(BUILD)
	$(CL) $(or $(CLFLAGS_$*),$(CLFLAGS)) /I"$(WININC)" /Fo"$@" "$<"

$(BUILD)/%_text.bin: $(BUILD)/%.obj | $(BUILD)
	@if [ -n "$(RELOCS_$*)" ]; then \
		python3 resolve_relocs.py "$<" "$@" "$(VA_$*)" $(RELOCS_$*); \
	else \
		$(OBJCOPY) -O binary --only-section=.text "$<" "$@"; \
	fi

$(BUILD)/%_patch.bin: $(BUILD)/%_text.bin | $(BUILD)
	@size=$(SIZE_$*); \
	if [ -z "$$size" ]; then \
		echo "Missing SIZE_$* for $*"; \
		exit 1; \
	fi; \
	$(DD) if="$<" of="$@" bs=1 count=$$size 2>/dev/null

$(TEXT_OUT): $(TEXT_RAW) $(PATCH_FILES)
	@cp "$(TEXT_RAW)" "$(TEXT_OUT)"
	@for f in $(PATCH_FILES); do \
		base=$$(basename "$$f"); \
		name=$${base%_patch.bin}; \
		va=$$(NAME=$$name python3 -c 'import os; name=os.environ["NAME"]; va = int(name[len("fcn_"):],16) if name.startswith("fcn_") else (0x10009320 if name=="init" else (0x10009350 if name=="exit" else (0x1001B9D4 if name=="entry0" else (_ for _ in ()).throw(SystemExit(1))))); print(va-0x10001000)'); \
		$(DD) if="$$f" of="$(TEXT_OUT)" bs=1 seek=$$va conv=notrunc 2>/dev/null; \
	done

dll: $(OUT_DLL)

$(OUT_DLL): $(ASM) $(TEXT_OUT)
	$(NASM) -f bin -o "$(OUT_DLL)" "$(ASM)"

verify: $(OUT_DLL)
	@cmp -s "$(OUT_DLL)" "$(ORIG_DLL)"
	@md5sum "$(OUT_DLL)" "$(ORIG_DLL)"
	@sha256sum "$(OUT_DLL)" "$(ORIG_DLL)"

clean:
	@rm -rf "$(BUILD)" \
	  "$(TEXT_OUT)" \
	  "$(OUT_DLL)"
