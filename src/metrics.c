/**
 * @file metrics.c
 * @brief Recolección y exposición de métricas del sistema.
 *
 * Este archivo contiene las funciones necesarias para recolectar y exponer
 * métricas del sistema, tales como fallos de página y uso de ancho de banda.
 * Las métricas se recolectan desde los archivos del sistema en /proc y se
 * exponen a través de Prometheus para su visualización en Grafana.
 *
 * Funciones incluidas:
 * - get_average_bandwidth(): Calcula el ancho de banda promedio de red.
 * - get_minor_page_faults(): Obtiene la cantidad de fallos de página menores.
 * - get_major_page_faults(): Obtiene la cantidad de fallos de página mayores.
 */

#include "metrics.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

/**
 * @brief Obtiene el número total de cambios de contexto desde /proc/stat.
 *
 * Lee el archivo /proc/stat y busca la línea que contiene el número
 * de cambios de contexto (línea que comienza con 'ctxt').
 *
 * @return El número total de cambios de contexto como un valor unsigned long long.
 * Si ocurre un error, devuelve -1.
 */
unsigned long long get_change_context()
{
    FILE* fp;
    char buffer[BUFFER_SIZE];
    unsigned long long cambios = INICIAL_VALUE;

    // Abrir el archivo /proc/stat
    fp = fopen("/proc/stat", "r");
    if (fp == NULL)
    {
        perror("Error al abrir /proc/stat");
        return ERROR_INT;
    }

    // Leer el archivo línea por línea
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        // Buscar la línea que comienza con 'ctxt'
        if (sscanf(buffer, "ctxt %llu", &cambios) == ASSIGNED_VALUE)
        {
            break;
        }
    }

    fclose(fp);

    if (cambios == INICIAL_VALUE)
    {
        fprintf(stderr, "No se encontró el número de cambios en /proc/stat\n");
        return ERROR_INT;
    }

    return cambios;
}

/**
 * @brief Obtiene el número total de procesos creados desde el inicio del sistema.
 *
 * Lee el archivo /proc/stat y busca la línea que contiene el número de procesos
 * (línea que comienza con 'processes').
 *
 * @return El número total de procesos creados como un valor unsigned long long.
 * Si ocurre un error, devuelve -1.
 */
unsigned long long get_total_processes()
{
    FILE* fp;
    char buffer[BUFFER_SIZE];
    unsigned long long processes = INICIAL_VALUE;

    // Abrir el archivo /proc/stat
    fp = fopen("/proc/stat", "r");
    if (fp == NULL)
    {
        perror("Error al abrir /proc/stat");
        return ERROR_INT;
    }

    // Leer el archivo línea por línea
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        // Buscar la línea que comienza con 'processes'
        if (sscanf(buffer, "processes %llu", &processes) == ASSIGNED_VALUE)
        {
            break;
        }
    }

    fclose(fp);

    if (processes == INICIAL_VALUE)
    {
        fprintf(stderr, "No se encontró el número de procesos en /proc/stat\n");
        return ERROR_INT;
    }

    return processes;
}

/**
 * @brief Obtiene las estadísticas de lectura y escritura del disco desde /proc/diskstats.
 *
 * Lee el archivo /proc/diskstats y obtiene los valores de lectura y escritura
 * correspondientes al dispositivo 'sda'. Retorna la suma de los bytes leídos y escritos.
 *
 * @return El total de lecturas y escrituras en el disco como un valor double.
 * Si ocurre un error, devuelve -1.0.
 */
double get_disk_stats()
{
    FILE* fp;
    char buffer[BUFFER_SIZE];
    unsigned long long read = INICIAL_VALUE, write = INICIAL_VALUE, total = INICIAL_VALUE;

    // Abrir el archivo /proc/diskstats
    fp = fopen("/proc/diskstats", "r");
    if (fp == NULL)
    {
        perror("\nError de apertura del archivo");
        return ERROR_FLOAT;
    }

    // Leer los valores de lectura y escritura del dispositivo 'sda'
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        if (sscanf(buffer, "%*u %*u sda %llu %*u %*u %*u %llu", &read, &write) == ASSIGNED_VALUE)
        {
            break; // Valores encontrados
        }
    }

    fclose(fp);

    // Verificar si se encontraron los valores
    if (read == INICIAL_VALUE)
    {
        fprintf(stderr, "Error al leer la información del disco desde /proc/diskstats\n");
        return ERROR_FLOAT;
    }

    total = read + write;

    return total;
}

