// Egy mergesort rendezést kell
// megvalósítani, de mint tudjátok, nem szabad függvénysablonokat feladni
// feladatként, ezért van egy mergesort_util osztály sablon. Ennek template
// paraméterei: az a típus, amilyen típusú elemeket rendezni fog, valamint
// egy opcionális rendezési funktortípus. A konstruktora egy megfelelő típusú
// tömböt vár paraméterként, valamint egy opcionális bool-t. Ha ez a bool
// érték hamis, akkor a mergesort-ban a merge-lést már nem kell végrehajtani,
// csak felbontani a tömböt és csak a kis tömbök rendezését kell
// biztosítani. Az osztály split tagfüggvénye két indexet vár paraméterként:
// mettől-meddig kell felbontani és/vagy rendezni a tömböt. A
// set_merge_on-nal bekapcsolható, hogy split merge-lje össze a kis tömböket.
// A sort tagfüggvény értelemszerűen az egész tömböt rendezi. Az algoritmusnak
// támogatnia kell a felhasználói predikátum funktor használatát (harmadik
// template paraméterként).


#include <iostream>
#include <functional>
#include "msort.h"
#include <vector>
#include <string>
#include <algorithm>
#include "msort.h"

struct string_size_less
{

  bool operator()( const std::string& a,
                   const std::string& b ) const
  {
    return a.size() < b.size();
  }

};

const int max = 1024;

bool check()
{
  int x[] = { 3, 7, 4, 1, 2, 5, 6, 9 };
  mergesort_util<int> ui( x, sizeof( x ) / sizeof( x[ 0 ] ), false );
  ui.split( 0, 7 );

  std::string s[] = { "Cobol", "ABAP", "Simula", "C" };
  mergesort_util<std::string> us( s, sizeof( s ) / sizeof( s[ 0 ] ), false );
  us.split( 0, 1 );

  int v[ max ];
  for( int i = 0; i < max; ++i )
  {
    v[ i ] = max - i;
  }
  mergesort_util<int> um( v, max, false );
  um.split( 0, max - 1 );

  if ( 1 != x[ 2 ] || 7 != x[ 1 ] || 4 != x[ 3 ] ||
       max - 1 != v[ 0 ] || max != v[ 1 ] || 2 != v[ max - 1 ] )
  {
    return false;
  }

  us.split( 0, 3 );

  ui.set_merge_on();
  ui.sort();

  mergesort_util<int> uv( v, max );
  uv.split( 0, max - 1 );

  if ( 1 != v[ 0 ] || max != v[ max - 1 ] ||
      "C" != s[ 2 ] || "Cobol" != s[ 1 ] ||
      3 != x[ 2 ] || 7 != x[ 6 ] )
  {
    return false;
  }


  mergesort_util<int, std::greater<int> > vg( v, max );
  vg.sort();

  mergesort( s, sizeof( s ) / sizeof( s[ 0 ] ), string_size_less() );

  mergesort( x, sizeof( x ) / sizeof( x[ 0 ] ) );

  return ( "C" == s[ 0 ] && "ABAP" == s[ 1 ] && v[ 0 ] == max && 1 == x[ 0 ] &&
           3 == x[ 2 ] && max / 2 == v[ max / 2 ] );
}

int main()
{
  std::cout
    << "Your solution is "
    << (check() ? "" : "not ")
    << "ready for submission."
    << std::endl;
}
