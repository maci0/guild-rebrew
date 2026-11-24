# DirectX archive inputs

GoldTL selects `references/dxsdk8/lib/d3dx8.lib` in `rebrew-project.toml`.
CMake also links the three import libraries below, all objects matching
`references/dxsdk8/supp/*.obj`, and two members extracted from
`references/dxsdk8/lib/d3dx8-xpsp1.lib`. Gold does not select these DirectX
archive paths.

## Local archives

Supply these local inputs under `references/dxsdk8/`; they are not release assets.
Paths in the tables are relative to that directory.

| Path | Bytes | SHA-256 |
| --- | ---: | --- |
| `lib/d3dx8.lib` | 2,150,226 | `39a8e21889a7c1f0b966f04a9e7d392de14ddebb3e091dfa1e5ce3e19564fc28` |
| `lib/d3dx8-xpsp1.lib` | 3,844,186 | `c02e4fedf3e2e0964a1eed98ca02b28d68a0a7ac184594b04212216253bfbd9d` |
| `lib/ddraw.lib` | 4,540 | `372bffe705284588bf27eeec4a09eb541336e4c1ca2c78f0ec413f509b05c43f` |
| `lib/dinput8.lib` | 19,928 | `8492ccaf3e8fdee6777aa21a6b693b3389450c290e3ae1de525956811614c97d` |
| `lib/d3d8.lib` | 2,466 | `90c3a046e41deef54eb8a68b01b527d1b2639dccee30135f1c7c72b835bc96a4` |

The DirectX 8.1 SDK archive came from `DXF/DXSDK/lib/d3dx8.lib` in
`dx81sdk_full.exe` (archive.org item `dx81sdk_full`). The October 25 entry records
the extraction and link results. [Archive provenance](provenance.md#2026-10-25-session-round-34-d3dx8-provider-replaced-with-directx-81-sdk-archive)

The archive label and matching bytes do not establish the provider selected by
the original game linker. Keep these files unchanged.

## XP archive members

CMake requires `llvm-ar` and extracts these exact members from
`lib/d3dx8-xpsp1.lib`. Configuration checks the archive hash above and both
member hashes below.

| Member | Bytes | SHA-256 |
| --- | ---: | --- |
| `obj\i386\cd3dximage.obj` | 22,584 | `d0c91f1bf7550ae39709f738416a48710e75aba61749203d8c7b03d5a07fe592` |
| `obj\i386\jerror.obj` | 26,570 | `e1203fbdc8cb43231d4952b24843030fdd4f332c51e858807bdaf6cbda0516ba` |

## Supplementary objects

From the checkout root, extract these 23 members into an empty `supp/` directory.
CMake links every `.obj` in that directory. The selection excludes
`pngpread.obj` and includes both occurrences of `pchintel.obj`.

```sh
(
  set -eu
  archive="$PWD/references/dxsdk8/lib/d3dx8-xpsp1.lib"
  out=references/dxsdk8/supp
  mkdir -p "$out"
  for member in jcomapi jdapimin jdapistd jdmarker jdmaster jdtrans \
                png pngerror pngget pngmem pngread pngrio pngrtran pngrutil \
                pngset pngtrans pngwio pngwrite pngwtran pngwutil; do
    llvm-ar p "$archive" "obj\\i386\\${member}.obj" > "$out/$member.obj"
  done
  llvm-ar p "$archive" 'objd\i386\pchamd.obj' > "$out/pchamd.obj"
  llvm-ar p "$archive" 'objd\i386\pchintel.obj' > "$out/pchintel.obj"
  cd "$out"
  llvm-ar xN 2 "$archive" 'objd\i386\pchintel.obj'
  mv 'objd\i386\pchintel.obj' pchintel-2.obj
)
```

CMake checks the XP archive and the two members it extracts itself. Verify the
other archive hashes above before linking.

## Import libraries

CMake links `lib/ddraw.lib`, `lib/dinput8.lib` and `lib/d3d8.lib` directly.
`llvm-ar t` lists DLL-named members in all three. `dinput8.lib` also contains
`obj\i386\dilib1.obj` through `obj\i386\dilib5.obj`; these archives contain
more than import descriptors alone.

Among the imports forced by
`layout/Europa1400Gold_TL.exe/import-includes.rsp` are the DirectX entries
`__imp__DirectDrawCreateEx@16` and `__imp__Direct3DCreate8@4`. Selecting these
inputs does not establish a matching complete import table. See the
[client comparison commands](../stubs/README.md#compare).
