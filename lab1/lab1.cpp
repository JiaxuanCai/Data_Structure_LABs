#include<iostream>
#include <stdio.h>
#include <cassert>
#include <stdlib.h>
#define Assert(a,b) assert((a)&&(b))
using namespace std;
#define defaultsize 999999
 
class item { // definition of data type class of one item of the polynomial
    public:
        double coef;
        int inde;
        item& operator = (const item& i ){ coef=i.coef; inde=i.inde;} // overload copy operator
        item(double c,int i) { coef=c;inde=i;}
        item(){}
        item& operator +(const item& i)  //overloaded plus operator
        {
          coef+=i.coef;
        }
        item& operator *(const item& i) //overloaded multipler operator
        {
          coef*=i.coef;
          inde+=i.inde;
        }
         
         
};
 
item operator *(const item& i1 ,const item& i2) //overloaded multipler operator for const item
{
  item i3;
  i3.coef=i1.coef*i2.coef;
  i3.inde=i1.inde+i2.inde;
  return i3;
}
 
bool operator == (const item& i1 , const item& i2) //overloaded == operator
{
    if(i1.inde==i2.inde) return true;
    else return false;  
}
 
bool operator > (const item& i1 , const item& i2) 
{
    if(i1.inde > i2.inde) return true;
    else return false; 
}
 
bool operator < (const item& i1 , const item& i2)
{
    if(i1.inde < i2.inde) return true;
    else return false; 
}
 
 
 
template <typename E> class node{ 
    private:
        static node<E>* freelist; // pointer to freelist head
    public:
        E element;
        node *next; // pointer to next node
        node *prev; //pointer to previous node
         
        node(const E& elemval, node* nextval=NULL)// constructor with only pointers
        {
            element=elemval;
            next=nextval;
        }
 
        node(node* nextval=NULL)// constructor with only pointers
        {
            next=nextval;
        }
 
        void* operator new(size_t){ // overloaded operator of 'new'
            if(freelist==NULL) return ::new node; // create space is freelist is empty
            node<E>* temp=freelist;
            freelist=freelist->next;
            return temp;
        }
 
        void operator delete(void* ptr){ ////overloaded delete operator
            ((node<E>*)ptr)->next=freelist;
            freelist=(node<E>*)ptr;
        }
};
 
template <typename E>
node<E>* node<E>::freelist=NULL;
 
template <typename E> class llist{
    private:
        node<E>* head;
        node<E>* tail;
        node<E>* curr;
        int cnt;
         
        void init() //initialiazation
        {
            curr=tail=head=new node<E>;
            cnt=0;
        } 
 
        void removeall() //delete the llist
        {
            while(head != NULL){
                curr=head;
                head=head->next;
                delete curr;
            }
        }
 
 
        public:
            llist (int size=defaultsize) {init();} //constructors
 
            ~llist() {removeall();}
 
            void clear() { removeall(); init();}
             
            void insert (const E& it) //insert a element at current place
            {
                curr->next=new node<E>(it, curr->next);
                if(tail==curr) tail=curr->next;
                cnt++;
            }
             
            void append(const E& it) //add a element to the end
            {
                tail=tail->next=new node<E>(it, NULL);
                cnt++;
            }
 
            void sortadd(const E& it) // add a element as sorted consequence
            {
                int flag=0; // to indicate whether the element has been inserted
                if(head==tail) insert(it); // if the llist is empty
                else{
                  movetostart(); //iterator through the llist to find where to insert the current element
                  while(currentposition()!=getlong())
                  {
                    if( it > getvalue() ){ //if the inde of current element is larger , then insert it
                      insert(it);
                      flag=1;
                      break;
                    }
 
                    if(it == getvalue()){ //Hebing the element if the index is equal.
                      E temp=remove();
                      sortadd(temp+it); 
                      flag=1;
                      break; //break from the circulation
                    }
 
                    next();
                  }
                  if(flag==0) append(it);// if the element has not been inserted, add it to the end of the llist.
                }
            }
 
            E remove() //remove the element from llist
            {
                Assert(curr->next !=NULL, "Empty list"); //assertion
                E it= curr->next->element; 
                node<E>* ntemp=curr->next;
                if(curr->next==tail) tail=curr;
                curr->next=curr->next->next;
                delete ntemp;
                cnt--;
                return it; //remember and return the value
            }
 
            void movetostart() {curr=head;} //operation towards the curr pointer
              
            void movetoend() {curr=tail;}  //operation towards the curr pointer
 
            void prev() { if(curr!=head) curr=curr->prev;} //operation towards the curr pointer
 
            void next() { if(curr!=tail) curr=curr->next;} //operation towards the curr pointer
             
            int getlong() {return cnt;} //get the length of the llist
 
            int currentposition() const //get current position
            {
                node<E>* temp=head;
                int i;
                for(i=0;curr!=temp;i++) temp=temp->next;
                return i;
            }
             
            void movetopos(int pos) //move to a specified position
            {
                Assert ((pos>=0)&&(pos<=cnt) , "Pos out of range");
                curr=head;
                for(int i=0;i<pos;i++) curr=curr->next;
            }
 
            const E& getvalue() const //get the current value
            {
                Assert( curr->next != NULL , "No value");
                return curr->next->element;
            }
};
 
