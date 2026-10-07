#!/usr/bin/env python3
"""Read the configured reference's two timestamps for native LIB and LINK."""
from pathlib import Path

import lief
from rebrew.config import load_config

cfg = load_config(Path(__file__).resolve().parents[1], target="server.dll")
pe = lief.PE.parse(str(cfg.target_binary))
if pe is None or not pe.has_exports:
    raise ValueError(f"Expected a PE with exports: {cfg.target_binary}")
epochs = (pe.header.time_date_stamps, pe.get_export().timestamp)
if any(not 0 <= epoch <= 2147483647 for epoch in epochs):
    raise ValueError("Native Wine clock requires timestamps in 0..2147483647")
print(";".join(str(epoch) for epoch in epochs) + ";" + cfg.target_binary.as_posix().replace(";", "\\;"))
