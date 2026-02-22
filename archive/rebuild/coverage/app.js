const DATA_URL = "data.json";

function hex(n, width) {
  return "0x" + n.toString(16).toUpperCase().padStart(width, "0");
}

function formatBytes(buf) {
  const bytes = new Uint8Array(buf);
  const perLine = 16;
  let out = "";
  for (let i = 0; i < bytes.length; i += perLine) {
    const slice = bytes.slice(i, i + perLine);
    const parts = [];
    for (const b of slice) parts.push(b.toString(16).toUpperCase().padStart(2, "0"));
    out += parts.join(" ") + "\n";
  }
  return out.trimEnd();
}

async function fetchTextSafe(url) {
  if (!url) return "(n/a)";
  const res = await fetch(url);
  if (!res.ok) return `(failed to load: ${url})`;
  return await res.text();
}

async function fetchArrayBufferSafe(url) {
  if (!url) return null;
  const res = await fetch(url);
  if (!res.ok) return null;
  return await res.arrayBuffer();
}

function setLinks(container, links) {
  container.innerHTML = "";
  for (const l of links) {
    const a = document.createElement("a");
    a.href = l.href;
    a.textContent = l.label;
    a.target = "_blank";
    a.rel = "noreferrer";
    container.appendChild(a);
  }
}

function computeCellClass(cell) {
  if (cell.state === "c") return "cell c";
  if (cell.state === "asm") return "cell asm";
  return "cell";
}

function initHighlighting() {
  if (!window.hljs) return;
  if (window.hljs.getLanguage && window.hljs.getLanguage("hex")) return;

  window.hljs.registerLanguage("hex", () => ({
    name: "Hex",
    contains: [
      { className: "number", begin: /\b0x[0-9A-Fa-f]+\b/ },
      { className: "number", begin: /\b[0-9A-Fa-f]{2}\b/ },
    ],
  }));
}

function setPreCode(pre, lang, text) {
  const code = document.createElement("code");
  if (lang) {
    code.className = `language-${lang}`;
  }
  code.textContent = text;

  pre.replaceChildren(code);

  if (window.hljs) {
    code.removeAttribute("data-highlighted");
    try {
      window.hljs.highlightElement(code);
    } catch (_) {
    }
  }
}

