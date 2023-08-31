#include <stdio.h>
#include <stdbool.h>
#include "calc3.h"
#include "y.tab.h"

#include "factorial.h"
#include "gcd.h"
#include "lntwo.h"

static int lbl;

int ex(nodeType *p)
{
    int lbl1, lbl2;
    int index[2] = {0};

    if (!p)
        return 0;
    switch (p->type)
    {
    case typeCon:
        printf("\tpush\t%d\n", p->con.value);
        break;
    case typeId:
        printf("\tlea\tr9, [rip+%c]\n", p->id.i + 'a');
        printf("\tpush\t[r9]\n");
        break;
    case typeOpr:
        switch (p->opr.oper)
        {
        case WHILE:
            printf("L%03d:\n", lbl1 = lbl++);
            ex(p->opr.op[0]);
            printf("\tpop\trcx\n");
            printf("\ttest\trcx, rcx\n");
            printf("\tjz\tL%03d\n", lbl2 = lbl++);
            ex(p->opr.op[1]);
            printf("\tjmp\tL%03d\n", lbl1);
            printf("L%03d:\n", lbl2);
            break;
        case IF:
            ex(p->opr.op[0]);
            printf("\tpop\trcx\n");
            if (p->opr.nops > 2)
            {
                /* if else */
                printf("\tjrcxz\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("\tjmp\tL%03d\n", lbl2 = lbl++);
                printf("L%03d:\n", lbl1);
                ex(p->opr.op[2]);
                printf("L%03d:\n", lbl2);
            }
            else
            {
                /* if */
                printf("\tjrcxz\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("L%03d:\n", lbl1);
            }
            break;
        case PRINT:
            ex(p->opr.op[0]);
            printf("\tpop\trdi\n");
            printf("\tcall\tprint\n");
            break;
        case '=':
            ex(p->opr.op[1]);
            index[0] = p->opr.op[0]->id.i;
            printf("\tlea\tr9, [rip+%c]\n", index[0] + 'a');
            printf("\tpop\t[r9]\n");
            break;
        case UMINUS:
            ex(p->opr.op[0]);
            index[0] = p->opr.op[0]->id.i;
            printf("\tpop\trdi\n");
            printf("\tneg\trdi\n");
            printf("\tpush\trdi\n");
            break;
        case FACT:
            ex(p->opr.op[0]);
            printf("\tpop\trdi\n");
            printf("\txor\trax, rax\n");
            printf("\tcall\tfactorial\n");
            printf("\tpush\trax\n");
            break;
        case LNTWO:
            ex(p->opr.op[0]);
            printf("\tpop\trdi\n");
            printf("\txor\trax, rax\n");
            printf("\tcall\tlntwo\n");
            printf("\tpush\trax\n");
            break;
        default:
            ex(p->opr.op[0]);
            ex(p->opr.op[1]);
            switch (p->opr.oper)
            {
            case GCD:
                printf("\tpop\trdi\n");
                printf("\tpop\trsi\n");
                printf("\txor\trax, rax\n");
                printf("\tcall\tgcd\n");
                printf("\tpush\trax\n");
                break;
            case '+':
                printf("\tpop\trdi\n");
                printf("\tpop\trsi\n");
                printf("\tadd\trdi, rsi\n");
                printf("\tpush\trdi\n");
                break;
            case '-':
                printf("\tpop\trdi\n");
                printf("\tpop\trsi\n");
                printf("\tsub\trsi, rdi\n");
                printf("\tpush\trsi\n");
                break;
            case '*':
                printf("\tpop\trdi\n");
                printf("\tpop\trax\n");
                printf("\txor\trdx, rdx\n");
                printf("\timul\trdi\n");
                printf("\tpush\trax\n");
                break;
            case '/':
                printf("\tpop\trdi\n");
                printf("\tpop\trax\n");
                printf("\txor\trdx, rdx\n");
                printf("\tidiv\trdi\n");
                printf("\tpush\trax\n");
                break;
            case '<':
                printf("\tpop\trsi\n");
                printf("\tpop\trdi\n");
                printf("\txor\trcx, rcx\n");
                printf("\tcmp\trdi, rsi\n");
                printf("\tsetl\tcl\n");
                printf("\tpush\trcx\n");
                break;
            case '>':
                printf("\tpop\trsi\n");
                printf("\tpop\trdi\n");
                printf("\txor\trcx, rcx\n");
                printf("\tcmp\trdi, rsi\n");
                printf("\tsetg\tcl\n");
                printf("\tpush\trcx\n");
                break;
            case GE:
                printf("\tpop\trsi\n");
                printf("\tpop\trdi\n");
                printf("\txor\trcx, rcx\n");
                printf("\tcmp\trdi, rsi\n");
                printf("\tsetge\tcl\n");
                printf("\tpush\trcx\n");
                break;
            case LE:
                printf("\tpop\trsi\n");
                printf("\tpop\trdi\n");
                printf("\txor\trcx, rcx\n");
                printf("\tcmp\trdi, rsi\n");
                printf("\tsetle\tcl\n");
                printf("\tpush\trcx\n");
                break;
            case NE:
                printf("\tpop\trdi\n");
                printf("\tpop\trsi\n");
                printf("\txor\trcx, rcx\n");
                printf("\tcmp\trdi, rsi\n");
                printf("\tsetne\tcl\n");
                printf("\tpush\trcx\n");
                break;
            case EQ:
                printf("\tpop\trdi\n");
                printf("\tpop\trsi\n");
                printf("\txor\trcx, rcx\n");
                printf("\tcmp\trdi, rsi\n");
                printf("\tsete\tcl\n");
                printf("\tpush\trcx\n");
                break;
            }
        }
    }
    return 0;
}
