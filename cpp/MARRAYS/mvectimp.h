/*------------------------------------------------------------------------*/
/*                                                                        */
/*  MVECTIMP.H                                                            */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __MVECTIMP_H )
#define __MVECTIMP_H

#include <windows.h>

#if !defined( __LIMITS_H )
#include <Limits.h>
#endif  // __LIMITS_H

#if !defined( __CHECKS_H )
#include <Checks.h>
#endif  // __CHECKS_H

#if !defined( __STDTEMPL_H )
#include <StdTempl.h>
#endif  // __STDTEMPL_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BIM_VectorImp                                 */
/*                                                                        */
/*  Implements a vector of objects of type T.  Assumes that               */
/*  T has meaningful copy semantics and a default constructor.            */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BIM_VectorImp
{

public:

	 friend class _CLASSTYPE BIM_VectorIteratorImp<T>;

	 BIM_VectorImp() :
		  h_data(0),
		  data(0),
		  lim(0)
		  {
		  }

	 BIM_VectorImp( int sz, int = 0 ) :
		  lim(sz)
		  {
		  // since we are operating at near the limit for int operations, convert the sizes to long during 
		  // math & allocation requests so that we don't hose ourselves...		  
		  h_data = GlobalAlloc( GHND, (long)((long) sizeof( T ) * (long)sz) );
		  data = ( T huge* ) GlobalLock( h_data );
		  }

	 BIM_VectorImp( const BIM_VectorImp<T>  & );

	 const BIM_VectorImp<T>  & operator = ( const BIM_VectorImp<T>  & );

	 ~BIM_VectorImp()
		  {
		  GlobalUnlock( h_data );
		  GlobalFree( h_data );
		  }

	 T  & operator [] ( int index ) const
		  {
		  PRECONDITION( lim > 0 && data != 0 && index < lim );
		  return data[index];
		  }

	 int limit() const
		  {
		  return lim;
		  }

	 virtual int top() const
		  {
		  return lim;
		  }

	 void resize( int, int = 0 );

	 void flush( int = 0, int = INT_MAX, int = 0 ) {}

	 void forEach( void ( *f)(T  &, void  *), void  *args )
		  {
		  forEach( f, args, 0, lim );
		  }

	 void forEach( void ( *)(T  &, void  *),
						void  *,
						int,
						int
					 );

	 T huge *firstThat( int ( *)(const T  &, void  *),
							  void  *,
							  int,
							  int
							) const;

	 T huge *firstThat( int ( *cond)(const T  &, void  *),
							  void  *args
							) const
		  {
		  return firstThat( cond, args, 0, lim );
		  }

	 T huge *lastThat( int ( *)(const T  &, void  *),
							 void  *,
							 int,
							 int
						  ) const;

	 T huge *lastThat( int ( *cond)(const T  &, void  *),
							 void  *args
						  ) const
		  {
		  return lastThat( cond, args, 0, lim );
		  }

	 virtual int getDelta() const
		  {
		  return 0;
		  }

protected:

	 T huge * data;
	 HGLOBAL  h_data;
	 int lim;

	 virtual void zero( int, int )
		  {
		  }

	 virtual void removeData( T )
		  {
		  }

};

template <class T>
BIM_VectorImp<T>::BIM_VectorImp( const BIM_VectorImp<T>  & v ) :
	 lim(v.lim)
{
	 // since we are operating at near the limit for int operations, convert the sizes to long during 
	 // math & allocation requests so that we don't hose ourselves...
	 h_data = GlobalAlloc( GHND, (long)((long)sizeof( T ) * (long)v.lim) );
	 data   = ( T huge* ) GlobalLock( h_data );

	 PRECONDITION( lim == 0 || (data != 0 && v.data != 0) );
	 for( int i = 0; i < lim; i++ )
		  data[i] = v.data[i];
}

