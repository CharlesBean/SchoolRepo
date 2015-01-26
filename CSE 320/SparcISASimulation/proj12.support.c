//Charles Bean
//CSE 320

#include <stdbool.h>

//unsigned update (unsigned nPC, unsigned PC, unsigned IR, unsigned PSR); //REMOVE
bool inArray(int val, int *array, int size);
unsigned newReg(unsigned rs1, unsigned rs2, unsigned i, unsigned simm13);


unsigned update (unsigned nPC, unsigned PC, unsigned IR, unsigned PSR){

/*****************************************************/

    //IR
    printf("==========\n\n\tPassed IR: %08x\n", IR);
    printf("\tPassed nPC: %08x\n", nPC);
    printf("\tPassed PC: %08x\n", PC);
    printf("\tPassed PSR: %08x\n\n", PSR);

    //NZVC (negative, zero, overflow, carry)
    unsigned nzvc = (PSR << 9) >> 28;
    nzvc = 0x00000008;

    //CALL
    unsigned op = (IR >> 30);

    //JMPL
    unsigned op3 = ((IR << 7) >> 26);
    unsigned rs1 = ((IR << 14) >> 27);
    unsigned i = ((IR << 18) >> 31);
    unsigned rs2 = ((IR << 27) >> 27);
    unsigned simm13 = ((IR << 20) >> 20);
    unsigned simmsign = simm13 >> 12;
    unsigned simext;

    //BICC
    unsigned cond = ((IR << 3) >> 28);
    unsigned annul = ((IR << 2) >> 31); //should equal 0 or 1
    unsigned post3 = ((IR << 7) >> 29); //should equal 010 (hex: 0002)
    unsigned disp22 = ((IR << 10) >> 10);
    unsigned d22sign = (disp22 >> 21);
    unsigned ext1 = 0xFFC00000;
    unsigned ext0 = 0x00000000;
    unsigned dext;

    //Sign Extension of d22
    if (d22sign == 0x00000001){
        dext = disp22|ext1;
    }
    else{
        dext = disp22|ext0;
    }

    //Sign Extension of simm13
    if (simmsign == 0x00000001){
        simext = simm13|ext1;
    }
    else{
        simext = simm13|ext0;
    }

    //NZVC checks (hexadecimals that will turn these on)
    const N[] = {0x00000008, 0x00000009, 0x0000000A, 0x0000000B, 0x0000000C, 0x0000000D, 0x0000000E, 0x0000000F};
    const Z[] = {0x00000004, 0x00000005, 0x00000006, 0x00000007, 0x0000000C, 0x0000000D, 0x0000000E, 0x0000000F};
    const V[] = {0x00000002, 0x00000003, 0x00000006, 0x00000007, 0x0000000A, 0x0000000B, 0x0000000E, 0x0000000F};
    const C[] = {0x00000001, 0x00000003, 0x00000005, 0x00000007, 0x00000009, 0x0000000B, 0x0000000D, 0x0000000F};

    //Booleans for NZVC
    bool isNegative = inArray(nzvc, &N, 7);
    bool isZero = inArray(nzvc, &Z, 7);
    bool isOverflow = inArray(nzvc, &V, 7);
    bool isCarry = inArray(nzvc, &C, 7);

    //Prints
    printf("\tNZVC: %08x\n", nzvc);
    printf("\top: %08x\n", op);
    printf("\trs1: %08x\n", rs1);
    printf("\trs2: %08x\n", rs2);
    printf("\ti: %08x\n", i);
    printf("\tsimm13: %08x\n", simm13);
    printf("\top3: %08x\n", op3);
    printf("\tcond: %08x\n", cond);
    printf("\tpost3: %08x\n", post3);
    printf("\tannul: %08x\n", annul);
    printf("\tdisp22: %08x\n", disp22);
    printf("\tdisp22 sign: %08x\n", d22sign);
    printf("\tdisp22 extension: %08x\n", dext);
    printf("\n\t*PROCESSING AS*\n");



/*****************************************************/

    //PROCESS

    //CALL
    if (op == 0x00000001){ //CALL
        printf("\t\tCALL - IR: %08x\n", IR);
        unsigned nPC = PC + ((IR << 2) * 4);
        return nPC;
    }


    //JMPL
    if ((op3 == 0x00000038) && (op == 0x00000002)){ //JMPL
        printf("\t\tJMPL - IR: %08x\n", IR);
        unsigned outReg = newReg(rs1, rs2, i, simext);
        return outReg;
    }


    //BICC
    if ((post3 == 0x00000002) && (op == 0x00000000) && (annul == 0x00000000 || 0x00000001)){ //BICC
        printf("\t\tBICC - IR: %08x\n", IR);
        if ((cond == 0x00000008) && (annul == 0x00000000)){ //BA
            printf("\t\tBA\n");
            nPC = PC + (4 * dext);
            return nPC;
        }
        if (cond == 0x00000000){ //BN
            printf("\t\tBN\n");
            nPC = PC + 4;
            return nPC;
        }
        if (cond == 0x00000009){ //BNE
            if (isZero == false){
                printf("\t\tBNE\n");
                nPC = PC + (4 * dext);
                return nPC;
            }
            else{
                nPC = nPC + 4;
                return nPC;
            }
        }
        if (cond == 0x00000001){ //BE
            printf("\t\tBE\n");
            if (isZero == true){
                printf("MADE IT\n");
                nPC = PC + (4 * dext);
                return nPC;
            }
            else{
                nPC = nPC + 4;
                return nPC;
            }
        }
        if (cond == 0x0000000A){ //BG
            if (!((isNegative && !isOverflow) || (isOverflow && !isNegative) || (isZero))){
                printf("\t\tBG\n");
                nPC = PC + (4 * dext);
                return nPC;
            }
            else{
                nPC = nPC + 4;
                return nPC;
            }
        }
        if (cond == 0x00000002){ //BLE
            if (((isNegative && !isOverflow) || (isOverflow && !isNegative) || (isZero))){
                printf("\t\tBLE\n");
                nPC = PC + (4 * dext);
                return nPC;
            }
            else{
                nPC = nPC + 4;
                return nPC;
            }
        }
        if (cond == 0x0000000B){ //BGE
            if (!((isNegative && !isOverflow) || (isOverflow && !isNegative))){
                printf("\t\tBGE\n");
                nPC = PC + (4 * dext);
                return nPC;
            }
            else{
                nPC = nPC + 4;
                return nPC;
            }
        }
        if (cond == 0x00000003){ //BL
            if ((isNegative && !isOverflow) || (isOverflow && !isNegative)){
                printf("\t\tBL\n");
                nPC = PC + (4 * dext);
                return nPC;
            }
            else{
                nPC = nPC + 4;
                return nPC;
            }
        }
        if (cond == 0x0000000C){ //BGU
            if (!(isCarry || isZero)){
                printf("\t\tBGU\n");
                nPC = PC + (4 * dext);
                return nPC;
            }
            else{
                nPC = nPC + 4;
                return nPC;
            }
        }
        if (cond == 0x00000004){ //BLEU
            if (isCarry || isZero){
                printf("\t\tBLEU\n");
                nPC = PC + (4 * dext);
                return nPC;
            }
            else{
                nPC = nPC + 4;
                return nPC;
            }
        }
        if (cond == 0x0000000D){ //No Carry
            if (!isCarry){
                printf("\t\tBCC\n");
                nPC = PC + (4 * dext);
                return nPC;
            }
            else{
                nPC = nPC + 4;
                return nPC;
            }
        }
        if (cond == 0x00000005){ //Carry
            if (isCarry){
                printf("\t\tBCS\n");
                nPC = PC + (4 * dext);
                return nPC;
            }
            else{
                nPC = nPC + 4;
                return nPC;
            }
        }
        if (cond == 0x0000000E){ //Positive
            if (!isNegative){
                printf("\t\tBPOS\n");
                nPC = PC + (4 * dext);
                return nPC;
            }
            else{
                nPC = nPC + 4;
                return nPC;
            }
        }
        if (cond == 0x00000006){ //Negative
            if (isNegative){
                printf("\t\tBNEG\n");
                nPC = PC + (4 * dext);
                return nPC;
            }
            else{
                nPC = nPC + 4;
                return nPC;
            }
        }
        if (cond == 0x0000000F){ //No Overflow
            if (!isOverflow){
                printf("\t\tBVC\n");
                nPC = PC + (4 * dext);
                return nPC;
            }
            else{
                nPC = nPC + 4;
                return nPC;
            }
        }
        if (cond == 0x00000007){ //Overflow
            if (isOverflow){
                printf("\t\tBVS\n");
                nPC = PC + (4 * dext);
                return nPC;
            }
            else{
                nPC = nPC + 4;
                return nPC;
            }
        }
    }

    else{
        printf("\t\tOther (Load, Sethi, etc.) - IR: %08x\n", IR);
        nPC = nPC + 4;
        return nPC;
    }

/*****************************************************/

}

bool inArray(int val, int *array, int size){
    int i;
    for (i=0; i < size; i++) {
        if (array[i] == val)
            return true;
    }
    return false;
}

unsigned newReg(unsigned rs1, unsigned rs2, unsigned i, unsigned simext){
    unsigned r1, r2, rtn;

    r1 = ((rs1 << 24) | (rs1 << 16) | (rs1 << 8) | rs1);
    r2 = ((rs2 << 24) | (rs2 << 16) | (rs2 << 8) | rs2);

    if (i == 0x00000000){
        rtn = r1 + r2;
    }
    else{
        rtn = r1 + simext;
    }

    printf("\t\t\tR1: %08x", r1);
    printf("\t\t\tR2: %08x\n", r2);
    return rtn;
}
