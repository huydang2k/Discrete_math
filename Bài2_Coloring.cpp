#include <iostream>	
#include <vector> 
#include <fstream>
#include <string>


using namespace std;

int n,m;                   //n la so dinh va m la so canh
bool colored[21];	     	// khi to mau cho mot dinh, danh dau mau i da duoc to cho dinh ke la colored[i]=true;
string color_arr[21];      // day 20 mau dung de to
vector <int> color;       // color[u] la mau cua dinh u
vector <vector <int> > edge;  //edge[u] la mot vector luu danh sach cac dinh ke cua dinh i
vector <vector<int> > edge_dis;  //edge_dis[i] luu canh thu i, dung de hien thi ra file dot
void make_color()   //luu 20 mau dung cho bai toan vao mang color_arr
{
	color_arr[1]="red";
	color_arr[2]="yellow";
	color_arr[3]="blue";
	color_arr[4]="green";
	color_arr[5]="black";
	color_arr[6]="purple";
	color_arr[7]="orange";
	color_arr[8]="tan1";
	color_arr[9]="aqua";
	color_arr[10]="brown";
	color_arr[11]="violet";
	color_arr[12]="silver";
	color_arr[13]="aquamarine";
	color_arr[14]="pink";
	color_arr[15]="darkviolet";
	color_arr[16]="teal";
	color_arr[17]="wheat";
	color_arr[18]="lightblue";
	color_arr[19]="grey";
	color_arr[20]="darkred";
}
void input() 
{	 
 fstream f1;
 f1.open("dothi.txt",ios::in);
 f1>>n; f1>>m;
 color.resize(n+1);
 edge.resize(n+1);
 edge_dis.resize(m);
 for (int i=0;i<m;i++) 
 for (int i=1;i<=m;i++)
  { 
    int v1,v2;
    f1>>v1;f1>>v2;
    edge[v1].push_back(v2); // khoi tai danh sach ke
    edge[v2].push_back(v1);
    edge_dis[i-1].push_back(v1); //luu lai canh thu i bang 1 vector co kich thuoc la 2 
    edge_dis[i-1].push_back(v2);
  }
  f1.close();
  for (int i=1;i<=n;i++) color[i]=0; 
}
void coloring(int u) //ham to mau
{
 for (int i=1;i<=20;i++) colored[i]=false; 
 if (edge[u].size()>0) 
  for (int i=0;i<=edge[u].size()-1;i++) 
   {
     int v=edge[u][i];
	 if (color[v]!=0) colored[color[v]]=true;	//gan colored[i]=true neu i la mau cac dinh ke voi u
   }	
 for (int i=1;i<=20;i++)   //tim mau dau tien chua duoc to cho cac dinh ke ( colored[i]=false) de gan cho dinh u
  if (colored[i]==false)
   {
   	color[u]=i;break;
   }
   
}
void output() //in output ra file dot
{
 fstream f2;
 f2.open("dothimau.dot", ios::out);
 f2<<"graph dothi"<<endl;
 f2<<"{"<<endl;
 for (int u=n;u>=1;u--)  
  {
 	f2<<"  "<<u<<"  [fillcolor="<<color_arr[color[u]]<<",  style=filled];"<<endl;
  }
  for(int i=0;i<m;i++)
  {
  	f2<<"  "<<edge_dis[i][0]<<" -- "<<edge_dis[i][1]<<";"<<endl;
  }
 f2<<"}";
 f2.close();
}
int main(){
	make_color();
	input();
	for (int u=1;u<=n;u++) coloring(u);
	output();
}
