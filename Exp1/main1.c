#include <stdlib.h>
#include <stdio.h>
typedef struct node{
    int ClassID;
    int StuID;
    int Grade;
    struct node *next;
}StudentLinkedListNode;


/* 锟斤拷印锟斤拷锟斤拷锟节碉拷 */
void printLinkedListNode(StudentLinkedListNode * node){
    printf("{class:%d, ID:%d, Grade:%d}",node->ClassID, node->StuID, node->Grade);
    if(node->next!=NULL){
        printf("->");
    }else
    {
        printf("\n");
    }

}

/* 锟斤拷锟斤拷帽锟斤拷某杉锟斤拷锟斤拷 */
void outputStudentLinkedList(StudentLinkedListNode* head){
    // 锟斤拷锟节碉拷锟斤拷锟节碉拷锟斤拷锟斤拷暮锟斤拷锟絧rintLinkedListNode锟斤拷锟结供
    //锟斤拷锟斤拷实锟街憋拷锟斤拷锟斤拷锟斤拷锟斤拷锟竭硷拷
	//TODO
    // (begin whsu, 2020.04.03)
    if (!head || !head->next) return;
    StudentLinkedListNode *iter = head->next;
    while (iter) {
        printLinkedListNode(iter);
        iter = iter->next;
    }
    // (end whsu, 2020.04.03)
}


/** 锟铰斤拷一锟斤拷锟斤拷锟斤拷node锟斤拷锟斤拷锟斤拷 */
StudentLinkedListNode* studentLinkedListCreate( int class_id,int student_id,int grade) {
    //tips:malloc锟斤拷时锟斤拷堑锟轿?转锟斤拷为锟结构锟斤拷指锟斤拷
	//TODO
    // (begin whsu, 2020.04.03)
    StudentLinkedListNode *tmp = (StudentLinkedListNode*)malloc(sizeof(StudentLinkedListNode));
    if (tmp) {
        tmp->ClassID = class_id;
        tmp->StuID = student_id;
        tmp->Grade = grade;
        tmp->next = NULL;
    }
    return tmp;
    // (end whsu, 2020.04.03)
}

/** copy一锟斤拷锟斤拷锟叫碉拷node */
StudentLinkedListNode* studentLinkedListCopy(StudentLinkedListNode* src){
    StudentLinkedListNode* tempNode = studentLinkedListCreate(src->ClassID,src->StuID,src->Grade);
    return tempNode;
}



/** 锟斤拷锟秸斤拷锟斤拷锟斤拷锟窖э拷锟斤拷某杉锟斤拷锟斤拷,锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷头指锟斤拷 */
StudentLinkedListNode* studentLinkedListAdd(StudentLinkedListNode* head, StudentLinkedListNode* node) {
//TODO
    // (begin whsu, 2020.04.03)

    // the head only stores ClassID, both StuID and Grade will be set to -1
    if (head==NULL) {
        head = studentLinkedListCreate(node->ClassID, -1, -1);
        head->next = node;
        node->next = NULL;
    } else {
        StudentLinkedListNode *iter = head;
        while (iter->next) {
            if (iter->next->Grade<node->Grade) break;
            else iter = iter->next; 
        }

        // insertion 
        // iter -> nextnode
        //      ^ insert here
        StudentLinkedListNode *nxt = iter->next;
        iter->next = node;
        node->next = nxt;
    }

    return head;
    // (end whsu, 2020.04.03)
}

/** 锟斤拷锟斤拷学锟斤拷锟斤拷锟斤拷某锟斤拷学锟斤拷锟侥成硷拷锟斤拷锟? 锟斤拷锟矫伙拷锟?,锟斤拷printf("this class  has no such student as id=%d",id)锟斤拷 */
void searchByID(StudentLinkedListNode*head ,int id){
//TODO
    // (begin whsu, 2020.04.03)
    if (head && head->next) {  // uses short circuit to avoid empty head
        StudentLinkedListNode *iter = head->next;
        while (iter) {
            if (iter->StuID==id) {
                printLinkedListNode(iter);
                return;  // return if found, avoid showing the error message
            } else {
                iter = iter->next;
            }
        }
    }

    // fixed duplicated whitespace
    printf("this class has no such student as id=%d",id);

    // (end whsu, 2020.04.03)
}

