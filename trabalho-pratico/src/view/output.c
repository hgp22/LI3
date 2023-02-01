#include "output.h"
#include <ctype.h>
#include <glib.h>
#include <math.h>
#include <stdbool.h>
#include <wchar.h>

#define BUFFER 128

struct output {
    GPtrArray *header;
    GPtrArray *lines;
};

Output output_new(void)
{
    Output output = malloc(sizeof(struct output));

    output->lines = NULL;
    output->header = NULL;

    return output;
}

Output output_build_lines(GPtrArray *entries)
{
    GPtrArray *lines = g_ptr_array_new_full(entries->len, free);

    for (guint i = 0; i < entries->len; i++) {
        char *entry = g_ptr_array_index(entries, i);
        wchar_t *line = malloc(BUFFER * sizeof(*line));
        mbstowcs(line, entry, BUFFER);
        g_ptr_array_add(lines, line);
    }

    // create output struct
    Output output = output_new();

    output->lines = lines;

    return output;
}

// se em vez fizer por colunas não preciso da varivel size porque será o numero
// de colunas
// ! gerar linhas com memória dinânmica ou gerar linhas com no máximo o número
// de nolunas disponiveis e usar "n" functions para evitar overflow ! e
// implementar horizontal scrolling? mas para isso tinham na mesma de ter todo o
// tamanho necessário... só no print é que só era usado o comprimento de uma
// linha
Output output_build_table(const GPtrArray *entries, int sizes[],
                          char *headers[])
{
    // get number of columns
    int size = ((GPtrArray *)g_ptr_array_index(entries, 0))->len;

    // get lenght of index
    int index_length = (int)(log10(entries->len)) + 1;

    // get max lengths of each collumn
    for (guint i = 0; i < entries->len; i++) {
        GPtrArray *entry = g_ptr_array_index(entries, i);
        for (guint j = 0; j < entry->len; j++) {
            char *field = g_ptr_array_index(entry, j);
            int len = mbstowcs(NULL, field, 0);
            if (len > sizes[j]) {
                sizes[j] = len;
            }
        }
    }

    // compare column max lengths with header length
    for (int i = 0; i < size; i++) {
        int header_size = strlen(headers[i]);
        if (header_size > sizes[i]) {
            sizes[i] = header_size;
        }
    }

    // output header
    GPtrArray *header = g_ptr_array_new_full(2, free);

    // build header
    wchar_t *titles = malloc(BUFFER * sizeof(*header));
    swprintf(titles, BUFFER, L" %*s ", index_length, "");
    wchar_t title[BUFFER];
    for (int i = 0; i < size; i++) {
        swprintf(title, BUFFER, L"│ %-*s ", sizes[i], headers[i]);
        wcscat(titles, title);
    }
    wcscat(titles, L"\n");
    g_ptr_array_add(header, titles);

    // build separator line
    wchar_t *seperator = malloc(BUFFER * sizeof(*seperator));
    for (int i = 0; i < index_length + 2; i++) {
        seperator[i] = L'─';
    }
    int k = index_length + 2;
    for (int i = 0; i < size; i++) {
        seperator[k++] = L'┼';
        for (int j = 0; j < sizes[i] + 2; j++) {
            seperator[k++] = L'─';
        }
    }
    seperator[k++] = L'\n';
    seperator[k] = L'\0';
    g_ptr_array_add(header, seperator);

    // output lines
    GPtrArray *lines = g_ptr_array_new_full(entries->len + 2, free);

    // build formatted lines
    size_t wfield_sizes[size];
    for (int i = 0; i < size; i++) {
        wfield_sizes[i] = (sizes[i] + 4) * sizeof(wchar_t);
    }

    for (guint i = 0; i < entries->len; i++) {
        GPtrArray *entry = g_ptr_array_index(entries, i);
        wchar_t *line = malloc(BUFFER * sizeof(wchar_t));
        swprintf(line, BUFFER, L" %*d ", index_length, i + 1);
        for (guint j = 0; j < entry->len; j++) {
            char *field = g_ptr_array_index(entry, j);
            size_t field_size =
                wfield_sizes[j]; // ! está a fazer n_colunas acessos por linha
                                 // em vez de n_colunas acessos
            wchar_t *wfield = malloc(field_size);
            if (isdigit(*field))
                swprintf(wfield, field_size, L"│ %*s ", sizes[j], field);
            else
                swprintf(wfield, field_size, L"│ %-*s ", sizes[j], field);
            wcscat(line, wfield);
            free(wfield);
        }
        wcscat(line, L"\n");
        g_ptr_array_add(lines, line);
    }

    // create output struct
    Output output = output_new();

    output->lines = lines;
    output->header = header;

    return output;
}

guint output_lines_len(Output output)
{
    if (output == NULL || output->lines == NULL) {
        return 0;
    }

    return output->lines->len;
}

guint output_header_len(Output output)
{
    if (output == NULL || output->header == NULL) {
        return 0;
    }

    return output->header->len;
}

bool output_has_header(Output output)
{
    return output->header != NULL;
}

wchar_t *output_header_index(Output output, guint index)
{
    return wcsdup(g_ptr_array_index(output->header, index));
}

wchar_t *output_lines_index(Output output, guint index)
{
    return wcsdup(g_ptr_array_index(output->lines, index));
}

void output_free(Output output)
{
    if (output != NULL) {
        if (output->header != NULL) {
            g_ptr_array_free(output->header, TRUE);
        }
        if (output->lines != NULL) {
            g_ptr_array_free(output->lines, TRUE);
        }
        free(output);
    }
}
