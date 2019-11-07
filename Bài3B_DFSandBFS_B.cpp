#include <string>
#include <iostream>
#include <vector> 
#include <queue>
#include <fstream>
#include <stack>

using namespace std;

vector < string > node ;         //vector luu cac dinh
vector < vector <int> > edge;    //vector cap 2 luu danh sach ke
vector <bool> done;             //danh dau nhung dinh da xoa cua do thi theo thuat toan tarjan
vector <int> visited;           //danh dau nhung dinh da tham
vector <int> smallest_vis;    
vector <int> display;           // vector luu cac dinh trong cung mot thanh phan lien thong manh voi tu duoc nhap vao
stack <int> path;             
vector <int> dis;              // dis[i] luu dinh dung truoc i theo thu tuc BFS
stack <int> s;                  //ngan xep s de chua cac dinh cua thanh phan lien thong manh
queue <int> q;					//hang doi dung trong BFS
string word,word1,word2;
int time;
int mark,mark1,mark2;
int compponent_count=0;   // so thanh phan lien thong manh


int min(int a,int b) 
 {
   return (a<b)?a:b;
 } 
bool is_edge(string a,string b) //kiem tra xem co canh noi 2 xau a va b khong
 {
	int count=0;
	for (int i=1;i<=4;i++) {
		for (int j=0;j<=4;j++)
		 if (a[i]==b[j] ) {
		 	count++; b[j]=' ';break;
		 }
	}
	if (count==4) return true;
	return false;
 }
void bfs(int u) //BFS theo dinh u, luu dinh duoc truoc dinh i vao dis[i] 
 {
  q.push(u);
  dis[u]=0;
  int k;

  while (!q.empty()) 
  {
  k=q.front();q.pop();
  if (edge[k].size()!=0) for (int i=0;i<edge[k].size();i++)
	if (dis[edge[k][i]]==-1)
	 {
		dis[edge[k][i]]=k;
		if (edge[k][i]==mark2) return;
		q.push(edge[k][i]);
		
	 }
	}
  }
	
void visit(int i)  //thuat toan tarjan tim so thanh phan lien thong manh
 {
	time++; 
	visited[i]=time;              //visited[i] la thu tu cua i trong phep tham
	smallest_vis[i]=visited[i];  //smallest_vis[i] la gia tri visited nho nhat cua cac dinh co the den duoc tu mot dinh nao do thuoc cay DFS goc i
	s.push(i);                   //dua i vao ngan xep
	if (edge[i].size()>0)       
	 for (int j=0;j<=edge[i].size()-1;j++) 
	 {  int k=edge[i][j];            //k la dinh ke thu j cua dinh i
	 	if ((visited[k]==0) &&(!done[k])) {visit(k);
	 		smallest_vis[i]=min(smallest_vis[i],smallest_vis[k]);
		 }
	 	 else if((visited[k]!=0) &&(!done[k])) 	smallest_vis[i]=min(smallest_vis[i],visited[k]);
	 	
	 }
	if (smallest_vis[i]==visited[i]) //neu i la chot
	{ 
	compponent_count++;  //tang so thanh phan lien thong manh len mot
	while (s.top()!=i) 	
	{
	done[s.top()]=true; //xoa cac dinh trong ngan xep (cac dinh thuoc cung thanh phan lien thong minh chot i)  ra khoi do thi
	
	if (mark==i) display.push_back(s.top());  // neu dinh i dang xet la dinh nguoi dung nhap vao de in ra cac dinh thuoc cung thanh phan lien thong 
	                                          //manh voi no thi them cac dinh trong ngan xep s vao display de hien thi ra man hinh
	s.pop();
	}
	done[s.top()]=true;  //xoa dinh cuoi cung trong ngan xep (chot i)
    s.pop();
	}
 }
int main () 
{
  int i=0;
  int num;
  time=0;
  cout<<"Nhap vao 1 tu de xem cac tu thuoc cung thanh phan lien thong manh voi no:";
  cin>>word;
  cout<<"Nhap tu bat dau:"; cin>>word1;
  cout<<"Nhap tu ke thuc:"; cin>>word2;
  fstream f;
  f.open("sgb_words.txt", ios::in);
  while (!f.eof())
   {
 	node.resize(i+1);
	getline(f,node[i]);
	if (node[i]==word)  mark=i;
	if (node[i]==word1) mark1=i;
	if (node[i]==word2) mark2=i;
    i++;
   }
  num=i; 
  smallest_vis.resize(num);
  visited.resize(num);
  edge.resize(num);
  done.resize(num);
  dis.resize(num);
 
  for (i=0;i<=num-1;i++) done[i]=false;
  for (i=0;i<=num-1;i++) visited[i]=0;
  for (i=0;i<=num-1;i++) dis[i]=-1;
 
  for(i=0;i<=num-1;i++) 
   {
     for(int j=0;(j<=num-1);j++) 
     if (i==j) continue; else
      if (is_edge(node[i],node[j])) //tao danh sach ke
	     edge[i].push_back(j);	 	    
   } 

  for (int i=0;i<=num-1;i++)
    {
     	if ((visited[i]==0)&&(done[i]==false) )visit(i);
    }
  cout<<"So thanh phan lien thong manh la:"<<compponent_count<<endl;
     if (display.size()>0)	
	 {
	 	cout<<"Cac tu thuoc cung thanh phan lien thong manh voi "<<word<<" la:"<<endl;
	 	for (int i=0;i<=display.size()-1;i++) cout<<node[display[i]]<<endl;
	 }
      else cout<<"Khong con tu nao khac thuoc cung thanh phan lien thong manh voi "<<word<<endl;
 
  bfs(mark1);
  int k=0;
  if (dis[mark2]==-1) cout<<"Khong co duong di tu dinh bat dau den dinh ket thuc";
   	 else {
   	 	   cout<<"Mot duong di ngan nhat tu "<<node[mark1]<<" den "<<node[mark2]<<" la:"<<endl;
   	 	   int point=mark2;
   	 	   while (point!=mark1) {
   	 	  	     path.push(point);point=dis[point];
				  }
		   path.push(point);
	       while (!path.empty()) 
		    {
					cout<<node[path.top()]<<endl;
					path.pop();	 	
	     	 }
		 }
	
	}

