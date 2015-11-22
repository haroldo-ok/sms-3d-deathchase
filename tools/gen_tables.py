import os, sys

PF_WIDTH = 32
PF_HEIGHT = 24

MAX_DEPTH = 63
TRUNK_WIDTH = 80

trunk_table = [{'width': 32}, {'width': 20}]

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

    f.write('\n')
    f.write('const trunk_data trunk_table[] = %s\n' %
            to_record_array_const(trunk_table, ['width']))

    f.write('\n#endif /* _THREE_D_TABLES_H */\n')