/**
 * @brief Obtiene el total de memoria disponible en el sistema desde /proc/meminfo.
 *
 * Lee el archivo /proc/meminfo y busca la línea que contiene el valor de 'MemTotal'.
 *
 * @return El valor total de memoria disponible en kilobytes como un valor double.
 * Si ocurre un error, devuelve -1.0.
 */
double get_memory_total()
{
    FILE* fp;
    char buffer[BUFFER_SIZE];
    unsigned long long total_mem = INICIAL_VALUE;

    // Abrir el archivo /proc/meminfo
    fp = fopen("/proc/meminfo", "r");
    if (fp == NULL)
    {
        perror("Error al abrir /proc/meminfo");
        return ERROR_FLOAT;
    }

    // Leer el valor de MemTotal
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        if (sscanf(buffer, "MemTotal: %llu kB", &total_mem) == ASSIGNED_VALUE)
        {
            break; // MemTotal encontrado
        }
    }

    fclose(fp);

    // Verificar si se encontró el valor
    if (total_mem == INICIAL_VALUE)
    {
        fprintf(stderr, "Error al leer la información de memoria desde /proc/meminfo\n");
        return ERROR_FLOAT;
    }

    return total_mem;
}

/**
 * @brief Obtiene la cantidad de memoria disponible en el sistema desde /proc/meminfo.
 *
 * Lee el archivo /proc/meminfo y busca la línea que contiene el valor de 'MemAvailable'.
 *
 * @return El valor de memoria disponible en kilobytes como un valor double.
 * Si ocurre un error, devuelve -1.0.
 */
double get_memory_avalible()
{
    FILE* fp;
    char buffer[BUFFER_SIZE];
    unsigned long long free_mem = INICIAL_VALUE;

    // Abrir el archivo /proc/meminfo
    fp = fopen("/proc/meminfo", "r");
    if (fp == NULL)
    {
        perror("Error al abrir /proc/meminfo");
        return ERROR_FLOAT;
    }

    // Leer el valor de MemAvailable
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        if (sscanf(buffer, "MemAvailable: %llu kB", &free_mem) == ASSIGNED_VALUE)
        {
            break; // MemAvailable encontrado
        }
    }

    fclose(fp);

    // Verificar si se encontró el valor
    if (free_mem == INICIAL_VALUE)
    {
        fprintf(stderr, "Error al leer la información de memoria desde /proc/meminfo\n");
        return ERROR_FLOAT;
    }

    return free_mem;
}

/**
 * @brief Calcula el porcentaje de uso de memoria en el sistema.
 *
 * Lee el archivo /proc/meminfo para obtener los valores de 'MemTotal' y 'MemAvailable',
 * y calcula el porcentaje de memoria usada en base a estos valores.
 *
 * @return El porcentaje de uso de memoria como un valor double.
 * Si ocurre un error, devuelve -1.0.
 */
double get_memory_usage()
{
    FILE* fp;
    char buffer[BUFFER_SIZE];
    unsigned long long total_mem = INICIAL_VALUE, free_mem = INICIAL_VALUE;

    // Abrir el archivo /proc/meminfo
    fp = fopen("/proc/meminfo", "r");
    if (fp == NULL)
    {
        perror("Error al abrir /proc/meminfo");
        return ERROR_FLOAT;
    }

    // Leer los valores de MemTotal y MemAvailable
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        if (sscanf(buffer, "MemTotal: %llu kB", &total_mem) == ASSIGNED_VALUE)
        {
            continue; // MemTotal encontrado
        }
        if (sscanf(buffer, "MemAvailable: %llu kB", &free_mem) == ASSIGNED_VALUE)
        {
            break; // MemAvailable encontrado, podemos dejar de leer
        }
    }

    fclose(fp);

    // Verificar si se encontraron ambos valores
    if (total_mem == INICIAL_VALUE || free_mem == INICIAL_VALUE)
    {
        fprintf(stderr, "Error al leer la información de memoria desde /proc/meminfo\n");
        return ERROR_FLOAT;
    }

    // Calcular el porcentaje de uso de memoria
    double used_mem = total_mem - free_mem;
    double mem_usage_percent = (used_mem / total_mem) * 100.0;

    return mem_usage_percent;
}

