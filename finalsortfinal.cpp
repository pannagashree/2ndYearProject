//Program to compare the execution time for insertion sort with and without binary search and implementing it with linked list 
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cstring>
#include<fstream>
#include<sys/time.h>
using namespace std;
long timediff(struct timeval *time2,struct timeval *time1)
{
	long t1,t2;
	t2=time2->tv_sec*1000000+time2->tv_usec;
	t1=time1->tv_sec*1000000+time1->tv_usec;
	return t2-t1;
}
template <class GT>
struct node
{
	GT data;
	int number;
	node *llink,*rlink;
};
template <class GT>
class sorting
{
	static int n;
	GT *a;
	node<GT> *head;
	public:
	sorting()
	{
		head=new node<GT>;
		head->llink=head->rlink=NULL;
		head->number=-1;
	}
	sorting(const sorting &original);
	void insert(char []);
	int binary_search_arr(GT &,int,int);
	int binary_search_list(GT &,node<GT> *,node<GT> *);
	void insertion_sort_arr();
	void insertion_sort_arrbin();
	void insertion_sort_list();
	void insertion_sort_listbin();
	void display();
	void display_arr();
	void display_list();
};
template <class GT>
int sorting<GT>::n;
template <class GT>
sorting<GT>::sorting(const sorting<GT> &original)
{

	a=new GT[n];
	head=new node<GT>;
	head->llink=head->rlink=NULL;
	head->number=-1;
	node<GT> *temp=head;
	for(int i=0;i<n;i++)
	{
		node<GT> *newnode;
		*(a+i)=original.a[i];
		newnode=new node<GT>;
		newnode->data=original.a[i];
		newnode->number=i;
		newnode->rlink=NULL;
		temp->rlink=newnode;
		newnode->llink=temp;
		temp=newnode;
	}
}
template <class GT>
void sorting<GT>::insert(char items[10])
{
	ifstream in(items);
	in.read((char *)&n,sizeof n);
	a=new GT[n];
	cout<<"size of a is "<<sizeof(*a)<<endl;
	in.read((char *)a,n*sizeof(*a));
	int i;
	node<GT> *temp=head;
	for(i=0;i<n;i++)
	{
		node<GT> *newnode;
		newnode=new node<GT>;
		newnode->data=*(a+i);
		newnode->number=i;
		newnode->rlink=NULL;
		temp->rlink=newnode;
		newnode->llink=temp;
		temp=newnode;
	}
}
template <class GT>
void sorting<GT>::insertion_sort_arr()
{
	GT temp;int i,j;
	for(i=1;i<n;i++)
	{
		j=i;
		while((j>=1)&&(*(a+j)<*(a+(j-1))))
		{
			temp=*(a+j);
			*(a+j)=*(a+(j-1));
			*(a+(j-1))=temp;
			j=j-1;
		}
	}
}
template <class GT>
int sorting<GT>::binary_search_arr(GT &item,int low,int high)
{
	if(high<=low)
		return (item>a[low])?low+1:low;
	int mid=(low+high)/2;
	if(item==*(a+mid))
		return mid+1;
	if(item>*(a+mid))
		return binary_search_arr(item,mid+1,high);
	return binary_search_arr(item,low,mid-1);
}
template <class GT>
int sorting<GT>::binary_search_list(GT &item,node<GT> *low,node<GT> *high)
{
	node<GT> *mid,*i;
	int m;
	if(high->number<=low->number)
		return (item>(low->data))?(low->number)+1:low->number;
	m=((low->number)+(high->number))/2;
	for(i=low;i!=high;i=i->rlink)
	{
		if(i->number==m)
			mid=i;
	}
	if(item==mid->data)
		return (mid->number);
	if(item>mid->data)
		return binary_search_list(item,mid->rlink,high);
	return binary_search_list(item,low,mid->llink);
}	
template <class GT>
void sorting<GT>::insertion_sort_arrbin()
{
	int i,loc,j,k;GT selected;
	for(i=1;i<n;i++)
	{
		j=i-1;
		selected=*(a+i);
		loc=binary_search_arr(selected,0,j);
		while(j>=loc)
		{
			*(a+(j+1))=*(a+j);
			j--;
		}
		*(a+(j+1))=selected;
	}
}
template <class GT> 
void sorting<GT>::insertion_sort_list()
{
	int m;
	node<GT> *cur;
	cur=head->rlink;
	if(cur->rlink==NULL)
		return;
	node<GT> *ptr,*temp;
	cur=cur->rlink;
	while(cur!=NULL)
	{
		m=0;
		ptr=cur;

		temp=cur->llink;
		cur=cur->rlink;
		while(temp!=NULL&&temp->data>ptr->data)
		{
			m++;
			temp=temp->llink;
		}
		if(m)
		{
			ptr->llink->rlink=ptr->rlink;
			if(ptr->rlink!=NULL)
				ptr->rlink->llink=ptr->llink;
			if(temp==NULL)
			{
				temp=head->rlink;
				ptr->llink=NULL;
				ptr->rlink=temp;
				ptr->rlink->llink=ptr;
			}
			else
			{
				temp=temp->rlink;
				temp->llink->rlink=ptr;
				ptr->llink=temp->llink;
					temp->llink=ptr;
				ptr->rlink=temp;
			}
		}
	}
}

