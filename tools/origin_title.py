"""Title-screen subtitle: draw "ORIGIN / REBORN" where FireRed's logo says "FIRERED / VERSION".

The logo is graphics/title_screen_frlg/firered/game_title_logo.png in the expansion fork: an 8bpp tile sheet
(256x64) laid out by game_title_logo.bin. The subtitle is the 80x40 px block under the Pokemon wordmark,
composite tiles (cols 6-15, rows 7-11), which the tilemap takes from sheet tiles 22-31, 54-63, 86-95, 118-127
and 150-159. This script redraws only those tiles, with palette indices the subtitle already uses (bank 12,
which the title screen never animates). Running it again gives the same file.

    python3 title_logo.py <fork>/graphics/title_screen_frlg/firered/game_title_logo.png [preview.png]

Needs Pillow (WSL has it).
"""
import os
import sys

from PIL import Image

BLACK, WHITE = 206, 207           # the subtitle's outline and letter fill
SHADES = [207, 202, 204, 205, 193, 194]   # top-to-bottom gradient: 255, 246, 230, 213, 197, 189 grey
SHADOW = 201                      # 98 grey, the letters' drop shadow

# 7x10 bold glyphs (I is 6 wide)
GLYPHS = {
    'P': ["######.", "#######", "##...##", "##...##", "#######", "######.", "##.....", "##.....", "##.....", "##....."],
    'H': ["##...##", "##...##", "##...##", "##...##", "#######", "#######", "##...##", "##...##", "##...##", "##...##"],
    'O': [".#####.", "#######", "##...##", "##...##", "##...##", "##...##", "##...##", "##...##", "#######", ".#####."],
    'E': ["#######", "#######", "##.....", "##.....", "######.", "######.", "##.....", "##.....", "#######", "#######"],
    'N': ["##...##", "###..##", "###..##", "####.##", "##.####", "##.####", "##..###", "##..###", "##...##", "##...##"],
    'I': ["######", "######", "..##..", "..##..", "..##..", "..##..", "..##..", "..##..", "######", "######"],
    'X': ["##...##", "##...##", ".##.##.", ".#####.", "..###..", "..###..", ".#####.", ".##.##.", "##...##", "##...##"],
    'R': ["######.", "#######", "##...##", "##...##", "#######", "######.", "##.##..", "##..##.", "##...##", "##...##"],
    'B': ["######.", "#######", "##...##", "##..##.", "######.", "######.", "##..##.", "##...##", "#######", "######."],
}
GLYPHS['G'] = [".#####.", "#######", "##...##", "##.....", "##.....", "##.####", "##.####", "##...##", "#######", ".#####."]
LINES = [("ORIGIN", 5), ("REBORN", 21)]   # word, top row inside the 80x40 block
GAP = 2
BOX_X, BOX_Y, BOX_W, BOX_H = 48, 56, 80, 40    # the subtitle block in composite pixels
TILES_W = 32                                   # sheet width in tiles


def word_width(word):
    return sum(len(GLYPHS[c][0]) for c in word) + GAP * (len(word) - 1)


def draw_block():
    """The new 80x40 subtitle as a dict (x, y) -> palette index; missing = transparent (0)."""
    letters = {}
    for word, top in LINES:
        x = (BOX_W - word_width(word)) // 2
        for c in word:
            for dy, row in enumerate(GLYPHS[c]):
                for dx, bit in enumerate(row):
                    if bit == '#':
                        letters[(x + dx, top + dy)] = SHADES[min(dy * len(SHADES) // 10, len(SHADES) - 1)]
            x += len(GLYPHS[c][0]) + GAP
    block = {}
    # black banner: the letters' bounding box plus 3 px, corners cut
    xs = [p[0] for p in letters]
    ys = [p[1] for p in letters]
    x0, x1, y0, y1 = min(xs) - 3, max(xs) + 3, min(ys) - 3, max(ys) + 3
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            corner = min(x - x0, x1 - x) + min(y - y0, y1 - y)
            if corner >= 2:
                block[(x, y)] = BLACK
    for (x, y) in letters:
        if (x + 1, y + 1) not in letters:
            block[(x + 1, y + 1)] = SHADOW
    block.update(letters)
    return block


def subtitle_tiles(tilemap):
    """composite tile (col, row) -> sheet tile index, for the subtitle block."""
    out = {}
    for r in range(BOX_Y // 8, (BOX_Y + BOX_H) // 8):
        for c in range(BOX_X // 8, (BOX_X + BOX_W) // 8):
            out[(c, r)] = tilemap[r * TILES_W + c] & 0x3FF
    return out


def main(png_path, preview=None):
    sheet = Image.open(png_path)
    assert sheet.mode == 'P' and sheet.size == (256, 64), (sheet.mode, sheet.size)
    raw = open(os.path.splitext(png_path)[0] + '.bin', 'rb').read()
    tilemap = [raw[i] | raw[i + 1] << 8 for i in range(0, len(raw), 2)]
    block = draw_block()
    px = sheet.load()
    for (c, r), t in subtitle_tiles(tilemap).items():
        assert t, f'subtitle tile ({c},{r}) maps to the blank tile'
        for dy in range(8):
            for dx in range(8):
                bx, by = c * 8 + dx - BOX_X, r * 8 + dy - BOX_Y
                px[(t % TILES_W) * 8 + dx, (t // TILES_W) * 8 + dy] = block.get((bx, by), 0)
    sheet.save(png_path, optimize=False)
    if preview:   # the whole 176x96 logo as the game lays it out, x4
        logo = Image.new('P', (176, 96))
        logo.putpalette(sheet.getpalette())
        for r in range(12):
            for c in range(22):
                t = tilemap[r * TILES_W + c] & 0x3FF
                tx, ty = (t % TILES_W) * 8, (t // TILES_W) * 8
                logo.paste(sheet.crop((tx, ty, tx + 8, ty + 8)), (c * 8, r * 8))
        logo.convert('RGB').resize((704, 384), Image.NEAREST).save(preview)


if __name__ == '__main__':
    main(*sys.argv[1:3])
