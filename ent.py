
#!/usr/bin/env python3
import sys,math
fn = sys.argv[1]
win = int(sys.argv[2]) if len(sys.argv)>2 else 256
step= int(sys.argv[3]) if len(sys.argv)>3 else 64

data = open(fn,'rb').read()
N = len(data)
def ent(b):
    if not b: return 0.0
    freq = [0]*256
    for c in b: freq[c]+=1
    e = 0.0
    L = len(b)
    for v in freq:
        if v:
            p = v/L
            e -= p * math.log2(p)
    return e

for off in range(0, max(1, N-win+1), step):
    block = data[off:off+win]
    e = ent(block)
    print("off=0x%x ent=%.3f len=%d" % (off, e, len(block)))
PY