template <class GT>
void sorting<GT>::insertion_sort_listbin()
{
	node<GT> *i=head->rlink->rlink;
	node<GT> *j;
	GT selected;
	int loc;
	for(;i!=NULL;i=i->rlink)
	{
		j=i->llink;
		selected=i->data;
		loc=binary_search_list(selected,head->rlink,j);
		while((j->number)>=loc)
		{
			j->rlink->data=j->data;
			j=j->llink;
		}
		j->rlink->data=selected;
	}
}

template <class GT>
void sorting<GT>::display()
{
	cout<<"Contents of array\n";
	for(int i=0;i<n;i++)
		cout<<*(a+i)<<"\t";
	cout<<"\n";
	cout<<"Contents of list\n";
	node<GT> *temp=head->rlink;
	for(;temp;temp=temp->rlink)
		cout<<temp->data<<"\t";
	cout<<"\n";
	
}
template <class GT>
void sorting<GT>::display_arr()
{
	cout<<"Contents of array\n";
	for(int i=0;i<n;i++)
		cout<<*(a+i)<<"\t";
	cout<<"\n";
}
template <class GT>
void sorting<GT>::display_list()
{
	cout<<"Contents of list\n";
	node<GT> *temp=head->rlink;
	for(;temp;temp=temp->rlink)
		cout<<temp->data<<"\t";
	cout<<"\n";
}
int main(int argc,char *argv[])
{
	struct timeval time1,time2,time3,time4,time5,time6;
	sorting<float> obj1;
	obj1.insert(argv[1]);
	cout<<"\nObject1 contents\n";
	obj1.display();
	sorting<float> obj2=obj1;
	cout<<"\nObject2 contents\n";
	obj2.display();
	cout<<"\nCalling the array sorting function for object1\n";
	gettimeofday(&time1,NULL);
	obj1.insertion_sort_arr();
	gettimeofday(&time2,NULL);
	obj1.display_arr();
	cout<<"Time taken for array sorting using original function insertion sort "<<timediff(&time2,&time1);
	cout<<"\n\nCalling the array sorting function with binary search for object2\n";
	gettimeofday(&time3,NULL);
	obj2.insertion_sort_arrbin();
	gettimeofday(&time4,NULL);
	obj2.display_arr();
	cout<<"Time taken for array sorting using binary search for insertion sort "<<timediff(&time4,&time3);
	cout<<"\n\nCalling the list sorting function for object\n";
	gettimeofday(&time5,NULL);
	obj1.insertion_sort_list();
	gettimeofday(&time6,NULL);
	obj1.display_list();
	cout<<"Time taken for list sorting using insertion sort "<<timediff(&time6,&time5);
	
}
	
