#include <stdio.h>
#include <setjmp.h>

static jmp_buf jmp1, jmp2;

static void function() {
    if (setjmp(jmp2) == 0) {
        printf("Second setjmp called\n");
    } else {
        printf("Jumped back to second setjmp\n");
        return;
    }

    // 跳转回第一次 setjmp
    longjmp(jmp1, 1);
}

//先跳到jmp1, 再跳到jmp2会报错, 因为堆栈已经在第一次跳转时没有第二次设置跳转点的堆栈环境
static void j1j2() {
    if (setjmp(jmp1) == 0) {
        printf("First setjmp called\n");
        function();
    } else {
        printf("Jumped back to first setjmp\n");
    }
    longjmp(jmp2, 1);
}

//先跳转到jmp2, 再跳转到jmp1就没有问题
static void j2j1() {
if (setjmp(jmp1) == 0) {
        printf("First setjmp called\n");
        function();
    } else {
        longjmp(jmp2, 1);
        printf("Jumped back to first setjmp\n");
    }
}

int main() {
    j2j1();

    return 0;
}