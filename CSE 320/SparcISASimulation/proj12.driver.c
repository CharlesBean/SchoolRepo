#include "/user/cse320/Projects/project12.support.h" //UNCOMMENT
#include <stdio.h>

int main(){
    unsigned nPC = 0x00010504;
    unsigned PC = 0x00010505;
    unsigned PSR = 0x00000003;

    unsigned CALL = 0x40000006;
    unsigned JMPL = 0x81C00000;
    unsigned LOAD = 0x80480000;
    unsigned BICC = 0x24B00001;
    unsigned JMPL2 = 0x81C7F5F2;

    unsigned STORE = 0xfe2A0f0f;
    unsigned BICC1 = 0x10911111;
    unsigned BICC2 = 0x38A01010;

    unsigned IR = BICC2;

    unsigned answer = update(nPC, PC, IR, PSR);

    printf("\n\tAnswer: %08x\n\n==========\n", answer);




    return 0;
}

