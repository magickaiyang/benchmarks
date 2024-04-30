#include "SIM.h"

#include "../../include/magicops.h"
#include "../../jemalloc/jemalloc.h"

#include <sys/mman.h>

#include <cstring>

unsigned __attribute__ ((noinline)) SIM_BEGIN(bool i)
{
    if (i==false) return 0;
    start_sim();
    return 1;
}
unsigned __attribute__ ((noinline)) SIM_END(bool i)
{
    if (i==false) return 0;
    end_sim();
    return 1;
} 

void __attribute__ ((noinline)) SIM_LOCK(bool * i)
{
	return;
}

void __attribute__ ((noinline)) SIM_UNLOCK(bool * i)
{
	return;
}

unsigned int arena_ind = -1;
bool hp_inited = false;
size_t new_calls = 0;

static bool
my_hooks_purge(extent_hooks_t *extent_hooks, void *addr, size_t size, size_t offset, size_t length, unsigned arena_ind_curr) {
	madvise((void*)((size_t)addr + offset), length, MADV_DONTNEED);
	printf("purge: %p\n", addr);
	return false;
}
	
static bool
my_hooks_dealloc(extent_hooks_t *extent_hooks, void *addr, size_t size,
		bool committed, unsigned arena_ind_curr) {
	printf("dealloc: %p\n", addr);
	munmap(addr, size);
	return false;
}

static void
my_hooks_destroy(extent_hooks_t *extent_hooks, void *addr, size_t size,
		bool committed, unsigned arena_ind_curr) {
	printf("destroy: %p\n", addr);
	munmap(addr, size);
}

static void *
my_hooks_alloc(extent_hooks_t *extent_hooks, void *new_addr, size_t size,
		size_t alignment, bool *zero, bool *commit, unsigned arena_ind_curr)
{
	/*printf("In wrapper alloc_hook: new_addr:%p "
		"size:%lu(%lu pages) alignment:%lu "
		"zero:%s commit:%s arena_ind:%u\n",
		new_addr, size, size / 4096, alignment,
		(*zero) ? "true" : "false",
		(*commit) ? "true" : "false",
		arena_ind_curr);*/

	if (new_addr) {
		printf("new_addr is not NULL\n");
		exit(1);
	}

	void *area = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!area) {
		perror("mmap");
		exit(1);
	}

	*commit = true;

	//printf("hook returning range: %p\n", area);
	return area;
}

extent_hooks_t exthooks = {
	my_hooks_alloc,
	my_hooks_dealloc,
	my_hooks_destroy,
	NULL,
	NULL,
	my_hooks_purge,
	my_hooks_purge,
	NULL,
	NULL
};

void init_hp_arena() {
	extent_hooks_t *new_hooks = &exthooks;
	//printf("Setting up new hooks\n");
	size_t sz = sizeof(arena_ind);
	int ret = hpmallctl("arenas.create", (void *)&arena_ind, &sz, (void *)&new_hooks, sizeof(extent_hooks_t *));
	if (ret) {
		printf("mallctl error creating arena with new hooks");
		exit(1);
	}

	//printf("Created arena: %u\n", arena_ind);
}

void* malloc (size_t size) {
	if (!hp_inited) {
		init_hp_arena();
		hp_inited = true;
	}

	new_calls++;
	if (new_calls % 10000 == 0) {
//		hpmalloc_stats_print(NULL, NULL, NULL);
	}

	void *p = hpmallocx(size, MALLOCX_ARENA(arena_ind));
	return p;
}

void free(void *ptr) {
        hpfree(ptr);
}

