#!/usr/bin/env bash
set -e

echo "=== PetoronAI Cognitive Audit ==="

echo
echo "1) Build"
cmake --build build -j$(sysctl -n hw.ncpu)

echo
echo "2) Full test suite"
ctest --test-dir build --output-on-failure

echo
echo "3) Executive 100k stress"
c++ -O3 -std=c++20 \
  petoron_ai_100k_stress.cpp \
  -I mind/include \
  -I zkPetoron-Core \
  build/libpetoron_ai.a \
  build/zkPetoron-Core/libzkpetoron.a \
  build/zkPetoron-Core/PetoronHash2/libpetoronhash2.a \
  -o petoron_ai_100k_stress

./petoron_ai_100k_stress

echo
echo "4) Cognitive capability tests"
ctest --test-dir build -R "determinism|contradiction|recursive|counterfactual|hypothesis|planning|world|goal|strategy|learning|safety|risk|reasoning|memory|thought|executive" --output-on-failure

echo
echo "5) Capability map"
find mind/include/petoron_ai mind/src -type f | \
grep -E "reasoning|hypothesis|counterfactual|world|goal|strategy|thought|memory|executive|planning|safety|risk|learning|experience|policy" | \
sort

echo
echo "=== Cognitive Audit PASS ==="
