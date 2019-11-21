#include <iostream>
#include<fstream>
#include<iomanip>
using namespace std;
const int num_of_cand=6;
const int num_of_regions=4;
void bubble_sort (string candidates[]);
void printHeading(ofstream&);
void SearchNumber(string store[], string cand_name, int &index);
void get_candidates(ifstream &read_cand, string cand_names[]);
void summing_results (const int list[][num_of_regions], int sum[num_of_cand], int &total_voters);
void bring_winner(int sum_per_can[], int &winner_index);
void read_election (ifstream &read, ofstream &write, int list[][num_of_regions], string array[]);
int main()
{
    ifstream input,names_of_cand; ofstream output;
    input.open("records.txt");
    names_of_cand.open("candidates.txt");
    output.open("output.txt");
    int list[num_of_cand][num_of_regions]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    string candidates[num_of_cand];
    if (!input||!names_of_cand)
    {
        cout<<"no data for the election result yet "<<endl;
        cout<<"program terminates.........."<<endl;
        return 1;
    }

get_candidates(names_of_cand,candidates);
bubble_sort(candidates);
printHeading(output);
read_election(input,output,list,candidates);
input.close();
names_of_cand.close();
output.close();

}
void get_candidates(ifstream &read_cand, string cand_names[])
{ string names;

   for(int i=0; i<num_of_cand; i++)
{
    read_cand>>names;
 cand_names[i]=names;
}

}

void bubble_sort (string array[])
{  string x,y;int p,length=num_of_cand;
      do {
  for (int i=0; i<length; i++)
  {
   if (i<length-1)
    p=i+1;
    else
    p=length-1;
      if (array[i]>array[p])
        {
          x=array[i];
          y=array[p];
          array[i]=y;
          array[p]=x;
        }
   }
length--;}while (length>0);
}
void printHeading(ofstream &decorate)
{
decorate << " -------------Election Results----------"<< "----" << endl << endl;
decorate << "Candidate Votes" << endl;
decorate<< "Name           Region1    Region2   Region3   Region4 Total" << endl;
decorate << "---------     -------   -------    -------   ------- -------" << endl;
}

void read_election (ifstream &read, ofstream &write, int list[][num_of_regions], string array[])
{
    string name; int region,votes,position,winner_pos; int all_voters=0; int sum_per_cand[num_of_cand]={0,0,0,0};
do{ read>>name>>region>>votes;
 SearchNumber(array,name,position); // search for the number assigned to the name read
 while(read)
  {list[position][region-1]+=votes;
        break;}
}while (read);
summing_results(list,sum_per_cand,all_voters);
bring_winner(sum_per_cand,winner_pos);
 for (int i=0; i<num_of_cand; i++)
 {     write<<left<<setw(7)<<array[i]<<"   ";
  write<<right;
     for (int j=0; j<num_of_regions; j++)
           write<<setw(8)<<list[i][j]<<"   ";
 write<<setw(6)<<sum_per_cand[i]<<endl;
 }
 write<<"WINNER OF THE ELECTION :"<<array[winner_pos]<<", Votes Received: "<<sum_per_cand[winner_pos]<<endl;
 write<<"TOTAL VOTERS ="<<all_voters;
}


void SearchNumber(string store[], string cand_name, int &index)
{ int length=num_of_cand;
 for (int i=0; i<length; i++)
 { if (cand_name==store[i])
    {
    index=i;
    break;
    }
 }

}
void summing_results (const int list[][num_of_regions], int sum[num_of_cand], int &total_voters)
{
    for (int i=0; i<num_of_cand; i++)
    {
        for (int j=0; j<num_of_regions; j++)
           {
               sum[i]+=list[i][j];

            }
    total_voters+=sum[i];}

}
void bring_winner(int store[], int&winner_index)
{
    int len=num_of_cand;
     int largest_vote=store[0];
    for (int i=0; i<len; i++)
    { for (int j=1; j<len; j++)
       {
           if (store[i]>store[j]&&store[i]>largest_vote)
           {
            winner_index=i;
           largest_vote =store[i];
            break;
            }

            else break;
        }
    }

}

