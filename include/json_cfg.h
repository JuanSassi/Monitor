#ifndef JSON_CFG_H
#define JSON_CFG_H

#include "cjson/cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variables globales que indican las banderas de métricas.

/**
 * @brief Bandera para el monitoreo del ancho de banda.
 *
 * Esta variable se utiliza para habilitar o deshabilitar el monitoreo
 * del uso del ancho de banda en la configuración.
 */
extern bool flag_bandwidth;

/**
 * @brief Bandera para el monitoreo del uso de CPU.
 *
 * Esta variable se utiliza para habilitar o deshabilitar el monitoreo
 * del uso de CPU en la configuración.
 */
extern bool flag_cpu;

/**
 * @brief Bandera para el monitoreo del uso de disco.
 *
 * Esta variable se utiliza para habilitar o deshabilitar el monitoreo
 * del uso del disco en la configuración.
 */
extern bool flag_disk;

/**
 * @brief Bandera para indicar cambios en la configuración.
 *
 * Esta variable se utiliza para señalar si ha habido cambios en
 * la configuración que deben ser procesados.
 */
extern bool flag_change;

/**
 * @brief Estructura que representa la configuración del sistema de monitoreo.
 */
typedef struct
{
    int sampling_interval; ///< Intervalo de muestreo en segundos.
    char** metrics;        ///< Lista de métricas a recolectar.
    int metrics_count;     ///< Número de métricas en la lista.
} Config;

/**
 * @brief Carga la configuración desde un archivo JSON.
 *
 * @param filename Ruta del archivo JSON que contiene la configuración.
 * @return Un puntero a una estructura Config que contiene los valores cargados, o NULL si hay un error.
 */
Config* load_config(const char* filename);

/**
 * @brief Libera la memoria ocupada por una estructura Config.
 *
 * @param config Puntero a la estructura Config a liberar.
 */
void free_config(Config* config);

#endif
