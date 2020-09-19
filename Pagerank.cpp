//============================================================================
// Name        : Pagerank.cpp
// Author      : Bhawana
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
struct node{long long int rv;long long int cv; node *rlink; node *dlink; node *ulink; node *llink;long long int increase;};
/*
    1) r=row headnode.
      p and p1 are to add nodes in the row.
    2)c=column head node.
      t and t1 are to add nodes in the column.
    3)program  is doubly multi linked circular list.
    4)rv=raw value and cv=column value.
    5)rlink=right link, llink=left link, dlink=down link, ulink= up link.
    6)increase= no. of links between a m[i][j].
    7)q=no. of operation in a test case.
    8)ocode= operation code.
    9)s=super head node.
 */
long long int x,q;
int ocode;
node *n,*r,*c,*p,*p1,*t1,*t,*s;

//function to take first set of entry
void initialdata(long long int i, long long int j)
{
        r=new node; r->rv=i; r->cv=j;
        c=new node; c->cv=j; c->rv=i;
        s=new node; s->rv=0; s->cv=0; s->increase=0;
        n=new node; n->rv=i; n->cv=j; n->increase=1;
        s->rlink=c; s->dlink=r; s->llink=c; s->ulink=r;
        r->rlink=n; r->ulink=s; r->llink=n; r->dlink=s;
        c->dlink=n; c->ulink=n; c->llink=s; c->rlink=s;
        n->rlink=r; n->dlink=c; n->ulink=c; n->llink=r;
        p=r; p1=s->ulink;                  //p is first node of row head and p1 is last node of row head
        t=c; t1=s->llink;                  //t is first node of column head and t1 is last node of column head
}

