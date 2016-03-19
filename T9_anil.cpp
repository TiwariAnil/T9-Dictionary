/*

Written by Anil Tiwari
Date: 27-Jan-2016

*/
#include<vector>
#include<stack>
#include<set>
#include<map>
#include<queue>
#include<deque>
#include<string>
//Other Includes
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cassert>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<sstream>
#include <fstream>
//some common functionn
#define maX(a,b)                     ( (a) > (b) ? (a) : (b))
#define miN(a,b)                     ( (a) < (b) ? (a) : (b))
#define FOR(i,a,b)              for(int i=a;i<b;i++)
#define FORs(i,a,b)             for(int i=a;i>=b;i--)
#define fill(a,v)               memset(a,v,sizeof a)
#define abS(x)                  ((x)<0?-(x):(x))
#define mP                      make_pair
#define pB                      push_back
#define error(x)                cout << #x << " : " << (x) << endl
#define all(c)                  (c).begin(),(c).end()
// Input macros
#define s(n)                        scanf("%d",&n)
#define sc(n)                       scanf("%c",&n)
#define sl(n)                       scanf("%lld",&n)
#define sf(n)                       scanf("%lf",&n)
#define ss(n)                       scanf("%s",n)

// Output macros
#define p(n)                        printf("%d",n)
#define pc(n)                       printf("%c",n)
#define pl(n)                       printf("%lld",n)
#define pf(n)                       printf("%lf",n)
#define ps(n)                       printf("%s",n)

using namespace std;

typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef pair<int,PII> TRI;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VII;
typedef vector<PLL> VLL;
typedef vector<TRI> VT;
typedef vector<VI> VVI;
typedef vector<VL> VVL;
typedef vector<VII> VVII;
typedef vector<VLL> VVLL;
typedef vector<VT> VVT;

#define ALPHA (26)
#define SIZE(a) sizeof(a)/sizeof(a[0])
#define CHAR_INDEX(c) ((int)c - (int)'a')
char my_map[10][5] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};


struct trie_node{
    int info;
    trie_node *children[ALPHA];
};

struct trie{
    int count;
    trie_node *root;
} trieNode;

trie_node *newNode(void){
    trie_node *tNode = NULL;
    tNode = new trie_node;

    if(tNode){
        tNode->info = 0;
        FOR(i,0,ALPHA){
            tNode->children[i]=NULL;
        }
    }
    return tNode;
}

void insert(trie *rootNode, char word[]){
    int n=strlen(word);
    trie_node *temp;
    rootNode->count++;
    temp = rootNode->root;

    FOR(i,0,n){
        int pos= CHAR_INDEX(word[i]);
        if(!temp->children[pos]){
            temp->children[pos] = newNode();
        }
        temp = temp->children[pos];
    }
    temp->info = rootNode->count;
}

int search(trie *rootNode, char word[]){
    int n=strlen(word);
    trie_node *temp;
    temp = rootNode->root;

    FOR(i,0,n){
        int pos = CHAR_INDEX(word[i]);
        if(!temp->children[pos])
            return 0;
        temp = temp->children[pos];
    }
    if(!temp)
        return 0;
    if(temp->info==0)
        return 0;
    return 1;
}

void print_next_5(trie_node *root, string s, int depth, int cnt ){
    trie_node *temp;
    temp = root;
    //error(cnt);
    if(depth >3 || cnt > 2) //>5)
        return ;
    char ch;
    FOR(i,0,ALPHA)
    {
        ch='a'+i;
        //error(ch);
        if(temp->children[i])
        {
            if(temp->children[i]->info){
                cout<<"Do you mean? -----"<<s<<ch<<endl;
                //cnt++;
            }
            print_next_5(temp->children[i], s+ch, depth+1, cnt+1);
        }
    }
}

void search_nearbuy(trie *rootNode, string word){
    int n=word.size();
    trie_node *temp;
    temp = rootNode->root;

    FOR(i,0,n){
        int pos = CHAR_INDEX(word[i]);
        if(!temp->children[pos])
        {
            //cout<<"No Such word present in Dictionary"<<endl;
            return;
        }
        temp = temp->children[pos];
    }
    if(!temp)
    {
        //cout<<"No Such word present in Dictionary"<<endl;
        return;
    }
    if(temp->info!=0)
        cout<<"Do you mean? -----"<<word<<endl;
    string st="";
    FOR(i,0,n)
        st+=word[i];
    //error(st);
    print_next_5(temp, st, 0,0);

}



void print_sub(int arr[], int pos, string final, int n){

    //error(final);
    if(pos == n)
    {
        //error(final);
        search_nearbuy(&trieNode, final);
        //cout<<endl;
        return ;
    }
    //int v = final[pos] - '0';
    FOR(i,0, strlen(my_map[arr[pos]])){

        if(arr[i] == 0 || arr[i] == 1)
            return;
        print_sub(arr, pos+1, final+my_map[arr[pos]][i], n);

    }

}

void print_main(string s, int n){
    string s_final = "";
    int arr[n];
    //error(s);
    FOR(i,0,n)
    {
        arr[i]= s[i]-'0';
    }
    print_sub(arr, 0, s_final, n);
}



int main(){


    trieNode.root = newNode();
    trieNode.count = 0;

    ifstream input_file;
    input_file.open("inputT9.txt");

    char str[50];

	FOR(i,0,5000)
	{

	    input_file >> str;
	    //cout<<str<<endl;//str;
		insert(&trieNode, str);
	}

    input_file.close();
    string inp;
    cout<<"Enter the number(use only 2-9), I will read your mind! \n\n    : ";
    cin>>inp;
    //cin>>str;

    print_main(inp, inp.size());

    //search_nearbuy(&trieNode, str);
    //cin>>str;
	// Search for different keys
/*
	if(search(&trieNode, str) )
        printf(" %s is found!", str );
    else
        printf(" %s is NOT found!", str );
*/
    return 0;
}