llist<item> padd (llist<item> i1 , llist<item> i2 ) // and two polinomials
{
  llist<item> inew; //the result
  i1.movetostart(); 
  i2.movetostart(); 
  while(i1.currentposition() != i1.getlong()) //iterate through both polinomials
  {
    inew.sortadd( i1.remove()); //using sortadd algorithm to make the code very easy  
  }
 
  while(i2.currentposition() != i2.getlong())
  {
    inew.sortadd( i2.remove()); //similar to upper codes
  }
  return inew; // return the result
}
 
llist<item> pmult (llist<item>& i1 , llist<item>& i2 ) // multiply two polinomials
{
  llist<item> inew; // the result llist
  i1.movetostart(); //move to start both lists
  i2.movetostart();
  while(i1.currentposition()!=i1.getlong()) //the first circulation
  {
      item tmp;
      i2.movetostart();//envey time move i2 to start
      while(i2.currentposition()!=i2.getlong()) //the second layer of circulation to iterate through i2
      {
        tmp=i1.getvalue() * i2.getvalue();// using overloaded *
        inew.sortadd(tmp); //directly sortadd
        i2.next();
      }
      i1.next();
  }
  return inew; // return the result
}
 
 
int main()
{
  llist<item> l1,l2; //the polinomials
  int a,b;
  scanf("%d%d",&a,&b);//to get the polinomials
  for(int i=0;i<a;i++)
  {
    double t1;
    int t2;
    scanf("%lf %d",&t1,&t2);
    item t(t1,t2);
    l1.sortadd(t);
  }
 
  for(int i=0;i<b;i++)//to get the polinomials
  {
    double t1;
    int t2;
    scanf("%lf %d",&t1,&t2);
    item t(t1,t2);
    l2.sortadd(t);
  }
 
   
  llist<item> lnew1=pmult(l1,l2); //call the functions to calculate
  llist<item> lnew=padd(l1,l2); //call the functions to calculate
   
   
   cout<<lnew.getlong()<<endl; //print the result
   lnew.movetostart();
   while(lnew.currentposition()!=lnew.getlong())
   {
     cout<<lnew.getvalue().coef<<' '<<lnew.getvalue().inde<<endl;
     lnew.next();
   }
    
   
   cout<<lnew1.getlong()<<endl;//print the result
   lnew1.movetostart();
   while(lnew1.currentposition()!=lnew1.getlong())
   {
     cout<<lnew1.getvalue().coef<<' '<<lnew1.getvalue().inde<<endl;
     lnew1.next();
   }
  exit(0); //return 0 to exit program
}