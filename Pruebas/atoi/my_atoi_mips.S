#include <sys/regdef.h>

/* Stack size */
#define SS 40 

/* SRA Offsets */
#define O_RA 32
#define O_GP 28 
#define O_FP 24

/* LTA Offsets */
#define LTA_SGN 20
#define LTA_S 16


.text
.align 2

/* 
int my_atoi(char* s) 
Set things up, then call an actual atoi implementation
*/

.globl my_atoi
.ent my_atoi

my_atoi:
    subu sp, sp, SS
    /* SRA */
    sw ra, O_RA(sp)
    sw gp, O_GP(sp)
    sw fp, O_FP(sp)

    move fp, sp

    sw a0, SS(fp)

    /* LTA */ 
    lw t0, SS(fp)
    sw t0, LTA_S(fp)

    /* Just default to 1 */
    li t0, 1
    sw t0, LTA_SGN(fp) 

    /* *s == '-' || *s == '+' */
    lw t0, LTA_S(fp)
    lbu t0, 0(t0)
    li t1, '-'
    beq t0, t1, L_SIGN

    lw t0, LTA_S(fp)
    lbu t0, 0(t0)
    li t1, '+'
    beq t0, t1, L_SIGN

    b L_ATOI_IMPL

L_SIGN:
    /* start_at */
    lw t0, SS(fp)
    addiu t0, t0, 1
    sw t0, LTA_S(fp)

    /* sign */
    lw t0, SS(fp)
    lbu t0, 0(t0)
    li t1, '+'
    beq t0, t1, L_PLUS

    /* It's '-' */
    li t0, -1
    sw t0, LTA_SGN(fp)
    b L_ATOI_IMPL
    
L_PLUS:
    /* It's '+', we're covered */
L_ATOI_IMPL:
#ifndef USE_REC_ATOI
    /* atoi_loop(s) */
    lw a0, LTA_S(fp)
    jal atoi_loop
#else /* USE_REC_ATOI */ 
    move a0, zero
    lw a1, LTA_S(fp)
    jal ratoi
#endif

    /*return  sign * atoi_impl(s) */
    lw t0, LTA_SGN(fp)
    mul v0, v0, t0

L_RET:
    /* Stack unwinding */
    lw fp, O_FP(sp)
    lw gp, O_GP(sp)
    lw ra, O_RA(sp)

    addiu sp, sp, SS
    jr ra
.end my_atoi
