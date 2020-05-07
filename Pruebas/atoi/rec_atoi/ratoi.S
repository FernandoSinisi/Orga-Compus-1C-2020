#include <sys/regdef.h>

.text
.align 2

/* int ratoi(int acc, char* e) */
.globl ratoi
.ent ratoi

.set    noreorder
.cpload t9
.set reorder

ratoi:
    subu sp, sp, 40
    /* SRA */
    .cprestore 28 /* redundant */
    sw ra, 32(sp)
    sw gp, 28(sp)
    sw fp, 24(sp)

    move fp, sp
    
    /* Store arguments in caller ABA */
    sw a0, 40(fp)
    sw a1, 44(fp)

    /* *e == 0 ? */
    lw t0, 44(fp)
    lbu t0, 0(t0)
    bnez t0, L_else

    lw v0, 40(fp) /* ret acc */

    b L_RET

L_else:

    /* i = *e - '0' */
    lw t0, 44(fp)
    lbu t0, 0(t0) 
    li t1, '0'
    subu t1, t0, t1 
    sw t1, 16(fp) 
    
    /* acc * 10 */
    lw t0, 40(fp)
    li t1, 10
    mul t0, t0, t1

    /* ratoi (acc * 10 + i, e + 1) */
    lw t1, 16(fp)
    add a0, t0, t1  

    lw t0, 44(fp)
    addiu a1, t0, 1 

    jal ratoi

L_RET:
    /* Stack unwinding */
    lw fp, 24(sp)
    lw gp, 28(sp)
    lw ra, 32(sp)

    addiu sp, sp, 40
    jr ra

.end ratoi
