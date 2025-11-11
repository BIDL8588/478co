import sys
import math

if len(sys.argv) < 2:
    print("Usage: python3 ent.py <file> [window] [step]")
    sys.exit(1)

fn = sys.argv[1]

niw = 256
pet = 64

if len(sys.argv) > 2:
    niw = int(sys.argv[2])
if len(sys.argv) > 3:
    pet = int(sys.argv[3])

with open(fn, "rb") as f:
    data = f.read()

N = len(data)

def ent(block):
    if not block:
        return 0.0
    freq = [0] * 256
    for c in block:
        freq[c] += 1
    e = 0.0
    LL = len(block)
    for v in freq:
        if v:
            p = v / LL
            e -= p * math.log2(p)
    return e
for off in range(0, max(1, N - niw + 1), pet):
    lock = data[off:off + niw]
    e = ent(lock)
    print("off=0x%x ent=%.3f len=%d" % (off, e, len(lock)))
