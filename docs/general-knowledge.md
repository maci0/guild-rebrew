# Original build facts

These are native/compiler observations. [Current work](TODO.md) owns status;
[build instructions](build.md) own setup and reference hashes.

## Original project

Embedded paths attest `D:\Develop`, game `DieGildeAddOn`, client
`DieGildeAddOnVc`, server `DieGildeAddOnServer` and shared `Units`.
A path establishes a unit witness, not every reconstructed file's original TU.
Use [source layout](source-layout.md) and [naming](naming_conventions.md) for those decisions.

## Original build

| Context | Server | GoldTL | Gold |
| --- | --- | --- | --- |
| Project compiler profile | Plain VC6 SP5 | SP5 Processor Pack | SP5 Processor Pack |
| Runtime | /MT, LIBCMT | /MT, LIBCMT | /ML, LIBC |
| Native retention evidence | /OPT:REF | /DEBUG, /OPT:NOREF, PDB path | /OPT:REF |

The same CL version can use different code generators. Game-only x87 compare
patterns and complete same-source controls distinguish plain VC6 from Processor
Pack; Rich records alone mix provenance from libraries. Some bodies are identical
under both generators, so one matching function cannot select the profile.

The October 18 server control held source, flags and link inputs fixed. Plain SP5
reproduced the reference; Processor Pack produced a different, shorter image.
Client comparison controls instead required Processor Pack. The complete compiler
hashes, censuses and receipts are in the archived notebook below.

Default game optimization is /O2 /Gd. Effective per-target/TU inputs live in
`rebrew-project.toml` and managed metadata. Independently built libraries can have
other evidenced contexts. Historical flag probes are not production overrides.

## Cross-target recovery

Match reference bytes, native calls, fields and literals before sharing a body.
Equal names or a score of 100 do not establish equal layouts or providers.
DirectInput is one concrete boundary: Gold uses version 7 and a 16-byte buffered
keyboard event; GoldTL uses version 8 and a 20-byte event.

Client data can be absent from the server despite adjacent shared code. Library
bands can contain different code generators. Neither adjacency nor a constant VA
shift establishes a counterpart.

Use `rebrew source import-related --help` for reviewed shared-source imports.
Source sharing still requires destination compilation and complete operand checks.


## Archived findings

<details>
<summary>Historical sections and address lookup</summary>

The [November 5 archive](archive/2026-11-05-documentation.tar.xz) preserves the full
`docs/general-knowledge.md` notebook, including corrections and receipt paths. Entries below locate
historical claims, not current instructions or verdicts. Hex values include
code/data addresses and constants.

```sh
tar -xOf docs/archive/2026-11-05-documentation.tar.xz docs/general-knowledge.md | less
```

