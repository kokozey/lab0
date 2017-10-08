#include<iostream>
using namespace std;

template<typename T>
class Sequence {
public:
virtual int GetLength()=0;
virtual T GetFirst()=0;
virtual T GetLast()=0;
virtual T Get(int index)=0;
virtual Remove(T elem)=0;
virtual Append(T elem)=0;
virtual Prepend(T elem)=0;
virtual InsertAt(int pos,T elem)=0;
virtual Sequence<T> *GetSubsequence(int i, int j)=0;
virtual print()=0;
};

template<typename T>
struct node{
T data;
struct node *next=nullptr;
};

template<typename T>
class List : public Sequence<T>
{
private:
    struct node<T> *ptr;
    int num=0;
public:

List(){ptr=nullptr;};

~List(){ptr=(struct node<T>*)malloc(0);}

int GetLength(){return num;};

T GetFirst(){return ptr->data;};

T GetLast(){
        struct node<T> *temp=ptr;
        int i;
    for(i=1;i<num;i++)temp=temp->next;
        return temp->data;}

T Get(int pos){
        struct node<T> *temp=ptr;
        int i;
        if((pos>=0) and (pos<num)){
    for(i=0;i<pos;i++)temp=temp->next;
        return temp->data;}
        else{ cout << "ERROR\n";return 0;
        }
}

int getIsEmpty(){
    bool boo;
if (num!=0) boo=true;
    else boo=false;
    return boo;}

Prepend(T elem){
        struct node<T> *temp=ptr;
            ptr=(struct node<T> *)malloc(sizeof(struct node<T>));
                ptr->data=elem;
                ptr->next=nullptr;
                if(num!=0)ptr->next=temp;
            ++num;}

print(){
    struct node<T> *temp=ptr;
    while (temp!=nullptr){
        cout << (temp->data) << "\n";
        temp=temp->next;
    };
        }

Append(T elem){
        struct node<T> *temp=ptr;
        struct node<T> *temp1;
        if(num==0)Prepend(elem); else{
        while (temp->next!=nullptr)
            temp=temp->next;
        temp1=(struct node<T> *)malloc(sizeof(struct node<T>));
        temp->next=temp1;
        temp1->data=elem;
        temp1->next=nullptr;
        num++;
        }
};

Sequence<T> *GetSubsequence(int i, int j){
    int k=0;
    List <T> b;
    struct node<T> *temp=ptr;
    while(k!=i){++k;temp=temp->next;}
        for(i=0;i<j-k+1;++i){
                b.Append(temp->data);
                temp=temp->next;}
        b.print();
};

InsertAt(int pos,T elem){
    int i;
    struct node<T> *temp=ptr;
    struct node<T> *temp1;
    struct node<T> *temp2;
    if (pos!=0){
            for(i=1;i<pos-1;++i)temp=temp->next;
    temp1=temp->next;
    temp2=(struct node<T> *)malloc(sizeof(struct node<T>));
    temp->next=temp2;
    temp2->data=elem;
    temp2->next=temp1;
    ++num;}
    if (pos==0) Prepend(elem);
    if (pos==num-1)Append(elem);
};

Remove(T elem){
    int i;
struct node<T> *temp=ptr;
struct node<T> *temp1;
for(i=1;i<num;++i){
        if(temp->data==elem)ptr=temp->next;
        if(temp->next->data==elem){
            temp1=temp->next;
            temp->next=temp->next->next;
            temp1=(struct node<T> *)malloc(sizeof(0));
        }
        temp=temp->next;
    };
    --num;
}
};


