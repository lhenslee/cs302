#include <iostream>
using namespace std;

struct LIST {
    struct LIST *pNext;
    int iValue;
};

struct LIST * insertion_sort(struct LIST * pList) {
    // zero or one element in list
    if(!pList || !pList->pNext)
        return pList;

    /* build up the sorted array from the empty list */
    struct LIST * pSorted = NULL;

    /* take items off the input list one by one until empty */
    while (pList != NULL) {
        /* remember the head */
        struct LIST *   pHead  = pList;
        /* trailing pointer for efficient splice */
        struct LIST ** ppTrail = &pSorted;
        
        /* pop head off list */
        pList = pList->pNext;
    
        /* splice head into sorted list at proper place */
        while (!(*ppTrail == NULL || pHead->iValue < (*ppTrail)->iValue)) /* does head belong here? */
            /* no - continue down the list */
            ppTrail = &(*ppTrail)->pNext;

        pHead->pNext = *ppTrail;
        *ppTrail = pHead;

    }
    return pSorted;
} 

int main() {
    struct LIST lis;
    lis.iValue = 3;
    struct LIST *p = new LIST;
    lis.pNext = p;
    p->iValue = 4;
    struct LIST *q = new LIST;
    p->pNext = q;
    q->iValue = 8;
    p = new LIST;
    q->pNext = p;
    p->iValue = 6;
    p->pNext = NULL;
    struct LIST *sorted = insertion_sort(&lis);
    struct LIST *f = sorted;
    while (f!=NULL) {
        cout << f->iValue << '\n';
        f=f->pNext;
    }
}
