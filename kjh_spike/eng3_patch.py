"""ENG-3 spike: let Hoenn's maps, layouts, tilesets and wild encounters into expansion's FireRed build."""
import os, re
os.chdir(os.path.expanduser('~/kjh/exp-fr-eng3'))

def edit(path, old, new, count=None):
    s = open(path).read()
    n = s.count(old)
    assert n and (count is None or n == count), (path, old, n)
    open(path, 'w').write(s.replace(old, new))
    print(f'{path}: {n} x')

# 1. mapjson: a FireRed build takes Hoenn maps and Emerald-format layouts too
edit('tools/mapjson/mapjson.cpp', '(version == "firered" && region != "REGION_KANTO")',
     '(version == "firered" && region != "REGION_KANTO" && region != "REGION_HOENN")', 1)
edit('tools/mapjson/mapjson.cpp', '(version == "firered" && layout_version != "frlg")',
     '(version == "firered" && layout_version != "frlg" && layout_version != "emerald")')

# 2. Emerald's tilesets in every build
for f in ['src/data/tilesets/headers.h', 'src/data/tilesets/graphics.h', 'src/data/tilesets/metatiles.h']:
    s = open(f).read()
    i = s.index('#if !IS_FRLG')
    s = s[:i] + '#if 1 // KJH ENG-3 spike: Hoenn tilesets in every build' + s[i + len('#if !IS_FRLG'):]
    j = s.find('\n#else\n', i)
    k = s.find('#endif', i)
    if j != -1 and j < k:
        s = s[:j] + '\n#endif\n#if IS_FRLG // KJH ENG-3 spike\n' + s[j + len('\n#else\n'):]
    open(f, 'w').write(s)
    print(f'{f}: gate opened')

# 3. Hoenn's wild encounters in the FireRed build too
edit('tools/wild_encounters/wild_encounters_to_header.py', 'self.WriteLine(f"#ifdef {version}")',
     'self.WriteLine("#if defined(EMERALD) || defined(FIRERED)" if version == "EMERALD" else f"#ifdef {version}")')

# 4. the KJH emulator harness
s = open('include/global.h').read()
if 'KJH_DEBUG_WARP' not in s:
    edit('include/global.h', '#define GUARD_GLOBAL_H\n', '#define GUARD_GLOBAL_H\n#define KJH_DEBUG_WARP 4 // KJH emulator harness (spike)\n', 1)