template<typename T>
class Array : public Sequence<T>
{
private:
    T *mass;
    int num=0;
public:
Array(){
    mass=(T*)malloc(sizeof(T));
}

~Array(){
    mass=(T*)malloc(0);
}

Append(T elem){
        mass=(T*)realloc(mass,sizeof(T)*(num+1));
            *(mass+num)=elem;
            num++;}

print(){
    int i;
        for(i=0;i<num;++i)
        cout << *(mass+i) << "\n";}

int GetLength(){return num;};

T GetFirst(){return *mass;};

T GetLast(){return*(mass+num-1);};

T Get(int index){return *(mass+index);};

int getIsEmpty(){return num;}

Array<T> *GetSubsequence(int i, int j){
    int k;
    Array<T> b;
        for(k=i-1;k<j;++k){b.Append(*(mass+k));}
    return &b;
};

Remove(T elem){int i,j=0;
for(i=0;i<num;++i)
    if(*(mass+i)==elem){
        for(j=i;j<num-1;++j)*(mass+j)=*(mass+j+1);
            mass=(T*)realloc(mass,sizeof(T)*(num-1));
            --num;}
};

Prepend(T elem){
    int i;
    mass=(T*)realloc(mass,sizeof(T)*(num+1));
        for(i=num+1;i>0;--i)
        *(mass+i)=*(mass+i-1);
    *(mass)=elem;
num++;}

InsertAt(int pos,T elem){
    int i;
    if (pos==0) Prepend(elem);
if (pos==num) Append(elem);
if ((pos!=0) and (pos!=num) and (num>pos)){
    mass=(T*)realloc(mass,sizeof(T)*(num+1));
        for(i=num;i>pos-1;--i)
        *(mass+i)=*(mass+i-1);
 *(mass+pos)=elem;
num++;}

}
};

template<typename T>
Test(Sequence <T> *a){
    Sequence <T> *b;
    bool flag=1;
    cout << "Длина начальной последовательности = " << a->GetLength();
    if(a->GetLength()==0) cout << " - Правильно\n";else{cout << " - Неправильно\n";flag=0;}
    cout << "Добавляем элемент 51\n";
    a->Append(51);
    cout << "Длина последовательности = " << a->GetLength();
    if(a->GetLength()==1) cout << " - Правильно\n";else{cout << " - Неправильно\n";flag=0;}
    cout << "Первый элемент последовательности = " << a->GetFirst();
    if(a->GetFirst()==51) cout << " - Правильно\n";else{cout << " - Неправильно\n";flag=0;}
    cout << "Последний элемент последовательности = " << a->GetLast();
    if(a->GetLast()==51) cout << " - Правильно\n";else{cout << " - Неправильно\n";flag=0;}
    cout << "Нулевой элемент последовательности = " << a->Get(0);
    if(a->Get(0)==51) cout << " - Правильно\n";else{cout << " - Неправильно\n";flag=0;}
    cout << "Добавляем элемент 33 в начало\n";
    a->Prepend(33);
    cout << "Длина последовательности = " << a->GetLength();
    if(a->GetLength()==2) cout << " - Правильно\n";else{cout << " - Неправильно\n";flag=0;}
    cout << "Первый элемент последовательности = " << a->GetFirst();
    if(a->GetFirst()==33) cout << " - Правильно\n";else{cout << " - Неправильно\n";flag=0;}
    cout << "Последний элемент последовательности = " << a->GetLast();
    if(a->GetLast()==51) cout << " - Правильно\n";else{cout << " - Неправильно\n";flag=0;}
    cout << "Первый по индексу элемент последовательности = " << a->Get(1);
    if(a->Get(1)==51) cout << " - Правильно\n";else{cout << " - Неправильно\n";flag=0;}
    cout << "Добавляем элемент 12 на место c индексом 1\n";
    a->InsertAt(1,12);
    cout << "Длина последовательности = " << a->GetLength();
    if(a->GetLength()==3) cout << " - Правильно\n";else{cout << " - Неправильно\n";flag=0;}
    cout << "Первый элемент последовательности = " << a->GetFirst();
    if(a->GetFirst()==33) cout << " - Правильно\n";else{cout << " - Неправильно\n";flag=0;}
    cout << "Последний элемент последовательности = " << a->GetLast();
    if(a->GetLast()==51) cout << " - Правильно\n";else{cout << " - Неправильно\n";flag=0;}
    cout << "Элемент последовательности с индексом 1 = " << a->Get(1);
    if(a->Get(1)==12) cout << " - Правильно\n";else{cout << " - Неправильно\n";flag=0;}
    cout << "Выделяем подпоследовательность с индексами 1-2\n";
    a->Remove(33);
    cout << "Длина последовательности = " << a->GetLength();
    if(a->GetLength()==2) cout << " - Правильно\n";else{cout << " - Неправильно\n";flag=0;}
    cout << "Первый элемент последовательности = " << a->Get(0) << "\nВторой элемент последовательности = " << a->Get(1);
    if((a->Get(1)==51) and (a->Get(0)==12)) cout << " - Правильно\n"; else{cout << " - Неправильно\n";flag=0;}
    cout << "Удаляем элемент 51\n";
    a->Remove(51);
    cout << "Длина последовательности = " << a->GetLength();
    if(a->GetLength()==1) cout << " - Правильно\n";else{cout << " - Неправильно\n";flag=0;}
    cout << "Первый элемент последовательности = " << a->GetFirst();
    if(a->GetFirst()==12) cout << " - Правильно\n";else{cout << " - Неправильно\n";flag=0;}
    cout << "Последний элемент последовательности = " << a->GetLast();
    if(a->GetLast()==12) cout << " - Правильно\n";else{cout << " - Неправильно\n";flag=0;}
    if(flag==1) cout << "======ТЕСТ ПРОЙДЕН УСПЕШНО======"; else cout << "======ТЕСТ HE ПРОЙДЕН======";
};

