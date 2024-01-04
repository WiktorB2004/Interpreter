#pragma once

/*!
 * \brief Retrieves the source code from a file.
 *
 * This function reads the contents of the specified file and returns
 * a dynamically allocated buffer containing the source code.
 *
 * @param filename The name of the file from which to retrieve the source code.
 *                 It should be a null-terminated string.
 * @return A pointer to a dynamically allocated buffer containing the source code.
 *         The caller is responsible for freeing the memory when no longer needed.
 *         If the file cannot be read or an error occurs, NULL is returned.
 */
char *get_source_code(const char *filename);