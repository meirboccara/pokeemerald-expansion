"""ENG-3 spike: KJH's converted New Bark Town (Johto) in expansion's FireRed build, as a Hoenn-format layout.

Tilesets: KJH's Johto tilesets are Hoenn-sized (512 tiles, 6 palettes) with FireRed's 32-bit metatile attributes in
pokefirered's behavior numbering. Here they become Hoenn-format attributes (16-bit: behavior | layer << 12) in
expansion's numbering, through expansion's own FRLG_TO_EMERALD table.
"""
import importlib.util, json, os, re, shutil, struct

KJH = '/mnt/d/Documents/Projet Meir/pokemon-kjh/source/pokefirered'
EXP = os.path.expanduser('~/kjh/exp-fr-eng3')
os.chdir(EXP)

spec = importlib.util.spec_from_file_location('conv', 'migration_scripts/frlg_metatile_behavior_converter.py')
conv = importlib.util.module_from_spec(spec)
spec.loader.exec_module(conv)

TILESETS = [('primary', 'johto_johto', 'J_johto', False),
            ('secondary', 'johto_johto_outdoor_day_new_bark_24', 'J_johto_outdoor_day_new_bark_24', True)]
unknown = set()

def convert_attributes(src, dst):
    data = open(src, 'rb').read()
    out = []
    for (value,) in struct.iter_unpack('<I', data):
        frlg = value & conv.BEHAVIOR_MASK
        if frlg in conv.FRLG_BEHAVIORS:
            behavior = conv.EMERALD_BEHAVIORS[conv.FRLG_TO_EMERALD[conv.FRLG_BEHAVIORS[frlg]]]
        else:
            unknown.add(frlg)
            behavior = 0
        layer = (value >> 29) & 3
        assert behavior < 0x100, behavior
        out.append(behavior | (layer << 12))
    open(dst, 'wb').write(struct.pack('<' + 'H' * len(out), *out))
    return len(out)

graphics, metatiles, headers = [], [], []
for kind, folder, label, secondary in TILESETS:
    src, dst = f'{KJH}/data/tilesets/{kind}/{folder}', f'data/tilesets/{kind}/{folder}'
    os.makedirs(f'{dst}/palettes', exist_ok=True)
    shutil.copy(f'{src}/tiles.png', dst)
    shutil.copy(f'{src}/metatiles.bin', dst)
    pals = sorted(p for p in os.listdir(f'{src}/palettes') if p.endswith('.pal'))
    for p in pals:
        shutil.copy(f'{src}/palettes/{p}', f'{dst}/palettes/')
    n = convert_attributes(f'{src}/metatile_attributes.bin', f'{dst}/metatile_attributes.bin')
    print(f'{folder}: {n} metatiles, {len(pals)} palettes')
    graphics.append(f'const u16 ALIGNED(4) gTilesetPalettes_{label}[][16] =\n{{\n'
                    + ''.join(f'    INCGFX_U16("{dst}/palettes/{p}", ".gbapal"),\n' for p in pals) + '};\n\n'
                    + f'const u32 gTilesetTiles_{label}[] = INCGFX_U32("{dst}/tiles.png", ".4bpp.smol");\n')
    metatiles.append(f'const u16 gMetatiles_{label}[] = INCBIN_U16("{dst}/metatiles.bin");\n'
                     f'const u16 gMetatileAttributes_{label}[] = INCBIN_U16("{dst}/metatile_attributes.bin");\n')
    headers.append(f'const struct Tileset gTileset_{label} =\n{{\n    .isCompressed = TRUE,\n'
                   f'    .isSecondary = {"TRUE" if secondary else "FALSE"},\n    .tiles = gTilesetTiles_{label},\n'
                   f'    .palettes = gTilesetPalettes_{label},\n    .metatiles = gMetatiles_{label},\n'
                   f'    .metatileAttributes = gMetatileAttributes_{label},\n    .callback = NULL,\n}};\n')
print('unknown FRLG behaviors (set to MB_NORMAL):', sorted(unknown))

def append(path, text):
    s = open(path).read()
    if 'KJH ENG-3 spike: Johto' not in s:
        open(path, 'a').write('\n// KJH ENG-3 spike: Johto (New Bark Town)\n' + text)
append('src/data/tilesets/graphics.h', '\n'.join(graphics))
append('src/data/tilesets/metatiles.h', '\n'.join(metatiles))
append('src/data/tilesets/headers.h', '\n'.join(headers))

