#include<iostream>
#include<fstream>
#include<cstdlib>
#define SIZE 10000
using namespace std;
int main()
{
	int n,i;float num[SIZE];
	cout<<"\nEnter the number of elements:";
	cin>>n;
	for(i=0;i<n;i++)
	{
		num[i]=static_cast<float>(rand())/(static_cast<float>(RAND_MAX/500));
		cout<<num[i]<<"\t";
	}
	cout<<endl;
	ofstream out("elements");
	out.write((char*)&n,sizeof n);
	out.write((char *)&num,sizeof num);
	out.close();
	ifstream in("elements");
	in.read((char*)&num,sizeof num);
	for(i=1;i<=n;i++)
		cout<<num[i]<<"\t";
	int length=in.tellg();
	cout<<"\n"<<length;
}
