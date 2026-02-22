# Build a bit-identical server.dll by assembling ASM functions
# and patching them into the original .text section.

ROOT := ../..
BUILD := build

NASM := nasm
DD := dd

ORIG_DLL := $(ROOT)/original/Server/server.dll

TEXT_RAW := $(ROOT)/rebuild/sections/text_raw.bin
TEXT_OUT := $(ROOT)/rebuild/sections/text_from_asm.bin

OUT_DLL := $(ROOT)/rebuild/Server/server_from_asm.dll

ASM_FILES := $(wildcard _*.asm)
BIN_FILES := $(patsubst %.asm,$(BUILD)/%.bin,$(ASM_FILES))

ASM := server_from_asm.asm

.PHONY: all bins text dll verify clean

all: verify

$(BUILD):
	@mkdir -p $(BUILD)

$(BUILD)/%.bin: %.asm | $(BUILD)
	$(NASM) -f bin -o "$@" "$<"

bins: $(BIN_FILES)

$(TEXT_OUT): $(TEXT_RAW) $(BIN_FILES)
	@cp "$(TEXT_RAW)" "$(TEXT_OUT)"
	@for f in $(BIN_FILES); do \
		base=$$(basename "$$f"); \
		name=$${base%.bin}; \
		va=$$(NAME=$$name python3 -c 'import os; name=os.environ["NAME"]; va = int(name[len("_fcn_"):],16) if name.startswith("_fcn_") else (0x10009320 if name=="_init" else (0x10009350 if name=="_exit" else (0x1001B9D4 if name=="_entry0" else (_ for _ in ()).throw(SystemExit(1))))); print(va-0x10001000)'); \
		$(DD) if="$$f" of="$(TEXT_OUT)" bs=1 seek=$$va conv=notrunc 2>/dev/null; \
	done

text: $(TEXT_OUT)

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
