#!/usr/bin/env bash

UTIME=`date +%s`
SVG_OUT=out$UTIME.svg
rm -rf $SVG_OUT

#path to perf
PERF_BIN=perf

#path to local directory with FlameGraph https://github.com/brendangregg/FlameGraph
FLAME_DIR=/home/igor/Projects/FlameGraph

$PERF_BIN record --call-graph dwarf -g $@

rm -rf /tmp/out.perf_folded
$PERF_BIN script | $FLAME_DIR/stackcollapse-perf.pl > /tmp/out.perf-folded
$FLAME_DIR/flamegraph.pl /tmp/out.perf-folded > $SVG_OUT


