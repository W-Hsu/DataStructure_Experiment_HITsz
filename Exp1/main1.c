
#include <stdio.h>
typedef struct node{
    int ClassID;
    int StuID;
    int Grade;
    struct node *next;
}StudentLinkedListNode;


/* ��ӡ�����ڵ� */
void printLinkedListNode(StudentLinkedListNode * node){
    printf("{name:%s, ID:%d, Grade:%d}",node->ClassID, node->StuID, node->Grade);
    if(node->next!=NULL){
        printf("->");
    }else
    {
        printf("\n");
    }

}

/* ����ñ�ĳɼ���� */
void outputStudentLinkedList(StudentLinkedListNode* head){
    // ���ڵ����ڵ�����ĺ���printLinkedListNode���ṩ
    //����ʵ�ֱ���������߼�
	//TODO
}


/** �½�һ������node������ */
StudentLinkedListNode* studentLinkedListCreate( int class_id,int student_id,int grade) {
    //tips:malloc��ʱ��ǵ�Ϊת��Ϊ�ṹ��ָ��
	//TODO
}

/** copyһ�����е�node */
StudentLinkedListNode* studentLinkedListCopy(StudentLinkedListNode* src){
    StudentLinkedListNode* tempNode = studentLinkedListCreate(src->ClassID,src->StuID,src->Grade);
    return tempNode;
}



/** ���ս������ѧ���ĳɼ����,����������ͷָ�� */
StudentLinkedListNode* studentLinkedListAdd(StudentLinkedListNode* head, StudentLinkedListNode* node) {
//TODO

}
/** ����ѧ������ĳ��ѧ���ĳɼ���� ���û��,��printf("this class  has no such student as id=%d",id)�� */
void searchByID(StudentLinkedListNode*head ,int id){
//TODO
}

/** ����ѧ��ɾ��ĳ��ѧ���ĳɼ���� ���û��,��printf("this class has no such student as id=%d",id);*/
StudentLinkedListNode* deleteByID(StudentLinkedListNode* head,int id){
//TODO
}


/** �ϲ������༶�ĳɼ���� */
StudentLinkedListNode* mergeLinkedList(StudentLinkedListNode* heads[]){
    //tips:��Ϊ����Ķ���ָ��,Ϊ�˷�ֹ��ֹ�����Ӱ����ԭ��������Ĵ洢,
    //������node��ֵ��ʱ������������ṩ��studentLinkedListCopy����
    //�� node->next = temp_node ��Ϊ node->next = studentLinkedListCopy(temp_node)
	//TODO
}

StudentLinkedListNode* reverseLinkedList(StudentLinkedListNode*head){
//TODO
}

int main(){
        StudentLinkedListNode* Class[2]={NULL};
        StudentLinkedListNode* All=NULL;
		StudentLinkedListNode* reAll=NULL;
        printf("1.insert 2.search by StuID 3.delete by StuID  4.merge 5.reverse 6.output  \n");

        int op;
        int i;
		
        int tempClass;
        int tempStuId;
        int tempGrade;
        char name[10];
        StudentLinkedListNode *tempNode;
        while (scanf("%d", &op) != EOF) {
            switch (op) {
                case 1:
                    printf("How many rows of data do you need to input?\n");
                    scanf("%d",&i);
                    printf("input the i row data format as:class_id,student_id,grade\n");
                    while (i!=0){
                        scanf("%d,%d,%d", &tempClass,,&tempStuId, &tempGrade);
                        tempNode = studentLinkedListCreate(tempClass, tempStuId, tempGrade);
                        Class[tempClass]=studentLinkedListAdd(Class[tempClass], tempNode);
                        i--;
                    }
                    break;
                case 2:
                    printf("input thedata format as: ClassID, StuID\n");
                    scanf("%d,%s",&tempClass,tempName);
                    searchByID(Class[tempClass], tempName);
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
