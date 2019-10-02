#ifndef SCK_UTILS_H
#define SCK_UTILS_H

#include <sck_core.h>

struct sck_util_table_elem_s {
    char *index;
    char *value;
};

static sck_util_table_elem_t sck_file_type_assoc[] = {
    //  File extension      Media-type

        // text/
        {"txt",             "text/plain"                    },  // This is default, if not matching MIME-type is found.
        {"css",             "text/css"                      },
        {"csv",             "text/csv"                      },
        {"htm",             "text/html"                     },
        {"html",            "text/html"                     },
        {"ics",             "text/calender"                 },
        {"js",              "text/javascript"               },
        {"mjs",             "text/javascript"               },

        // application/
        {"json",            "application/json"              },
        {"pdf",             "application/pdf"               },
        {"xml",             "application/xml"               },
        {"ps",              "application/postscript"        },
        {"ogx",             "application/ogg"               },
        {"php",             "application/php"               },
        {"rar",             "application/x-rar-compressed"  },
        {"tar",             "application/x-tar"             },
        {"rtf",             "application/rtf"               },
        {"zip",             "application/zip"               },
        {"xhtml",           "application/xhtml+xml"         },

        // audio/
        {"aac",             "audio/aac"                     },
        {"mp3",             "audio/mpeg"                    },
        {"oga",             "audio/ogg"                     },
        {"wav",             "audio/wav"                     },
        {"weba",            "audio/webm"                    },

        // video/
        {"avi",             "video/x-msvideo"               },
        {"ogv",             "video/ogg"                     },
        {"mpeg",            "video/mpeg"                    },
        {"webm",            "video/webm"                    },

        // image/
        {"bmp",             "image/bmp"                     },
        {"gif",             "image/gif"                     },
        {"jpg",             "image/jpeg"                    },
        {"jpeg",            "image/jpeg"                    },
        {"png",             "image/png"                     },
        {"webp",            "image/webp"                    },
};

#define SIZE(x)    (sizeof(x)/sizeof(x[0]))

#define SCK_FILE_REG    (uint8_t) 0  // Regular file
#define SCK_FILE_DIR    (uint8_t) 1  // Directory
#define SCK_FILE_CHR    (uint8_t) 2  // Character device
#define SCK_FILE_BLK    (uint8_t) 3  // Block device
#define SCK_FILE_FIFO   (uint8_t) 4  // FIFO
#define SCK_FILE_LNK    (uint8_t) 5  // Symbolic link
#define SCK_FILE_IDK    (uint8_t) 6  // ¯\_(ツ)_/¯

/*
 * Gets the length of an integer.
 * Fx. the length of 1932 is 4, as there are four digits.
 * 
 * Returns: Amount of digits in 'x'
 */
int     sck_util_length_of_int(int);

/*
 * Retrieve substring from 'beginning' to 'end' of 'string'
 * Both 'beginning' and 'end' are zero-indexed.
 * 'end' can be set as -1, to get the substring from 'beginning' to the end of the string.
 * 
 * Returns: The substring retrieved.
 */
char   *sck_util_substring(char *, int, int);

/*
 * Get the amount of occurences of 'chars' in 'string'
 * Much like strpbrk (string.h), but retrieves the amount, instead of the char-pointer.
 * 
 * Returns: The amount of character occurences.
 */
int     sck_util_char_amount(char *, char *);

/*
 * Trim the ends of 'string' from newlines and spaces.
 * Much like the trim() function from Python 2.7+.
 * 
 * Returns: The trimmed string.
 */
char   *sck_util_trim(char *);

/*
 * Join two paths, so that a valid path is created.
 * This function, however, does now check the presence of the resulting path.
 * 
 * Returns: The joined path.
 */
char   *sck_util_path_join(char *, char *);

/*
 * Check whether a directory/file/etc. exists in the filesystem.
 * The result can also be false, if we don't have reading permissions on the specified file.
 * 
 * Returns: 1 on true/success, 0 otherwise.
 */
uint8_t sck_util_file_exists(char *);

/*
 * Check whether the specified path is a file, directory, character block, block device, FIFO/pipe or socket.
 * 
 * [0] SCK_FILE_REG:  regular file
 * [1] SCK_FILE_DIR:  directory
 * [2] SCK_FILE_CHR:  character block
 * [3] SCK_FILE_BLK:  block device
 * [4] SCK_FILE_FIFO: FIFO-file/pipe
 * [5] SCK_FILE_LNK:  symbolic/hard link
 * [6] SCK_FILE_IDK:  No idea.
 * 
 * Returns: Numerical value, representing the result. See above.
 */
uint8_t sck_util_is_file(char *);

/*
 * Lists the specified directory, and parses the result into the passed sck_vector_t.
 * 
 * Returns: SCK_OK (0) on success, negative value otherwise.
 * See sck_log.h for error codes.
 * 
 * REMARK: The vector does not get allocated, so do this yourself.
 */
int     sck_util_list_directory(char *, sck_vector_t *);

/*
 * Checks for possible file extension.
 * 
 * Returns: file-extension of 'file.' If none is found, the returned value is empty.
 * 
 * REMARK: This function does not check wether the file exists or not.
 * TODO: Handle invalid characters after '.' (such as backslash, pound-signs, etc.)
 */
char   *sck_util_get_file_extension(char *);

/*
 * Gets the default media-type (MIME-type). This is usually 'text/plain'.
 * 
 * Returns: The first file-association defined (in sck_utils.h).
 */
char   *sck_util_default_content_type();

/*
 * Gets the first matching media-type (MIME-type) for 'extension'
 * 
 * Returns: Matching Media-Type for the specified extension.
 *          If no match is found, the first file-association (in sck_utils.h)
 *          is returned.
 */
char   *sck_util_get_content_type(char *);

#endif /* SCK_UTILS_H */