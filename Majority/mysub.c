#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
struct node
{
    int cnt; //How many quad are represented by this object;
    int begin;
    struct node* parent;
    struct node* next;
};

void identifyIndex(int n, int s, int* X, int* X1, int* Y, int* NumOfX, int* NumOfY, int* used){
    int res1;
    int res2;
    
    //Initial Query - not recursive
    if(s == 0){
        int arr1[4] = {1,2,3,4};
        int arr2[4] = {2,3,4,5};
        res1 = QCOUNT(1, arr1);
        res2 = QCOUNT(1, arr2);
    }
    //Not initial check - recursive
    else{
        int arr[4] = {s+2, s+3, s+4, s+5};
        res1 = 4;
        res2 = QCOUNT(1, arr);
    }
    //00111 or 11000
    if(res1 == 0 && res2 == 2){
        *X = 5;
        *Y = 1;
        //find x2
        int param[3][2] = {{2,3}, {2,4}, {3,4}};
        int i;
        for( i = 0; i < 3; i++){
            int a = param[i][0];
            int b = param[i][1];
            int temp[4] = {*X, a, b, *Y};
            int res = QCOUNT(1,temp);
            if(res == 2){
                //set x2
                *X1 = a;
                break;
            }
        }
        *NumOfX = 3;
        *NumOfY = 2;
        *used = 5;
    }
    //11100 or 00011
    else if(res1 == 2 && res2 == 0){
        *X = 1;
        *Y = 5;
        //find x2
        int param[3][2] = {{2,3}, {2,4}, {3,4}};
        int i;
        for( i = 0; i < 3; i++){
            int a = param[i][0];
            int b = param[i][1];
            int temp[4] = {*X, a, b, *Y};
            int res = QCOUNT(1,temp);
            if(res == 2){
                //set x2
                *X1 = a;
                break;
            }
        }
        *NumOfX = 3;
        *NumOfY = 2;
        *used = 5;
    }
    //11001 or 00110
    else if(res1 == 0 && res2 == 0){
        *X = 1;
        *X1 = 5;
        //find y
        int param[3][2] = {{2,3}, {2,4}, {3,4}};
        int i;
        for( i = 0; i < 3; i++){
            int a = param[i][0];
            int b = param[i][1];
            int temp[4] = {*X, a, b, *X1};
            int res = QCOUNT(1,temp);
            if(res == 0){
                //set y
                *Y = a;
                break;
            }
        }
        *NumOfX = 3;
        *NumOfY = 2;
        *used = 5;
    }
    //10111 or 01000 || 10001 or 01110
    else if(res1 == 2 && res2 == 2){
        *X = 1;
        *X1 = 5;
        int param[3][3] = {{2,3,4}, {2,4,3}, {3,4,2}};
        int sum = 0;
        int i;
        for( i = 0; i < 3; i++){
            int a = param[i][0];
            int b = param[i][1];
            int c = param[i][2];
            int temp[4] = {*X, a, b, *X1};
            int res = QCOUNT(1,temp);
            sum += res;
            //case: 10111 or 01000
            if(res == 4){
                //set y
                *Y = c;
                break;
            }
        }
        //case:10001 or 01110
        if(sum == 0){
            *Y = 2;
            *NumOfX = 2;
            *NumOfY = 3;
        }
        //case:10111 or 01000
        else{
            *NumOfX = 4;
            *NumOfY = 1;
        }
        *used = 5;
    }
    //01111 or 10000
    else if(res1 == 2 && res2 == 4){
        *X = 2;
        *X1 = 3;
        *Y = 1;
        *NumOfX = 4;
        *NumOfY = 1;
        *used = 5;
    }
    //11110 or 00001
    else if(res1 == 4 && res2 == 2){
        *X = 1;
        *X1 = 2;
        *Y = 5 + s;
        *NumOfX += s + 4;
        *NumOfY = 1;
        *used += s + 5;
    }
    //11111 or 00000
    else if(res1 == 4 && res2 == 4){
        //need recursive call to check next pos
        if(s + 5 < (n/2+1)){
            identifyIndex(n, s+1, X, X1, Y, NumOfX, NumOfY, used);
        }
        else{
            *used = n/2 + 1;
            *NumOfX = n/2 + 1;
            *NumOfY = 0;
            *X = 1;
            *X1 = 2;
            *Y = -1;
        }
    }
    else{
        perror("QCOUNT Error - Identiry Indices");
    }
}

