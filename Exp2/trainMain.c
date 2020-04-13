#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// meta: partly fixed indents and whitespaces
// meta: slightly changed capitalized variable name "StackNode::Next" -> "StackNode::next"

typedef struct StackNode{
    /** 栈中存储的节点 */
    int id;
    struct StackNode *next;

    // begin: whsu 2020.04.10
    // comment: benefit popping
    struct StackNode *prev;
    // end: whsu 2020.04.10

    /** 可自由添加需要用的变量 */
}StackNode;

// begin: whsu 2020.04.10
// comment: a constructor for struct Stacknode
StackNode *newStackNode(int new_id, StackNode *new_prev) {
    StackNode *stackNode = (StackNode*)malloc(sizeof(StackNode));
    stackNode->id = new_id;
    stackNode->next = NULL;
    stackNode->prev = new_prev;

    return stackNode;
}
// end: whsu 2020.04.10

typedef struct LinkStack{
    /** 栈 */
    StackNode* top;
    // begin: whsu 2020.04.10
    StackNode *head;
 // end: whsu 2020.04.10
}LinkStack;

LinkStack* InitStack(){
    /** 初始化栈 */
    LinkStack* linkStack = (LinkStack *)malloc(sizeof(LinkStack));

    // begin: whsu 2020.04.10
    // comment: changed integer-based size control to headnode-based size control
    linkStack->head = linkStack->top = newStackNode(0, NULL);
    // end: whsu 2020.04.10

    return linkStack;
}

// begin: whsu 2020.04.10
// comment: let it be more c++!

int StackEmpty(LinkStack *thisStack) {
    /** 判断栈是否为空 */

    // begin: whsu 2020.04.10
    // comment: changed integer-based size control to headnode-based size control
    return (thisStack->top == thisStack->head);
    // end: whsu 2020.04.10
}

int Push(LinkStack *thisStack,int ele){
    /** 将一个节点压入栈 */

    // begin: whsu 2020.04.10
    StackNode *new_node = newStackNode(ele, thisStack->top);
    if (new_node) {
        thisStack->top->next = new_node;
        thisStack->top = new_node;
        return 1;
    }
    else return 0;
    // end: whsu 2020.04.10
}

// begin: whsu 2020.04.10
// comment: (personal opinion) no need to return the top element when popping 
//          use GetTop() instead 
int Pop(LinkStack* thisStack){
// end: whsu 2020.04.10
    /** 将一个节点弹出栈 */

    // begin: whsu 2020.04.10
    if (StackEmpty(thisStack)) return 0;  // else

    thisStack->top = thisStack->top->prev;
    free(thisStack->top->next);
    thisStack->top->next = NULL;

    return 1;
    // end: whsu 2020.04.10
}

int GetTop(LinkStack* thisStack){
    /** 若栈不空，返回栈的栈顶元素 */
    return StackEmpty(thisStack) ? 0x7f7f7f7f : thisStack->top->id;
}

// begin: whsu 2020.04.10
// comment: deleted stackLength

// end: whsu 2020.04.10



int SeqLegal(int in[],int out[],int num){
    /** 实验内容1:判断输入的出站序列是否可由输入的进站序列通过进出栈得到
     可行返回1，不可行返回0
     */
    // begin: whsu 2020.04.10
    int out_index = 0;
    LinkStack *s_in = InitStack(), *s_station = InitStack();

    // initialize a "coming train" stack with the given "in" sequence
    for (int i=num ; i>=0 ; i--) Push(s_in, in[i]);

    while (out_index<num) {
        if (StackEmpty(s_station) || GetTop(s_station)!=out[out_index]) {
            if (StackEmpty(s_in)) return 0;
            else {
                Push(s_station, GetTop(s_in));
                Pop(s_in);
            }
        }
        else {
            Pop(s_station);
            out_index++;
        }
    }

    return 1;
    // end: whsu 2020.04.10
}


typedef struct QueueNode{
    /** 队列节点 */
    int id;
    struct QueueNode* next;

    // begin: whsu 2020.04.10
    // comment: change to double-linked list
    struct QueueNode* prev;
    // end: whsu 2020.04.10

}QueueNode;

// begin: whsu 2020.04.10
QueueNode *newQueueNode(int new_id, QueueNode *new_prev) {
    QueueNode *newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->id = new_id;
    newNode->next = NULL;
    newNode->prev = new_prev;

    return newNode;
}
// end: whsu 2020.04.10

typedef struct Queue{
    /** 队列 */
    QueueNode *head;
    QueueNode *rear;
}LinkQueue;

// begin: whsu 2020.04.10
// comment: let it be more c++!

LinkQueue* InitQueue(){
    /** 初始化队列 */
    LinkQueue* thisQueue = (LinkQueue*) malloc(sizeof(LinkQueue));

    // begin: whsu 2020.04.10
    // comment: "with head node" style
    thisQueue->head = thisQueue->rear = newQueueNode(-1, NULL);
    // end: whsu 2020.04.10

    return thisQueue;
}

int QueueEmpty(LinkQueue* thisQueue){
    /** 判断队列是否为空 */

    // begin: whsu 2020.04.10
    // comment: a compatible function!
    // end: whsu 2020.04.10

    return (thisQueue->head == thisQueue->rear);
}

int EnQueue(LinkQueue *thisQueue,int ele){
    /** 入队 */

    // begin: whsu 2020.04.10
    QueueNode *newRear = newQueueNode(ele, thisQueue->rear);

    if (!newRear) return 0;  // else

    thisQueue->rear->next = newRear;
    thisQueue->rear = newRear;
    return 1;
    // end: whsu 2020.04.10
}

