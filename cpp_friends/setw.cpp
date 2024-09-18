#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

int main ()
{
  string one = "Один", two = "Два", eight = "Восемь";
  cout << setw (10) << one <<endl;
  cout << setw (10) << two <<endl;
  cout << setw (10) << eight <<endl;
  return 0;
}