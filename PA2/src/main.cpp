#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

struct Pts 
{ 
	int pt1; 
	int pt2; 
};

bool mycmp (Pts &i,Pts &j) { return (i.pt1<j.pt1); }
// bool cmpint (int &i,int &j) { return (i<j); }
int main(int argc, char** argv)
{
	fstream newfile;
	vector<Pts> arr;
	Pts pt_obj;
   	newfile.open(argv[1],ios::in);
   	if (newfile.is_open()){   
      	string tp;
      	getline(newfile, tp);
      	// int arr_size = stoi(tp);
      	// cout << "size of array is: " << arr_size << endl;
      	while(getline(newfile, tp)){
      		if(tp != "0")
      		{
      			istringstream iss(tp);
      			int a,b;
      			iss >> a >> b;
      			if(a > b) swap(a,b);
         		pt_obj.pt1 = a;	
         		pt_obj.pt2 = b;
         		arr.push_back(pt_obj); 	
         		//cout << pt_obj.pt1 << "," << pt_obj.pt2 << "\n"; 
      		} 
      	}
      	newfile.close(); 
   }
	sort(arr.begin(),arr.end(),mycmp);
	int arr_size = arr.size()*2;
	//cout << "size of arr is: " << arr_size << endl;

	// vector<vector<Pts> > MIS(arr_size,vector<Pts>(arr_size, 0));
	// vector<vector<vector<Pts>>> MIS(arr_size,vector<vector<Pts>,arr_size>);
	// vector<vector<Pts> > MIS(arr_size,vector<Pts>(arr_size, 0));
	
	vector<vector<vector<Pts> > > MIS (arr_size,vector<vector<Pts> >(arr_size,vector <Pts>()));
	//cout << MIS[0][-1].size();
	
	vector<Pts> chrod;
	Pts obj;
	int k = 0;
	int count = 0;
	vector<int> flag;
	
	for(int j = 0; j < (int)arr.size()*2; j++)
	{
		//find correspnding k
		for(int p = 0; p < (int)arr.size(); p++)
		{
			if(arr[p].pt1 == j)	k = arr[p].pt2;
			else if(arr[p].pt2 == j) k = arr[p].pt1;
			// cout << "k is: " << k << endl;
		}
			count++;
		// if(k>0){
		for(int i = 0; i < j; i++)
		{
			if(((i <= k) && (k <= j-1)) && ((MIS[i][k-1].size()+1+MIS[k+1][j-1].size()) > MIS[i][j-1].size()))
			{
				// cout << "k: " << k << endl;
				obj.pt1 = k;
				obj.pt2 = j;
				MIS[i][j].push_back(obj);
				if(k==0)
				{
					// MIS[i][j].insert(MIS[i][j].end(),MIS[i][k-1].begin(),MIS[i][k-1].end());
					MIS[i][j].insert(MIS[i][j].end(),MIS[k+1][j-1].begin(),MIS[k+1][j-1].end());
				}
				else
				{
					MIS[i][j].insert(MIS[i][j].end(),MIS[k+1][j-1].begin(),MIS[k+1][j-1].end());
					MIS[i][j].insert(MIS[i][j].end(),MIS[i][k-1].begin(),MIS[i][k-1].end());
				}
				// MIS[i][j].push_back(MIS[i][k-1]);
				// MIS[i][j].push_back(MIS[k+1][j-1]);

				// if(k>idy)
				// {
					// // idx = k;
					// // idy = j;
					// chrod.push_back(obj);
					// flag.push_back(count);
				// }
			}
			else 
			{
					// cout << "mp222\n";

				MIS[i][j].insert(MIS[i][j].end(),MIS[i][j-1].begin(),MIS[i][j-1].end());
				// MIS[i][j].push_back(MIS[i][j-1]);
				// obj.pt1 = k;
				// obj.pt2 = j;
				// chrod.push_back(obj);

			}
		}
	// }

	}
	// cout << "mp\n";
	fstream out;
	out.open(argv[2],ios::out);
	out << MIS[0][(int)arr.size()*2-1].size() << endl;
	// cout << "the result is: " << MIS[0][(int)arr.size()*2-1].size() << endl;
	vector<Pts> sort_out;
	Pts oo;
	for(int i = 0; i < (int)(MIS[0][(int)arr.size()*2-1].size()); i++)
	{
		oo.pt1 = MIS[0][(int)arr.size()*2-1][i].pt1;
		oo.pt2 = MIS[0][(int)arr.size()*2-1][i].pt2;
		sort_out.push_back(oo);
	}
	sort(sort_out.begin(),sort_out.end(),mycmp);
	for(int i = 0; i < (int)(MIS[0][(int)arr.size()*2-1].size()); i++)
	{
		// cout << MIS[0][(int)arr.size()*2-1][i].pt1 << " "<< MIS[0][(int)arr.size()*2-1][i].pt2 << endl;
		// out << MIS[0][(int)arr.size()*2-1][i].pt1 << " " << MIS[0][(int)arr.size()*2-1][i].pt2 << endl;
		out << sort_out[i].pt1 << " " << sort_out[i].pt2 << endl;
	}


/*
	cout << "the result is: " << MIS[0][(int)arr.size()*2-1] << endl;

	// for(int i = 0; i < (int)MIS.size(); i++)
	// {
	
		// for(int i = 0; i < (int)MIS.size(); i++)
		// {
			for(int j = 0; j < (int)MIS.size(); j++)
			{
			cout << j << ":" <<MIS[j][(int)MIS.size()-1] << endl; //x
				// cout << j << ":" <<MIS[0][j] << endl; //y

			}
			// cout << endl;
		// }
	// }
	cout << endl; 
	sort(chrod.begin(),chrod.end(),mycmp);

	int idx = -1; 
	int idy = -1;	
	for(int i = 0; i < (int)chrod.size(); i++)
	{
		// if(chrod[i].pt1 > idy || ((chrod[i].pt1 > idx) && chrod[i].pt2 < idy))
		// {
			// cout << chrod[i].pt1 <<" " << chrod[i].pt2 << endl;
			idx = chrod[i].pt1;
			idy = chrod[i].pt2;
		// }
			// cout << flag[i] << endl;

	}*/
	return 0;
}