// begin: whsu 2020.04.10
// comment: (personal opinion) no need to return the top element when dequeuing 
//          use GetHead() instead
int DeQueue(LinkQueue *thisQueue){
// end: whsu 2020.04.10
    // begin: whsu 2020.04.10
    if (QueueEmpty(thisQueue)) return 0;  // else

    QueueNode *del = thisQueue->head->next;

    if (del==thisQueue->rear) thisQueue->rear = thisQueue->head;
    else del->next->prev = thisQueue->head;

    thisQueue->head->next = del->next;
    free(del);

    return 1;
    // end: whsu 2020.04.10
}

// begin: whsu 2020.04.10
// comment: deleted QueueLength
// end: whsu 2020.04.10

int GetFront(LinkQueue *thisQueue){
    // begin: whsu 2020.04.10
    return QueueEmpty(thisQueue) ? 0x7f7f7f7f : thisQueue->head->next->id;
    // end: whsu 2020.04.10
}

int GetRear(LinkQueue *thisQueue){
    // begin: whsu 2020.04.10
    return QueueEmpty(thisQueue) ? 0x7f7f7f7f : thisQueue->rear->id;
    // end: whsu 2020.04.10
}


int findClosestQueue(LinkQueue *railQueue[],int usedQueue,int curTrain, int num){
    /**  找到最合适的火车轨道 */
    // Tips：请考虑如若找不到的情况
    int closestIdx = -1;

    // begin: whsu 2020.04.10
    int queue_max_rear = -1;  // compatible for 
    for (int i=0 ; i<usedQueue ; i++) {
        // empty queue is the least-concerned result
        if (QueueEmpty(railQueue[i])) {
                if (closestIdx==-1) {
                closestIdx = i;
                queue_max_rear = 0;  // the smallest
            }
        }
        // the larger the rear, the better
        else if (queue_max_rear<GetRear(railQueue[i]) && GetRear(railQueue[i])<curTrain) {
            closestIdx = i;
            queue_max_rear = GetRear(railQueue[i]);
        }
    }
    
    // if haven't found a closest queue, then return -1 to call for a new buffer queue

    // end: whsu 2020.04.10
    
    return closestIdx;
}

// end: whsu 2020.04.10

int minBufferQueue(int out[],int num){
    /** 实验内容2:求解所需缓冲轨道的最小值*/
    LinkQueue *railQueue[num]; //指针数组，记录各缓存轨道的火车，有与火车数相等的轨道数时一定可行

    int usedQueue = 0;      //已使用的队列数

    // begin: whsu 2020.04.10
    int toArrange = 1;      // 需要被安排的火车
    int in_index = 0;       // 将被安排的火车

    while (toArrange<=num) {
        // first find the queue containing the train to be arranged
        int found = 0;
        for (int i=0 ; i<usedQueue ; i++) if (GetFront(railQueue[i])==toArrange) {
            found = 1;
            DeQueue(railQueue[i]);
            toArrange++;
            break;
        }
        
        // if not found, push a train into the closest queue
        if (!found) {
            int closestQueue = findClosestQueue(railQueue, usedQueue, out[in_index], num);

            if (closestQueue==-1) {
                usedQueue++;
                railQueue[usedQueue-1] = InitQueue();
                EnQueue(railQueue[usedQueue-1], out[in_index]);
            }
            else EnQueue(railQueue[closestQueue], out[in_index]);

            in_index++;
        }
    }

    for (int i=0 ; i<usedQueue ; i++) free(railQueue[i]);

    // end: whsu 2020.04.10

    return usedQueue;
}

int main()
{
    
    int trainNum;
    int count = 0;
    freopen("data/TestTrain.in", "r", stdin);
    
    while(scanf("%d",&trainNum)!=EOF){
        count++;
        int trainIn[trainNum];
        int trainOut[trainNum];

        int validate[trainNum+1];
        int validFlag1 = 1, validFlag2 = 1;
        
        memset(validate, 0, sizeof(int)*(trainNum+1));
        for(int i = 0;i < trainNum;i++){
            scanf("%d",&trainIn[i]);
            if (trainIn[i]<1 || trainNum<trainIn[i]) {
                printf("Input sequence 1 error: %d is a not valid id\n", trainIn[i]);
                validFlag1 = 0;
            }
            else {
                validate[trainIn[i]] = 1;
            }
        }

        for (int i=1 ; i<=trainNum ; i++) if (!validate[i]) {
            printf("Sequence 1 incomplete!\n");
            validFlag1 = 0;
            break;
        }

        memset(validate, 0, sizeof(int)*(trainNum+1));
        for(int i = 0;i < trainNum;i++){
            scanf("%d",&trainOut[i]);
            if (trainOut[i]<1 || trainNum<trainOut[i]) {
                printf("Input sequence 2 error: %d is a not valid id!\n", trainOut[i]);
                validFlag2 = 0;
            }
            else {
                validate[trainOut[i]] = 1;
            }
        }

        for (int i=1 ; i<=trainNum ; i++) if (!validate[i]) {
            printf("Sequence 2 incomplete!\n");
            validFlag2 = 0;
            break;
        }

        printf("====Case %d====\n",count);
        // 实验内容1
        if (validFlag1 && validFlag2) {
            if(SeqLegal(trainIn,trainOut,trainNum)){
                printf("The output train sequence is Possible\n");
            } else {
                printf("The output train sequence is impossible\n");
            }
        }
        else printf("Subtask1: Sequence Error: Can't judge whether the output sequence is possible or not.\n");
        // 实验内容2
        if (validFlag2) printf("To recover the order, %d buffer queue is needed.\n",minBufferQueue(trainOut, trainNum));
        else printf("Subtask2: Sequence Error: Can't calculate the minimal buffer needed.\n");

    }
    fclose(stdin);
    return 0;
}
