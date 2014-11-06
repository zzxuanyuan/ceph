#!/bin/sh

NUM="$1"
GAP="$2"
DUR="$3"
FEATURES="$4"

[ -z "$NUM" ] && NUM=30
[ -z "$GAP" ] && GAP=5
[ -z "$DUR" ] && DUR=30
[ -n "$FEATURES" ] && FEATURES="--features ${FEATURES}"

for n in `seq 1 $NUM`; do
    echo "Starting $n of $NUM ..."
    ceph_smalliobenchrbd --pool rbd --duration $DUR --disable-detailed-ops 1 $FEATURES &
    sleep $GAP
done
echo "Waiting..."
wait
echo "OK"
