# Coverage Map (Defrag-Style)

This is a tiny static web UI that renders a defrag-like grid of the `.text` section, highlights documented areas, and lets you click blocks to view:

- original bytes (sliced from `original/Server/server.dll`)
- docs markdown (`rebuild/docs/functions/*.md`)
- the reconstructed asm file (`rebuild/asm/*.asm` when available)
- the pure-C 1:1 source (`rebuild/c/*.c` when available)

## Generate Data

From repo root:

```bash
python3 rebuild/coverage/gen_coverage_data.py
```

This writes `rebuild/coverage/data.json`.

Notes on cell sizing:
- Default: undocumented gaps are emitted as 128-byte cells.
- Functions: emitted at their exact byte size.
- Grid base unit is 128 bytes per column; function cells span columns as needed.

## Run

### Option A (Recommended): dev server with regen endpoint

This supports the UI "Reload" button regenerating `data.json`.

```bash
python3 rebuild/coverage/dev_server.py
```

Open:

- `http://localhost:8000/rebuild/coverage/`

### Option B: plain static server

Serve from the repo root so relative file paths resolve (UI reload will only re-fetch `data.json`, not regenerate it):

```bash
python3 -m http.server
```

Then open:

- `http://localhost:8000/rebuild/coverage/`
