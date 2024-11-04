#include "json_cfg.h"

/**
 * @brief Bandera para el monitoreo del ancho de banda.
 *
 * Esta variable se utiliza para habilitar o deshabilitar el monitoreo
 * del uso del ancho de banda en la configuración.
 */
bool flag_bandwidth = false;

/**
 * @brief Bandera para el monitoreo del uso de CPU.
 *
 * Esta variable se utiliza para habilitar o deshabilitar el monitoreo
 * del uso de CPU en la configuración.
 */
bool flag_cpu = false;

/**
 * @brief Bandera para el monitoreo del uso de disco.
 *
 * Esta variable se utiliza para habilitar o deshabilitar el monitoreo
 * del uso del disco en la configuración.
 */
bool flag_disk = false;

/**
 * @brief Bandera para indicar cambios en la configuración.
 *
 * Esta variable se utiliza para señalar si ha habido cambios en
 * la configuración que deben ser procesados.
 */
bool flag_change = false;

/**
 * @brief Carga la configuración desde un archivo JSON.
 *
 * Esta función intenta abrir un archivo JSON especificado por `filename`,
 * lee su contenido y lo parsea. Se devuelve un puntero a una estructura
 * `Config` que contiene los valores cargados, o NULL si ocurre un error.
 * @return Un puntero a una estructura Config que contiene los valores cargados, o NULL si hay un error.
 */
Config* load_config(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        perror("Error abriendo el archivo de configuración");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* data = malloc(length + 1);
    fread(data, 1, length, file);
    data[length] = '\0';
    fclose(file);

    cJSON* json = cJSON_Parse(data);
    free(data);
    if (!json)
    {
        printf("Error parseando JSON: %s\n", cJSON_GetErrorPtr());
        return NULL;
    }

    Config* config = malloc(sizeof(Config));

    // Leer sampling_interval
    cJSON* sampling_interval = cJSON_GetObjectItem(json, "sampling_interval");
    if (cJSON_IsNumber(sampling_interval))
    {
        config->sampling_interval = sampling_interval->valueint; ///< Asignar el intervalo de muestreo.
    }
    else
    {
        config->sampling_interval = 1; // Valor predeterminado si falta en JSON
    }

    // Leer metrics
    cJSON* metrics = cJSON_GetObjectItem(json, "metrics");
    if (cJSON_IsArray(metrics))
    {
        config->metrics_count = cJSON_GetArraySize(metrics);
        config->metrics = malloc(config->metrics_count * sizeof(char*));

        for (int i = 0; i < config->metrics_count; i++)
        {
            cJSON* metric = cJSON_GetArrayItem(metrics, i);
            if (cJSON_IsString(metric))
            {
                config->metrics[i] = strdup(metric->valuestring); ///< Copiar la métrica a la estructura.
            }
        }
    }
    else
    {
        config->metrics_count = 0; ///< No hay métricas si no se encuentra un array.
        config->metrics = NULL;
    }

    // Inicializar banderas a false
    flag_bandwidth = false;
    flag_change = false;
    flag_cpu = false;
    flag_disk = false;

    // Verificar qué métricas están habilitadas
    for (int i = 0; i < config->metrics_count; i++)
    {
        if (strcmp(config->metrics[i], "bandwidth_usage") == 0)
        {
            flag_bandwidth = true; ///< Activar bandera de ancho de banda.
        }
        else if (strcmp(config->metrics[i], "cpu_usage_percentage") == 0)
        {
            flag_cpu = true; ///< Activar bandera de CPU.
        }
        else if (strcmp(config->metrics[i], "disk_usage_percentage") == 0)
        {
            flag_disk = true; ///< Activar bandera de disco.
        }
        else if (strcmp(config->metrics[i], "change_contexts") == 0) // Corregido el error de sintaxis
        {
            flag_change = true; ///< Activar bandera de cambios en contextos.
        }
        else
        {
            printf("Métrica desconocida: %s\n", config->metrics[i]); ///< Mensaje para métricas desconocidas.
        }
    }

    cJSON_Delete(json); ///< Liberar memoria del objeto JSON.
    return config;      ///< Devolver la configuración cargada.
}

/**
 * @brief Libera la memoria ocupada por una estructura Config.
 *
 * Esta función libera la memoria asignada a la estructura
 * `Config`, incluyendo sus métricas.
 */
void free_config(Config* config)
{
    if (config)
    {
        for (int i = 0; i < config->metrics_count; i++)
        {
            free(config->metrics[i]); ///< Liberar cada métrica.
        }
        free(config->metrics); ///< Liberar la lista de métricas.
        free(config);          ///< Liberar la estructura de configuración.
    }
}