/**
 * @brief Obtiene el uso de memoria como un porcentaje normalizado (dividido por 100).
 *
 * @return El uso de memoria como valor double, normalizado.
 */
double get_memory_usage_2()
{
    return get_memory_usage() / PORCENTAGE_INT;
}

/**
 * @brief Calcula el porcentaje de uso de CPU en el sistema.
 *
 * Lee el archivo /proc/stat para obtener los tiempos de CPU y calcula el porcentaje de uso
 * en base a las diferencias de tiempos entre lecturas consecutivas.
 *
 * @return El porcentaje de uso de CPU como un valor double. Si ocurre un error, devuelve -1.0.
 */
double get_cpu_usage()
{
    static unsigned long long prev_user = INICIAL_VALUE, prev_nice = INICIAL_VALUE, prev_system = INICIAL_VALUE,
                              prev_idle = INICIAL_VALUE, prev_iowait = INICIAL_VALUE, prev_irq = INICIAL_VALUE,
                              prev_softirq = INICIAL_VALUE, prev_steal = INICIAL_VALUE;
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
    unsigned long long totald, idled;
    double cpu_usage_percent;

    // Abrir el archivo /proc/stat
    FILE* fp = fopen("/proc/stat", "r");
    if (fp == NULL)
    {
        perror("Error al abrir /proc/stat");
        return ERROR_FLOAT;
    }

    char buffer[BUFFER_SIZE * 4];
    if (fgets(buffer, sizeof(buffer), fp) == NULL)
    {
        perror("Error al leer /proc/stat");
        fclose(fp);
        return ERROR_FLOAT;
    }
    fclose(fp);

    // Analizar los valores de tiempo de CPU
    int ret = sscanf(buffer, "cpu  %llu %llu %llu %llu %llu %llu %llu %llu", &user, &nice, &system, &idle, &iowait,
                     &irq, &softirq, &steal);
    if (ret < ASSIGNED_VALUE_8)
    {
        fprintf(stderr, "Error al parsear /proc/stat\n");
        return ERROR_FLOAT;
    }

    // Calcular las diferencias entre las lecturas actuales y anteriores
    unsigned long long prev_idle_total = prev_idle + prev_iowait;
    unsigned long long idle_total = idle + iowait;

    unsigned long long prev_non_idle = prev_user + prev_nice + prev_system + prev_irq + prev_softirq + prev_steal;
    unsigned long long non_idle = user + nice + system + irq + softirq + steal;

    unsigned long long prev_total = prev_idle_total + prev_non_idle;
    unsigned long long total = idle_total + non_idle;

    totald = total - prev_total;
    idled = idle_total - prev_idle_total;

    if (totald == INICIAL_VALUE)
    {
        fprintf(stderr, "Totald es cero, no se puede calcular el uso de CPU!\n");
        return ERROR_FLOAT;
    }

    // Calcular el porcentaje de uso de CPU
    cpu_usage_percent = ((double)(totald - idled) / totald) * 100.0;

    // Actualizar los valores anteriores para la siguiente lectura
    prev_user = user;
    prev_nice = nice;
    prev_system = system;
    prev_idle = idle;
    prev_iowait = iowait;
    prev_irq = irq;
    prev_softirq = softirq;
    prev_steal = steal;

    return cpu_usage_percent;
}