/** 锟斤拷锟斤拷学锟斤拷删锟斤拷某锟斤拷学锟斤拷锟侥成硷拷锟斤拷锟? 锟斤拷锟矫伙拷锟?,锟斤拷printf("this class has no such student as id=%d",id);*/
StudentLinkedListNode* deleteByID(StudentLinkedListNode* head,int id){
//TODO
    // (begin whsu, 2020.04.03)
    if (head && head->next) {  // uses short circuit to avoid empty head
        StudentLinkedListNode *iter = head;
        while (iter->next) {
            if (iter->next->StuID==id) {
                StudentLinkedListNode *del = iter->next;
                iter->next = del->next;
                free(del);

                return head;  // return if found, avoid showing the error message
            } else {
                iter = iter->next;
            }
        }
    }

    // fixed duplicated whitespace
    printf("this class has no such student as id=%d",id);

    return head;
    // (end whsu, 2020.04.03)
}


/** 锟较诧拷锟斤拷锟斤拷锟洁级锟侥成硷拷锟斤拷锟? */
StudentLinkedListNode* mergeLinkedList(StudentLinkedListNode* heads[]){
    //tips:锟斤拷为锟斤拷锟斤拷亩锟斤拷锟街革拷锟?,为锟剿凤拷止锟斤拷止锟斤拷锟斤拷锟接帮拷锟斤拷锟皆?锟斤拷锟斤拷锟斤拷锟斤拷锟侥存储,
    //锟斤拷锟斤拷锟斤拷node锟斤拷值锟斤拷时锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷峁╋拷锟絪tudentLinkedListCopy锟斤拷锟斤拷
    //锟斤拷 node->next = temp_node 锟斤拷为 node->next = studentLinkedListCopy(temp_node)
	//TODO
}

StudentLinkedListNode* reverseLinkedList(StudentLinkedListNode*head){
//TODO
}

int main(){
        StudentLinkedListNode* Class[2]={NULL};
        StudentLinkedListNode* All=NULL;  // merged list
		StudentLinkedListNode* reAll=NULL;  // reversed
        printf("\
        1.insert \
        2.search by StuID \
        3.delete by StuID  \
        4.merge \
        5.reverse \
        6.output  \
        \n");

        int op;
        int i;
		
        /* temporary input */
        int tempClass;
        int tempStuId;
        int tempGrade;
        char name[10];
        StudentLinkedListNode *tempNode;
        while (scanf("%d", &op) != EOF) {
            switch (op) {
                case 1:
                    printf("How many rows of data do you need to input?\n");
                    // (modify whsu, 2020.04.03)  // robust
                    while(!scanf("%d",&i)) while(getchar()!='\n');
                    // (end whsu, 2020.04.03)
                    printf("input the i row data format as:class_id,student_id,grade\n");
                    while (i!=0){
                        // (modify whsu, 2020.04.03)  // robust
                        while (scanf("%d,%d,%d", &tempClass, &tempStuId, &tempGrade)!=3) {
                            printf("BAD FORMAT!\n");
                            printf("RE-input the data formatted as:class_id,student_id,grade\n");
                            while (getchar()!='\n');
                        }
                        while (tempClass<0 || 1<tempClass) {
                            printf("Bad class_id, input class_id again\n");
                            scanf("%d", &tempClass);
                        }
                        // (end whsu, 2020.04.03)  // will fix remaining robust problem in the next updates
                        tempNode = studentLinkedListCreate(tempClass, tempStuId, tempGrade);
                        Class[tempClass]=studentLinkedListAdd(Class[tempClass], tempNode);
                        i--;
                    }
                    break;
                case 2:
                    printf("input the data format as: ClassID, StuID\n");
                    scanf("%d,%d",&tempClass, &tempStuId);
                    searchByID(Class[tempClass], tempStuId);
                    break;
                case 3:
                    printf("input the data format as: ClassID, StuID\n");
                    scanf("%d,%d",&tempClass,&tempStuId);
                    Class[tempClass]=deleteByID(Class[tempClass], tempStuId);
                    break;
                case 4:
                    All=mergeLinkedList(Class);
                    outputStudentLinkedList(All);
                    break;
                case 5:
                    reAll=reverseLinkedList(All);
                    outputStudentLinkedList(reAll);
                    break;
                case 6:
                    printf("Class 0:\n");
                    outputStudentLinkedList(Class[0]);
                    printf("\nClass 1:\n");
                    outputStudentLinkedList(Class[1]);
                    break;

            }
            printf("\n###################################\n");
            printf("1.insert 2.search by studentID 3.delete by studentID 4.merge 5. reverse 6.output  \n");
    }
}
