/*
 * Progarm Name: ctest.c
 * Created Time: 2016-05-14 19:56:38
 * Last modified: 2016-12-05 21:49:21
 * @author: minphone.linails linails@foxmail.com 
 */

#include "ctest.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*ctest*/
void ctest(void)
{
    printf("--------------------------- ctest ---------------------------\n");
    {
        int test01(void);
        printf("test01 return : %d\n",test01());
    }
    printf("--------------------------- ----- ---------------------------\n");
    {
        void cout_tdv_tde(void);
        cout_tdv_tde();
    }
    printf("--------------------------- ----- ---------------------------\n");
    {
        int *p = (int *)malloc(100);
        unsigned addr[100];

        for(int i=0; i<100; i++){
            printf("&p[i] : %#x\n", &p[i]);
            addr[i] = &p[i];
        }

        p = realloc(p, 1000);
        for(int i=0; i<100; i++){
            printf("&p[i] : %#x - orig : %#x\n", &p[i], addr[i]);
        }

        free(p);
    }
    printf("--------------------------- ----- ---------------------------\n");
    {
        Test_t td = {
            .a = 10,
            .b = 20,
            .c = 30
        };

        printf("td.a = %d\n", td.a);
        printf("td.b = %d\n", td.b);
        printf("td.c = %d\n", td.c);
    }
    printf("--------------------------- ----- ---------------------------\n");
    {
        char *sp = "line 1\n"
                   "line 2\n"
                   "line 3\n";

        printf("string sp = %s", sp);
    }
}

int test01(void)
{
    printf("sizeof(int) : %d - 0x%x\n",sizeof(int),sizeof(int));
    printf("1 - sizeof(int) : %d - 0x%x\n",1 - sizeof(int),1 - sizeof(int));
    printf("(1 - sizeof(int)) >> 32 : %d - 0x%x\n",(1 - sizeof(int)) >> 32,(1 - sizeof(int)) >> 32);
    return ((1 - sizeof(int)) >> 32);
}

typedef struct {
    double posx;
    double posy;
    double posz;
    int    nwk;
    int    mac[8];
    int    nodetype;    /* [0:'C', 1:'R', 2:'E'] */
}TestDataVes_t;

typedef struct {
    double sposx;
    double sposy;
    double sposz;
    double eposx;
    double eposy;
    double eposz;
}TestDataEdg_t;

static TestDataVes_t tdv[] = {
    {0, 0, 0,      0x0000, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07}, 0},
    {0.7, 2.2, 1,  0x0001, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x08}, 1},
    {0, 1.8, 3,    0x0002, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x09}, 1},
    {1.6, 2.3, -1, 0x0003, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0a}, 2},
    {2, 0.8, 3,    0x0004, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0b}, 2},
    {-0.6, -0.6, 2,0x0005, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0c}, 2},
    {-1.3, 0.8, 2, 0x0006, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0d}, 1},
    {-1.5, -1, 0.3,0x0007, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0e}, 2},
    {0.5, -1.5, 2, 0x0008, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0f}, 1},
    {1.7, -0.8, 1, 0x0009, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x10}, 2},
    {1.5, -2.3, 0, 0x000a, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x11}, 2}
};

/* 此种定义在 C 中非法 */
static TestDataEdg_t tde[] = {
#if 0
    {tdv[0].posx, tdv[0].posy, tdv[0].posz, tdv[1].posx, tdv[1].posy, tdv[1].posz},
    {tdv[0].posx, tdv[0].posy, tdv[0].posz, tdv[2].posx, tdv[2].posy, tdv[2].posz},
    {tdv[0].posx, tdv[0].posy, tdv[0].posz, tdv[3].posx, tdv[3].posy, tdv[3].posz},
    {tdv[1].posx, tdv[1].posy, tdv[1].posz, tdv[4].posx, tdv[4].posy, tdv[4].posz},
    {tdv[1].posx, tdv[1].posy, tdv[1].posz, tdv[5].posx, tdv[5].posy, tdv[5].posz},
    {tdv[2].posx, tdv[2].posy, tdv[2].posz, tdv[6].posx, tdv[6].posy, tdv[6].posz},
    {tdv[2].posx, tdv[2].posy, tdv[2].posz, tdv[7].posx, tdv[7].posy, tdv[7].posz},
    {tdv[6].posx, tdv[6].posy, tdv[6].posz, tdv[8].posx, tdv[8].posy, tdv[8].posz},
    {tdv[8].posx, tdv[8].posy, tdv[8].posz, tdv[9].posx, tdv[9].posy, tdv[9].posz},
    {tdv[8].posx, tdv[8].posy, tdv[8].posz, tdv[10].posx, tdv[10].posy, tdv[10].posz}
#endif
};

void cout_tdv_tde(void)
{
    printf("tdv\n");
    printf("tde\n");

    printf("tdv List :\n");
    for(int i=0; i<(int)(sizeof(tdv)/sizeof(TestDataVes_t)); i++){
        printf("(%.2f, %.2f, %.2f) - 0x%.4x - ", tdv[i].posx, tdv[i].posy, tdv[i].posz, tdv[i].nwk);
        printf("0x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x - ", 
                tdv[i].mac[0], 
                tdv[i].mac[1], 
                tdv[i].mac[2], 
                tdv[i].mac[3], 
                tdv[i].mac[4], 
                tdv[i].mac[5], 
                tdv[i].mac[6], 
                tdv[i].mac[7]
                );
        if(tdv[i].nodetype == 0) printf("'C'\n");
        else if(tdv[i].nodetype == 1) printf("'R'\n");
        else printf("'E'\n");
    }

    printf("\n");

#if 0
    printf("tde List :\n");
    for(int i=0; i<(int)(sizeof(tde)/sizeof(TestDataEdg_t)); i++){
        printf("((%.2f, %.2f, %.2f) -> (%.2f, %.2f, %.2f))\n", 
                tde[i].sposx,
                tde[i].sposy,
                tde[i].sposz,
                tde[i].eposx,
                tde[i].eposy,
                tde[i].eposz
                );
    }
#endif
}