//function to create new head nodes
bool createheadnode(long long int i,long long int j)
{
        if(r!=s and p!=s and p1!=s and c!=s and t!=s and t1!=s)
        {                                                        //p is first node of row head and p1 is last node of row head
            while(r->rv < i and p1->rv >i)
            {
                r=r->dlink;              //r move down the row heads
                p1=p1->ulink;            //p1 move up the row  heads
            }
            if(r->rv > i)                //if r gets matched the condition.
            {
                p=r;                     //assign r to p
                r=new node;              //insert the new row head between p and p1.
                r->rv=i;
                r->cv=j;
                p1=p->ulink;
                r->dlink=p; r->ulink=p1; p->ulink=r; p1->dlink=r;
            }
            else if(p1->rv < i)          //if p1 gets matched the condition.
            {
                r=new node;             //insert the new row head between p1 and p.
                r->rv=i;
                r->cv=j;
                p=p1->dlink;
                r->ulink=p1;  p1->dlink=r; p->ulink=r; r->dlink=p;
                p=p1;                   //assign p1 to p
            }
            else
            {
                if(r->rv == i)
                {
                    p=r;                //assign r to p
                }
                else
                {
                    p=p1;              //assign p1 to p
                }
            }
           while(c->cv < j and t1->cv > j)     //t is first node of column head and t1 is last node of column head
            {
                c=c->rlink;                    //c move right the column heads
                t1=t1->llink;                  //t1 move left the column heads
            }
            if(c->cv > j)                      //if c gets matched the condition.
            {
                t=c;                           //assign t to c
                c=new node;                    //insert the new column head between t and t1.
                c->cv=j;
                c->rv=i;
                t1=t->llink;
                c->rlink=t; c->llink=t1; t1->rlink=c; t->llink=c;
            }
            else if (t1->cv < j)               //if t1 gets matched the condition.
            {
                c=new node;                    //insert the new column head between t1 and t.
                c->cv=j;
                c->rv=i;
                t=t1->rlink;
                c->rlink=t; c->llink=t1; t1->rlink=c; t->llink=c;
                t=t1;
            }
            else
            {
                if(c->cv == j)
                {
                    t=c;                     //assign t to c
                }
                else
                {
                    t=t1;                   //assign t1 to c
                }
            }
            return true;
        }
        else
         {
            delete [] s;
            initialdata( i, j);
            return false;
        }
}
void AddLink()
{
    long long int i,j;
    cin>>j>>i;
    if(createheadnode(i,j)==true)   //call of function to create heads nodes.
    {
        n=new node;
        n->rv=i;
        n->cv=j;
        if(p->rv==i and t->cv==j)         //no new heads is created.
        {
            p1=p->llink; t1=t->ulink;
            r=p->rlink;   c=t->dlink;
            while (r->cv < j and p1->cv > j )
            {
                r=r->rlink;            //r move right the row.
                p1=p1->llink;          //p1 move left the row.
            }
            if(r->cv >= j)
            {
                if(r->cv==j)
                {
                    r->increase+=1;             //if m[i][j] is present increase by one.
                }
                else                         // else insert new node between t ,t1 and p, p1.
                {
                    p=r->llink;
                    n->rlink=r; n->llink=p; p->rlink=n; r->llink=n;
                    n->increase=1;
                    while(c->rv < i and t1->rv > i)
                    {
                        c=c->dlink;
                        t1=t1->ulink;
                    }
                    if(c->rv > i)
                    {
                        t=c->ulink;
                        n->dlink=c; n->ulink=t; t->dlink=n; c->ulink=n;
                    }
                    else
                    {
                        c=t1->dlink;
                        t=c->ulink;
                        n->dlink=c; n->ulink=t; t->dlink=n; c->ulink=n;
                    }
                }
            }
            else if(p1->cv  <= j)
            {
                if(p1->cv==j)
                {
                    p1->increase+=1;
                }
                else
                {
                    r=p1->rlink; p=r->llink;
                    n->rlink=r; n->llink=p; p->rlink=n; r->llink=n;
                    n->increase=1;
                    while(c->rv < i and t1->rv > i)
                    {
                        c=c->dlink;
                        t1=t1->ulink;
                    }
                    if(c->rv > i)
                    {
                        t=c->ulink;
                        n->dlink=c; n->ulink=t; t->dlink=n; c->ulink=n;
                    }
                    else
                    {
                        c=t1->dlink;
                        t=c->ulink;
                        n->dlink=c; n->ulink=t; t->dlink=n; c->ulink=n;
                    }
                }
            }
        }
        else if(p->rv!=i and t->cv!=j)              // both new heads are created.
        {
            n->rlink=r; n->dlink=c; n->ulink=c; n->llink=r;      //link new node to new row and column heads.
            r->rlink=n; r->llink=n; c->dlink=n; c->ulink=n;
            n->increase=1;
        }
        else if(p->rv==i and t->cv!=j)         //only column head is created and insert new node in proper place
        {
            p1=p->llink; r=p->rlink;
            while(r->cv < j and p1->cv > j)
            {
                r=r->rlink;
                p1=p1->llink;
            }
            if(r->cv >j)
            {
                p=r->llink;
                n->rlink=r; n->llink=p; n->dlink=c; n->ulink=c;
                p->rlink=n; r->llink=n; c->dlink=n; c->ulink=n;
                n->increase=1;
            }
            else if(p1->cv < j)
            {
                p=p1->rlink;
                n->rlink=p; n->llink=p1; n->dlink=c; n->ulink=c;
                p1->rlink=n; p->llink=n; c->dlink=n; c->ulink=n;
                n->increase=1;
            }
        }
        else if(p->rv!=i and t->cv==j)         //only row head is created and insert new node in proper place
        {
            t1=t->ulink; c=t->dlink;
            while(c->rv < i and t1->rv > i)
            {
                c=c->dlink;
                t1=t1->ulink;
            }
            if(c->rv > i)
            {
                t=c->ulink;
                n->rlink=r; n->llink=r; n->dlink=c; n->ulink=t;
                t->dlink=n; c->ulink=n; r->rlink=n; r->llink=n;
                n->increase=1;
            }
            else if(t1->rv < i)
            {
                t=t1->dlink;
                n->rlink=r; n->llink=r; n->dlink=t; n->ulink=t1;
                t1->dlink=n; t->ulink=n; r->rlink=n; r->llink=n;
                n->increase=1;
            }
        }
    }

    r=s->dlink;
    c=s->rlink;
    p=r; p1=s->ulink;
    t=c; t1=s->llink;
}

