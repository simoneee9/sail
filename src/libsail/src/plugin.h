#ifndef SAIL_PLUGIN_H
#define SAIL_PLUGIN_H

#ifdef SAIL_BUILD
    #include "error.h"
    #include "export.h"
#else
    #include <sail/error.h>
    #include <sail/export.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct sail_plugin_info;

struct sail_read_features;
struct sail_read_options;
struct sail_write_features;
struct sail_write_options;
struct sail_file;
struct sail_image;

/* V1 declarations. */
typedef sail_error_t (*sail_plugin_read_features_v1_t)(struct sail_read_features **read_features);
typedef sail_error_t (*sail_plugin_read_init_v1_t)(struct sail_file *file, struct sail_read_options *read_options);
typedef sail_error_t (*sail_plugin_read_seek_next_frame_v1_t)(struct sail_file *file, struct sail_image **image);
typedef sail_error_t (*sail_plugin_read_seek_next_pass_v1_t)(struct sail_file *file, struct sail_image *image);
typedef sail_error_t (*sail_plugin_read_scan_line_v1_t)(struct sail_file *file, struct sail_image *image, void *scanline);
typedef sail_error_t (*sail_plugin_read_finish_v1_t)(struct sail_file *file, struct sail_image *image);

/* V2 declarations. */
typedef sail_error_t (*sail_plugin_read_scan_line_v2_t)(struct sail_file *file, struct sail_image *image, void **scanline);

struct sail_plugin_layout_v1 {
    sail_plugin_read_features_v1_t        sail_plugin_read_features_v1;
    sail_plugin_read_init_v1_t            sail_plugin_read_init_v1;
    sail_plugin_read_seek_next_frame_v1_t sail_plugin_read_seek_next_frame_v1;
    sail_plugin_read_seek_next_pass_v1_t  sail_plugin_read_seek_next_pass_v1;
    sail_plugin_read_scan_line_v1_t       sail_plugin_read_scan_line_v1;
    sail_plugin_read_finish_v1_t          sail_plugin_read_finish_v1;
};

struct sail_plugin_layout_v2 {
    sail_plugin_read_features_v1_t        sail_plugin_read_features_v1;
    sail_plugin_read_init_v1_t            sail_plugin_read_init_v1;
    sail_plugin_read_seek_next_frame_v1_t sail_plugin_read_seek_next_frame_v1;
    sail_plugin_read_seek_next_pass_v1_t  sail_plugin_read_seek_next_pass_v1;
    sail_plugin_read_scan_line_v1_t       sail_plugin_read_scan_line_v1;
    sail_plugin_read_finish_v1_t          sail_plugin_read_finish_v1;

    sail_plugin_read_scan_line_v2_t sail_plugin_read_scan_line_v2;
};

/*
 * SAIL plugin.
 */
struct sail_plugin {

    /* Layout version. */
    int layout;

    /* System-specific library handle. */
    void *handle;

    /* Plugin interface. */
    union {
        struct sail_plugin_layout_v1 *v1;
        struct sail_plugin_layout_v2 *v2;
    } interface;
};

typedef struct sail_plugin sail_plugin_t;

/*
 * Loads the specified plugin by its info and saves its handle and exported interfaces into the specified plugin
 * instance. The assigned plugin MUST be destroyed later with sail_destroy_plugin().
 *
 * Returns 0 on success or sail_error_t on error.
 */
SAIL_EXPORT sail_error_t sail_alloc_plugin(struct sail_plugin_info *plugin_info, struct sail_plugin **plugin);

/*
 * Destroys the specified plugin and all its internal memory buffers.
 * The plugin MUST NOT be used anymore after calling this function.
 */
SAIL_EXPORT void sail_destroy_plugin(struct sail_plugin *plugin);

/* extern "C" */
#ifdef __cplusplus
}
#endif

#endif
