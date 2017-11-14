#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

template<typename T>
class Sequence {
public:
virtual void Random(int number)=0;
virtual int GetLength()=0;
virtual T GetFirst()=0;
virtual void InsertionSort()=0;
virtual void TestInit()=0;
virtual int TestCheck()=0;
virtual T GetLast()=0;
virtual void QuickSort()=0;
virtual T Get(int index)=0;
virtual void Remove(T elem)=0;
virtual void Append(T elem)=0;
virtual void Prepend(T elem)=0;
virtual void InsertAt(int pos,T elem)=0;
virtual Sequence<T> *GetSubsequence(int i, int j)=0;
virtual void print()=0;
};

template<typename T>
struct node{
  T data;
  struct node *next=NULL;
};

template<typename T>
void my_realloc(T *arr, int size, int new_size)
{
    T *new_arr = new T [new_size];
    size = size < new_size ? size : new_size;

    for (int i = 0; i < size; ++i)
        new_arr[i] = arr[i];
    arr = new_arr;
};

template <typename T> class Array : public Sequence<T>
{
private:
    T *arr;
    int num;
public:
Array(){
    arr=new T;
    num=0;
};
//_______________________________QUICKSORT________________________________//
void QuickSort(){
  quickSort(arr,0,num-1);
}
void quickSort(T *arr, int left, int right) {
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];

      while (i <= j) {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      };

      if (left < j)
            quickSort(arr, left, j);
      if (i < right)
            quickSort(arr, i, right);
}