async function boot() {
  const grid = document.getElementById("grid");
  const subtitle = document.getElementById("subtitle");
  const reload = document.getElementById("reload");

  const panelTitle = document.getElementById("panelTitle");
  const panelMeta = document.getElementById("panelMeta");
  const overlapsEl = document.getElementById("overlaps");
  const bytesEl = document.getElementById("bytes");

  const docEl = document.getElementById("doc");
  const asmEl = document.getElementById("asm");
  const cEl = document.getElementById("c");
  const docLinks = document.getElementById("docLinks");
  const asmLinks = document.getElementById("asmLinks");
  const cLinks = document.getElementById("cLinks");

  let data;
  let originalDll;

  initHighlighting();

  function resizeGridSquares() {
    const columns = (data && typeof data.columns === "number") ? data.columns : 64;
    const styles = window.getComputedStyle(grid);
    const gap = parseFloat(styles.columnGap || styles.gap || "2") || 2;
    const padL = parseFloat(styles.paddingLeft || "0") || 0;
    const padR = parseFloat(styles.paddingRight || "0") || 0;
    const usable = Math.max(0, grid.clientWidth - padL - padR);
    const colW = (usable - gap * (columns - 1)) / columns;
    const px = Math.max(6, Math.floor(colW));
    grid.style.gridAutoRows = `${px}px`;
  }

  async function tryRegen() {
    try {
      const res = await fetch("regen", { method: "POST", cache: "no-store" });
      return res.ok;
    } catch (_) {
      return false;
    }
  }

  async function loadData() {
    const res = await fetch(DATA_URL, { cache: "no-store" });
    if (!res.ok) throw new Error(`failed to load ${DATA_URL}`);
    data = await res.json();
    originalDll = await fetchArrayBufferSafe(data.paths.originalDll);
  }

  function renderGrid() {
    grid.innerHTML = "";
    const cells = data.cells || data.chunks || [];
    for (let i = 0; i < cells.length; i++) {
      const cell = cells[i];
      const el = document.createElement("div");
      el.className = computeCellClass(cell);
      if (typeof cell.span === "number") {
        el.style.gridColumn = `span ${cell.span}`;
      }
      el.title = `${i}  ${hex(cell.start, 5)}..${hex(cell.end, 5)}  ${cell.functions.length} fn`;
      el.addEventListener("mousedown", (e) => e.preventDefault());
      el.addEventListener("click", () => selectChunk(i));
      grid.appendChild(el);
    }
    resizeGridSquares();
  }

  function renderOverlaps(functionIds) {
    overlapsEl.innerHTML = "";
    if (!functionIds.length) {
      overlapsEl.textContent = "(none)";
      return;
    }

    for (const id of functionIds) {
      const fn = data.functions[id];
      const chip = document.createElement("button");
      chip.className = "chip";
      chip.type = "button";
      chip.textContent = fn.name;
      chip.addEventListener("click", () => selectFunction(id));
      overlapsEl.appendChild(chip);
    }
  }

  function sliceOriginalBytes(fn) {
    if (!originalDll) return null;
    const start = fn.fileOffset;
    const end = start + fn.size;
    if (start < 0 || end > originalDll.byteLength) return null;
    return originalDll.slice(start, end);
  }

  async function selectFunction(id) {
    const fn = data.functions[id];
    panelTitle.textContent = fn.name;
    panelMeta.textContent = [
      `VA: ${fn.vaStart}..${fn.vaEnd} (${fn.size} bytes)`,
      `file_offset=${hex(fn.fileOffset, 5)}  text_off=${hex(fn.textOffset, 5)}`,
      `md5=${fn.md5 || "(n/a)"}`,
      `sha256=${fn.sha256 || "(n/a)"}`,
      `doc=${fn.docPath || "(none)"}`,
      `asm=${fn.asmPath || "(none)"}`,
      `asm_raw=${fn.asmRawPath || "(none)"}`,
      `c=${fn.cPath || "(none)"}`
    ].join("\n");

    const buf = sliceOriginalBytes(fn);
    setPreCode(
      bytesEl,
      "hex",
      buf ? formatBytes(buf) : "(failed to slice bytes from original DLL)"
    );

    setLinks(docLinks, fn.docPath ? [{ label: "open", href: fn.docPath }] : []);
    const asmLinkList = [];
    if (fn.asmPath) asmLinkList.push({ label: "open", href: fn.asmPath });
    if (fn.asmRawPath) asmLinkList.push({ label: "raw", href: fn.asmRawPath });
    setLinks(asmLinks, asmLinkList);
    setLinks(cLinks, fn.cPath ? [{ label: "open", href: fn.cPath }] : []);

    docEl.textContent = await fetchTextSafe(fn.docPath);

    setPreCode(asmEl, "x86asm", await fetchTextSafe(fn.asmPath));

    if (fn.cPath) {
      setPreCode(cEl, "c", await fetchTextSafe(fn.cPath));
    } else {
      setPreCode(cEl, "plaintext", "(no C implementation for this function yet)");
    }
  }

  function selectChunk(i) {
    const cells = data.cells || data.chunks || [];
    const cell = cells[i];
    if (!cell) return;
    renderOverlaps(cell.functions);
    if (cell.functions.length) {
      selectFunction(cell.functions[0]);
    } else {
      panelTitle.textContent = `Block ${i}`;
      panelMeta.textContent = `${hex(cell.start, 5)}..${hex(cell.end, 5)} (no documented functions)`;
      bytesEl.textContent = "(select a function)";
      docEl.textContent = "(select a function)";
      asmEl.textContent = "(select a function)";
      cEl.textContent = "(select a function)";
      setLinks(docLinks, []);
      setLinks(asmLinks, []);
      setLinks(cLinks, []);
    }
  }

  async function refresh(opts) {
    const o = opts || { regen: false };
    subtitle.textContent = "Loading…";
    if (o.regen) {
      const ok = await tryRegen();
      if (!ok) {
        subtitle.textContent = "Regen unavailable (use: python3 rebuild/coverage/dev_server.py)";
      }
    }
    await loadData();

    subtitle.textContent = [
      `.text=${data.textSize} bytes`,
      `documented=${data.summary.documentedFunctions}`,
      `pureC=${data.summary.cRebuiltFunctions}`,
      `coverage=${data.summary.coveragePercent.toFixed(2)}%`,
      `base=${data.defaultGapBytes || data.chunkSize || 128}`
    ].join("  ·  ");

    renderGrid();
    renderOverlaps([]);
  }

  window.addEventListener("resize", () => resizeGridSquares());

  reload.addEventListener("click", () => refresh({ regen: true }).catch((e) => {
    subtitle.textContent = `Error: ${e.message}`;
  }));

  try {
    await refresh({ regen: false });
  } catch (e) {
    subtitle.textContent = `Error: ${e.message}`;
  }
}

boot();
