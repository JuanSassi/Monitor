#!/bin/bash
find / -name "cJSON.h" 2>/dev/null

# Compilación del proyecto
gcc src/*.c -o metrics -I include/ -I /usr/local/include/ -lprom -pthread -lpromhttp -lcjson

# Actualización de la variable de entorno para localizar las bibliotecas dinámicas
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

# Ejecución del binario generado
#./metrics
