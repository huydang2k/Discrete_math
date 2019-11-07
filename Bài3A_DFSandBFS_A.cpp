#include <string>
#include <iostream>
#include <vector> 
#include <queue>
#include <fstream>

using namespace std; 

queue  <int> q;          //hang doi dung trong bfs
vector <int> visited;   // danh dau cac danh da tham hay chua trong dfs
vector < vector <int> > edge;  //vector cap 2 luu danh sach ke
vector <string> node;    //vector luu cac dinh
vector <int> dis;      //vector luu khoang cach cua cac dinh khac den dinh dang xet
int fst_ind,last_ind; // chi so cua dinh bat dau va dinh ket thuc

int is_edge(string a,string b)  // ham kiem tra xem 2 dinh a va b co phai la 2 dinh ke nhau k ( tra ve so ky tu khac nhau cua 2 xau a,b) 
{
	int count=0;
	for (int i=0;i<=4;i++) 
	 {
	  if (a[i]!=b[i]) count++;	
     }
	return count;
}
void explore(int node)  // DFS
{
	visited[node]=1;
	if(edge[node].size()>0)
	    {
		 for(int i=0;i<=edge[node].size()-1;i++ ) 
	      if (visited[edge[node][i]]==0) 
			explore(edge[node][i]);
		} 
}
void bfs(int x) //bfs de tinh khoang cach cua cac dinh khac den dinh x. neu y khong lien thong voi y thi dis[y]=-1
 {
	dis[x]=0;
	q.push(x);    //them dinh x vao hang doi
	while(!q.empty()) 
	 {
		int node=q.front();
		q.pop();
	    if (edge[node].size()>0 ) 
		 for(int i=0;i<=edge[node].size()-1;i++)
	      { 
	        if (dis[edge[node][i]]==-1)   //neu dinh edge[node][i] (dinh ke thu i cua dinh node) chua duoc duyet theo chieu rong
		      {
		        q.push(edge[node][i]);    // thi them dinh edge[node][i] vao hang doi
		        dis[edge[node][i]]=dis[node]+1; 
		        if (edge[node][i]==last_ind) return;
		      }
          }
  	 }
  }
void best_path(int x, int dis1)  //in ra duong di ngan nhat tu dinh bat dau den dinh x 
 {
	if (dis1>0) //neu x khong phai la dinh bat dat thi tim dinh dung truoc x trong duong di
	 {
		for(int i=0;i<=edge[x].size()-1;i++) 
		if (dis[edge[x][i]]==dis1-1) //tim dinh ke voi x co dis giam di mot don vi. Do se la dinh dung truoc x trong duong di.
		  {
		    best_path(edge[x][i],dis1-1) ;
		    break;
		  }	
     };
    cout<<node[x]<<endl;
 }
int main() 
 {  
  int i=0;
  int num; //num la so dinh
 
  fstream f;
  f.open("sgb_words.txt", ios::in);
  while (!f.eof())
   {
     node.resize(i+1); //luu cac dinh vao node
     getline(f,node[i]);
     i++;
   }
  num=i;  
  f.close();
   
  string s1,s2;	
  
  cout<<"Nhap dinh bat dau: ";
  getline(cin,s1);
  cout<<"Nhap dinh ket thuc: ";
  getline(cin,s2);

  edge.resize(num);
  visited.resize(num);
  dis.resize(num);
 
  for(i=0;i<=num-1;i++) 
   {
     visited[i]=0;
     dis[i]=-1;
     if (node[i]==s1)  fst_ind=i;
     if (node[i]==s2)  last_ind=i;
     for(int j=i+1;j<=num-1;j++) 
      if (is_edge(node[i],node[j])==1) //neu co canh noi giua 2 dinh i va j thi them chung vao danh sach ke cua nhau
	    { 
	     edge[i].push_back(j);
	     edge[j].push_back(i);
  	 
 	    }
   }
  int count=0; //bien count dem so thanh phan lien thong
	
  for (i=0;i<=num-1;i++) if(!visited[i]) 
   {
    count++;
    explore(i);
   };

  cout<<"So thanh phan lien thong cua do thi la: "<<count<<endl;

  bfs(fst_ind);
  if (dis[last_ind]==-1) cout<<"Khong the tim duong tu dinh bat dau den dinh ket thuc";
   else 
    {
 	 cout<<"Mot duong di ngan nhat tu dinh bat dau "<<node[fst_ind]<<" den dinh ket thuc "<<node[last_ind]<<":"<<endl;
 	 best_path(last_ind,dis[last_ind]);
    }
  return 0;
}