void TOSHORTMORE(long long int value,int ocode)
{
   if(r->increase==1 and ocode==2)          //delete that m[i][j]
   {
       p=r->llink;   p1=r->rlink;   t=r->ulink; t1=r->dlink;
       p->rlink=p1;  p1->llink=p;    t->dlink=t1; t1->ulink=t;
       delete [] r;
       if(p==p1)                 //delete the row head if no element is present in that row.
       {
           r=p; p=r->ulink; p1=r->dlink;
           p->dlink=p1; p1->ulink=p;
           if(s!=r){delete [] r;}
       }
       if(t==t1)                //delete the column head if no element is present in that column.
       {
           c=t; t=c->llink; t1=c->rlink;
           t->rlink=t1; t1->llink=t;
           if(s!=c) {delete [] c;}
       }
   }
   else if(ocode==2)            //decrease the no. link if it is greater than 1
   {
       if(r->increase>1){r->increase--;}
   }
   else if(ocode==3)
   {
       cout<<r->increase<<endl;
   }

}
void toshortthedeletefunctionrow(long long int value,int ocode)
{
    while(r->cv < value and p1->cv >value )      //traverse in the row to find that m[i][j]
    {
        r=r->rlink;
        p1=p1->llink;
    }
    if(r->cv==value)
    {
        TOSHORTMORE(value,ocode);    //call to delete or retrive node according to the operation code
    }
    else if(p1->cv==value)
    {
        r=p1;/////very imp. conversion.
        TOSHORTMORE(value,ocode);
    }
    else
    {
        if(ocode==3)
        {
            cout<<0<<endl;
        }
    }

}

void DeleteLink(int ocode)
{
    long long int j,i;
    cin>>j>>i;
    while(r->rv < i and p1->rv > i)   //find the row head in which element may present
    {
        r=r->dlink;
        p1=p1->ulink;
    }
    if (r->rv==i)
    {
        p=r; p1=p->llink;
        r=p->rlink;
        toshortthedeletefunctionrow(j,ocode);  //call to find the m[i][j] after finding that row head.
    }
    else if(p1->rv==i)
    {
        p=p1;  r=p->rlink;  p1=p->llink;
        toshortthedeletefunctionrow(j,ocode);  //call to find the m[i][j] after finding that row head.
    }
    else
    {
        if(ocode==3)
        {
            cout<<0<<endl;
        }
    }
    r=s->dlink;
    c=s->rlink;
    p=r; p1=s->ulink;
    t=c; t1=s->llink;
}


long long int RetrieveRowSumUptoKthColumn()
{
    long long int RetrieveRowSumUptoKthColumn=0,i,k;
    cin>>i>>k;
    if(r!=s and p!=s and p1!=s and c!=s and t!=s and t1!=s)
    {
        while(r->rv < i and p1->rv > i)      //find the row head whose summation is required.
        {
            r=r->dlink;
            p1=p1->ulink;
        }
        if(r->rv==i)                        //if r get matched
        {
            p=r;
            r=r->rlink;
            while(r->cv< k and p!=r)       //summation upto kth column
            {
                RetrieveRowSumUptoKthColumn+=r->increase;
                r=r->rlink;
            }
            r=s->dlink;
            c=s->rlink;
            p=r; p1=s->ulink;
            t=c; t1=s->llink;
            return RetrieveRowSumUptoKthColumn;
        }
        else if(p1->rv==i)
        {
            p=p1;
            r=p1;
            r=r->rlink;
            while(r->cv < k and p!=r)
            {
                RetrieveRowSumUptoKthColumn+=r->increase;
                r=r->rlink;
            }
            r=s->dlink;
            c=s->rlink;
            p=r; p1=s->ulink;
            t=c; t1=s->llink;
            return RetrieveRowSumUptoKthColumn;

        }
        else
        {
            r=s->dlink;
            c=s->rlink;
            p=r; p1=s->ulink;
            t=c; t1=s->llink;
            return 0;
        }
    }
    else
    {
         r=s->dlink;
         c=s->rlink;
         p=r; p1=s->ulink;
         t=c; t1=s->llink;
         return 0;
    }
}