template <class T>
const BIM_VectorImp<T>  & BIM_VectorImp<T>::operator = ( const BIM_VectorImp<T>  & v )
{
	 if( data != v.data )
		  {
		  GlobalUnlock( h_data );
		  GlobalFree( h_data );
		  // since we are operating at near the limit for int operations, convert the sizes to long during 
		  // math & allocation requests so that we don't hose ourselves...
		  h_data =  GlobalAlloc( GHND, (long)((long)sizeof( T ) * (long)v.lim) );
		  data =  ( T huge* ) GlobalLock( h_data );

		  CHECK( data != 0 );
		  lim = v.lim;
		  for( int i = 0; i < lim; i++ )
				data[i] = v.data[i];
		  }
	 return *this;
}

inline int nextDelta( int sz, int delta )
{

	return (sz % delta) ? ((sz + delta)/ delta) * delta : sz;

}

template <class T>
void BIM_VectorImp<T>::resize( int newSz, int offset )
{
	 long l_sz;
	 int	sz;
	 if( newSz <= lim || getDelta() == 0 )
		  return;

	 // get to the absolute top of the 32K barrier....
	 l_sz = (long) lim + (long) nextDelta( newSz - lim, getDelta() );
	 if (l_sz > INT_MAX)
	 {
		sz = INT_MAX;
	 }
	 else
	 {
		sz = (int) l_sz;
	 }
	 
	 // since we are operating at near the limit for int operations, convert the sizes to long during 
	 // math & allocation requests so that we don't hose ourselves...
	 HGLOBAL h_temp = GlobalAlloc( GHND, (long) ((long) sizeof( T ) * (long) sz) );
	 T huge *temp = ( T huge* ) GlobalLock( h_temp );

	 int last = ( sz-offset < lim ) ? sz-offset : lim ;
	 for( int i = 0; i < last; i++ )
		  temp[i+offset] = data[i];

	 GlobalUnlock( h_data );
	 GlobalFree( h_data );

	 h_data = h_temp;
	 data = temp;
	 lim = sz;
	 zero( last+offset, sz );
}

template <class T>
void BIM_VectorImp<T>::forEach( void ( *f)( T  &, void  * ),
										 void  *args,
										 int start,
										 int stop
									  )
{
	 for( int cur = start; cur < stop; cur++ )
		  f( data[cur], args );
}

template <class T>
T huge *BIM_VectorImp<T>::firstThat( int ( *cond)( const T  &, void  * ),
										 void  *args,
										 int start,
										 int stop
									  ) const
{
	 for( int cur = start; cur < stop; cur++ )
		  if( cond( data[cur], args ) != 0 )
				return &data[cur];
	 return 0;
}

