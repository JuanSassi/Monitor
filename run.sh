#!/bin/bash
 gcc src/*.c -o metrics -I include/ -lprom -pthread -lpromhttp
#gcc src/metrics.c src/expose_metrics.c src/main.c -o metrics -lprom -pthread -lpromhttp
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
./metrics
