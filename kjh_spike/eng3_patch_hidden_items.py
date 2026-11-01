import os
p = os.path.expanduser('~/kjh/exp-fr-eng3/asm/macros/map.inc')
s = open(p).read()
old = '.if \\flag < FLAG_HIDDEN_ITEMS_START\n'
assert s.count(old) == 1, s.count(old)
s = s.replace(old, '.if \\flag && \\flag < FLAG_HIDDEN_ITEMS_START @ KJH ENG-3 spike: Hoenn flags are 0 in a FireRed build\n')
open(p, 'w').write(s)
print('ok')
