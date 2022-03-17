/*  This file is part of SAIL (https://github.com/smoked-herring/sail)

    Copyright (c) 2020 Dmitry Baryshev

    The MIT License

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>

#include "sail-common.h"

sail_status_t sail_alloc_read_features(struct sail_read_features **read_features) {

    SAIL_CHECK_PTR(read_features);

    struct sail_read_features *read_features_local;

    void *ptr;
    SAIL_TRY(sail_malloc(sizeof(struct sail_read_features), &ptr));
    read_features_local = ptr;

    SAIL_TRY_OR_CLEANUP(sail_alloc_hash_set(&read_features_local->codec_features),
                        /* cleanup */ sail_destroy_read_features(read_features_local));

    *read_features = read_features_local;

    return SAIL_OK;
}

void sail_destroy_read_features(struct sail_read_features *read_features) {

    if (read_features == NULL) {
        return;
    }

    sail_destroy_hash_set(read_features->codec_features);
    sail_free(read_features);
}
