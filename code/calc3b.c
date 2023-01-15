#include <stdio.h>
#include "calc3.h"
#include "y.tab.h"

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
        // printf("\tpush\t%c\n", p->id.i + 'a');
        break;
    case typeOpr:
        switch (p->opr.oper)
        {
        case WHILE:
            printf("L%03d:\n", lbl1 = lbl++);
            ex(p->opr.op[0]);
            printf("\tjz\tL%03d\n", lbl2 = lbl++);
            ex(p->opr.op[1]);
            printf("\tjmp\tL%03d\n", lbl1);
            printf("L%03d:\n", lbl2);
            break;
        case IF:
            ex(p->opr.op[0]);
            if (p->opr.nops > 2)
            {
                /* if else */
                printf("\tjz\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("\tjmp\tL%03d\n", lbl2 = lbl++);
                printf("L%03d:\n", lbl1);
                ex(p->opr.op[2]);
                printf("L%03d:\n", lbl2);
            }
            else
            {
                /* if */
                printf("\tjz\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("L%03d:\n", lbl1);
            }
            break;
        case PRINT:
            ex(p->opr.op[0]);
            index[0] = p->opr.op[0]->id.i;
            printf("\tlea r8, [rip+ARRAY]\n");
            if (index[0] != 0)
            {
                printf("\tadd r8, 8*%d\n", index[0]);
            }
            printf("\tpush rbp\n");
            printf("\tlea rdi, [rip+fmt_str]\n");
            printf("\tmov rsi, [r8]\n");
            printf("\txor rax, rax\n");
            printf("\tcall printf\n");
            printf("\tpop rbp\n");
            break;
        case '=':
            ex(p->opr.op[1]);
            index[0] = p->opr.op[0]->id.i;
            printf("\tpop\tr8\n");
            printf("\tlea r9, [rip+ARRAY]\n");
            if (index[0] != 0)
            {
                printf("\tadd r9, 8*%d\n", index[0]);
            }
            printf("\tmov [r9], r8\n");
            break;
        case UMINUS:
            ex(p->opr.op[0]);
            index[0] = p->opr.op[0]->id.i;
            printf("\tpop\tr8\n");
            printf("\tlea r9, [rip+ARRAY]\n");
            if (index[0] != 0)
            {
                printf("\tadd r9, 8*%d\n", index[0]);
            }
            printf("\tneg r8\n");
            printf("\tmov [r9], r8\n");
            printf("\tpush r8\n");
            break;
        case FACT:
            ex(p->opr.op[0]);
            printf("\tfact\n");
            break;
        case LNTWO:
            ex(p->opr.op[0]);
            printf("\\lntwo\n");
            break;
        default:
            ex(p->opr.op[0]);
            ex(p->opr.op[1]);
            index[0] = p->opr.op[0]->id.i;
            index[1] = p->opr.op[1]->id.i;
            switch (p->opr.oper)
            {
            case GCD:
                printf("\tgcd\n");
                break;
            case '+':
                if (p->opr.op[0]->type == typeCon)
                {
                    printf("\tpop rdi\n");
                }
                else
                {
                    printf("\tlea r9, [rip+ARRAY]\n");
                    if (index[0] != 0)
                    {
                        printf("\tadd r9, 8*%d\n", index[0]);
                    }
                    printf("\tmov rdi, [r9]\n");
                }
                if (p->opr.op[1]->type == typeCon)
                {
                    printf("\tpop rsi\n");
                }
                else
                {
                    printf("\tlea r9, [rip+ARRAY]\n");
                    if (index[1] != 0)
                    {
                        printf("\tadd r9, 8*%d\n", index[1]);
                    }
                    printf("\tmov rsi, [r9]\n");
                }
                printf("\tadd rdi, rsi\n");
                printf("\tpush rdi\n");
                break;
            case '-':
                printf("\tlea r9, [rip+ARRAY]\n");
                if (index[0] != 0)
                {
                    printf("\tadd r9, 8*%d\n", index[0]);
                }
                printf("\tmov rdi, [r9]\n");
                printf("\tlea r9, [rip+ARRAY]\n");
                if (index[1] != 0)
                {
                    printf("\tadd r9, 8*%d\n", index[1]);
                }
                printf("\tmov rsi, [r9]\n");
                printf("\tsub rdi, rsi\n");
                printf("\tpush rdi\n");
                break;
            case '*':
                printf("\tlea r9, [rip+ARRAY]\n");
                if (index[0] != 0)
                {
                    printf("\tadd r9, 8*%d\n", index[0]);
                }
                printf("\tmov rax, [r9]\n");
                printf("\tlea r9, [rip+ARRAY]\n");
                if (index[1] != 0)
                {
                    printf("\tadd r9, 8*%d\n", index[1]);
                }
                printf("\tmov rdi, [r9]\n");
                printf("\timul rdi\n");
                printf("\tpush rax\n");
                break;
            case '/':
                printf("\tlea r9, [rip+ARRAY]\n");
                if (index[0] != 0)
                {
                    printf("\tadd r9, 8*%d\n", index[0]);
                }
                printf("\tmov rax, [r9]\n");
                printf("\tlea r9, [rip+ARRAY]\n");
                if (index[1] != 0)
                {
                    printf("\tadd r9, 8*%d\n", index[1]);
                }
                printf("\tmov rdi, [r9]\n");
                printf("\tidiv rdi\n");
                printf("\tpush rax\n");
                break;
            case '<':
                printf("\tlea r9, [rip+ARRAY]\n");
                if (index[0] != 0)
                {
                    printf("\tadd r9, 8*%d\n", index[0]);
                }
                printf("\tmov rdi, [r9]\n");
                printf("\tlea r9, [rip+ARRAY]\n");
                if (index[1] != 0)
                {
                    printf("\tadd r9, 8*%d\n", index[1]);
                }
                printf("\tmov rsi, [r9]\n");

                printf("\tmov r9, 0\n");
                printf("\tmov r8, 1\n");
                printf("\tcmp rdi, rsi\n");
                printf("\tcmovl r9, r8\n");
                printf("\ttest r9, r9\n");

                break;
            case '>':
                printf("\tlea r9, [rip+ARRAY]\n");
                if (index[0] != 0)
                {
                    printf("\tadd r9, 8*%d\n", index[0]);
                }
                printf("\tmov rdi, [r9]\n");
                printf("\tlea r9, [rip+ARRAY]\n");
                if (index[1] != 0)
                {
                    printf("\tadd r9, 8*%d\n", index[1]);
                }
                printf("\tmov rsi, [r9]\n");

                printf("\tmov r9, 0\n");
                printf("\tmov r8, 1\n");
                printf("\tcmp rdi, rsi\n");
                printf("\tcmovg r9, r8\n");
                printf("\ttest r9, r9\n");

                break;
            case GE:
                printf("\tlea r9, [rip+ARRAY]\n");
                if (index[0] != 0)
                {
                    printf("\tadd r9, 8*%d\n", index[0]);
                }
                printf("\tmov rdi, [r9]\n");
                printf("\tlea r9, [rip+ARRAY]\n");
                if (index[1] != 0)
                {
                    printf("\tadd r9, 8*%d\n", index[1]);
                }
                printf("\tmov rsi, [r9]\n");

                printf("\tmov r9, 0\n");
                printf("\tmov r8, 1\n");
                printf("\tcmp rdi, rsi\n");
                printf("\tcmovge r9, r8\n");
                printf("\ttest r9, r9\n");
                break;
            case LE:
                printf("\tlea r9, [rip+ARRAY]\n");
                if (index[0] != 0)
                {
                    printf("\tadd r9, 8*%d\n", index[0]);
                }
                printf("\tmov rdi, [r9]\n");
                printf("\tlea r9, [rip+ARRAY]\n");
                if (index[1] != 0)
                {
                    printf("\tadd r9, 8*%d\n", index[1]);
                }
                printf("\tmov rsi, [r9]\n");

                printf("\tmov r9, 0\n");
                printf("\tmov r8, 1\n");
                printf("\tcmp rdi, rsi\n");
                printf("\tcmovle r9, r8\n");
                printf("\ttest r9, r9\n");
                break;
            case NE:
                printf("\tlea r9, [rip+ARRAY]\n");
                if (index[0] != 0)
                {
                    printf("\tadd r9, 8*%d\n", index[0]);
                }
                printf("\tmov rdi, [r9]\n");
                printf("\tlea r9, [rip+ARRAY]\n");
                if (index[1] != 0)
                {
                    printf("\tadd r9, 8*%d\n", index[1]);
                }
                printf("\tmov rsi, [r9]\n");

                printf("\tmov r8, 0\n");
                printf("\tmov r9, 1\n");
                printf("\ttest rdi, rsi\n");
                printf("\tcmovne r8, r9\n");
                printf("\txor r9, r8\n");

                break;
            case EQ:
                printf("\tlea r9, [rip+ARRAY]\n");
                if (index[0] != 0)
                {
                    printf("\tadd r9, 8*%d\n", index[0]);
                }
                printf("\tmov rdi, [r9]\n");
                printf("\tlea r9, [rip+ARRAY]\n");
                if (index[1] != 0)
                {
                    printf("\tadd r9, 8*%d\n", index[1]);
                }
                printf("\tmov rsi, [r9]\n");

                printf("\ttest rdi, rsi\n");
                break;
            }
        }
    }
    return 0;
}
