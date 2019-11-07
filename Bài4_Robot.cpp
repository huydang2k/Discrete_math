#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std; 
struct ver_type {   //xay dung do thi G' voi cac dinh la mot nut gom 2 truong: loc1 la vi tri robot 1, loc2 2 la vi tri robot 2
	int loc1;
	int loc2;
};

int a,b,c,d,r,n,m;
vector <vector <int> > edge1;  //canh cua do thi ban dau
vector <vector <int> > w;      //trong so
vector < ver_type > ver;    //dinh cua do thi G'
vector <int> dis;         
vector < vector < int> > edge2;  //canh cua do thi G'
vector <int> pre;
int heap[100];    // mang heap co chuc nang nhu hang doi uu tien
queue <int> q;
stack <int> path;  //lich di chuyen

int bd=-1;
int kt=-1;

int deletemin(){  //tra ve phan tu k co do uu tien cao nhat trong heap
int min_ind=-1;
 for (int k=0;k<n;k++) if (( (min_ind==-1) && (heap[k]>=0) ) || ( (heap[k]>=0) && (heap[k]<min_ind) )) min_ind=heap[k];
 for (int k=0;k<n;k++) if ( (dis[k]==min_ind) && (dis[k]>=0) &&(heap[k]!=-2))  {
 	return k;
 }
 return 0;
}
bool done_djstra(){ //kiem tra tinh dung thuat toan dijtra
	for (int k=0;k<n;k++) if (heap[k]!=-2) return false;
	return true;
}

void djstra(int i){
	int u=0;
	dis[i]=0; heap[i]=0; 
	while(!done_djstra()) {
		u=deletemin();
		heap[u]=-2;  //mot dinh u coi nhu duoc lay ra khoi hang doi khi heap[u]=-2
		for (int k=0;k<=edge1[u].size()-1;k++) {
			if (dis[edge1[u][k]]==-1) {
			
				dis[edge1[u][k]]=dis[u]+w[u][k];
				heap[edge1[u][k]]=dis[u]+w[u][k]; 
			}
			else if ( (dis[edge1[u][k]]>dis[u]+w[u][k])) 
			 { 
			 dis[edge1[u][k]]=dis[u]+w[u][k];
			  heap[edge1[u][k]]=dis[u]+w[u][k]; 
		}
		}
	}
}

int check(int i,int j){ //tra ve khoang cach giua 2 dinh i va j
	for (int k=0;k<n;k++) dis[k]=-1;
	for (int k=0;k<n;k++) heap[k]=-1;
	djstra(i);
	return dis[j];
}

void input(){
	cin>>n; cin>>m;
	edge1.resize(n);
	w.resize(n);
	dis.resize(n);
	for (int i=1;i<=m;i++) {
		int t1,t2,l;
		cin>>t1; cin>>t2;cin>>l;
		edge1[t1].push_back(t2);
		edge1[t2].push_back(t1);
		w[t1].push_back(l);
		w[t2].push_back(l);
	}
	cin>>a;cin>>b;cin>>c;cin>>d;cin>>r;
}
void make_ver(){ //tao dinh cua do thi G'
	for (int i=0;i<n-1;i++)
	 for (int j=i+1;j<n;j++)
	  if ((i!=j)&&(check(i,j)>r)) //neu i khac j va khoang cach (i,j)>=r thi cap (i,j) va (j.i) la 2 dinh cua G'
	   {
	  	ver.resize(ver.size()+2);
	  	ver[ver.size()-2].loc1=i;
	  	ver[ver.size()-2].loc2=j;
	  	ver[ver.size()-1].loc1=j;
	   	ver[ver.size()-1].loc2=i;
	  	 }
}
bool is_edge1(int u,int v) { //kiem tra u v co phai 2 dinh ke cua do thi ban dau
	for (int i=0;i<=edge1[u].size()-1;i++) 
	 if (edge1[u][i]==v) return true;
	 return false;
}
void make_edge2(){ //tao canh cua do thi G'
	for (int i=0;i<ver.size()-1;i++)
	 for(int j=i+1;j<ver.size();j++)
	 if (((ver[i].loc1==ver[j].loc1)&&(is_edge1(ver[i].loc2,ver[j].loc2)))||((ver[i].loc2==ver[j].loc2)&&(is_edge1(ver[i].loc1,ver[j].loc1))))
	   {
	   	edge2[i].push_back(j);
	   	edge2[j].push_back(i);
	   }
}

void bfs(int u) { //tim duong di ngan nhat ( lich di chuyen ngan nhat)
 q.push(u);
 int k;

while (!q.empty()) {
 k=q.front();q.pop();
 if (edge2[k].size()!=0)for (int i=0;i<edge2[k].size();i++)
	if (pre[edge2[k][i]]==-1) {
		pre[edge2[k][i]]=k;
		if (edge2[k][i]==kt) return;
		q.push(edge2[k][i]);
		}
	}
}
int main (){
	
	input();
	for (int k=0;k<n;k++) dis[k]=-1;
	for (int k=0;k<n;k++) heap[k]=-1;

	make_ver(); 
	edge2.resize(ver.size());
	pre.resize(ver.size());
	make_edge2();
	for (int i=0;i<=ver.size()-1;i++)
	{
		if (ver[i].loc1==a&&ver[i].loc2==b) bd=i;
		if (ver[i].loc1==c&&ver[i].loc2==d) kt=i;
	}
	if (bd==-1||kt==-1) {
		cout<<"Khong the!";
		return 0;
	} 
    for (int i=0;i<pre.size();i++) pre[i]=-1;
    bfs(bd);
   	int point=0;
   	if (pre[kt]==-1) cout<<"Khong the!";
   	 else {
  
   	 	  point=kt;
   	 	  while (point!=bd)
			 {
   	 	  	    path.push(point);point=pre[point];
			 }
		  path.push(point);
	      while (!path.empty())
		      {
      			cout<< ver[path.top()].loc1<<" "<<ver[path.top()].loc2<<endl;	path.pop();	 	
	    	 }
		}
}


