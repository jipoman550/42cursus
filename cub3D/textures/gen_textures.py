#!/usr/bin/env python3
"""Generate 64x64 brick-pattern .xpm textures for cub3D testing."""

import os

def generate_brick_xpm(filename, name, brick_color, mortar_color, highlight_color):
    """Generate a 64x64 brick pattern XPM file."""
    W, H = 64, 64
    BRICK_W, BRICK_H = 16, 8  # brick size
    MORTAR = 1  # mortar thickness

    # Build pixel grid
    pixels = []
    for y in range(H):
        row = []
        for x in range(W):
            # Horizontal mortar lines
            if y % BRICK_H < MORTAR:
                row.append('m')  # mortar
            else:
                # Offset every other row
                offset = (BRICK_W // 2) if ((y // BRICK_H) % 2 == 1) else 0
                bx = (x + offset) % BRICK_W
                # Vertical mortar lines
                if bx < MORTAR:
                    row.append('m')  # mortar
                else:
                    # Add highlight on top-left edge of brick
                    local_y = y % BRICK_H
                    if local_y == MORTAR and bx > MORTAR:
                        row.append('h')  # highlight
                    elif bx == MORTAR and local_y > MORTAR:
                        row.append('h')  # highlight
                    else:
                        row.append('b')  # brick
        pixels.append(''.join(row))

    # Write XPM
    with open(filename, 'w') as f:
        f.write('/* XPM */\n')
        f.write(f'static char *{name}[] = {{\n')
        f.write(f'"64 64 3 1",\n')
        f.write(f'"b c {brick_color}",\n')
        f.write(f'"m c {mortar_color}",\n')
        f.write(f'"h c {highlight_color}",\n')
        for i, row in enumerate(pixels):
            comma = ',' if i < len(pixels) - 1 else ''
            f.write(f'"{row}"{comma}\n')
        f.write('};\n')

    print(f"  ✅ Generated {filename}")

if __name__ == '__main__':
    tex_dir = '/root/workspace/42cursus/cub3D/textures'
    os.makedirs(tex_dir, exist_ok=True)

    # North - Blue bricks
    generate_brick_xpm(f'{tex_dir}/north.xpm', 'north',
                        '#4466AA', '#222233', '#6688CC')
    # South - Green bricks
    generate_brick_xpm(f'{tex_dir}/south.xpm', 'south',
                        '#44AA44', '#223322', '#66CC66')
    # West - Red bricks
    generate_brick_xpm(f'{tex_dir}/west.xpm', 'west',
                        '#AA4444', '#332222', '#CC6666')
    # East - Yellow/Orange bricks
    generate_brick_xpm(f'{tex_dir}/east.xpm', 'east',
                        '#AAAA44', '#333322', '#CCCC66')

    print("\n🎨 All 4 textures generated in textures/")
