
#include<iostream>
#include<string>
using namespace std;

#define MAX 5
#define price 0.05 
typedef struct time
{
	int hour, min;
}Time;
typedef struct node
{
	string num;
	Time reach, leave;
}CarNode;//�ṹ�壺����ÿ�������ƺţ�����״̬����Ϊ������ʱ�����뿪ʱ��
typedef struct NODE
{
	CarNode* stack[MAX + 1];
	int top;
}SeqStackCar;//��ջ���壬����ͣ����
typedef struct car
{
	CarNode* data;
	struct car* next;
}QueueNode;//�ö��н�㶨�壬����ͣ������ĵ����Ⱥ���
typedef struct Node
{
	QueueNode* head, * rear;
}LinkQueueCar;//�ö��ж��壬����ͣ������ĵȺ���

void InitStack(SeqStackCar*);
int InitQueue(LinkQueueCar*);
int Reach(SeqStackCar*, LinkQueueCar*);
void Leave(SeqStackCar*, SeqStackCar*, LinkQueueCar*);
void List(SeqStackCar, LinkQueueCar);
void PRINT(CarNode* p, int room);
int main()
{
	SeqStackCar Enter, Temp;//��ʼջ����תջ
	LinkQueueCar Wait;//�������
	int a;
	InitStack(&Enter);
	InitStack(&Temp);
	InitQueue(&Wait);//��ʼ��
	while (1)
	{
		cout << "            ��ӭ����ͣ����!             " << endl;
		cout << "           1.��������Ǽ�" << endl;
		cout << "           2.�����뿪�Ǽ�" << endl;
		cout << "           3.����ͣ����ѯ" << endl;
		cout << "           4.�˳�ϵͳ" << endl;//ϵͳ����
		while (1)
		{
			cin >> a;
			if (a >= 1 && a <= 4)break;
			else cout << endl << "��ѡ��1~4";
		}
		switch (a)
		{
		case 1:Reach(&Enter, &Wait); break;
		case 2:Leave(&Enter, &Temp, &Wait); break;
		case 3:List(Enter, Wait); break;
		case 4:exit(0);
		default:break;
		}

	}

}
void InitStack(SeqStackCar* s)//��ջ��ʼ��
{
	s->top = 0;
	s->stack[s->top] = NULL;
}
int InitQueue(LinkQueueCar* Q)//���г�ʼ��
{
	Q->head = new QueueNode;
	if (Q->head != NULL)
	{
		Q->head->next = NULL;
		Q->rear = Q->head;
		return 1;
	}
	else return -1;
}
void PRINT(CarNode* p, int room)//����뿪ͣ�����ĳ������
{
	int A, B, C, D;
	cout << "\n�����뿪��ʱ��:" << endl;
	cout << "����Сʱ��";
	cin >> p->leave.hour;
	cout << "�������:";
	cin >> p->leave.min;
	cout << "�뿪�����ĳ��ƺ�Ϊ��";
	cout << p->num;
	cout << endl << "�䵽��ʱ��Ϊ��" << p->reach.hour << ":" << p->reach.min;
	cout << "�뿪ʱ��Ϊ��" << p->leave.hour << ":" << p->leave.min;
	A = p->reach.hour;
	B = p->reach.min;
	C = p->leave.hour;
	D = p->leave.min;
	cout << endl << "Ӧ������Ϊ��" << ((C - A) * 60 + (D - B)) * price << "Ԫ" << endl;
	cout << "�����뿪�Ǽ����!" << endl;
	cout << "------------------------------------------------------" << endl;
	delete p;
}
int Reach(SeqStackCar* Enter, LinkQueueCar* W)
{
	CarNode* p;
	QueueNode* t;
	p = new CarNode;
	cout << "-------------------------------------------------------" << endl;
	cout << "��������Ǽǿ�ʼ��" << endl;
	cout << endl << "�����복�ƺţ�";
	cin >> p->num;
	if (Enter->top < MAX)//�����λδ�������ͣ����
	{
		Enter->top++;
		cout << endl << "�����ڳ�����" << Enter->top << "λ��.";
		cout << endl << "��������ʱ�䣺" << endl;
		cout << "����Сʱ��";
		cin >> p->reach.hour;
		cout << "�������:";
		cin >> p->reach.min;
		cout << endl << "��������Ǽ����!" << endl;
		cout << "---------------------------------------------------" << endl;
		Enter->stack[Enter->top] = p;
		return 1;
	}
	else//�����λ��������ͣ�ڱ����
	{
		cout << "----------------------------------------------------" << endl;
		cout << endl << "�ó���ͣ���ڱ���ϣ��г�λʱ����ͣ����" << endl;
		t = new QueueNode;
		t->data = p;
		t->next = NULL;
		W->rear->next = t;
		W->rear = t;
		return 1;
	}
}
void Leave(SeqStackCar* Enter, SeqStackCar* Temp, LinkQueueCar* W)
{
	int room;
	CarNode* p, * t;
	QueueNode* q;

	if (Enter->top > 0)
	{
		while (1)
		{
			cout << "----------------------------------------------" << endl;
			cout << "�����뿪�Ǽǿ�ʼ��" << endl;
			cout << endl << "�����복�ڳ�����λ��/1--" << Enter->top << "/:";
			cin >> room;//�뿪���ĺ���
			if (room >= 1 && room <= Enter->top)
				break;
		}
		while (Enter->top > room)//��ͣ������ջ����ת��ջ�ƶ�������ֱ��Ҫ�뿪������λ��ֹͣ
		{
			Temp->top++;
			Temp->stack[Temp->top] = Enter->stack[Enter->top];
			Enter->stack[Enter->top] = NULL;
			Enter->top--;
		}
		p = Enter->stack[Enter->top];
		Enter->stack[Enter->top] = NULL;
		Enter->top--;
		while (Temp->top >= 1)//����ת��ջ�еĳ����Ƶ�ͣ������ջ
		{
			Enter->top++;
			Enter->stack[Enter->top] = Temp->stack[Temp->top];
			Temp->stack[Temp->top] = NULL;
			Temp->top--;
		}
		cout << "-----------------------------------------------------" << endl;
		cout << "�����뿪�Ǽǽ��㣺" << endl;
		PRINT(p, room);
		if ((W->head != W->rear) && Enter->top < MAX)
		{
			q = W->head->next;
			t = q->data;
			Enter->top++;//
			cout << "ͣ�����е�" << room + 1 << "," << room + 2 << "�ų��뿪ͣ����Ϊ" << room << "�ų���λ��" << endl;
			cout << "ͣ������" << room << "�ų��뿪��" << endl;
			cout << "�����" << t->num << "�ų����복����" << Enter->top << "λ��." << endl;
			cout << "������" << t->num << "�ų����복��ʱ�䣺" << endl;
			cout << "����Сʱ��";
			cin >> t->reach.hour;
			cout << "�������:";
			cin >> t->reach.min;
			W->head->next = q->next;
			if (q == W->rear)W->rear = W->head;
			Enter->stack[Enter->top] = t;
			delete q;
		}
		else cout << endl << "�����û�г�!" << endl;
	}
	else cout << endl << "������û�г�" << endl;
}
void List1(SeqStackCar* S)//�鿴ͣ�����ڳ�������ĺ�������
{
	int i;
	if (S->top > 0)
	{
		cout << "-----------------------------------------------------" << endl;
		cout << endl << "�����ڲ�����ͣ�������" << endl;
		cout << endl << "λ��       ����ʱ��         ���ƺ�" << endl;
		for (i = 1; i <= S->top; i++)
		{
			cout << i;
			cout << "             " << S->stack[i]->reach.hour << ":" << S->stack[i]->reach.min;
			cout << "             " << S->stack[i]->num << endl;
		}
	}
	else cout << endl << "������û�г�" << endl;
	cout << "--------------------------------------------------------" << endl;
}
void List2(LinkQueueCar* W)//�鿴�����ͣ����������ĺ�������
{
	QueueNode* p;
	p = W->head->next;
	if (W->head != W->rear)
	{
		cout << "---------------------------------------------------" << endl;
		cout << endl << "���ͣ�����������" << endl;
		while (p != NULL)
		{
			cout << endl << "�����ƺţ�";
			cout << p->data->num << endl;
			p = p->next;
		}
	}
	else cout << endl << "�����û�г���" << endl;
	cout << "--------------------------------------------------------" << endl;
}
void List(SeqStackCar S, LinkQueueCar W)//�����б���ʾ����
{
	int flag, tag;
	flag = 1;
	while (flag)
	{
		cout << "----------------------------------------------------" << endl;
		cout << "����ͣ����ѯ��ʼ��" << endl;
		cout << endl << "��ѡ�� 1|2|3�� " << endl;
		cout << "1.�����б�" << endl << "2.����б�" << endl << "3.�������˵�" << endl;
		while (1)
		{
			cin >> tag;
			if (tag >= 1 || tag <= 3)break;
			else cout << endl;
			cout << "��ѡ�� 1~3��";
		}
		switch (tag)
		{
		case 1:List1(&S);
			cout << "����ͣ����ѯ����!" << endl; break;
		case 2:List2(&W);
			cout << "����ͣ����ѯ����!" << endl; break;
		case 3:flag = 0; break;
		default:break;
		}
	}
	cout << "-----------------------------------------------------" << endl;
}