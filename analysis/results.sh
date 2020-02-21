#!/bin/bash

root -l run_analysis.C

grep -r "e:" ../data/anahit*.out | awk '{print $3 "\t" $5}' > ../data/eff.dat


printf "%d\t%d\n" "-100" "-90" > ../data/pos.dat
grep "setPos" ../CTSci-run/scan_short.mac | awk '{print $2 "\t" $4}' >> ../data/pos.dat


pr -m -t ../data/pos.dat ../data/eff.dat

root -l plot.C
