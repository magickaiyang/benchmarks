#include "SIM.h"

#include "../../include/magicops.h"

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