int mysub(int n)
{
    int NumOfX = 0;
    int NumOfY = 0;
    int X = 0;
    int X1 = 0;
    int Y = 0;
    struct node* head4 = NULL;
    struct node* head2 = NULL;
    struct node* cur4 = NULL;
    struct node* cur2 = NULL;
    int used = 0;
    int twoCounter = 0;
    //int conti = 0;
    
    identifyIndex(n, 0, &X, &X1, &Y, &NumOfX, &NumOfY, &used);
    
    if(NumOfX > n/2) return X;
    if(NumOfY > n/2) return Y;

    assert(NumOfX + NumOfY == used);

    int i = used+1;
    for(; i + 3 <= n; i+=4)
    {
        int myarray[4] = {i, i+1, i+2, i+3};
        int qcnt = QCOUNT(1, myarray);
        if(qcnt == 0)
        {
            NumOfX += 2;
            NumOfY += 2;
        }
        else if(qcnt == 2)
        {
            if(!head2)
            {
                head2 = malloc(sizeof(struct node));
                head2 -> begin = i;
                head2 -> cnt = 4;
                head2 -> parent = NULL;
                head2 -> next = NULL;
                cur2 = head2;
            }
            else
            {
                cur2 -> next = malloc(sizeof(struct node));
                cur2 -> next -> parent = cur2;
                cur2 = cur2 -> next;
                cur2 -> begin = i;
                cur2 -> cnt = 4;
                cur2 -> next = NULL;
            }
            twoCounter++;
        }
        else //qcnt == 4
        {
            if(!head4)
            {
                head4 = malloc(sizeof(struct node));
                head4 -> begin = i;
                head4 -> cnt = 4;
                head4 -> parent = NULL;
                head4 -> next = NULL;
                cur4 = head4;
            }
            else
            {
                cur4 -> next = malloc(sizeof(struct node));
                cur4 -> next -> parent = cur4;
                cur4 = cur4 -> next;
                cur4 -> begin = i;
                cur4 -> cnt = 4;
                cur4 -> next = NULL;
            }
        }
    }

    while(head4 && head4 -> next)
    {
        cur4 = head4;
        while(cur4 && cur4 -> next)
        {
            struct node* tmp4 = cur4 -> next;
            int myarray[] = {cur4 -> begin, cur4 -> begin + 1, tmp4 -> begin, tmp4 -> begin + 1};
            int qcnt = QCOUNT(1, myarray);
            assert(qcnt == 0 ||  qcnt == 4);
            if(qcnt == 0)
            {
                if(X == -1) {}//Won't happen
                
                if(cur4 -> cnt == tmp4 -> cnt) //Delete both node
                {
                    
                    NumOfX += tmp4 -> cnt;
                    NumOfY += tmp4 -> cnt;
                    
                    struct node* prev = cur4 -> parent;
                    if(!prev)
                    {
                        head4 = tmp4 -> next;
                        if(tmp4 -> next) tmp4 -> next -> parent = NULL;
                        free(cur4);
                        free(tmp4);
                        if(head4) cur4 = head4 -> next;
                        else break;
                        continue;
                    }
                    prev -> next = tmp4 -> next;
                    if(tmp4 -> next) tmp4 -> next -> parent = prev;
                    free(cur4);
                    free(tmp4);
                    cur4 = prev -> next;
                    continue;
                    
                }
                else if(cur4 -> cnt < tmp4 -> cnt)
                {
                    NumOfX += cur4 -> cnt;
                    NumOfY += cur4 -> cnt;
                    cur4 -> cnt = tmp4 -> cnt - cur4 -> cnt;
                    cur4 -> begin = tmp4 -> begin;
                }
                else
                {
                    NumOfX += tmp4 -> cnt;
                    NumOfY += tmp4 -> cnt;
                    cur4 -> cnt = cur4 -> cnt - tmp4 -> cnt;
                }
                    
            }
            else //qcnt == 4
            {
                cur4 -> cnt += tmp4 -> cnt;
            }
            
            // Free the tmp
            cur4 -> next = tmp4 -> next;
            if (tmp4 -> next) tmp4 -> next -> parent = cur4;
            cur4 = cur4 -> next;
            free(tmp4);
        }

    }

    if(head4)
    {
        if(X == -1) //Won't happen
        {
            NumOfX += head4 -> cnt;
        }
        else
        {
            int myarray[4] = {head4 -> begin, head4 -> begin +1, head4 -> begin+2, X};
            int qcnt = QCOUNT(1, myarray);
            assert(qcnt == 2 || qcnt == 4);
            if(qcnt == 4)
                NumOfX += head4 -> cnt;
            else
                NumOfY += head4 -> cnt;
        }
        assert(head4 -> next == NULL);
        free(head4);
    }

    if(NumOfX > n/2) return X;
    if(NumOfY > n/2) return Y;
    
    // Traverse2
    int subTwos[2*twoCounter];
    memset(subTwos, -1, 2*twoCounter*sizeof(int));
    int t = 0;
    
    while(head2)
    {
        int myarray[4] = {head2 -> begin, head2 -> begin + 1, X, X1};
        int qcnt = QCOUNT(1, myarray);
        assert(qcnt == 0 || qcnt == 2 || qcnt == 4);
        if(qcnt == 0)
        {
            NumOfY += 3;
            NumOfX += 1;
        }
        else if(qcnt == 4)
        {
            NumOfX += 3;
            NumOfY += 1;
        }
        else
        {
            //process later
            NumOfX += 1;
            NumOfY += 1;
            subTwos[t] = head2 -> begin + 2;
            subTwos[t+1] = head2 -> begin + 3;
            t += 2;
        }
        
        if(NumOfX > n/2) break;
        if(NumOfY > n/2) break;
        struct node* to_del = head2;
        head2 = head2 -> next;
        free(to_del);
    }
    
    for (int j = 0; j + 4 <= t; j += 4) {
        //process 2 at a time
        int a = subTwos[j];
        int b = subTwos[j+2];
        int temp[4] = {X, X1, a, b};
        int res = QCOUNT(1, temp);
        if(res == 0){
            //11|00 00
            NumOfY += 4;
        }
        else if(res == 2){
            //11|00 11
            NumOfX += 2;
            NumOfY += 2;
        }
        else if(res == 4){
            //11|11 11
            NumOfX += 4;
        }
        else{
            perror("QCOUNT - Invalid Result - Process Twos Else If Else");
        }
        if(NumOfX > n/2) return X;
        if(NumOfY > n/2) return Y;
    }
    
    //process 2's left
    int left = t % 4;
    if(left == 2){
        //process final 2
        int a = subTwos[t-1];
        int b = subTwos[t-2];
        int temp[4] = {X, X1, a, b};
        int res = QCOUNT(1, temp);
        if(res == 0){
            //11|00
            NumOfY += 2;
        }
        else if(res == 4){
            //11|11
            NumOfX += 2;
        }
        else{
            perror("QCOUNT - Invalid Result - Process Twos Else If Else");
        }
        if(NumOfX > n/2) return X;
        if(NumOfY > n/2) return Y;
    }

    while(i <= n)
    {
        int myarray[4] = {X, X1, Y ,i};
        int qcnt = QCOUNT(1, myarray);
        if(qcnt == 2) NumOfX ++;
        else NumOfY ++;
        assert(qcnt == 0 || qcnt == 2);

        if(NumOfX > n/2) return X;
        if(NumOfY > n/2) return Y;
        i += 1;
    }
    if(NumOfX > n/2) return X;
    if(NumOfY > n/2) return Y;

    return 0;
}

