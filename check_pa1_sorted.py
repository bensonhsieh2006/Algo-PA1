#!/usr/bin/env python3
import sys
from collections import Counter

def read_rows(path):
    rows = []
    with open(path, 'r', encoding='utf-8', errors='ignore') as f:
        for line in f:
            s = line.strip()
            if not s or s.startswith('#'):
                continue
            parts = s.split()
            ints = []
            for p in parts:
                try:
                    if any(ch in p for ch in ".eE"):
                        raise ValueError
                    ints.append(int(p))
                except ValueError:
                    pass
            if len(ints) >= 2:
                rows.append(ints[:2])
    return rows

def strictly_increasing(seq):
    return all(seq[i] < seq[i+1] for i in range(len(seq)-1))

def non_decreasing(seq):
    return all(seq[i] <= seq[i+1] for i in range(len(seq)-1))

def is_contiguous_seq(seq):
    n = len(seq)
    if n == 0: return False
    # 0..n-1
    if seq[0] == 0 and strictly_increasing(seq) and seq[-1] == n-1:
        return all(x == i for i, x in enumerate(seq))
    # 1..n
    if seq[0] == 1 and strictly_increasing(seq) and seq[-1] == n:
        return all(x == i for i, x in enumerate(seq, start=1))
    return False

def main():
    if len(sys.argv) != 3:
        print("Usage: python check_pa1_v4_nondecreasing.py <input_2col> <output_2col>")
        sys.exit(2)
    fin, fout = sys.argv[1], sys.argv[2]
    in_rows  = read_rows(fin)
    out_rows = read_rows(fout)

    if not in_rows or not out_rows:
        print("[FAIL] empty or invalid files.")
        sys.exit(1)
    if any(len(r) != 2 for r in in_rows) or any(len(r) != 2 for r in out_rows):
        print("[FAIL] this checker only supports 2-column input and 2-column output.")
        sys.exit(1)

    if len(in_rows) != len(out_rows):
        print(f"[FAIL] line-count mismatch: input {len(in_rows)} vs output {len(out_rows)}")
        sys.exit(1)

    vals_in  = [v for (_,v) in in_rows]
    idx_out  = [i for (i,_) in out_rows]
    vals_out = [v for (_,v) in out_rows]

    if Counter(vals_in) != Counter(vals_out):
        print("[FAIL] values multiset mismatch between input(value) and output(value).")
        sys.exit(1)

    if not is_contiguous_seq(idx_out):
        print("[FAIL] first column is not a contiguous strictly increasing sequence (0..n-1 or 1..n).")
        sys.exit(1)

    if not non_decreasing(vals_out):
        # find first violation
        for k in range(len(vals_out)-1):
            if not (vals_out[k] <= vals_out[k+1]):
                print(f"[FAIL] values are not non-decreasing at output lines {k} and {k+1}: {vals_out[k]} > {vals_out[k+1]}")
                sys.exit(1)
        print("[FAIL] values are not non-decreasing.")
        sys.exit(1)

    print("[PASS] lines match, index contiguous, and values are non-decreasing.")
    sys.exit(0)

if __name__ == "__main__":
    main()
