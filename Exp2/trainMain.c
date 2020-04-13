#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// meta: partly fixed indents
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
}QueueNode;

typedef struct Queue{
    /** 队列 */
    QueueNode *front;
    QueueNode *rear;
    int size;
}LinkQueue;

LinkQueue* InitQueue(){
    /** 初始化队列 */
    LinkQueue* linkQueue = (LinkQueue*) malloc(sizeof(LinkQueue));
    linkQueue->front = linkQueue->rear = (QueueNode *)malloc(sizeof(QueueNode));
    linkQueue->front->next = NULL;
    linkQueue -> size = 0;
    return linkQueue;
}

int QueueEmpty(LinkQueue* linkQueue){
    /** 判断队列是否为空 */
    return (linkQueue->front == linkQueue->rear);
}

int EnQueue(LinkQueue *linkQueue,int ele){
    /** 入队 */
    return 1;//可删除
}

int DeQueue(LinkQueue *linkQueue,int* ele){
    /** 出队 */
    return 1;//可删除
}

int QueueLength(LinkQueue *linkQueue){
    /** 队列长度 */
    return 1;//可删除
}

int GetHead(LinkQueue *linkQueue,int* ele){
    /** 返回队头 */
    return 1;//可删除
}

int GetRear(LinkQueue *linkQueue,int *ele){
    /** 返回队尾 */
    return 1;//可删除
}


int findClosestQueue(LinkQueue *railQueue[],int usedQueue,int curTrain){
    /**  找到最合适的火车轨道 */
    // Tips：请考虑如若找不到的情况
    int closestIdx = -1;
    
    /** 寻找最合适的火车轨道  */
    //Tips：每个队列中后边的元素要大于前边的元素
    
    // Todo
    
    return closestIdx;
}

int minBufferQueue(int out[],int num){
    /** 实验内容2:求解所需缓冲轨道的最小值*/
    LinkQueue *railQueue[num]; //指针数组，记录各缓存轨道的火车，有与火车数相等的轨道数时一定可行
    for(int i = 0;i < num;i++){
        railQueue[i] = InitQueue();
    }
    int usedQueue = 0;      //已使用的队列数
    int arrangedTrain = 0;  //已安排的火车
    
    /**
     当火车未完全安排完时
     从其中找到最合适放置的轨道
     放置火车
     */
    
    // Todo
    
    return usedQueue;
}

int main()
{
    
    int trainNum;
    int count = 0;
    freopen("Train.in", "r", stdin);
    
    while(scanf("%d",&trainNum)!=EOF){
        count++;
        int trainIn[trainNum];
        int trainOut[trainNum];
        for(int i = 0;i < trainNum;i++){
            scanf("%d",&trainIn[i]);
        }
        for(int i = 0;i < trainNum;i++){
            scanf("%d",&trainOut[i]);
        }
        printf("====Case %d====\n",count);
        // 实验内容1
        if(SeqLegal(trainIn,trainOut,trainNum)){
            printf("The output train sequence is Possible\n");
        }else{
            printf("The output train sequence is impossible\n");
        }
        // 实验内容2
        printf("To recover the order, %d buffer queue is needed:\n",minBufferQueue(trainOut, trainNum));

    }
    fclose(stdin);
    return 0;
}
