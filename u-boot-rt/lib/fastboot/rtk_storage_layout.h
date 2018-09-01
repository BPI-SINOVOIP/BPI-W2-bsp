
#pragma once

int write_to_storage(const char *arg, uint64_t file_size, uint64_t offset,
	    void *data, unsigned sz);

size_t dump_fw_layout(char *buf, size_t buf_sz);

size_t dump_part_info(char *buf, size_t buf_sz);
size_t dump_fw_info(char *buf, size_t buf_sz);