template <class T>
T huge *BIM_VectorImp<T>::lastThat( int ( *cond)( const T  &, void  * ),
										void  *args,
										int start,
										int stop
									 ) const
{
	 T huge *res = 0;
	 for( int cur = start; cur < stop; cur++ )
		  if( cond( data[cur], args ) != 0 )
				res = &data[cur];
	 return res;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BIM_CVectorImp                                */
/*                                                                        */
/*  Implements a counted vector of objects of type T.  Assumes that       */
/*  T has meaningful copy semantics and a default constructor.            */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BIM_CVectorImp : public BIM_VectorImp<T>
{

public:

	 BIM_CVectorImp() :
		  count_(0),
		  delta(0)
		  {
        }

    BIM_CVectorImp( int sz, int d = 0 ) :
        BIM_VectorImp<T>( sz ),
        count_(0),
		  delta(d)
        {
		  }

	 void add( T );
	 void addAt( T, int );
	 void detach( T, int = 0 );
	 void detach( unsigned int, int = 0 );

	 int isEmpty() const
		  {
		  return count_ == 0;
		  }

	 void forEach( void ( *f)(T  &, void  *), void  *args )
		  {
		  forEach( f, args, 0, count_ );
		  }

	 void forEach( void ( *func)(T  &, void  *),
						void  *args,
						int low,
						int high
					 )
		  {
		  BIM_VectorImp<T>::forEach( func, args, low, high );
		  }

	 T huge *firstThat( int ( *cond)(const T  &, void  *),
							  void  *args
							) const
		  {
		  return firstThat( cond, args, 0, count_ );
		  }

	 T huge *firstThat( int ( *cond)(const T  &, void  *),
							  void  *args,
							  int low,
							  int high
							) const
		  {
		  return BIM_VectorImp<T>::firstThat( cond, args, low, high );
		  }

	 T huge *lastThat( int ( *cond)(const T  &, void  *),
							 void  *args
						  ) const
		  {
		  return lastThat( cond, args, 0, count_ );
		  }

	 T huge *lastThat( int ( *cond)(const T  &, void  *),
							 void  *args,
							 int low,
							 int high
						  ) const
		  {
		  return BIM_VectorImp<T>::lastThat( cond, args, low, high );
		  }

	 void flush( int del = 0,
					 int stop = INT_MAX,
					 int start = 0
				  )
		  {
		  BIM_VectorImp<T>::flush( del, stop, start ); count_ = 0;
		  }

	 virtual unsigned find( T ) const;

	 virtual int top() const
		  {
		  return count_;
		  }

	 int count() const
		  {
		  return count_;
		  }

	 virtual int getDelta() const
		  {
		  return delta;
		  }

protected:

	 int count_;
	 int delta;

};

template <class T> void BIM_CVectorImp<T>::add( T t )
{
	 if( ++count_ > lim )
		  resize( count_ );
	 data[count_-1] = t;
}

template <class T> void BIM_CVectorImp<T>::addAt( T t, int loc)
{
	 if( loc >= lim )
		  resize( loc+1 );
	 data[loc] = t;
}

template <class T> void BIM_CVectorImp<T>::detach( T t, int del )
{
	 detach( find(t), del );
}

template <class T> void BIM_CVectorImp<T>::detach( unsigned int loc, int del )
{
	 if( loc >= lim )
		  return;
	 if( del )
		  removeData( data[loc] );
	 if( loc >= count_ )
		  {
		  zero( loc, loc+1 ); // removing an element that's not
		  return;             // in the counted portion
		  }
	 count_--;
	 for( int cur = loc; cur < count_; cur++ )
		  data[cur] = data[cur+1];
	 zero( count_, count_+1 );
}

template <class T> unsigned BIM_CVectorImp<T>::find( T t ) const
{
	 if( count_ != 0 )
		  {
		  for( int loc = 0; loc < count_; loc++ )
				if( data[loc] == t )
					 return loc;
		  }
	 return INT_MAX;
}

											
											
/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BIM_SVectorImp                               */
/*                                                                        */
/*  Implements a sorted vector of objects of type T.  Assumes that        */
/*  T has meaningful copy semantics, a meaningful < operator,             */
/*  and a default constructor.                                            */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BIM_SVectorImp : public BIM_CVectorImp<T>
{

public:

    BIM_SVectorImp()
        {
        }

    BIM_SVectorImp( unsigned sz, unsigned d = 0 ) :
        BIM_CVectorImp<T>( sz, d )
		  {
		  }

	 void add( T );

	 virtual unsigned find( T ) const;

};

template <class T> void BIM_SVectorImp<T>::add( T t )
{
    unsigned loc = count_++;
    if( count_ > lim )
        resize( count_ );
    while( loc > 0 && t < data[loc-1] )
        {
		  data[loc] = data[loc-1];
		  loc--;
		  }
	 data[loc] = t;
}

template <class T> unsigned BIM_SVectorImp<T>::find( T t ) const
{
	 unsigned lower = 0;
	 unsigned upper = count_-1;
	 if( count_ != 0 )
		  {
		  while( lower < upper && upper != UINT_MAX )
				{
				unsigned middle = (lower+upper)/2;
				if( data[middle] == t )
					 return middle;
				if( data[middle] < t )
					 lower = middle+1;
				else
					 upper = middle-1;
				}
		  }
	 if( lower == upper && data[lower] == t )
		  return lower;
	 else
		  return UINT_MAX;
}
											
											

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BIM_VectorIteratorImp                         */
/*                                                                        */
/*  Implements a vector iterator.  This iterator works with any direct    */
/*  vector.  For indirect vectors, see BIM_IVectorIteratorImp.             */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BIM_VectorIteratorImp
{

public:

    BIM_VectorIteratorImp( const BIM_VectorImp<T>  &v )
		  {
        vect = &v;
        restart(0,v.limit());
        }

    BIM_VectorIteratorImp( const BIM_VectorImp<T>  &v,
                          int start,
								  int stop
                        )
        {
        vect = &v;
        restart( start, stop );
        }


    operator int()
        {
        return cur < upper;
        }

    T current()
        {
        return (cur < upper) ? (*vect)[cur] : (*vect)[upper-1];
        }

	 T operator ++ ( int )
        {
        if( cur >= upper )
            return (*vect)[upper-1];
		  else
            return (*vect)[cur++];
		  }

    T operator ++ ()
        {
        if( cur < upper )
            cur++;
        if( cur >= upper )
            return (*vect)[upper-1];
        else
            return (*vect)[cur];
        }

    void restart()
        {
        restart(lower,upper);
        }

	 void restart( int start, int stop )
        {
        cur = lower = start;
        upper = stop;
        }

private:

    const BIM_VectorImp<T>  *vect;
    int cur;
    int lower, upper;

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T, class Vect> class BIM_InternalIVectorImp            */
/*                                                                        */
/*  Implements a vector of pointers to objects of type T.                 */
/*  This is implemented through the form of BIM_VectorImp specified by     */
/*  Vect.  Since pointers always have meaningful copy semantics,          */
/*  this class can handle any type of object.                             */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T, class Vect> class _CLASSTYPE BIM_InternalIVectorImp :
    public Vect
{

public:

    BIM_InternalIVectorImp( int sz, int d = 0 ) :
        Vect( sz, d )
        {
        zero( 0, sz );
        }

    ~BIM_InternalIVectorImp()
        {
        flush();
        }

	 T  *  & operator [] ( int index )
		  {
		  PRECONDITION( lim == 0 || data != 0 && index < lim );
		  return (T  *)(data[index]);
		  }

	 T  *  & operator [] ( int index ) const
		  {
		  PRECONDITION( lim > 0 && data != 0 && index < lim );
		  return (T  *)(data[index]);
		  }

	 void flush( int = 0, int = INT_MAX, int = 0 );

	 void forEach( void ( *f)(T  &, void  *), void  *args )
		  {
		  forEach( f, args, 0, lim );
		  }

	 void forEach( void ( *)(T  &, void  *),
						void  *,
						int,
						int
					 );

	 T  *firstThat( int ( *cond)(const T  &, void  *),
							  void  *args
							) const
		  {
		  return firstThat( cond, args, 0, lim );
		  }

	 T  *firstThat( int ( *)(const T  &, void  *),
							  void  *,
							  int,
							  int
							) const;

	 T  *lastThat( int ( *cond)(const T  &, void  *),
							 void  *args
						  ) const
		  {
		  return lastThat( cond, args, 0, lim );
		  }

	 T  *lastThat( int ( *)(const T  &, void  *),
							 void  *,
							 int,
							 int
						  ) const;

	 virtual void zero( int, int );

protected:

	 virtual void removeData( void  *t )
		  {
		  delete (T  *)t;
		  }

private:

	 static void delObj( T  &, void  * );

};

template <class T, class Vect>
void BIM_InternalIVectorImp<T,Vect>::delObj( T  &tRef, void  *vect )
{
	 ((BIM_InternalIVectorImp<T,Vect> *)vect)->removeData( &tRef );
}

template <class T, class Vect>
void BIM_InternalIVectorImp<T,Vect>::flush(
                                           int del,
                                           int upr,
                                           int lwr
                                         )
{
	 upr = ( upr < limit() ) ? upr : limit();
    if( del )
        forEach( delObj, this, lwr, upr );
    zero( lwr, upr );
    Vect::flush( del, upr, lwr );
}

template <class T, class Vect>
void BIM_InternalIVectorImp<T,Vect>::forEach( void ( *f)( T  &, void  * ),
                                             void  *args,
                                             int start,
                                             int stop
                                           )
{
    for( int cur = start; cur < stop; cur++ )
        if( data[cur] != 0 )
            f( *(T  *)(data[cur]), args );
}

template <class T, class Vect>
T  *BIM_InternalIVectorImp<T,Vect>::firstThat( int ( *cond)( const T  &, void  * ),
                                             void  *args,
                                             int start,
															int stop
                                           ) const
{
    for( int cur = start; cur < stop; cur++ )
        if( data[cur] != 0 && cond( *(T  *)(data[cur]), args ) != 0 )
            return (T  *)data[cur];
    return 0;
}

template <class T, class Vect>
T  *BIM_InternalIVectorImp<T,Vect>::lastThat( int ( *cond)( const T  &, void  * ),
                                            void  *args,
                                            int start,
                                            int stop
                                          ) const
{
    T  *res = 0;
    for( int cur = start; cur < stop; cur++ )
        if( data[cur] != 0 && cond( *(T  *)(data[cur]), args ) != 0 )
            res = (T  *)data[cur];
    return res;
}

template <class T, class Vect>
void BIM_InternalIVectorImp<T,Vect>::zero( int lwr, int upr )
{
	 for( int i = lwr; i < ( ( limit() < upr ) ? limit() : upr ); i++ )
        data[i] = 0;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BIM_IVectorImp                                */
/*                                                                        */
/*  Implements a vector of pointers to objects of type T.                 */
/*  This is implemented through the template BIM_InternalIVectorImp.       */
/*  Since pointers always have meaningful copy semantics, this class      */
/*  can handle any type of object.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

//template <class T> class _CLASSTYPE BIM_IVectorImp :
//	 public BIM_InternalIVectorImp<T, BIM_VectorImp<void  *> >
//{
//
//public:
//
//	 BIM_IVectorImp( int sz ) :
//		  BIM_InternalIVectorImp<T, BIM_VectorImp<void  *> >(sz)
//		  {
//		  }
//
//
//};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BIM_ICVectorImp                               */
/*                                                                        */
/*  Implements a counted vector of pointers to objects of type T.         */
/*  Since pointers always have meaningful copy semantics, this class      */
/*  can handle any type of object.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BIM_ICVectorImp :
    public BIM_InternalIVectorImp<T, BIM_CVectorImp<void  *> >
{

public:

    BIM_ICVectorImp( int sz, int d = 0 ) :
        BIM_InternalIVectorImp<T, BIM_CVectorImp<void  *> >(sz)
        {
        delta = d;
        }

	 unsigned find( T  *t ) const
		  {
		  return find( (void  *)t );
		  }

    void add( T  *t );

protected:

	 virtual unsigned find( void  * ) const;

};

template <class T> unsigned BIM_ICVectorImp<T>::find( void  *t ) const
{
	 if( limit() != 0 )
		  {
		  for( int loc = 0; loc < limit(); loc++ )
				if( data[loc] &&
					 *(const T  *)(data[loc]) == *(const T  *)t
				  )
					 return loc;
		  }
	 return INT_MAX;
}

template <class T > void BIM_ICVectorImp<T>::add( T  *t )
{
	 while( count_ < limit() && (*this)[count_] != 0 )
		  count_++;
    BIM_InternalIVectorImp<T, BIM_CVectorImp<void  *> >::add(t);
}


/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_ISVectorImp                               */
/*                                                                        */
/*  Implements a sorted vector of pointers to objects of type T.          */
/*  This is implemented through the template BI_InternalIVectorImp.       */
/*  Since pointers always have meaningful copy semantics, this class      */
/*  can handle any type of object.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BIM_ISVectorImp :
    public BIM_InternalIVectorImp<T, BIM_SVectorImp<void *> >
{

public:

    BIM_ISVectorImp( unsigned sz, unsigned d = 0 ) :
        BIM_InternalIVectorImp<T, BIM_SVectorImp<void *> >(sz)
        {
        delta = d;
        }

	 unsigned find( T *t ) const
		  {
		  return find( (void  *)t );
		  }

    void add( T *t );

protected:

	 virtual unsigned find( void * ) const;

};

template <class T> unsigned BIM_ISVectorImp<T>::find( void *t ) const
{

//  TSC Change fix GPR/ 09/01/93
// ------------------------------
//	 unsigned lower = 0;
//	 unsigned upper = count_-1;
//------------------------------- Instead
	 signed lower = 0;
	 signed upper = count_-1;
//-------------------------------
	 if( count_ != 0 )
		  {
		  while( lower < upper )
				{
				unsigned middle = (lower+upper)/2;
				if( *(const T  *)(data[middle]) == *(const T *)t )
					 return middle;
				if( *(const T  *)(data[middle]) < *(const T  *)t )
					 lower = middle+1;
				else
					 upper = middle-1;
				}
		  }
	 if( lower == upper && *(const T *)(data[lower]) == *(const T *)t )
		  return lower;
	 else
		  return UINT_MAX;
}

template <class T> void BIM_ISVectorImp<T>::add( T *t )
{
	 unsigned loc = count_++;
	 if( count_ > lim )
		  resize( count_ );
	 while( loc > 0 && *t < *((T *)(*this)[loc-1]) )
		  {
        data[loc] = data[loc-1];
        loc--;
        }
    data[loc] = t;
}



/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BIM_IVectorIteratorImp                        */
/*                                                                        */
/*  Implements a vector iterator.  This iterator works with any indirect  */
/*  vector.  For direct vectors, see BIM_VectorIteratorImp.                */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BIM_IVectorIteratorImp :
    public BIM_VectorIteratorImp<void  *>
{

public:

    BIM_IVectorIteratorImp( const BIM_VectorImp<void  *>  &v ) :
        BIM_VectorIteratorImp<void  *>(v)
        {
        bump();
        }

    BIM_IVectorIteratorImp( const BIM_VectorImp<void  *>  &v,
									int l, int u
                         ) :
        BIM_VectorIteratorImp<void  *>(v,l,u)
        {
        bump();
        }

    T  *current()
        {
        return (T  *)BIM_VectorIteratorImp<void  *>::current();
        }

	 T  *operator ++ ( int );
    T  *operator ++ ();

    void restart()
        {
        BIM_VectorIteratorImp<void  *>::restart();
        bump();
		  }

	 void restart( int start, int stop )
        {
        BIM_VectorIteratorImp<void  *>::restart( start, stop );
        bump();
        }

private:

    void bump();

};

template <class T> T  * BIM_IVectorIteratorImp<T>::operator ++ ()
{
    BIM_VectorIteratorImp<void  *>::operator++();
    bump();
    return (T  *)current();
}

template <class T> T  * BIM_IVectorIteratorImp<T>::operator ++ ( int )
{
    void *temp = current();
    BIM_VectorIteratorImp<void  *>::operator++(1);
    bump();
    return (T  *)temp;
}

template <class T> void BIM_IVectorIteratorImp<T>::bump()
{
    while( *this != 0 && current() == 0 )
		  BIM_VectorIteratorImp<void  *>::operator++();
}

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif // __MVECTIMP_H