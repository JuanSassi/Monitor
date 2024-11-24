#include "json_cfg.h"

/**
 * @brief Bandera para el monitoreo del ancho de banda.
 *
 * Esta variable se utiliza para habilitar o deshabilitar el monitoreo
 * del uso del ancho de banda en la configuración.
 */
bool flag_bandwidth = true;

/**
 * @brief Bandera para el monitoreo del uso de CPU.
 *
 * Esta variable se utiliza para habilitar o deshabilitar el monitoreo
 * del uso de CPU en la configuración.
 */
bool flag_cpu = true;

/**
 * @brief Bandera para el monitoreo del uso de disco.
 *
 * Esta variable se utiliza para habilitar o deshabilitar el monitoreo
 * del uso del disco en la configuración.
 */
bool flag_disk = true;

/**
 * @brief Bandera para indicar cambios en la configuración.
 *
 * Esta variable se utiliza para señalar si ha habido cambios en
 * la configuración que deben ser procesados.
 */
bool flag_change = true;

int read_sampling_interval(const char *file_path) {
    // Abrir el archivo JSON
    FILE *file = fopen(file_path, "r");
    if (!file) {
        perror("Error al abrir el archivo");
        return -1;
    }

    // Leer el contenido del archivo
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *json_content = (char *)malloc(file_size + 1);
    if (!json_content) {
        perror("Error al asignar memoria");
        fclose(file);
        return -1;
    }

    fread(json_content, 1, file_size, file);
    json_content[file_size] = '\0';
    fclose(file);

    // Parsear el JSON
    cJSON *json = cJSON_Parse(json_content);
    free(json_content);
    if (!json) {
        fprintf(stderr, "Error al parsear el JSON: %s\n", cJSON_GetErrorPtr());
        return -1;
    }

    // Obtener el valor de "sampling_interval"
    cJSON *sampling_interval = cJSON_GetObjectItemCaseSensitive(json, "sampling_interval");
    if (!cJSON_IsNumber(sampling_interval)) {
        fprintf(stderr, "El valor de 'sampling_interval' no es válido\n");
        cJSON_Delete(json);
        return -1;
    }

    int interval = sampling_interval->valueint;
    cJSON_Delete(json);
    return interval;
}

/**
 * @brief Actualiza las banderas de monitoreo según las métricas en el JSON.
 *
 * @param file_path Ruta al archivo JSON que contiene la configuración.
 */
void update_flags_from_json(const char *file_path) {
    // Abrir el archivo JSON
    FILE *file = fopen(file_path, "r");
    if (!file) {
        perror("Error al abrir el archivo");
        return;
    }

    // Leer el contenido del archivo
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *json_content = (char *)malloc(file_size + 1);
    if (!json_content) {
        perror("Error al asignar memoria");
        fclose(file);
        return;
    }

    fread(json_content, 1, file_size, file);
    json_content[file_size] = '\0';
    fclose(file);

    // Parsear el JSON
    cJSON *json = cJSON_Parse(json_content);
    free(json_content);
    if (!json) {
        fprintf(stderr, "Error al parsear el JSON: %s\n", cJSON_GetErrorPtr());
        return;
    }

    // Obtener el array de "metrics"
    cJSON *metrics = cJSON_GetObjectItemCaseSensitive(json, "metrics");
    if (!cJSON_IsArray(metrics)) {
        fprintf(stderr, "'metrics' no es un array válido\n");
        cJSON_Delete(json);
        return;
    }

    // Resetear banderas
    flag_bandwidth = false;
    flag_cpu = false;
    flag_disk = false;
    flag_change = false;

    // Actualizar banderas según las métricas
    cJSON *metric;
    cJSON_ArrayForEach(metric, metrics) {
        if (cJSON_IsString(metric)) {
            if (strcmp(metric->valuestring, "bandwith_usage") == 0) {
                flag_bandwidth = true;
            } 
            if (strcmp(metric->valuestring, "cpu_usage_porcentage") == 0) {
                flag_cpu = true;
            } 
            if (strcmp(metric->valuestring, "disk_usage_porcentage") == 0) {
                flag_disk = true;
            } 
            if (strcmp(metric->valuestring, "change_contexts") == 0){
                flag_change = true;
            }
        }
    }

    // Indicar si hubo cambios en la configuración
    if (flag_bandwidth || flag_cpu || flag_disk) {
        flag_change = true;
    }

    cJSON_Delete(json);
}