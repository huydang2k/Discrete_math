#include <iostream>	
#include <vector> 
#include <list>

using namespace std;

vector <int> deg;                          //vector luu bac cua cac dinh
vector < list <int> > edge;				  // Danh sach ke cua moi dinh duoc luu bang 1 phan tu cua edge co kieu la list
vector <bool> done;						 // Vecor luu cac dinh da xoa khoi do thi theo thu tuc tim prufer code
vector <int> pru_code;					// Vector luu prufer code
int E;								   // E la so canh
bool stop()  // Ham kiem tra lieu tat ca cac dinh da duoc xoa hay chua
{
 for(int v=0;v<=E;v++) 
  {
 	if (!edge[v].empty()) return false;
  }
 return true;
}
void input() // Nhap input
{
  cin>>E;
  int e1,e2;
  deg.resize(E+1);
  edge.resize(E+1);
  done.resize(E+1);
  for (int i=0;i<=E;i++)
	  done[i]=false; 
  for (int e=1;e<=E;e++)
   {
		cin>>u1; cin>>u2;  
		edge[u1].push_back(u2); //them dinh u2 vao danh sach ke cua u1 va nguoc lai
		edge[u2].push_back(u1);
		deg[u1]++; deg[u2]++;   // tang bac cua u1 va u2 len 1
   }
}
void make_code() // Ham sinh prufer code
{
 while (!stop()) 	
  for (int v=1;v<=E;v++)
   {
		if((deg[v]==1)&&(done[v]==false)) 
		{
			done[v]=true;   //xoa dinh v khoi do thi
			deg[v]--;
			deg[edge[v].front()]--;   //giam bac cua dinh ke voi dinh v vua bi xoa
			pru_code.push_back(edge[v].front());  //them dinh ke voi dinh vua moi xoa vao prufer code
			edge[edge[v].front()].remove(v);      // xoa dinh v khoi danh sach ke cua dinh ke voi dinh v
			edge[v].pop_back();                  // xoa dinh ke voi dinh v ra khoi danh sach ke cua v
			break;
		}
	}
}
int main ()
{
	input();
 	make_code();
 	for (int i=0;i<E-1;i++) cout<<pru_code[i]<<" ";
}
