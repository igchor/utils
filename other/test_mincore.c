#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

/*
 * count_resident_pages -- count resident_pages
 */
static size_t
count_resident_pages(void *pool, size_t length)
{
	size_t pagesize = sysconf(_SC_PAGESIZE);
	size_t arr_len = (length + pagesize - 1) / pagesize;
	unsigned char *vec = malloc(sizeof(*vec) * arr_len);

	int ret = mincore(pool, length, vec);
	assert(ret == 0);

	size_t resident_pages = 0;
	for (size_t i = 0; i < arr_len; ++i)
		resident_pages += vec[i] & 0x1;

	free(vec);

	return resident_pages;
}

int main(int argc, char *argv[])
{
	if (argc < 3) {
		printf("usage: ./a.out filename size");
		return 1;
	}

	char* path = argv[1];
	int size = atoi(argv[2]);

	int fd = open(path, O_RDWR | O_CREAT, 0777);

	int ret = posix_fallocate(fd, 0, size);
	if (ret != 0) {
		printf("fallocate failed\n");
		close(fd);
		return 1;
	}

	void* pool = mmap(NULL, size, PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (pool == MAP_FAILED) {
		printf("mmap failed\n");
		close(fd);
		return 1;
	}

	printf("mincore: %d\n", count_resident_pages(pool, size));

	close(fd);

	return 0;
}