| Historical section | Referenced hex values |
| --- | --- |
| <a id="original-build-and-native-facts"></a>Original build and native facts | - |
| <a id="where-to-read"></a>Where to read | - |
| Original project | - |
| Original build | `0x5e0000`, `0x64ffff`, `0x10000000`, `0x10009320`, `0x10009350` |
| <a id="toolchain-observations-verified-with-commands-round-938"></a>Toolchain observations (verified with commands; round 938) | - |
| <a id="deliverable-mechanics"></a>Deliverable mechanics | - |
| <a id="game-domain"></a>Game domain | - |
| <a id="the-command_c-discovery-boundaries-are-an-inventory-artefact-not-a-coverage-gap"></a><a id="the-build-is-bit-reproducible-from-scratch-and-the-correct-clean-recipe-is---target-final"></a>The `command_c` discovery boundaries are an INVENTORY artefact, not a coverage gap | `0x1000d8a0`, `0x1000d930` |
| <a id="round-1039-reproduced-a-retired-postlink-image"></a><a id="done-criteria-status-verified-independently-round-1043"></a>Round 1039 reproduced a retired postlink image | - |
| <a id="round-1043s-structural-checks-did-not-establish-completion"></a><a id="faking-the-original-d-build-path-through-wine-is-possible-and-unnecessary-round-1054"></a>Round 1043's structural checks did not establish completion | - |
| <a id="round-1054-a-wine-drive-map-was-unnecessary-for-these-__file__-literals"></a><a id="the-data-sections-are-complete-and-rebrew-todo-was-reporting-123-phantoms-round-1078"></a>Round 1054: a Wine drive map was unnecessary for these `__FILE__` literals | - |
| <a id="round-1078s-completed-data-claim-measured-a-postlinked-image"></a><a id="section-by-section-parity-the-shipped-file-is-byte-identical-outside-text-by-copying-not-by-compiling-round-1089-corrected-round-1092"></a>Round 1078's completed-data claim measured a postlinked image | `0x10035000`, `0x1176759c` |
| <a id="round-1089s-non-text-parity-came-from-copying-and-was-retracted"></a>Round 1089's non-text parity came from copying and was retracted | - |
| <a id="finding-code-we-already-reversed-in-another-target-rebrew-source-import-related"></a>Finding code we already reversed in another target: `rebrew source import-related` | - |
| <a id="the-three-binaries-one-compiler-version-two-code-generators-round-1379-definitive"></a>The three binaries: one compiler version, two code generators (round 1379, definitive) | `0x000a2306`, `0x00302354` |
| <a id="game-code-only-round-1379c"></a>Game code only (round 1379c) | `0x459940`, `0x492990`, `0x4fffb0` |
| <a id="does-the-processor-pack-work-for-the-server-target-round-1379e"></a>Does the Processor Pack work for the SERVER target? (round 1379e) | `0x4514d0`, `0x453b30`, `0x1000c3c0`, `0x100100a0`, `0x100151e0` |
| <a id="using-the-two-clients-as-a-reference-for-the-remaining-server-work-round-1380"></a>Using the two clients as a reference for the remaining server work (round 1380) | - |
| <a id="native-findings"></a>Native findings | `0x401470`, `0x402aa0`, `0x405870`, `0x406410`, `0x406560`, `0x40cba0`, `0x40dd90`, `0x40eca0`, `0x410710`, `0x410740`, `0x410770`, `0x4112e0`, `0x411820`, `0x4124b0`, `0x41e350`, `0x41e3e0`, `0x41e410`, `0x41e440`, `0x41e490`, `0x41e4d0`, `0x420b70`, `0x420ba0`, `0x4210a0`, `0x4210ed`, `0x42114a`, `0x421262`, `0x421290`, `0x421328`, `0x422ba0`, `0x422c30`, `0x422c60`, `0x4247e0`, `0x424810`, `0x435500`, `0x450a00`, `0x450b20`, `0x450c5c`, `0x453890`, `0x4737e0`, `0x476c80`, `0x499a50`, `0x499ad0`, `0x49a010`, `0x4a1130`, `0x4a16f0`, `0x4bc5a0`, `0x4bcb80`, `0x4c4d30`, `0x4cef30`, `0x4e58e0`, `0x4e5af0`, `0x4e73c0`, `0x4e73f0`, `0x4e7600`, `0x4e77e0`, `0x004fe5e2`, `0x004fe60c`, `0x501030`, `0x0050108a`, `0x005010a3`, `0x005010b2`, `0x005010dc`, `0x503e80`, `0x00504100`, `0x00504e70`, `0x505df0`, `0x508e40`, `0x509ee0`, `0x50a640`, `0x50dac0`, `0x5a3580`, `0x5a35c2`, `0x5de784`, `0x5eaad6`, `0x5ecef0`, `0x5ed0a8`, `0x5eee50`, `0x5eee60`, `0x5fcc78`, `0x5fcc7c`, `0x5fcc80`, `0x600190`, `0x602840`, `0x0061aa00`, `0x62e108`, `0x633174`, `0x633178`, `0x63317c`, `0x633180`, `0x64d3f8`, `0x66080a`, `0x662384`, `0x66417c`, `0x664340`, `0x66cc40`, `0x66cc50`, `0x675058`, `0x675da8`, `0x67bbdc`, `0x67bbe0`, `0x67bbe4`, `0x67edf8`, `0x6814a8`, `0x68d934`, `0x00699748`, `0x6f1bc5`, `0x770ae0`, `0x770b60`, `0x7f4c00`, `0x00868050`, `0x00889f74`, `0x0090e094`, `0x9b4a40`, `0x9b8dc0`, `0xf8ab80`, `0xf8abc8`, `0x1011980`, `0x10119c8`, `0x143ab0c`, `0x1460b00`, `0x1467360`, `0x14673cc`, `0x14a5c6c`, `0x14cbcc0`, `0x14ce8a0`, `0x14ce90c`, `0x10014ee0`, `0x10019be0`, `0x1002d878` |

</details>
