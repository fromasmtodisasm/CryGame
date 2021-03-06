#define _STLP_DO_IMPORT_CSTD_FUNCTIONS
#include <cmath>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)

namespace NS1 {

void f()
{
  double d( 1.0 );

  d = sqrt( d );
  d = ::sqrt( d );
  d = std::sqrt( d );
};

}

namespace {

void g()
{
  double d( 1.0 );

  d = sqrt( d );
  d = ::sqrt( d );
  d = std::sqrt( d );
};

}

#ifndef _STLP_MSVC // I'm sorry, VC still can't resolve name below
using namespace std;
#endif

void h()
{
  double d( 1.0 );

  d = sqrt( d );
  d = ::sqrt( d );
  d = std::sqrt( d );
};

struct sq
{
    sq()
      { }

    double sqroot( double x )
      {
        using std::sqrt;
        return sqrt(x);
      }
};

#endif


#if 0 // Do nothing, this should be compiled only

#include "cppunit/cppunit_proxy.h"

class ResolveNameTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(ResolveNameTest);
  CPPUNIT_TEST(cstyle);
  CPPUNIT_TEST_SUITE_END();

protected:
  void cstyle();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ResolveNameTest);

void ResolveNameTest::cstyle()
{
}

#endif
