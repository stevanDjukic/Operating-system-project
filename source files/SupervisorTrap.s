.extern _ZN5Riscv20handleSupervisortrapEv

.align 4
.global _ZN5Riscv14superVisortrapEv
.type _ZN5Riscv14superVisortrapEv, @function
_ZN5Riscv14superVisortrapEv:
    addi sp, sp, -256
    .irp index, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    sd x\index, \index * 8(sp)
    .endr

    mv fp, sp

    call _ZN5Riscv20handleSupervisortrapEv

    .irp index, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    ld x\index, \index * 8(sp)
    .endr
    addi sp, sp, 256

    sret