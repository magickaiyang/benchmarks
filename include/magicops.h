#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef unsigned long uint64_t;

enum {
   ZSIM_MAGIC_OP_START_SIM,        // Start simulation
   ZSIM_MAGIC_OP_PAUSE_SIM,        // Pause simulation after it has started
   ZSIM_MAGIC_OP_RESUME_SIM,       // Resume simulation
   ZSIM_MAGIC_OP_END_SIM,          // End simulation
   ZSIM_MAGIC_OP_START_MOVE,       // Start page move
   ZSIM_MAGIC_OP_END_MOVE,         // End page move
   ZSIM_MAGIC_OP_START_SHOOTDOWN,  // Start TLB shootdown
   ZSIM_MAGIC_OP_END_SHOOTDOWN,    // TLB shootdown ended
   ZSIM_MAGIC_OP_START_COPY,       // copying start
   ZSIM_MAGIC_OP_END_COPY,         // copying end
   ZSIM_MAGIC_OP_NETBUF_ADD,         // new networking buffer
   ZSIM_MAGIC_OP_NETBUF_DEL,         // remove networking buffer
};

typedef struct {
	int op;
	union {
		struct { // Used for ZSIM_MAGIC_OP_START_MOVE and END_MOVE
			uint64_t move_src_addr;
			uint64_t move_dest_addr;
		};
		struct { // net buf
			uint64_t buf_addr;
			uint64_t buf_size;
		};
	};
} zsim_magic_op_t;

// General-purpose magic op interface
static inline void zsim_magic_op(zsim_magic_op_t *op)
{
	// Write op pointer into R10
	__asm__ __volatile__("mov %0, %%r10\n\t"
				 : /* no output */
				 : "a"(op)
				 : "%r10");
	// XCHG R10, R10
	__asm__ __volatile__(".byte 0x4D, 0x87, 0xD2");
	return;
}

static inline void zsim_magic_op_start_sim(void)
{
	zsim_magic_op_t op;
	op.op = ZSIM_MAGIC_OP_START_SIM;
	zsim_magic_op(&op);
	return;
}

static inline void zsim_magic_op_end_sim(void)
{
	zsim_magic_op_t op;
	op.op = ZSIM_MAGIC_OP_END_SIM;
	zsim_magic_op(&op);
	return;
}

static inline void zsim_magic_op_start_move(uint64_t move_src_addr, uint64_t move_dest_addr)
{
	zsim_magic_op_t op;
	op.op = ZSIM_MAGIC_OP_START_MOVE;
	op.move_src_addr = move_src_addr;
	op.move_dest_addr = move_dest_addr;
	zsim_magic_op(&op);
	return;
}

static inline void zsim_magic_op_end_move(uint64_t move_src_addr, uint64_t move_dest_addr)
{
	zsim_magic_op_t op;
	op.op = ZSIM_MAGIC_OP_END_MOVE;
	op.move_src_addr = move_src_addr;
	op.move_dest_addr = move_dest_addr;
	zsim_magic_op(&op);
	return;
}

static inline void zsim_magic_op_netbuf_add(uint64_t addr, uint64_t size)
{
	zsim_magic_op_t op;
	op.op = ZSIM_MAGIC_OP_NETBUF_ADD;
	op.buf_addr = addr;
	op.buf_size = size;
	zsim_magic_op(&op);
	return;
}

static inline void zsim_magic_op_netbuf_del(uint64_t addr)
{
	zsim_magic_op_t op;
	op.op = ZSIM_MAGIC_OP_NETBUF_DEL;
	op.buf_addr = addr;
	op.buf_size = 0UL; // does not pass a size
	zsim_magic_op(&op);
	return;
}

static inline void zsim_magic_op_shootdown_start(void)
{
	zsim_magic_op_t op;
	op.op = ZSIM_MAGIC_OP_START_SHOOTDOWN;
	zsim_magic_op(&op);
	return;
}

static inline void zsim_magic_op_shootdown_end(void)
{
	zsim_magic_op_t op;
	op.op = ZSIM_MAGIC_OP_END_SHOOTDOWN;
	zsim_magic_op(&op);
	return;
}

static inline void zsim_magic_op_start_copy(void)
{
	zsim_magic_op_t op;
	op.op = ZSIM_MAGIC_OP_START_COPY;
	zsim_magic_op(&op);
	return;
}

static inline void zsim_magic_op_end_copy(void)
{
	zsim_magic_op_t op;
	op.op = ZSIM_MAGIC_OP_END_COPY;
	zsim_magic_op(&op);
	return;
}

static void start_sim_notify_os(void) {
	int fd, bytes_written;
	fd = open("/proc/self/sim_target", O_WRONLY);
	bytes_written = write(fd, "1", 1);
	close(fd);
	printf("%d bytes written\n", bytes_written);

	zsim_magic_op_start_sim();
	printf("start sim magic op issued\n");
}

static void end_sim(void) {
	zsim_magic_op_end_sim();
	printf("end sim magic op issued\n");
}
