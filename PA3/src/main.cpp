#include <cstdlib>
#include <iostream>
#include <climits>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>
using namespace std;


class result
{
public:
	result() {};
	result(int b, int e, int w):begin(b), end(e), weight(w) {};
	int begin;
	int end;
	int weight;
};

class Graph
{
public:
	Graph(int n):vertic_num(n)
	{
		adjMatrix.resize(vertic_num, vector<int>(vertic_num));
		for(int i = 0; i < vertic_num; i++)
		{
			for(int j = 0; j < vertic_num; j++)
				adjMatrix[i][j] = 0;
		}


	};
	void addEdges(int begin, int end, int edge)
	{
		adjMatrix[begin][end] = edge;

	}

	int extractMin(int *key, bool *visited, int size)
	{
		int Min = Maxnum;
		int minIdx = 0;
    	for (int i = 0; i < size; i++) 
    	{
        	if (visited[i] == false && key[i] < Min) 
        	{
            	Min = key[i];
            	minIdx = i;
        	}
    	}
    	return minIdx;
	}

	vector<result> printResult(int begin, vector<result>& arr, int &tot_cost)
	{
		int key[vertic_num];
		int predec[vertic_num];
		bool visited[vertic_num];
		vector<result> re;
		for(int i = 0; i < vertic_num; i++)
		{
			key[i] = Maxnum;
			predec[i] = -1;
			visited[i] = 0;
		}
		key[begin] = 0;
		int u = 0;
		for(int i = 0; i < vertic_num; i++)
		{
			u = extractMin(key, visited, vertic_num);
			visited[u] = 1;
			for(int i = 0; i < vertic_num; i++)
			{
				if ( visited[i] == 0 && adjMatrix[u][i] != 0 && adjMatrix[u][i]<key[i])
				{
                	predec[i] = u;
               		key[i] = adjMatrix[u][i];
            	}
			}
		}

		// cout << setw(3) << "v1 - " << setw(3) << "v2"<< " : weight\n";
		int i = (begin + 1) %vertic_num;
		while(i != begin)
		{
			result _obj(predec[i], i, adjMatrix[predec[i]][i]);
 			re.push_back(_obj);			  
			// cout << setw(3) << predec[i] << " - " << setw(3) << i
			     // << " : " << setw(4) << adjMatrix[predec[i]][i] <<"\n";
			i = (++i)%vertic_num;
		}
		// cout << endls << endl << endl;
		/*
		for(size_t j = 0; j < re.size(); j++)
		{
			cout << re[j].begin << " " << re[j].end << " " << re[j].weight << endl;
		}
		*/
		vector<result> final;
		// int tot_cost = 0;
		for(size_t i = 0; i < arr.size(); i++)
		{
			size_t j = 0;
			for(j = 0; j < re.size(); j++)
			{
				if(((arr[i].begin == re[j].begin) && (arr[i].end == re[j].end)) || ((arr[i].begin == re[j].end) && (arr[i].end == re[j].begin)))
				{
					break;
				}
			}
			if(j == re.size())
			{
				result _fin(arr[i].begin, arr[i].end, arr[i].weight);
				tot_cost += arr[i].weight;
				final.push_back(_fin);
				// cout << arr[i].begin << " " << arr[i].end << " " << arr[i].weight << endl;;
			}

		}
		return final;
/*
		//write result
		cout << tot_cost << endl;
		for(size_t p = 0; p < final.size() ; p++)
		{
			cout << final[p].begin << " " << final[p].end << " " << final[p].weight << endl;;
		}*/

	}
private:
	int Maxnum = INT_MAX;
	int vertic_num = 0;
	vector<vector<int>> adjMatrix;



};



int main(int argc, char** argv)
{

	fstream newfile;
	fstream out_file;
	out_file.open(argv[2], ios::out); 
	vector<result> arr;
	result _obj;
   	newfile.open(argv[1],ios::in);
   	if (newfile.is_open()){   
      	string tp;
      	getline(newfile, tp);
      	int tot_cost = 0;
      	if(tp == "u")
      	{
	      	int ver, edge;
	      	getline(newfile, tp);
	      	ver = stoi(tp);
	      	Graph gg(stoi(tp));
	      	getline(newfile, tp);
	      	edge = stoi(tp);
	      	if(edge == (ver-1))
	      	{
	      		// cout << 0 << endl;
	      		out_file << 0 << endl;
	      		exit(0);
	      	}
	      	// int arr_size = stoi(tp);
	      	// cout << "size of array is: " << arr_size << endl;
	      	while(getline(newfile, tp)){
	      		if(tp != "0")
	      		{
					// Pts* pt_obj = new Pts;
	      			istringstream iss(tp);
	      			int a,b,c;
	      			iss >> a >> b >> c;
	      			// if(a > b) swap(a,b);
	         		_obj.begin = a;	
	         		_obj.end = b;
	         		_obj.weight = c;
	         		arr.push_back(_obj); 	
	         		// cout << _obj.begin << "," << _obj.end << "," << _obj.weight << "\n"; 
	         		gg.addEdges(a, b, -c);
	         		gg.addEdges(b, a, -c);


	      		} 
	      	}
      	vector<result> final = gg.printResult(0, arr, tot_cost);

      	// write file
      	// cout << tot_cost << endl;
      	out_file << tot_cost << endl;
		for(size_t p = 0; p < final.size() ; p++)
		{
			out_file << final[p].begin << " " << final[p].end << " " << final[p].weight << "\n";
			// cout << final[p].begin << " " << final[p].end << " " << final[p].weight << endl;;
		}
      	}


      	else if(tp == "d")
      	{
	      	int ver, edge;
	      	getline(newfile, tp);
	      	ver = stoi(tp);
	      	Graph gg(stoi(tp));
	      	getline(newfile, tp);
	      	edge = stoi(tp);
	      	if(edge == (ver-1))
	      	{
	      		cout << 0 << endl;
	      		// out_file << 0 << endl;
	      		exit(0);
	      	}
	      	// int arr_size = stoi(tp);
	      	// cout << "size of array is: " << arr_size << endl;
	      	while(getline(newfile, tp)){
	      		if(tp != "0")
	      		{
					// Pts* pt_obj = new Pts;
	      			istringstream iss(tp);
	      			int a,b,c;
	      			iss >> a >> b >> c;
	      			// if(a > b) swap(a,b);
	         		_obj.begin = a;	
	         		_obj.end = b;
	         		_obj.weight = c;
	         		arr.push_back(_obj); 	
	         		// cout << _obj.begin << "," << _obj.end << "," << _obj.weight << "\n"; 
	     	        gg.addEdges(a, b, -c);

	      		} 
	      	}
      	vector<result> final = gg.printResult(0, arr, tot_cost);

      	//write file
      	// cout << tot_cost << endl;
      	out_file << tot_cost << endl;
		for(size_t p = 0; p < final.size() ; p++)
		{
			out_file << final[p].begin << " " << final[p].end << " " << final[p].weight << "\n";
			// cout << final[p].begin << " " << final[p].end << " " << final[p].weight << endl;;
		}
      	}




      }
     

	return 0;
}