/**
 * @brief Calcula el uso del disco.
 *
 * Lee las estadísticas del disco desde /proc/diskstats y calcula el número total de sectores leídos y escritos,
 * devolviendo el valor total en MB.
 *
 * @return El uso de disco en MB como valor double. Si ocurre un error, devuelve -1.0.
 */
double get_disk_usage()
{
    char buffer[BUFFER_SIZE * 2];
    static unsigned long long prev_read_sectors = INICIAL_VALUE, prev_write_sectors = INICIAL_VALUE;
    unsigned long long read_sectors = INICIAL_VALUE, write_sectors = INICIAL_VALUE;

    // Abrir el archivo /proc/diskstats
    FILE* fp = popen("cat /proc/diskstats|  grep -w 'sda'", "r");
    if (fp == NULL)
    {
        perror("Error al abrir /proc/diskstats");
        return ERROR_FLOAT;
    }

    // Leer las estadísticas del disco
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        unsigned int major, minor;
        char device_name[DEVICE_SIZE];
        unsigned long reads, writes;

        // Parsear los valores de lecturas y escrituras
        if (sscanf(buffer, "%u %u %s %*u %*u %lu %*u %*u %*u %lu", &major, &minor, device_name, &reads, &writes) ==
            ASSIGNED_VALUE_5)
        {
            read_sectors += reads;
            write_sectors += writes;
        }
    }

    fclose(fp);

    // Calcular el delta en sectores desde la última lectura
    unsigned long long delta_reads = read_sectors - prev_read_sectors;
    unsigned long long delta_writes = write_sectors - prev_write_sectors;
    unsigned long long total_sectors = delta_reads + delta_writes;

    // Actualizar los valores anteriores para la siguiente llamada
    prev_read_sectors = read_sectors;
    prev_write_sectors = write_sectors;

    // Convertir los sectores a bytes y calcular el porcentaje (simplificado)
    double disk_usage_percent = (double)(total_sectors * SECTOR_SIZE) / (ONE_KB * ONE_KB); // Convertir a MB

    return disk_usage_percent;
}

/**
 * @brief Calcula el uso de red total (envío y recepción de bytes).
 *
 * Lee las estadísticas de las interfaces de red desde /proc/net/dev y devuelve el uso total de red en MB.
 *
 * @return El uso de red total en MB como valor double. Si ocurre un error, devuelve -1.0.
 */
double get_network_usage()
{
    char buffer[BUFFER_SIZE * 2];
    unsigned long long rx_bytes = INICIAL_VALUE, tx_bytes = INICIAL_VALUE;

    // Abrir el archivo /proc/net/dev
    FILE* fp = fopen("/proc/net/dev", "r");
    if (fp == NULL)
    {
        perror("Error al abrir /proc/net/dev");
        return ERROR_FLOAT;
    }

    // Saltar las primeras dos líneas que son encabezados
    fgets(buffer, sizeof(buffer), fp);
    fgets(buffer, sizeof(buffer), fp);

    // Leer las estadísticas de las interfaces de red
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        char interface[INTERFACE_SIZE];
        unsigned long long rx, tx;

        // Parsear los bytes recibidos y transmitidos por cada interfaz
        if (sscanf(buffer, "%s %llu %*u %*u %*u %*u %*u %*u %*u %llu", interface, &rx, &tx) == ASSIGNED_VALUE_3)
        {
            rx_bytes += rx;
            tx_bytes += tx;
        }
    }

    fclose(fp);

    // Calcular el tráfico de red total (simplificado)
    double network_usage = ((double)(rx_bytes + tx_bytes)) / (ONE_KB * ONE_KB); // Convertir a MB

    return network_usage;
}

/**
 * @brief Calculates the average network bandwidth usage.
 *
 * This function reads the network statistics from the file `/proc/net/dev`
 * and calculates the average bandwidth usage in MB/s since the last call.
 * It tracks the total number of bytes received and transmitted across all interfaces
 * and computes the difference from the previous reading.
 *
 * @return The average network bandwidth usage in MB/s. Returns -1.0 on error.
 */
