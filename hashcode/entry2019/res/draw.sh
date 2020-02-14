#!/bin/sh

cargo run > res/output.dot
dot -Tps res/output.dot -o res/graph.ps
ps2pdf res/graph.ps res/graph.pdf
rm -rf res/graph.ps
zathura res/graph.pdf