int main(){
    setlocale(0,"Russian");
    int e,d,z,f,u;
Array<int> a;int c=0;
List<int> b; int k=0;

cout << "Введите, что хотите сделать\n1)Работать с последовательностью\n2)Работать со списком\n3)Тестировать программу";

cin >> e;
if(e==1)do{
cout << "Введите, что хотите сделать\n1)Добавить элемент в конец\n2)Добавить элемент в начало\n3)Вывести длину последовательности\n4)Вывести первый элемент\n5)Вывести последний элемент\n6)Вывести элемент по номеру\n7)Вставить элемент на i позицию\n8)Удалить элемент\n9)Выделить подпоследовательность\n10)Вывести последовательность\n11)Завершить программу\n";
cin >> c;
if (c==1){cin >> d;a.Append(d);};
if (c==2){cin >> d;a.Prepend(d);}
if (c==3){cout << a.GetLength() << "\n";};
if (c==4){cout << a.GetFirst() << "\n";};
if (c==5){cout << a.GetLast() << "\n";};
if (c==6){cin >> d;cout <<a.Get(d);};
if (c==7){cin >> z;cin >> u; a.InsertAt(z,u);};
if (c==10){a.print();};
if (c==8){cin >> d;a.Remove(d);};
if (c==9){a.GetSubsequence(2,3);};
}while (c<11);
if (e==2) do {
cout << "Введите, что хотите сделать\n1)Добавить элемент в конец\n2)Добавить элемент в начало\n3)Вывести длину списка\n4)Вывести первый элемент\n5)Вывести последний элемент\n6)Вывести элемент по номеру\n7)Вставить элемент на i позицию\n8)Удалить элемент\n9)Выделить подпоследовательность\n10)Вывести список\n11)Завершить программу\n";
cin >> c;
if (c==1){cin >> z;b.Append(z);};
if (c==2){cin >> z;b.Prepend(z);}
if (c==3){cout << b.GetLength() << "\n";};
if (c==4){cout << b.GetFirst() << "\n";};
if (c==5){cout << b.GetLast() << "\n";};
if (c==6){cin >> z;cout <<b.Get(z);};
if (c==7){cin >> f;cin>> u;b.InsertAt(z,u);};
if (c==10){b.print();};
if (c==8){cin >> z;b.Remove(z);};
if (c==9){a.GetSubsequence(2,3);};
}while (c<11);
if (e==3)Test(&a);
return 0;
}
