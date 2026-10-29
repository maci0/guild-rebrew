"""Drive shipped cross-import on one function that already lives in both clients.

The fixture is a real source file with one body and one metadata binding per client.
The test does not reimplement matching: it loads both binaries through
rebrew, builds the signatures cross-import uses, and asks cross_match
whether the destination bytes are that source function. A dry-run of
import_shared_function must name the same file.
"""

from __future__ import annotations

from pathlib import Path

from rebrew.cli import require_config
from rebrew.config import load_config
from rebrew.cross_import import (
    cross_match,
    import_shared_function,
    signature_for,
    target_bytes_by_va,
)
from rebrew.metadata.bindings import SourceBinding, read_source_bindings

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "src" / "Develop" / "Unassigned" / "GOLD.fcn_0040abd0.c"


def _bindings(target: str) -> list[SourceBinding]:
    cfg = load_config(root=ROOT, target=target)
    return read_source_bindings(
        SOURCE,
        target_name=cfg.module,
        base_dir=cfg.reversed_dir,
        metadata_dir=cfg.metadata_dir,
        project_root=cfg.root,
    )


def test_shared_bound_function_is_the_transferred_body() -> None:
    gold = _bindings("Europa1400Gold.exe")
    goldtl = _bindings("Europa1400Gold_TL.exe")
    assert len(gold) == 1 and len(goldtl) == 1
    assert gold[0].module == "GOLD"
    assert goldtl[0].module == "GOLDTL"
    assert gold[0].name == goldtl[0].name == "fcn_0040abd0"
    assert gold[0].va != goldtl[0].va
    assert gold[0].size and gold[0].size == goldtl[0].size

    cfg_gold = require_config(target="Europa1400Gold.exe", root=ROOT)
    cfg_tl = require_config(target="Europa1400Gold_TL.exe", root=ROOT)
    gold_bytes = target_bytes_by_va(cfg_gold, {gold[0].va: gold[0].size})
    tl_bytes = target_bytes_by_va(cfg_tl, {goldtl[0].va: goldtl[0].size})
    assert set(gold_bytes) == {gold[0].va}
    assert set(tl_bytes) == {goldtl[0].va}

    src_sig = signature_for(cfg_gold, gold_bytes[gold[0].va], gold[0].va)
    dst_sig = signature_for(cfg_tl, tl_bytes[goldtl[0].va], goldtl[0].va)
    assert src_sig is not None and dst_sig is not None
    matched = cross_match(
        {goldtl[0].va: dst_sig},
        {gold[0].va: src_sig},
        min_score=95.0,
        min_gap=5.0,
    )
    assert goldtl[0].va in matched
    src_va, score = matched[goldtl[0].va]
    assert src_va == gold[0].va
    assert score == 100.0

    rel = SOURCE.relative_to(cfg_gold.reversed_dir).as_posix()
    preview = import_shared_function(
        cfg_tl,
        cfg_gold,
        goldtl[0].va,
        gold[0].va,
        rel,
        goldtl[0].size,
        dry_run=True,
    )
    assert preview["action"] == "would-import-shared"
    assert preview["filepath"].endswith("GOLD.fcn_0040abd0.c")
    assert preview["dst_va"] == f"0x{goldtl[0].va:08x}"
    assert preview["src_va"] == f"0x{gold[0].va:08x}"
