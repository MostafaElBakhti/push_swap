#!/usr/bin/env bash
# Simple tester for push_swap: generates random unique numbers, runs push_swap,
# counts operations, and reports min/avg/max. Usage: test_random.sh SIZE TRIALS

set -euo pipefail
SIZE=${1:-100}
TRIALS=${2:-100}
OUTDIR=${3:-results}
RANGE_MAX=100000
mkdir -p "$OUTDIR"
OUT_CSV="$OUTDIR/results_${SIZE}.csv"
: > "$OUT_CSV"

echo "size,trial,ops" >> "$OUT_CSV"
min_ops=99999999
max_ops=0
sum_ops=0
worst_sequence_file="$OUTDIR/worst_${SIZE}.txt"
: > "$worst_sequence_file"

for i in $(seq 1 $TRIALS); do
  nums=$(shuf -i 1-$RANGE_MAX -n $SIZE | tr '\n' ' ')
  ops=$(./push_swap $nums | wc -l)
  echo "${SIZE},${i},${ops}" >> "$OUT_CSV"
  sum_ops=$((sum_ops + ops))
  if [ $ops -lt $min_ops ]; then min_ops=$ops; fi
  if [ $ops -gt $max_ops ]; then
    max_ops=$ops
    echo "$nums" > "$worst_sequence_file"
  fi
  printf "\rTrial %d/%d — ops: %d (min:%d max:%d)" "$i" "$TRIALS" "$ops" "$min_ops" "$max_ops"
done

echo
avg_ops=$(awk -v s=$sum_ops -v t=$TRIALS 'BEGIN{printf "%.2f", s/t}')
cat <<EOF
Results for size=$SIZE (trials=$TRIALS):
- min: $min_ops
- avg: $avg_ops
- max: $max_ops
CSV: $OUT_CSV
Worst sequence saved to: $worst_sequence_file
EOF