//_________________________________INSERTIONSORT_________________________________//
void InsertionSort(){
  insertionSort(arr,num);
}
void insertionSort(T *arr, int n)
{
   int i, key, j;
   for (i = 1; i < n; i++)
   {
       key = arr[i];
       j = i-1;

       while (j >= 0 && arr[j] > key)
       {
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = key;
   }
}
///////////////////////////////////////////////////////////////////////////
void Append(T elem){
        my_realloc(arr,num,num+1);
            *(arr+num)=elem;
            num++;};

void print(){
    int i;
        for(i=0;i<num;++i)
        cout << *(arr+i) << "\n";};

int GetLength(){return num;};

T GetFirst(){return *arr;};

T GetLast(){return*(arr+num-1);};

T Get(int index){return *(arr+index);};

int getIsEmpty(){return num;}

Array<T> *GetSubsequence(int i, int j){
    if((i>j) or (j<0) or (j>num-1)){
		cout << "INDEX ERROR\n";
		return 0;}
    int k;
    Array<T> *b;
    b=new Array<T>;
        for(k=i;k<j+1;++k)
			b->Append(*(arr+k));
    return b;
};

void Remove(T elem){int i,j=0;
for(i=0;i<num;++i)
    if(*(arr+i)==elem){
        for(j=i;j<num-1;++j)*(arr+j)=*(arr+j+1);
            my_realloc(arr,num,num-1);
            --num;}
};

void TestInit(){
  int i;
  arr=new T[100];
  num=100;
  for(i=num;i>0;--i)
    arr[100-i]=i;
}

void Random(int number){
  int i;
  num=number;
  arr=new T[number];
  for(i=0;i<number;++i)
    arr[i]=rand()%100;
}

int TestCheck(){
  int i;
  int flag=1;
  for(i=0;i<100;++i)
    if (arr[i]!=i+1) flag=0;
  return flag;
}
void Prepend(T elem){
    int i;
    my_realloc(arr,num,num+1);
        for(i=num+1;i>0;--i)
        *(arr+i)=*(arr+i-1);
    *(arr)=elem;
num++;};

void InsertAt(int pos,T elem){
    if(pos>num-1){
		cout << "INDEX ERROR\n";
		return ;
	}
    int i;
    if (pos==0) Prepend(elem);
if (pos==num) Append(elem);
if ((pos!=0) and (pos!=num) and (num>pos)){
    my_realloc(arr,num,num+1);
        for(i=num;i>pos-1;--i)
        *(arr+i)=*(arr+i-1);
 *(arr+pos)=elem;
num++;}
};
};
template<typename T> class List : public Sequence<T>
{
private:
    struct node<T> *ptr;
    int num;
public:


List(){ptr=NULL;num=0;};

~List(){delete ptr;}

int GetLength(){return num;};

T GetFirst(){return ptr->data;};

T GetLast(){
	struct node<T> *temp=ptr;
	int i;
	for(i=1;i<num;i++)
		temp=temp->next;
	return temp->data;
}

void FrontBackSplit(struct node<T>* source,
          struct node<T>** frontRef, struct node<T>** backRef)
{
  struct node<T>* fast;
  struct node<T>* slow;
  if (source==NULL || source->next==NULL)
  {
    /* length < 2 cases */
    *frontRef = source;
    *backRef = NULL;
  }
  else
  {
    slow = source;
    fast = source->next;

    while (fast != NULL)
    {
      fast = fast->next;
      if (fast != NULL)
      {
        slow = slow->next;
        fast = fast->next;
      }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
  }
}
//________________________________QUICKSORT_____________________________________//
struct node<T> *getTail(struct node<T> *cur)
{
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}

struct node<T> *partition(struct node<T> *head, struct node<T> *end,
                       struct node<T> **newHead, struct node<T> **newEnd)
{
    struct node<T> *pivot = end;
    struct node<T> *prev = NULL, *cur = head, *tail = pivot;

    while (cur != pivot)
    {
        if (cur->data < pivot->data)
        {
            if ((*newHead) == NULL)
                (*newHead) = cur;

            prev = cur;
            cur = cur->next;
        }
        else // If cur node is greater than pivot
        {
            if (prev)
                prev->next = cur->next;
            struct node<T> *tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }


    if ((*newHead) == NULL)
        (*newHead) = pivot;

    (*newEnd) = tail;

    return pivot;
}


struct node<T> *quickSortRecur(struct node<T> *head, struct node<T> *end)
{
    if (!head || head == end)
        return head;

    struct node<T> *newHead = NULL, *newEnd = NULL;

    struct node<T> *pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot)
    {
        struct node<T> *tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;

        newHead = quickSortRecur(newHead, tmp);

        tmp = getTail(newHead);
        tmp->next =  pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

void QuickSort()
{
    struct node<T> **headRef=&ptr;
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
    return;
}
//______________________________________INSERTIONSORT__________________________//
void sortedInsert(struct node<T>** head_ref, struct node<T>* new_node)
{
    struct node<T>* current;
    if (*head_ref == NULL || (*head_ref)->data >= new_node->data)
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        current = *head_ref;
        while (current->next!=NULL &&
               current->next->data < new_node->data)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

void InsertionSort()
{
    struct node<T> **head_ref=&ptr;
    struct node<T> *sorted = NULL;

    struct node<T> *current = *head_ref;
    while (current != NULL)
    {
        struct node<T> *next = current->next;

        sortedInsert(&sorted, current);

        current = next;
    }

    *head_ref = sorted;
}
///////////////////////////////////////////////////////////////////////////
T Get(int pos){
	struct node<T> *temp=ptr;
	int i;
	if((pos>=0) and (pos<num)){
	for(i=0;i<pos;i++)
		temp=temp->next;
	return temp->data;}
	else{ cout << "ERROR\n";return 0;
        }
}

void TestInit(){
  int i;
  ptr=NULL;
  for(i=0;i<100;++i)
    Prepend(i);
}

int TestCheck(){
  int i;
  int flag=1;
  for(i=0;i<100;i++){
    if(Get(i)!=i) flag=0;
  }
  return flag;
}

int getIsEmpty(){return num;}

void Prepend(T elem){
	struct node<T> *temp=ptr;
	ptr=new node <T>;
    ptr->data=elem;
    ptr->next=NULL;
    if(num!=0)
		ptr->next=temp;
    ++num;}

void print(){
    struct node<T> *temp=ptr;
    while (temp!=NULL){
        cout << (temp->data) << "\n";
        temp=temp->next;
    };
        }

void Append(T elem){
    struct node<T> *temp=ptr;
    struct node<T> *temp1;
    if(num==0)
		Prepend(elem);
	else{
        while (temp->next!=NULL)
            temp=temp->next;
        temp1=new node <T>;
        temp->next=temp1;
        temp1->data=elem;
        temp1->next=NULL;
        num++;
        }
};

void Random(int number){
  int i;
  T elem;
  for(i=0;i<number;++i){
    elem=rand()%100;
    Prepend(elem);
  }
}
Sequence<T> *GetSubsequence(int i, int j){
    if((i>j) or (j<0) or (j>num-1)){
		cout << "INDEX ERROR\n";
		return 0;}
    int k=0;
    List <T> *b;
    b=new List<T>;
    struct node<T> *temp=ptr;
    while(k!=i){++k;temp=temp->next;}
        for(i=0;i<j-k+1;++i){
                b->Append(temp->data);
                temp=temp->next;}
        b->print();
        return b;
};

void InsertAt(int pos,T elem){
    if(pos>num-1){
		cout << "INDEX ERROR\n";
		return ;
	}
    int i;
    struct node<T> *temp=ptr;
    struct node<T> *temp1;
    struct node<T> *temp2;
    if (pos!=0){
            for(i=1;i<pos-1;++i)
				temp=temp->next;
		temp1=temp->next;
		temp2=new node <T>;
		temp->next=temp2;
		temp2->data=elem;
		temp2->next=temp1;
		++num;
		}
    if (pos==0)
		Prepend(elem);
    if (pos==num-1)
		Append(elem);
};

void Remove(T elem){
    int i;
	struct node<T> *temp=ptr;
	struct node<T> *temp1;
	for(i=1;i<num;++i){
        if((i==1) and (temp->data==elem))
			ptr=temp->next;
        if(temp->next->data==elem){
            temp1=temp->next;
            temp->next=temp->next->next;
            delete temp1;
        }
        temp=temp->next;
    };
    --num;
}
};
template<typename T>
void Test(Sequence <T> *a){
    bool flag=1;
    float t=0;
    cout << "Длина начальной последовательности = " << a->GetLength();
    if(a->GetLength()==0)
		cout << " - Правильно\n";
	else{
		cout << " - Неправильно\n";
		flag=0;}
    cout << "Добавляем элемент 51\n";
    a->Append(51);
    cout << "Длина последовательности = " << a->GetLength();
    if(a->GetLength()==1)
		cout << " - Правильно\n";
	else{
		cout << " - Неправильно\n";
		flag=0;}
    cout << "Первый элемент последовательности = " << a->GetFirst();
    if(a->GetFirst()==51)
		cout << " - Правильно\n";
	else{
		cout << " - Неправильно\n";
		flag=0;}
    cout << "Последний элемент последовательности = " << a->GetLast();
    if(a->GetLast()==51)
		cout << " - Правильно\n";
	else{
		cout << " - Неправильно\n";
		flag=0;}
    cout << "Нулевой элемент последовательности = " << a->Get(0);
    if(a->Get(0)==51)
		cout << " - Правильно\n";
	else{
		cout << " - Неправильно\n";
		flag=0;}
    cout << "Добавляем элемент 33 в начало\n";
    a->Prepend(33);
    cout << "Длина последовательности = " << a->GetLength();
    if(a->GetLength()==2)
		cout << " - Правильно\n";
	else{
		cout << " - Неправильно\n";
		flag=0;}
    cout << "Первый элемент последовательности = " << a->GetFirst();
    if(a->GetFirst()==33)
		cout << " - Правильно\n";
	else{
		cout << " - Неправильно\n";
		flag=0;}
    cout << "Последний элемент последовательности = " << a->GetLast();
    if(a->GetLast()==51)
		cout << " - Правильно\n";
	else{
		cout << " - Неправильно\n";
		flag=0;}
    cout << "Первый по индексу элемент последовательности = " << a->Get(1);
    if(a->Get(1)==51)
		cout << " - Правильно\n";
	else{
		cout << " - Неправильно\n";
		flag=0;}
    cout << "Добавляем элемент 12 на место c индексом 1\n";
    a->InsertAt(1,12);
    cout << "Длина последовательности = " << a->GetLength();
    if(a->GetLength()==3)
		cout << " - Правильно\n";
	else{
		cout << " - Неправильно\n";
		flag=0;}
    cout << "Первый элемент последовательности = " << a->GetFirst();
    if(a->GetFirst()==33)
		cout << " - Правильно\n";
	else{
		cout << " - Неправильно\n";
		flag=0;}
    cout << "Последний элемент последовательности = " << a->GetLast();
    if(a->GetLast()==51)
		cout << " - Правильно\n";
	else{
		cout << " - Неправильно\n";
		flag=0;}
    cout << "Элемент последовательности с индексом 1 = " << a->Get(1);
    if(a->Get(1)==12)
		cout << " - Правильно\n";
	else{
		cout << " - Неправильно\n";
		flag=0;}
    cout << "Выделяем подпоследовательность с индексами 1-2\n";
    a->Remove(33);
    cout << "Длина последовательности = " << a->GetLength();
    if(a->GetLength()==2)
		cout << " - Правильно\n";
	else{
		cout << " - Неправильно\n";
		flag=0;}
    cout << "Первый элемент последовательности = " << a->Get(0) << "\nВторой элемент последовательности = " << a->Get(1);
    if((a->Get(1)==51) and (a->Get(0)==12))
		cout << " - Правильно\n";
	else{
		cout << " - Неправильно\n";
		flag=0;}
    cout << "Удаляем элемент 51\n";
    a->Remove(51);
    cout << "Длина последовательности = " << a->GetLength();
    if(a->GetLength()==1)
		cout << " - Правильно\n";
	else{
		cout << " - Неправильно\n";
		flag=0;}
    cout << "Первый элемент последовательности = " << a->GetFirst();
    if(a->GetFirst()==12)
		cout << " - Правильно\n";
    else{
		cout << " - Неправильно\n";
		flag=0;}
    cout << "Последний элемент последовательности = " << a->GetLast();
    if(a->GetLast()==12)
		cout << " - Правильно\n";
	else{
		cout << " - Неправильно\n";
		flag=0;}
		a->Remove(12);
		cout << "Тестируем сортировку вставками: ";
		a->TestInit();
		t=clock();
		a->InsertionSort();
		if(a->TestCheck()==1)
		cout << " - Правильно ";
	else{
		cout << " - Неправильно ";
		flag=0;}
		cout << "Время работы алгоритма " << (clock()-t)/1000 << "c\n";
		cout << "Тестируем быструю сортировку: ";
		a->TestInit();
		t=clock();
		a->QuickSort();
		if(a->TestCheck()==1)
		cout << " - Правильно ";
	else{
		cout << " - Неправильно ";
		flag=0;}
		cout << "Время работы алгоритма " << (clock()-t)/1000 << "c\n";
    if(flag==1) cout << "======ТЕСТ ПРОЙДЕН УСПЕШНО======"; else cout << "======ТЕСТ HE ПРОЙДЕН======";
}

int main(){
    setlocale(LC_ALL,"Russian");
  srand(time(NULL));
	int e,d,f,g;
	List<int> a;
	Array<int> b;
	float t;
	int c=0;
	cout << "Введите, с чем хотите работать\n1)Массив\n2)Список\n";
	cin >> g;
	switch(g){
	case 1:
	cout << "Введите, что хотите сделать\n1)Работать с последовательностью\n2)Тестировать программу\n";
		cin >> e;
		if(e==1)do{
		cout << "Введите, что хотите сделать\n1)Добавить элемент в начало\n2)Добавить элемент в конец\n3)Вывести длину последовательности\n4)Вывести первый элемент\n5)Вывести последний элемент\n6)Вывести элемент по номеру\n7)Вставить элемент на i позицию\n8)Удалить элемент\n9)Выделить подпоследовательность\n10)Вывести последовательность\n11)Сортировать методом вставок\n12)Быстрая сортировка\n13)Случайная генерация чисел\n14)Завершить программу\n";
		cin >> c;
		switch(c){
		case 1:
			cout << "Enter element\n";
			cin >> d;
			b.Prepend(d);
			break;
		case 2:
			cout << "Enter element\n";
			cin >> d;
			b.Append(d);
			break;
		case 3:
			cout << b.GetLength() << "\n";
			break;
		case 4:
			cout << b.GetFirst() << "\n";
			break;
		case 5:
			cout << b.GetLast() << "\n";
			break;
		case 6:
			cout << "Enter index\n";
			cin >> d;
			cout << b.Get(d) << "\n";
			break;
		case 7:
			cout << "Enter index\n";
			cin >> d;
			cout << "Enter element\n";
			cin >> f;
			b.InsertAt(d,f);
			break;
		case 8:
			cin >> d;
			b.Remove(d);
			break;
		case 9:
			cout << "Enter start index\n";
			cin >> d;
			cout << "Enter end index\n";
			cin >> f;
			b.GetSubsequence(d,f);
			break;
		case 10:
			b.print();
			break;
		case 11:
			t=clock();
			b.InsertionSort();
			cout << "Время работы алгоритма " << (clock()-t)/1000 << "c\n";
			break;
		case 12:
			t=clock();
			b.QuickSort();
			cout << "Время работы алгоритма " << (clock()-t)/1000 << "c\n";
			break;
		case 13:
		  cout << "Enter number of elements\n";
			cin >> d;
			b.Random(d);
			break;
		}
	}while (c<14);
		if(e==2)Test(&b);
	break;
	case 2:
		cout << "Введите, что хотите сделать\n1)Работать с последовательностью\n2)Тестировать программу";
		cin >> e;
		if(e==1)do{
		cout << "Введите, что хотите сделать\n1)Добавить элемент в начало\n2)Добавить элемент в конец\n3)Вывести длину последовательности\n4)Вывести первый элемент\n5)Вывести последний элемент\n6)Вывести элемент по номеру\n7)Вставить элемент на i позицию\n8)Удалить элемент\n9)Выделить подпоследовательность\n10)Вывести последовательность\n11)Сортировать методом вставок\n12)Быстрая сортировка\n13)Случайная генерация чисел\n14)Завершить программу\n";
		cin >> c;
		switch(c){
		case 1:
			cout << "Enter element\n";
			cin >> d;
			a.Prepend(d);
			break;
		case 2:
			cout << "Enter element\n";
			cin >> d;
			a.Append(d);
			break;
		case 3:
			cout << a.GetLength() << "\n";
			break;
		case 4:
			cout << a.GetFirst() << "\n";
			break;
		case 5:
			cout << a.GetLast() << "\n";
			break;
		case 6:
			cout << "Enter index\n";
			cin >> d;
			cout << a.Get(d) << "\n";
			break;
		case 7:
			cout << "Enter index\n";
			cin >> d;
			cout << "Enter element\n";
			cin >> f;
			a.InsertAt(d,f);
			break;
		case 8:
			cout << "Enter element\n";
			cin >> d;
			a.Remove(d);
			break;
		case 9:
			cout << "Enter start index\n";
			cin >> d;
			cout << "Enter end index\n";
			cin >> f;
			a.GetSubsequence(d,f);
			break;
		case 10:
			a.print();
			break;
		case 11:
			t=clock();
			a.InsertionSort();
			cout << "Время работы алгоритма " << (clock()-t)/1000 << "c\n";
			break;
		case 12:
			t=clock();
			a.QuickSort();
			cout << "Время работы алгоритма " << (clock()-t)/1000 << "c\n";
			break;
		case 13:
		  cout << "Enter number of elements\n";
			cin >> d;
			a.Random(d);
			break;
		}
	}while (c<14);
		if(e==2)Test(&a);
	break;
	}
	return 0;
}