long long int RetrieveColumnSumUptoKthRow()
{
    long long  int RetrieveColumnSumUptoKthRow=0,j,k;
    cin>>j>>k;
    if(r!=s and p!=s and p1!=s and c!=s and t!=s and t1!=s)
    {
        while(c->cv < j and t1->cv > j)     //find the column head whose summation is required.
        {
            c=c->rlink;
            t1=t1->llink;
        }
        if(c->cv==j)                  //if c get matched
        {
            t=c;
            c=c->dlink;
            while(c->rv < k and t!=c)    //summation upto kth row
            {
                RetrieveColumnSumUptoKthRow+=c->increase;
                c=c->dlink;
            }
            r=s->dlink;
            c=s->rlink;
            p=r; p1=s->ulink;
            t=c; t1=s->llink;
            return RetrieveColumnSumUptoKthRow;
        }
        else if(t1->cv==j)
        {
            t=t1;
            c=t1;
            c=c->dlink;
            while(c->rv < k and t!=c)
            {
                RetrieveColumnSumUptoKthRow+=c->increase;
                c=c->dlink;
            }
            r=s->dlink;
            c=s->rlink;
            p=r; p1=s->ulink;
            t=c; t1=s->llink;
            return RetrieveColumnSumUptoKthRow;

        }
        else
        {
            r=s->dlink;
            c=s->rlink;
            p=r; p1=s->ulink;
            t=c; t1=s->llink;
            return 0;
        }
    }
    else
    {
         r=s->dlink;
         c=s->rlink;
         p=r; p1=s->ulink;
         t=c; t1=s->llink;
         return 0;
    }
}




void MultiplyVector()
{
    long long  int termM,element;
    cin>>termM;
    long long int arr[termM]={0};
    if(r!=s and p!=s and p1!=s and c!=s and t!=s and t1!=s)
    {
        t=s;
        for (long long int x=0; x<termM; x++)
        {
            c=t;
            c=c->rlink;
            cin>>element;
            if(c->cv==x)
            {
                t=c;
                c=c->dlink;
                while(t!=c and c->rv < termM)      //multiply the every element of a column to element if matched
                {

                    arr[c->rv]+=c->increase * element;        //store the result in corresponding row value
                    c=c->dlink;
                }
            }
        }
        for (long long int  x=0; x<termM-1; x++)
        {
            cout<<arr[x]<<" ";
        }
        cout<<arr[termM-1]<<endl;
   }
    else
    {
        for (long long int x=0; x<termM-1; x++)
        {
            cin>>element;
            cout<<arr[x]<<" ";
        }
        cout<<arr[termM-1]<<endl;
    }
    r=s->dlink;
    c=s->rlink;
    p=r; p1=s->ulink;
    t=c; t1=s->llink;
}


int main()
{
    long long int i,j,y=0;
    cin>>q;
    cin>>ocode;
    while(ocode!=1 and y!=q)
    {
        cin>>j>>i;
        if(ocode==3)
        {
            cout<<0<<endl;
        }
        else if(ocode==4)
        {
            cout<<0<<endl;
        }
        else if(ocode==5)
        {
            cout<<0<<endl;
        }
        else if(ocode==6)
        {
             while(j>=2)
             {
                 cin>>i;
                 cout<<0<<" ";
                 j--;
             }
             if(j==1){cout<<0<<endl;}
         }
        cin>>ocode;
        y++;
    }
    cin>>j>>i;
    initialdata(i,j);           // call to take initial set of entry.
    for (x=y+1;x<q;x++)
    {
        cin>>ocode;
        if(ocode==1)
        {
            AddLink();
        }
        else if(ocode==2)
        {
            DeleteLink(2);
        }
        else if(ocode==3)
        {
            DeleteLink(3);
        }
        else if(ocode==4)
        {
            cout<<RetrieveRowSumUptoKthColumn()<<endl;
        }
        else if(ocode==5)
        {
            cout<<RetrieveColumnSumUptoKthRow()<<endl;
        }
        else if(ocode==6)
        {
            MultiplyVector();
        }
    }
}