# layout
os.makedirs('data/layouts/JohtoNewBarkTown', exist_ok=True)
for f in ['border.bin', 'map.bin']:
    shutil.copy(f'{KJH}/data/layouts/JohtoNewBarkTown/{f}', 'data/layouts/JohtoNewBarkTown/')
layouts = json.load(open('data/layouts/layouts.json'))
if not any(l.get('id') == 'LAYOUT_JOHTO_NEW_BARK_TOWN' for l in layouts['layouts']):
    layouts['layouts'].append({'id': 'LAYOUT_JOHTO_NEW_BARK_TOWN', 'name': 'JohtoNewBarkTown_Layout', 'width': 20,
                               'height': 18, 'primary_tileset': 'gTileset_J_johto',
                               'secondary_tileset': 'gTileset_J_johto_outdoor_day_new_bark_24',
                               'border_filepath': 'data/layouts/JohtoNewBarkTown/border.bin',
                               'blockdata_filepath': 'data/layouts/JohtoNewBarkTown/map.bin',
                               'layout_version': 'emerald'})
    json.dump(layouts, open('data/layouts/layouts.json', 'w'), indent=2)

# map: KJH's objects with simple scripts; no connections, warps or signs (their targets aren't ported)
kjh_map = json.load(open(f'{KJH}/data/maps/JohtoNewBarkTown/map.json'))
os.makedirs('data/maps/JohtoNewBarkTown', exist_ok=True)
objects = []
for i, o in enumerate(kjh_map['object_events']):
    o = dict(o, script=f'JohtoNewBarkTown_EventScript_Npc{i}', flag='0')
    if o['graphics_id'] == 'OBJ_EVENT_GFX_FISHER':
        o['graphics_id'] = 'OBJ_EVENT_GFX_FISHERMAN'
    objects.append(o)
m = {k: v for k, v in kjh_map.items() if k not in ('connections', 'warp_events', 'bg_events', 'coord_events', 'object_events')}
m.update({'region': 'REGION_JOHTO', 'music': 'MUS_RG_PALLET', 'region_map_section': 'MAPSEC_PALLET_TOWN',
          'connections': None, 'object_events': objects, 'warp_events': [], 'coord_events': [], 'bg_events': []})
json.dump(m, open('data/maps/JohtoNewBarkTown/map.json', 'w'), indent=2)
texts = ['Johto loads in the new engine!', 'This is New Bark Town,\\nfrom Pokemon Crystal.', 'Johto, Kanto and Hoenn\\nin one ROM?']
script = 'JohtoNewBarkTown_MapScripts::\n\t.byte 0\n\n'
for i in range(len(objects)):
    script += (f'JohtoNewBarkTown_EventScript_Npc{i}::\n\tmsgbox JohtoNewBarkTown_Text_Npc{i}, MSGBOX_NPC\n\tend\n\n'
               f'JohtoNewBarkTown_Text_Npc{i}:\n\t.string "{texts[i % len(texts)]}$"\n\n')
open('data/maps/JohtoNewBarkTown/scripts.inc', 'w').write(script)

# map group and script include
groups = json.load(open('data/maps/map_groups.json'))
if 'gMapGroup_Johto' not in groups:
    groups['group_order'].append('gMapGroup_Johto')
    groups['gMapGroup_Johto'] = ['JohtoNewBarkTown']
    json.dump(groups, open('data/maps/map_groups.json', 'w'), indent=2)
es = open('data/event_scripts.s').read()
inc = '\t.include "data/maps/JohtoNewBarkTown/scripts.inc"\n'
if inc not in es:
    anchor = '\t.include "data/maps/LittlerootTown/scripts.inc"\n'
    assert anchor in es
    open('data/event_scripts.s', 'w').write(es.replace(anchor, anchor + inc))

# mapjson: Johto maps in a FireRed build too
mj = open('tools/mapjson/mapjson.cpp').read()
old = 'region != "REGION_KANTO" && region != "REGION_HOENN")'
if 'REGION_JOHTO' not in mj:
    assert mj.count(old) == 1
    open('tools/mapjson/mapjson.cpp', 'w').write(mj.replace(old, 'region != "REGION_KANTO" && region != "REGION_HOENN" && region != "REGION_JOHTO")'))
print('done')
