#ifndef __LOADER_H__
#define __LOADER_H__

/**
 * @brief
 *
 * @param inputs_path
 * @param input_file
 * @param collection
 * @param load_record
 * @return void*
 */
void *load_file(const char *inputs_path, char *input_file, void *collection,
                void (*load_record)(void *, char *));

#endif
