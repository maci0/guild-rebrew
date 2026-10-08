#!/usr/bin/env python3
"""Check or regenerate the vendored library trees from pristine upstream plus patches.

Each references/vendor/<name>/vendor.toml names a pristine upstream directory, the
sha256 list that pins it, the output tree the build compiles, the output's files and
the ordered patches. Both modes copy the files from the pristine tree into
<stage>/<name> and apply every patch with GNU patch (--fuzz=0). `check` then requires
the output tree to equal the staged result byte for byte; `sync` writes the staged
result into the output tree. Any hash mismatch, failed patch or drift exits 1.
"""

import argparse
import hashlib
import shutil
import subprocess
import sys
import tomllib
from dataclasses import dataclass
from pathlib import Path

PROJECT_MARKER = "rebrew-project.toml"
MANIFEST_GLOB = "references/vendor/*/vendor.toml"


class VendorError(Exception):
    """A vendored tree does not match its manifest."""


@dataclass(frozen=True)
class Manifest:
    path: Path
    name: str
    pristine: Path
    checksums: Path
    output: Path
    files: tuple[str, ...]
    patches: tuple[Path, ...]


def find_root(start: Path) -> Path:
    for candidate in (start, *start.parents):
        if (candidate / PROJECT_MARKER).is_file():
            return candidate
    raise VendorError(f"no {PROJECT_MARKER} above {start}")


def load_manifest(root: Path, path: Path) -> Manifest:
    with path.open("rb") as handle:
        data = tomllib.load(handle)
    keys = (
        "name",
        "version",
        "url",
        "sha256",
        "pristine",
        "checksums",
        "output",
        "files",
        "patches",
    )
    missing = [key for key in keys if key not in data]
    if missing:
        raise VendorError(f"{path}: missing {', '.join(missing)}")
    files = tuple(data["files"])
    if not files or any(Path(name).is_absolute() or ".." in Path(name).parts for name in files):
        raise VendorError(f"{path}: files must be nonempty relative paths")
    return Manifest(
        path=path,
        name=data["name"],
        pristine=root / data["pristine"],
        checksums=root / data["checksums"],
        output=root / data["output"],
        files=files,
        patches=tuple(path.parent / name for name in data["patches"]),
    )


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def verify_pristine(root: Path, manifest: Manifest) -> None:
    """Every listed file matches its hash and the pristine tree holds no other file."""
    listed: dict[Path, str] = {}
    for line in manifest.checksums.read_text().splitlines():
        digest, _, name = line.partition("  ")
        if len(digest) != 64 or not name:
            raise VendorError(f"{manifest.checksums}: malformed line {line!r}")
        listed[root / name] = digest
    errors = [
        f"{path.relative_to(root)}: sha256 differs from {manifest.checksums.relative_to(root)}"
        for path, digest in listed.items()
        if path.is_relative_to(manifest.pristine) and (not path.is_file() or sha256(path) != digest)
    ]
    errors += [
        f"{path.relative_to(root)}: not in {manifest.checksums.relative_to(root)}"
        for path in sorted(manifest.pristine.rglob("*"))
        if path.is_file() and path not in listed
    ]
    errors += [
        f"{manifest.name}: {name} is not a pinned pristine file"
        for name in manifest.files
        if manifest.pristine / name not in listed
    ]
    if errors:
        raise VendorError("\n".join(errors))


def stage(manifest: Manifest, stage_root: Path) -> Path:
    """Copy the pristine files into a fresh stage directory and apply the patches."""
    target = stage_root / manifest.name
    shutil.rmtree(target, ignore_errors=True)
    for name in manifest.files:
        (target / name).parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(manifest.pristine / name, target / name)
    for patch in manifest.patches:
        # The stdlib has no unified-diff applier; GNU patch is the one dependency here.
        result = subprocess.run(
            [
                "patch",
                "-p1",
                "--batch",
                "--forward",
                "--fuzz=0",
                "--quiet",
                "--no-backup-if-mismatch",
                "--reject-file=-",
                "-d",
                str(target),
                "-i",
                str(patch),
            ],
            capture_output=True,
            text=True,
            check=False,
        )
        if result.returncode != 0:
            raise VendorError(f"{patch.name} does not apply:\n{result.stdout}{result.stderr}")
    produced = {p.relative_to(target).as_posix() for p in target.rglob("*") if p.is_file()}
    extra = sorted(produced - set(manifest.files))
    if extra:
        raise VendorError(f"{manifest.name}: patches create unlisted files {extra}")
    return target


def output_files(manifest: Manifest) -> set[str]:
    if not manifest.output.is_dir():
        return set()
    return {
        p.relative_to(manifest.output).as_posix() for p in manifest.output.rglob("*") if p.is_file()
    }


def check(manifest: Manifest, staged: Path) -> None:
    present = output_files(manifest)
    errors = [
        f"{manifest.output.name}/{name}: missing" for name in manifest.files if name not in present
    ]
    errors += [
        f"{manifest.output.name}/{name}: not in {manifest.path.name}"
        for name in sorted(present - set(manifest.files))
    ]
    errors += [
        f"{manifest.output.name}/{name}: differs from pristine + patches"
        for name in manifest.files
        if name in present and (manifest.output / name).read_bytes() != (staged / name).read_bytes()
    ]
    if errors:
        raise VendorError("\n".join(errors) + "\nedit a patch, then run scripts/vendor.py sync")


def sync(manifest: Manifest, staged: Path) -> None:
    for name in sorted(output_files(manifest) - set(manifest.files)):
        (manifest.output / name).unlink()
    for directory in sorted(manifest.output.rglob("*"), reverse=True):
        if directory.is_dir() and not any(directory.iterdir()):
            directory.rmdir()
    for name in manifest.files:
        (manifest.output / name).parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(staged / name, manifest.output / name)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("mode", choices=("check", "sync"))
    parser.add_argument(
        "--stage", required=True, type=Path, help="scratch directory for patched copies"
    )
    parser.add_argument("--root", type=Path, help="project root (default: found from the cwd)")
    args = parser.parse_args(argv)
    try:
        root = (args.root or find_root(Path.cwd())).resolve()
        manifests = [load_manifest(root, path) for path in sorted(root.glob(MANIFEST_GLOB))]
        if not manifests:
            raise VendorError(f"no manifests match {MANIFEST_GLOB}")
        for manifest in manifests:
            verify_pristine(root, manifest)
            staged = stage(manifest, args.stage.resolve())
            (check if args.mode == "check" else sync)(manifest, staged)
            print(f"{manifest.name}: {len(manifest.patches)} patches, {args.mode} ok")
    except VendorError as error:
        print(f"vendor: {error}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
