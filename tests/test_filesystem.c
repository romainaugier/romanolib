  /* SPDX-License-Identifier: BSD-3-Clause */
/* Copyright (c) 2023 - Present Romain Augier */
/* All rights reserved. */

#include "libromano/filesystem.h"
#include "libromano/logger.h"

int main(void)
{
    logger_init();

    logger_log(LogLevel_Info, "Verifying the existence of this file : "__FILE__);
    int exists;

    exists = fs_path_exists(__FILE__);

    logger_log(LogLevel_Info, "File \""__FILE__"\" exists : %d", exists);

    char dir_path[MAX_PATH];
    fs_parent_dir(__FILE__, dir_path);

    logger_log(LogLevel_Info, "Directory of "__FILE__" is %s", dir_path);

    logger_log(LogLevel_Info, "Starting filesystem walk");

    char walk_dir_path[MAX_PATH];
    fs_parent_dir(dir_path, walk_dir_path);

    fs_walk_item_t walk_item;

    while(fs_walk(walk_dir_path, &walk_item, 0) != 0)
    {
        logger_log(LogLevel_Info, "%s", walk_item.path);
    }

    logger_log(LogLevel_Info, "Finished filesystem walk");

    logger_release();

    return 0;
}

