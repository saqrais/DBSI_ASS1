#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <climits>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <list>
#include <bitset>
#include <set>
#include <map>
#include <functional>
#include <numeric>
#include <utility>
#include <iomanip>
using namespace std;
typedef long long int ll;
typedef long double ld;
#define rep(i,a,b) for(ll i=a;i<=b;++i)
#define rev(i,a,b) for(ll i=a;i>=b;i--)
#define pll pair<ll,ll>
#define sll set<ll>
#define vll vector<ll>
#define vpll vector<pll>
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define ln length()
#define M 1000000007
#define endl '\n'
#define FIO ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)


class Bucket
{
int local_depth;
vector<int> record;

Bucket()
{
  local_depth = 0;
}

int get_local_depth ()
{
  return local_depth;
}

void set_local_depth(int loc)
{
local_depth = loc;
}

int get_bucket_size()
{
  return record.size();
}

void insert_record(int number)
{
record.push_back(number);
}

};


int generate_random_number()
{
    return (rand() % 800000);
}

int main()
{
  Bucket x;

cout <<generate_random_number();

  return 0;
}
