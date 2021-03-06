#include <slist>
#include <list>
#include <deque>
#include <vector>
#include <algorithm>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class AlgTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(AlgTest);
  CPPUNIT_TEST(min_max);
  CPPUNIT_TEST(count_test);
  CPPUNIT_TEST(sort_test);
  CPPUNIT_TEST(search_n_test);
  CPPUNIT_TEST_SUITE_END();

protected:
  void min_max();
  void count_test();
  void sort_test();
  void search_n_test();
};

CPPUNIT_TEST_SUITE_REGISTRATION(AlgTest);

//
// tests implementation
//
void AlgTest::min_max()
{
  int i = min(4, 7);
  CPPUNIT_ASSERT(i==4);
  char c = max('a', 'z');
  CPPUNIT_ASSERT(c=='z');
}

void AlgTest::count_test()
{
  {
    int n = 0;
    int i[] = { 1, 4, 2, 8, 2, 2 };
    n = count(i, i + 6, 2);
    CPPUNIT_ASSERT(n==3);
#if !defined (_STLP_NO_ANACHRONISMS)
    n = 0;
    count(i, i + 6, 2, n);
    CPPUNIT_ASSERT(n==3);
#endif
  }
  {
    int n=0;
    vector<int> i;
    i.push_back(1);
    i.push_back(4);
    i.push_back(2);
    i.push_back(8);
    i.push_back(2);
    i.push_back(2);
    n = count(i.begin(), i.end(), 2);
    CPPUNIT_ASSERT(n==3);
#if !defined (_STLP_NO_ANACHRONISMS)
    n = 0;
    count(i.begin(), i.end(), 2, n);
    CPPUNIT_ASSERT(n==3);
#endif
  }
}

void AlgTest::sort_test()
{
  {
    vector<int> years;
    years.push_back(1962);
    years.push_back(1992);
    years.push_back(2001);
    years.push_back(1999);
    sort(years.begin(), years.end());
    CPPUNIT_ASSERT(years[0]==1962);
    CPPUNIT_ASSERT(years[1]==1992);
    CPPUNIT_ASSERT(years[2]==1999);
    CPPUNIT_ASSERT(years[3]==2001);
  }
  {
    deque<int> years;
    years.push_back(1962);
    years.push_back(1992);
    years.push_back(2001);
    years.push_back(1999);
    sort(years.begin(), years.end()); // <-- changed!
    CPPUNIT_ASSERT(years[0]==1962);
    CPPUNIT_ASSERT(years[1]==1992);
    CPPUNIT_ASSERT(years[2]==1999);
    CPPUNIT_ASSERT(years[3]==2001);
  }
}

#define ARRAY_SIZE(arr) sizeof(arr) / sizeof(arr[0])

void AlgTest::search_n_test()
{
  int ints[] = {0, 1, 2, 3, 3, 4, 4, 4, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5};

  //search_n
  //Forward iterator
  {
    slist<int> slint(ints, ints + ARRAY_SIZE(ints));
    slist<int>::iterator slit = search_n(slint.begin(), slint.end(), 2, 2);
    CPPUNIT_ASSERT( slit != slint.end() );
    CPPUNIT_ASSERT( *(slit++) == 2 );
    CPPUNIT_ASSERT( *slit == 2 );
  }

  //Bidirectionnal iterator
  {
    list<int> lint(ints, ints + ARRAY_SIZE(ints));
    list<int>::iterator lit = search_n(lint.begin(), lint.end(), 3, 3);
    CPPUNIT_ASSERT( lit != lint.end() );
    CPPUNIT_ASSERT( *(lit++) == 3 );
    CPPUNIT_ASSERT( *(lit++) == 3 );
    CPPUNIT_ASSERT( *lit == 3 );
  }

  //Random access iterator
  {
    deque<int> dint(ints, ints + ARRAY_SIZE(ints));
    deque<int>::iterator dit = search_n(dint.begin(), dint.end(), 4, 4);
    CPPUNIT_ASSERT( dit != dint.end() );
    CPPUNIT_ASSERT( *(dit++) == 4 );
    CPPUNIT_ASSERT( *(dit++) == 4 );
    CPPUNIT_ASSERT( *(dit++) == 4 );
    CPPUNIT_ASSERT( *dit == 4 );
  }

  //search_n with predicate
  //Forward iterator
  {
    slist<int> slint(ints, ints + ARRAY_SIZE(ints));
    slist<int>::iterator slit = search_n(slint.begin(), slint.end(), 2, 1, greater<int>());
    CPPUNIT_ASSERT( slit != slint.end() );
    CPPUNIT_ASSERT( *(slit++) > 1 );
    CPPUNIT_ASSERT( *slit > 2 );
  }

  //Bidirectionnal iterator
  {
    list<int> lint(ints, ints + ARRAY_SIZE(ints));
    list<int>::iterator lit = search_n(lint.begin(), lint.end(), 3, 2, greater<int>());
    CPPUNIT_ASSERT( lit != lint.end() );
    CPPUNIT_ASSERT( *(lit++) > 2 );
    CPPUNIT_ASSERT( *(lit++) > 2 );
    CPPUNIT_ASSERT( *lit > 2 );
  }

  //Random access iterator
  {
    deque<int> dint(ints, ints + ARRAY_SIZE(ints));
    deque<int>::iterator dit = search_n(dint.begin(), dint.end(), 4, 3, greater<int>());
    CPPUNIT_ASSERT( dit != dint.end() );
    CPPUNIT_ASSERT( *(dit++) > 3 );
    CPPUNIT_ASSERT( *(dit++) > 3 );
    CPPUNIT_ASSERT( *(dit++) > 3 );
    CPPUNIT_ASSERT( *dit > 3 );
  }

  // test for bug reported by Jim Xochellis
  {
    int array[] = {0, 0, 1, 0, 1, 1};
    int* array_end = array + sizeof(array) / sizeof(*array);
    CPPUNIT_ASSERT(search_n(array, array_end, 3, 1) == array_end);
  }
}
