"""Generate GBA-safe Origin Reborn character and footer tile sheets.
Run: python tools/origin_art.py [repository root]
Requires Pillow. Uses only the repository's existing Pokemon sprite artwork.
"""
from pathlib import Path
import struct
import sys
from PIL import Image, ImageDraw, ImageFont

SPECIES = ('bulbasaur', 'charmander', 'squirtle', 'pikachu')


def palette(path):
    return [tuple(map(int, line.split())) for line in path.read_text().splitlines()[3:19]]


def save_tiles(image, stem, bank):
    """Encode a 240x160 indexed canvas into a deduplicated sheet and 32x20 map."""
    tiles = [bytes(64)]
    lookup = {tiles[0]: 0}
    tilemap = []
    for y in range(0, 160, 8):
        for x in range(0, 256, 8):
            tile = image.crop((x, y, x + 8, y + 8)).tobytes() if x < 240 else bytes(64)
            if tile not in lookup:
                lookup[tile] = len(tiles)
                tiles.append(tile)
            tilemap.append(lookup[tile] | bank << 12)
    assert len(tiles) <= 512
    sheet = Image.new('P', (128, ((len(tiles) + 15) // 16) * 8))
    sheet.putpalette(image.getpalette())
    for i, tile in enumerate(tiles):
        sheet.paste(Image.frombytes('P', (8, 8), tile), ((i % 16) * 8, (i // 16) * 8))
    sheet.save(str(stem) + '.png')
    Path(str(stem) + '.bin').write_bytes(struct.pack('<640H', *tilemap))


def opaque_mask(image):
    """Build alpha from indices, without interpreting them through the palette."""
    mask = Image.new('L', image.size)
    mask.putdata([255 if index else 0 for index in image.getdata()])
    return mask


def main(root):
    root = Path(root)
    folder = root / 'graphics/title_screen_frlg'
    art = Image.new('RGB', (240, 160))
    mask = Image.new('1', art.size)
    for i, species in enumerate(SPECIES):
        path = root / 'graphics/pokemon' / species
        frame = Image.open(path / 'anim_front.png').crop((0, 0, 64, 64))
        pal = palette(path / 'normal.pal')
        frame.putpalette([v for color in pal for v in color])
        alpha = opaque_mask(frame)
        box = alpha.getbbox()
        rgb = frame.convert('RGB').crop(box)
        alpha = alpha.crop(box)
        ratio = min(48 / rgb.width, 36 / rgb.height, 1)
        size = (round(rgb.width * ratio), round(rgb.height * ratio))
        rgb = rgb.resize(size, Image.Resampling.NEAREST)
        alpha = alpha.resize(size, Image.Resampling.NEAREST)
        pos = (i * 58 + 33 - size[0] // 2, 132 - size[1])
        art.paste(rgb, pos, alpha)
        mask.paste(alpha, pos)
    # Reserve index zero for transparency; share 15 colours across the four starters.
    colors = Image.new('RGB', (sum(mask.getdata()), 1))
    colors.putdata([rgb for rgb, opaque in zip(art.getdata(), mask.getdata()) if opaque])
    quantized = colors.quantize(colors=15, method=Image.Quantize.MEDIANCUT)
    pal = quantized.getpalette()[:45]
    reference = Image.new('P', (1, 1))
    reference.putpalette(pal + pal[:3] * (256 - 15))
    reduced = art.quantize(palette=reference, dither=Image.Dither.NONE)
    indexed = Image.new('P', art.size)
    indexed.putpalette([0, 0, 0] + pal + [0] * (768 - 48))
    indexed.putdata([p + 1 if opaque else 0 for p, opaque in zip(reduced.getdata(), mask.getdata())])
    assert max(indexed.getdata()) <= 15
    stem = folder / 'firered/box_art_mon'
    save_tiles(indexed, stem, 13)
    rgb_pal = [tuple(indexed.getpalette()[i:i + 3]) for i in range(0, 48, 3)]
    stem.with_suffix('.pal').write_text('JASC-PAL\n0100\n16\n' + ''.join('%d %d %d\n' % c for c in rgb_pal))

    # Preserve original PRESS START pixels (including their blinking colour indices).
    old = Image.open(folder / 'copyright_press_start.png')
    entries = struct.unpack('<640H', (folder / 'copyright_press_start.bin').read_bytes())
    prompt = Image.new('P', (96, 8))
    # Supports both the original moved prompt and this generator's centered result.
    source_row, source_col = (17, 9) if entries[17 * 32 + 9] & 1023 else (16, 17)
    for i in range(12):
        entry = entries[source_row * 32 + source_col + i]
        tile = entry & 1023
        x, y = tile % (old.width // 8) * 8, tile // (old.width // 8) * 8
        piece = old.crop((x, y, x + 8, y + 8))
        if entry & 1024:
            piece = piece.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
        if entry & 2048:
            piece = piece.transpose(Image.Transpose.FLIP_TOP_BOTTOM)
        prompt.paste(piece, (i * 8, 0))
    footer = Image.new('P', (240, 160))
    footer.putpalette([v for c in palette(folder / 'firered/background.pal') for v in c])
    footer.paste(prompt, (72, 136))
    # Pillow's built-in bitmap font is portable and legible at native resolution.
    font = ImageFont.load_default_imagefont()
    text = '2026 khol games'
    draw = ImageDraw.Draw(footer)
    bounds = draw.textbbox((0, 0), text, font=font)
    draw.text(((240 - (bounds[2] - bounds[0])) // 2, 150 - bounds[1]), text, font=font, fill=10)
    save_tiles(footer, folder / 'copyright_press_start', 15)
    preview = Image.new('RGB', (240, 160), (16, 24, 40))
    preview.paste(indexed.convert('RGB'), (0, 0), mask.convert('L').point(lambda p: 255 if p else 0))
    footer_mask = opaque_mask(footer)
    preview.paste(footer.convert('RGB'), (0, 0), footer_mask)
    # Reconstruct the actual logo tilemap, rather than displaying its tile sheet.
    logo = Image.open(folder / 'firered/game_title_logo.png')
    logo_map = struct.unpack('<640H', (folder / 'firered/game_title_logo.bin').read_bytes())
    for r in range(20):
        for c in range(30):
            entry = logo_map[r * 32 + c]
            tile = entry & 1023
            piece = logo.crop((tile % 32 * 8, tile // 32 * 8, tile % 32 * 8 + 8, tile // 32 * 8 + 8))
            if entry & 1024:
                piece = piece.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
            if entry & 2048:
                piece = piece.transpose(Image.Transpose.FLIP_TOP_BOTTOM)
            preview.paste(piece.convert('RGB'), (c * 8, r * 8), opaque_mask(piece))
    preview.resize((960, 640), Image.Resampling.NEAREST).save(root / 'origin-title-preview.png')


if __name__ == '__main__':
    main(sys.argv[1] if len(sys.argv) > 1 else Path(__file__).resolve().parents[1])
