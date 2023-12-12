#include <iostream>
using namespace std;
struct sv
{
	int ms;
	float dt;
	float dth;
	sv *next;
};
int rong(sv *first, sv *last)
{
    return (first == NULL);
}
void themdau( sv x, sv *&first, sv *&last)
{
	 sv *p;
    p=new sv;
    p->ms=x.ms;
    p->dth=x.dth;
    p->dt=x.dt;
    p->next=NULL;
    if(rong(first,last))
    {
        first = p;
        last = p;
    }
    else
    {
        p->next=first;
        first=p;
    }
}
void themptdau( sv *&first, sv *&last)
{
	sv x;
	{
		cout<<"MS cua sv dau : ";
        cin>>x.ms;
        cout<<"DT cua sv dau : ";
        cin>>x.dt;
        cout<<"DTH cua  sv dau : ";
        cin>>x.dth;
        themdau(x,first,last);
    }
}
void themcuoi( sv x, sv *&first, sv *&last)
{
    sv *p;
    p=new sv;
    p->ms=x.ms;
    p->dth=x.dth;
    p->dt=x.dt;
    p->next=NULL;
    if(rong(first,last))
    {
        first = p;
        last = p;
    }
    else
    {
        last->next=p;
        last =p;
    }
}
void themptcuoi( sv *&first, sv *&last)
{
	sv x;
	{
		cout<<"MS cua sv cuoi : ";
        cin>>x.ms;
        cout<<"DT cua sv cuoi : ";
        cin>>x.dt;
        cout<<"DTH cua  sv cuoi : ";
        cin>>x.dth;
        themcuoi(x,first,last);
    }
}
void xoaptdau(sv *&first, sv *&last)
{ 
	sv *p;
	if (first->next==NULL)
	{
		delete first;
		first=NULL;
		last=NULL;
	}
	else if (rong(first,last))
	{
		cout<<"khong the xoa"<<endl;
	}
	else
	{
		p=first;
		first=p->next;
		delete p;
		p=NULL;
	}
}
void xoaptcuoi(sv *&first, sv*&last)
{
	sv *p;
	if (first->next==NULL)
	{
		delete first;
		first =NULL;
		last=NULL;
	}
	else if (rong(first,last))
	{
		cout<<"khong the xoa"<<endl;
	}
	else
	{
		p=first;
		while(p->next!=last)
		{
			p=p->next;
		}
		last=p;
		p=p->next;
		delete p;
		p=NULL;
		last->next=NULL;
	}
}
void nhap(int n, sv *&first, sv *&last)
{
    sv x;
    for (int i=0;i<n;i++)
    {
        cout<<"MS cua sv thu "<<i+1<<": ";
        cin>>x.ms;
        cout<<"DT cua sv thu "<<i+1<<": ";
        cin>>x.dt;
        cout<<"DTH cua  sv thu "<<i+1<<": ";
        cin>>x.dth;
        themcuoi(x,first,last);
    }
}
void xuat(sv *first, sv *last)
{
	cout<<"MS\t\tDT\t\tDTH"<<endl;
	sv *p=first;
	if(!rong(first,last))
		while(p!=NULL)
		{
			cout<<p->ms<<"\t\t"<<p->dt<<"\t\t"<<p->dth<<endl;
			p=p->next;
		}
	else	cout<<"ds rong";
}
int main()
{
	sv *first=NULL;
	sv *last=NULL;
	int n;
	cout<<"so luong sv ban dau ";
	cin>>n;
	nhap(n,first,last);
	xuat(first,last);
	themptdau(first,last);
	xuat(first,last);
	xoaptdau(first,last);
	themptcuoi(first,last);
	xuat(first,last);
	xoaptcuoi(first,last);
	cout<<"danh sach sau khi xoa dau "<<endl;
	xuat(first,last);
	xoaptcuoi(first,last);
	cout<<"danh sach sau khi xoa cuoi "<<endl;
	xuat(first,last);
}
