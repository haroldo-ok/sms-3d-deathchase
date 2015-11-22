import os, sys

PF_WIDTH = 32
PF_HEIGHT = 24

MAX_DEPTH = 63
TRUNK_WIDTH = 80
TRUNK_HEIGHT = 128
MIN_TRUNK_WIDTH = 8

MAX_X = PF_WIDTH

trunk_table = []
x_table = []
max_divider = TRUNK_WIDTH / MIN_TRUNK_WIDTH
for depth in range(0, MAX_DEPTH + 1):
    # TRUNK_WIDTH * n / 64 = 2 => n = 2 * 64 / TRUNK_WIDTH
    scale = 1.0 / (depth * max_divider / MAX_DEPTH + 1)

    trunk_table.append({
        'width': int(round(TRUNK_WIDTH * scale)),
        'height': int(round(TRUNK_WIDTH * scale))
    })

    x_for_depth = []
    x_table.append(x_for_depth);
    for x in range(0, MAX_X):
        screen_x = scale * x
        x_for_depth.append(int(screen_x))

def to_record_array_const(records, keys):
    internal = ',\n\t'.join([to_record_const(r, keys) for r in records])
    return '{\n\t%s\n};\n' % internal.strip()

def to_record_const(record, keys):
    internal = ', '.join([str(record[k]) for k in keys])
    return '{%s}' % internal

script_dir = os.path.dirname(os.path.realpath(sys.argv[0]))

with open(script_dir + '/../three_d_tables.h', 'w') as f:
    f.write('#ifndef _THREE_D_TABLES_H\n')
    f.write('#define _THREE_D_TABLES_H\n\n')

    f.write('#define PF_WIDTH %d\n' % PF_WIDTH)
    f.write('#define PF_HEIGHT %d\n' % PF_HEIGHT)

    f.write('\nconst trunk_data trunk_table[] = %s\n' %
            to_record_array_const(trunk_table, ['width', 'height']))

    x_depth_string = ',\n\t'.join(['{%s}' % ','.join(map(str, l)) for l in x_table])
    f.write('\nconst UBYTE trunk_depth_x[][%d] = {\n\t%s\n};\n' % (MAX_X, x_depth_string))

    f.write('\n#endif /* _THREE_D_TABLES_H */\n')
