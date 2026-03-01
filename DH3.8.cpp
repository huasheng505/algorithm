#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
class Node {
private:
	int data;
	Node* next;
public:
	Node():next(NULL){}
	 void CreatListHead(Node** ptr,int num){
		 Node* p;
		 *ptr=new Node;
		 (*ptr)->next=NULL;
		 for(int i=0;i<num;i++){
			 p=new Node;
			 p->data=rand()%100+1;
			 p->next=(*ptr)->next;//让p的指针域指向头节点之前指向的节点
			 (*ptr)->next=p;//让头节点指向新生成的节点
		 }
	 }
	int speakList(Node*ptr,int num){//读取节点的内容
		if(ptr->next!=NULL)
			ptr=ptr->next;
		else return 0;
		for(int i=0;i<num;i++){
			cout<<ptr->data<<",";
			if(ptr->next==NULL)
				return 0;
			ptr=ptr->next;
		}
		return 0;
	}
};

int main(){
	srand((unsigned int)time(NULL));
	  Node* list=NULL;
	Node nodeObj;
	nodeObj.CreatListHead(&list,10);	
	nodeObj.speakList(list,10);
	system("pause");
	return 0;
}