double get_average_bandwidth()
{
    char buffer[BUFFER_SIZE * 2];
    unsigned long long rx_bytes = INICIAL_VALUE, tx_bytes = INICIAL_VALUE;
    static unsigned long long prev_rx_bytes = INICIAL_VALUE, prev_tx_bytes = INICIAL_VALUE;

    // Variables para el cálculo del tiempo
    static clock_t last_time = INICIAL_VALUE; // Almacena el tiempo de la última llamada
    clock_t current_time = clock();           // Obtiene el tiempo actual

    // Calcular el tiempo transcurrido en segundos
    double elapsed_time = (double)(current_time - last_time) / CLOCKS_PER_SEC;

    // Abrir el archivo /proc/net/dev
    FILE* fp = fopen("/proc/net/dev", "r");
    if (fp == NULL)
    {
        perror("Error al abrir /proc/net/dev");
        return ERROR_FLOAT;
    }

    // Saltar las primeras dos líneas que son encabezados
    fgets(buffer, sizeof(buffer), fp);
    fgets(buffer, sizeof(buffer), fp);

    // Leer las estadísticas de las interfaces de red
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        char interface[INTERFACE_SIZE];
        unsigned long long rx, tx;

        // Parsear los bytes recibidos y transmitidos por cada interfaz
        if (sscanf(buffer, "%s %llu %*u %*u %*u %*u %*u %*u %*u %llu", interface, &rx, &tx) == ASSIGNED_VALUE_3)
        {
            rx_bytes += rx;
            tx_bytes += tx;
        }
    }

    fclose(fp);

    // Calcular el delta de bytes recibidos y transmitidos
    unsigned long long delta_rx = rx_bytes - prev_rx_bytes;
    unsigned long long delta_tx = tx_bytes - prev_tx_bytes;
    unsigned long long total_bytes = delta_rx + delta_tx;

    // Actualizar los valores anteriores para la siguiente llamada
    prev_rx_bytes = rx_bytes;
    prev_tx_bytes = tx_bytes;

    // Calcular el tráfico de red total (simplificado)
    double network_usage = ((double)total_bytes) / (ONE_KB * ONE_KB); // Convertir a MB
    double bandwidth = network_usage / elapsed_time;                  // Calcular el ancho de banda promedio

    // Actualizar el tiempo de la última llamada
    last_time = current_time;

    return bandwidth;
}

/**
 * @brief Retrieves the number of minor page faults.
 *
 * This function reads the `/proc/vmstat` file to get the current number of minor page faults.
 *
 * @return The number of minor page faults. Returns -1 on error.
 */
unsigned long long get_minor_page_faults()
{
    FILE* fp;
    char buffer[BUFFER_SIZE];
    unsigned long long minor_faults = INICIAL_VALUE;

    // Abrir el archivo /proc/vmstat
    fp = fopen("/proc/vmstat", "r");
    if (fp == NULL)
    {
        perror("Error al abrir /proc/vmstat");
        return ERROR_INT;
    }

    // Leer las métricas de fallos menores
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        if (sscanf(buffer, "pgfault %llu", &minor_faults) == ASSIGNED_VALUE)
        {
            break;
        }
    }

    fclose(fp);
    return minor_faults;
}

/**
 * @brief Retrieves the number of major page faults.
 *
 * This function reads the `/proc/vmstat` file to get the current number of major page faults.
 *
 * @return The number of major page faults. Returns -1 on error.
 */
unsigned long long get_major_page_faults()
{
    FILE* fp;
    char line[BUFFER_SIZE];
    unsigned long long major_faults = INICIAL_VALUE;

    // Abrir el archivo /proc/vmstat
    fp = fopen("/proc/vmstat", "r");
    if (fp == NULL)
    {
        perror("Error al abrir /proc/vmstat");
        return ERROR_INT;
    }

    // Leer las métricas de fallos mayores
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (sscanf(line, "pgmajfault %llu", &major_faults) == ASSIGNED_VALUE)
        {
            break;
        }
    }

    fclose(fp);
    return major_faults;
}
