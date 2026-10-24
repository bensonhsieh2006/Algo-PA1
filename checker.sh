# This script contain compile or examination commands
# This script should be executed under "<id>_pa1"
# How to execute: type "./checker.sh <mode>" in terminal
# Selectable mode: IS, MS, BMS, QS, RQS, HS
set -Eeuo pipefail

if [[ $# -lt 1 ]]; then
  echo "Usage: $0 <mode>"
  exit 1
fi
MODE="$1"

RESULT_DIR="./results"
INPUT_DIR="./inputs"
OUTPUT_DIR="./outputs"
BIN="./bin/NTU_sort"
CHECKER="python3 check_pa1_sorted.py"

RESULT_FILE="$RESULT_DIR/${MODE}.result"
rm -f "$RESULT_FILE"

make
#datas
sizes=(5 1000 2000 4000 8000 16000 32000 1000000)

run_one_case() {
  local n="$1"
  local case_id="$2"

  local in_file="${INPUT_DIR}/${n}.case${case_id}.in"
  local out_file="${OUTPUT_DIR}/${n}.case${case_id}.out"

  "${BIN}" -"${MODE}" "${in_file}" "${out_file}"

  printf "case %s: " "${case_id}" >> "${RESULT_FILE}"
  ${CHECKER} "${in_file}" "${out_file}" >> "${RESULT_FILE}"
}

for n in "${sizes[@]}"; do
  if [[ "${n}" -ge 1000000 ]]; then
    ulimit -s 262144 || true   
  fi

  echo "Now running ${MODE} sorter: n=${n}"
  {
    echo "Sorter: ${MODE}, n = ${n}"
    echo "----------"
  } >> "${RESULT_FILE}"

  # n=5 只跑 case1，其餘跑 1..3
  if [[ "${n}" -eq 5 ]]; then
    run_one_case "${n}" 1
  else
    for case_id in 1 2 3; do
      run_one_case "${n}" "${case_id}"
    done
  fi

  echo "----------" >> "${RESULT_FILE}"
done

echo "Done execution"