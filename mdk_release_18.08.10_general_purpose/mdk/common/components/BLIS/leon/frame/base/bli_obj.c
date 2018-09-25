/*

   BLIS    
   An object-based framework for developing high-performance BLAS-like
   libraries.

   Copyright (C) 2014, The University of Texas

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    - Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    - Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    - Neither the name of The University of Texas nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "blis.h"
#include "mv_types.h"

void bli_obj_create( num_t  dt,
                     dim_t  m,
                     dim_t  n,
                     inc_t  rs,
                     inc_t  cs,
                     obj_t* obj )
{
	bli_obj_create_without_buffer( dt, m, n, obj );
	bli_obj_alloc_buffer( rs, cs, obj );
}

void bli_obj_create_with_attached_buffer( num_t  dt,
                                          dim_t  m,
                                          dim_t  n,
                                          void*  p,
                                          inc_t  rs,
                                          inc_t  cs,
                                          obj_t* obj )
{
	bli_obj_create_without_buffer( dt, m, n, obj );

	bli_obj_attach_buffer( p, rs, cs, obj );
}

void bli_obj_create_without_buffer( num_t  dt,
                                    dim_t  m,
                                    dim_t  n,
                                    obj_t* obj )
{
	siz_t  elem_size;
	mem_t* pack_mem;
	void*  s;

	if ( bli_error_checking_is_enabled() )
		bli_obj_create_without_buffer_check( dt, m, n, obj );

	// Query the size of one element of the object's pre-set datatype.
	elem_size = bli_datatype_size( dt );

	// Set any default properties that are appropriate.
	bli_obj_set_defaults( *obj );

	// Set the object root to itself, since obj is not presumed to be a view
	// into a larger matrix. This is typically the only time this field is
	// ever set; henceforth, subpartitions and aliases to this object will
	// get copies of this field, and thus always have access to its
	// "greatest-grand" parent (ie: the original parent, or "root", object).
	// However, there ARE a few places where it is convenient to reset the
	// root field explicitly via bli_obj_set_as_root(). (We do not list
	// those places here. Just grep for bli_obj_set_as_root within the
	// top-level 'frame' directory to see them.
	bli_obj_set_as_root( *obj );

	// Set individual fields.
	bli_obj_set_buffer( NULL, *obj );
	bli_obj_set_datatype( dt, *obj );
	bli_obj_set_elem_size( elem_size, *obj );
	bli_obj_set_target_datatype( dt, *obj );
	bli_obj_set_execution_datatype( dt, *obj );
	bli_obj_set_dims( m, n, *obj );
	bli_obj_set_offs( 0, 0, *obj );
	bli_obj_set_diag_offset( 0, *obj );

	pack_mem = bli_obj_pack_mem( *obj );
	bli_mem_set_buffer( NULL, pack_mem );

	// Set the internal scalar to 1.0.
	s = bli_obj_internal_scalar_buffer( *obj );

	if      ( bli_is_float( dt )    ) { bli_sset1s( *(( float*    )s) ); }
	else if ( bli_is_double( dt )   ) { bli_dset1s( *(( double*   )s) ); }
	else if ( bli_is_scomplex( dt ) ) { bli_cset1s( *(( scomplex* )s) ); }
	else if ( bli_is_dcomplex( dt ) ) { bli_zset1s( *(( dcomplex* )s) ); }
}

void bli_obj_alloc_buffer( inc_t  rs,
                           inc_t  cs,
                           obj_t* obj )
{
	dim_t  n_elem = 0;
	dim_t  m, n;
	inc_t  rs_abs, cs_abs;
	siz_t  elem_size;
	siz_t  buffer_size;
	void*  p;

	m  = bli_obj_length( *obj );
	n  = bli_obj_width( *obj );
	// Adjust the strides, if needed, before doing anything else
	// (particularly, before doing any error checking).
	bli_adjust_strides( m, n, &rs, &cs );
	if ( bli_error_checking_is_enabled() )
		bli_obj_alloc_buffer_check( rs, cs, obj );
	// Query the size of one element.
	elem_size = bli_obj_elem_size( *obj );
	// Compute the magnitude of the row and column strides. We will use
	// these in the comparisons below since those comparisions really
	// relate only to the magnitudes of the strides, not their signs.
	rs_abs = bli_abs( rs );
	cs_abs = bli_abs( cs );
	// Determine how much object to allocate.
	if ( m == 0 || n == 0 )
	{
		// For empty objects, set n_elem to zero. Row and column strides
		// should remain unchanged (because alignment is not needed).
		n_elem = 0;
	}
	else if ( rs_abs == 1 )
	{
		cs     = bli_align_dim_to_size( cs, elem_size,
		                                BLIS_HEAP_STRIDE_ALIGN_SIZE );
		n_elem = bli_abs( cs ) * n;
	}
	else if ( cs_abs == 1 )
	{
		rs     = bli_align_dim_to_size( rs, elem_size,
		                                BLIS_HEAP_STRIDE_ALIGN_SIZE );
		n_elem = bli_abs( rs ) * m;
	}
	else
	{
		if ( rs_abs < cs_abs )
		{
			// Note this case is identical to that of rs == 1 above.
			cs     = bli_align_dim_to_size( cs, elem_size,
			                                BLIS_HEAP_STRIDE_ALIGN_SIZE );
			n_elem = bli_abs( cs ) * n;
		}
		else if ( cs_abs < rs_abs )
		{
			// Note this case is identical to that of cs == 1 above.
			rs     = bli_align_dim_to_size( rs, elem_size,
			                                BLIS_HEAP_STRIDE_ALIGN_SIZE );
			n_elem = bli_abs( rs ) * m;
		}
		else
		{
			bli_check_error_code( BLIS_NOT_YET_IMPLEMENTED );
		}
	}

	// Compute the size of the total buffer to be allocated, which includes
	// padding if the leading dimension was increased for alignment purposes.
	buffer_size = ( siz_t )n_elem * elem_size;
	// Allocate the buffer.
	p = bli_malloc( buffer_size );

	// Set individual fields.
	bli_obj_set_buffer( p, *obj );
	bli_obj_set_incs( rs, cs, *obj );
}

void bli_obj_attach_buffer( void*  p,
                            inc_t  rs,
                            inc_t  cs,
                            obj_t* obj )
{
	dim_t  m, n;

	m = bli_obj_length( *obj );
	n = bli_obj_width( *obj );

	// Adjust the strides, if necessary.
	bli_adjust_strides( m, n, &rs, &cs );

	// Notice that we wait until after strides have been adjusted to
	// error-check.
	if ( bli_error_checking_is_enabled() )
		bli_obj_attach_buffer_check( p, rs, cs, obj );

	// Update the object.
	bli_obj_set_buffer( p, *obj );
	bli_obj_set_incs( rs, cs, *obj );
}

void bli_obj_create_1x1( num_t  dt,
                         obj_t* obj )
{
	bli_obj_create_without_buffer( dt, 1, 1, obj );

	bli_obj_alloc_buffer( 1, 1, obj );
}

void bli_obj_create_1x1_with_attached_buffer( num_t  dt,
                                              void*  p,
                                              obj_t* obj )
{
	bli_obj_create_without_buffer( dt, 1, 1, obj );

	bli_obj_attach_buffer( p, 1, 1, obj );
}

void bli_obj_free( obj_t* obj )
{
	if ( bli_error_checking_is_enabled() )
		bli_obj_free_check( obj );

	// Don't dereference obj if it is NULL.
	if ( obj != NULL )
	{
		// Idiot safety: Don't try to free the buffer field if the object
		// is a detached scalar (ie: if the buffer pointer refers to the
		// address of the internal scalar buffer).
		if ( bli_obj_buffer( *obj ) != bli_obj_internal_scalar_buffer( *obj ) )
			bli_free( bli_obj_buffer( *obj ) );
	}
}

void bli_obj_create_const( double value, obj_t* obj )
{
	gint_t*   temp_i;
	float*    temp_s;
	double*   temp_d;
	scomplex* temp_c;
	dcomplex* temp_z;
	if ( bli_error_checking_is_enabled() )
		bli_obj_create_const_check( value, obj );

	bli_obj_create( BLIS_CONSTANT, 1, 1, 1, 1, obj );

	temp_s = bli_obj_buffer_for_const( BLIS_FLOAT,    *obj );
	temp_d = bli_obj_buffer_for_const( BLIS_DOUBLE,   *obj );
	temp_c = bli_obj_buffer_for_const( BLIS_SCOMPLEX, *obj );
	temp_z = bli_obj_buffer_for_const( BLIS_DCOMPLEX, *obj );
	temp_i = bli_obj_buffer_for_const( BLIS_INT,      *obj );
	
	*temp_s      = ( float  ) value;
	*temp_d      =            value;
	temp_c->real = ( float  ) value;
	temp_c->imag = ( float  ) 0.0;
	temp_z->real =            value;
	temp_z->imag =            0.0;
	*temp_i      = ( gint_t ) value;

}

void bli_obj_create_const_copy_of( obj_t* a, obj_t* b )
{
	gint_t*   temp_i;
	float*    temp_s;
	double*   temp_d;
	scomplex* temp_c;
	dcomplex* temp_z;
	dcomplex  value;

	if ( bli_error_checking_is_enabled() )
		bli_obj_create_const_copy_of_check( a, b );

	bli_obj_create( BLIS_CONSTANT, 1, 1, 1, 1, b );

	temp_s = bli_obj_buffer_for_const( BLIS_FLOAT,    *b );
	temp_d = bli_obj_buffer_for_const( BLIS_DOUBLE,   *b );
	temp_c = bli_obj_buffer_for_const( BLIS_SCOMPLEX, *b );
	temp_z = bli_obj_buffer_for_const( BLIS_DCOMPLEX, *b );
	temp_i = bli_obj_buffer_for_const( BLIS_INT,      *b );

	value.real = 0.0;
	value.imag = 0.0;

	if ( bli_obj_is_float( *a ) )
	{
		value.real = *(( float*    )( bli_obj_buffer_at_off( *a ) ));
		value.imag = 0.0;
	}
	else if ( bli_obj_is_double( *a ) )
	{
		value.real = *(( double*   )( bli_obj_buffer_at_off( *a ) ));
		value.imag = 0.0;
	}
	else if ( bli_obj_is_scomplex( *a ) )
	{
		value.real =  (( scomplex* )( bli_obj_buffer_at_off( *a ) ))->real;
		value.imag =  (( scomplex* )( bli_obj_buffer_at_off( *a ) ))->imag;
	}
	else if ( bli_obj_is_dcomplex( *a ) )
	{
		value.real =  (( dcomplex* )( bli_obj_buffer_at_off( *a ) ))->real;
		value.imag =  (( dcomplex* )( bli_obj_buffer_at_off( *a ) ))->imag;
	}
	else
	{
		bli_check_error_code( BLIS_NOT_YET_IMPLEMENTED );
	}

	*temp_s      = ( float  ) value.real;
	*temp_d      =            value.real;
	temp_c->real = ( float  ) value.real;
	temp_c->imag = ( float  ) value.imag;
	temp_z->real =            value.real;
	temp_z->imag =            value.imag;
	*temp_i      = ( gint_t ) value.real;
}

void bli_adjust_strides( dim_t  m,
                         dim_t  n,
                         inc_t* rs,
                         inc_t* cs )
{
	// Here, we check the strides that were input from the user and modify
	// them if needed.

	// Handle the special "empty" case first. If either dimension is zero,
	// we set both strides to zero.
	if ( m == 0 || n == 0 )
	{
		*rs = 0;
		*cs = 0;

		return;
	}
		
	// Interpret rs = cs = 0 as request for column storage.
	if ( *rs == 0 && *cs == 0 )
	{
		// First we handle the 1x1 scalar case explicitly.
		if ( m == 1 && n == 1 )
		{
			*rs = 1;
			*cs = 1;
		}
		// We use column-major storage, except when m == 1, because we don't
		// want both strides to be unit.
		else if ( m == 1 && n > 1 )
		{
			*rs = n;
			*cs = 1;
		}
		else
		{
			*rs = 1;
			*cs = m;
		}
	}
	else if ( *rs == 1 && *cs == 1 )
	{
		// If both strides are unit, this is probably a "lazy" request for a
		// single vector (but could also be a request for a 1xn matrix in
		// column-major order or an mx1 matrix in row-major order). In BLIS,
		// we have decided to "reserve" the case where rs = cs = 1 for
		// 1x1 scalars only.
		if ( m > 1 && n == 1 )
		{
			// Set the column stride to indicate that this is a column vector
			// stored in column-major order. This is done for legacy reasons,
			// because we at one time we had to satisify the error checking
			// in the underlying BLAS library, which expects the leading 
			// dimension to be set to at least m, even if it will never be
			// used for indexing since it is a vector and thus only has one
			// column of data.
			*cs = m;
		}
		else if ( m == 1 && n > 1 )
		{
			// Set the row stride to indicate that this is a row vector stored
			// in row-major order.
			*rs = n;
		}

		// Nothing needs to be done for the 1x1 scalar case where m == n == 1.
	}
}

static siz_t dt_sizes[6] =
{
	sizeof( float ),
	sizeof( scomplex ),
	sizeof( double ),
	sizeof( dcomplex ),
	sizeof( gint_t ),
	BLIS_CONSTANT_SIZE
};

siz_t bli_datatype_size( num_t dt )
{
	if ( bli_error_checking_is_enabled() )
		bli_datatype_size_check( dt );

	return dt_sizes[dt];
}

dim_t bli_align_dim_to_mult( dim_t dim, dim_t dim_mult )
{
	dim = ( ( dim + dim_mult - 1 ) /
	        dim_mult ) *
	        dim_mult;

	return dim;
}

dim_t bli_align_dim_to_size( dim_t dim, siz_t elem_size, siz_t align_size )
{
	dim = ( ( dim * ( dim_t )elem_size +
	                ( dim_t )align_size - 1
	        ) /
	        ( dim_t )align_size
	        ) *
	        ( dim_t )align_size /
	        ( dim_t )elem_size;

	return dim;
}

static num_t type_union[BLIS_NUM_FP_TYPES][BLIS_NUM_FP_TYPES] =
{
            // s             c              d              z
	/* s */ { BLIS_FLOAT,    BLIS_SCOMPLEX, BLIS_DOUBLE,   BLIS_DCOMPLEX },
	/* c */ { BLIS_SCOMPLEX, BLIS_SCOMPLEX, BLIS_DCOMPLEX, BLIS_DCOMPLEX },
	/* d */ { BLIS_DOUBLE,   BLIS_DCOMPLEX, BLIS_DOUBLE,   BLIS_DCOMPLEX },
	/* z */ { BLIS_DCOMPLEX, BLIS_DCOMPLEX, BLIS_DCOMPLEX, BLIS_DCOMPLEX }
};

num_t bli_datatype_union( num_t dt1, num_t dt2 )
{
	if ( bli_error_checking_is_enabled() )
		bli_datatype_union_check( dt1, dt2 );

	return type_union[dt1][dt2];
}

void bli_obj_print( char* label, obj_t* obj )
{
	FILE*  file     = stdout;
	UNUSED(file);
	mem_t* pack_mem = bli_obj_pack_mem( *obj );
	//mem_t* cast_mem = bli_obj_cast_mem( *obj );

	if ( bli_error_checking_is_enabled() )
		bli_obj_print_check( label, obj );

	FPRINTF0( file, "\n" );
	FPRINTF1( file, "%s\n", label );
	FPRINTF0( file, "\n" );

	FPRINTF2( file, " m x n           %lu x %lu\n", ( unsigned long int )bli_obj_length( *obj ),
	                                               ( unsigned long int )bli_obj_width( *obj ) );
	FPRINTF0( file, "\n" );

	FPRINTF2( file, " offm, offn      %lu, %lu\n", ( unsigned long int )bli_obj_row_offset( *obj ),
	                                              ( unsigned long int )bli_obj_col_offset( *obj ) );
	FPRINTF1( file, " diagoff         %ld\n", ( signed long int )bli_obj_diag_offset( *obj ) );
	FPRINTF0( file, "\n" );

	FPRINTF1( file, " buf             %p\n",  ( void* )bli_obj_buffer( *obj ) );
	FPRINTF1( file, " elem size       %lu\n", ( unsigned long int )bli_obj_elem_size( *obj ) );
	FPRINTF2( file, " rs, cs          %ld, %ld\n", ( signed long int )bli_obj_row_stride( *obj ),
	                                              ( signed long int )bli_obj_col_stride( *obj ) );
	FPRINTF0( file, " pack_mem          \n" );
	FPRINTF1( file, " - buf           %p\n",  ( void* )bli_mem_buffer( pack_mem ) );
	FPRINTF1( file, " - buf_type      %lu\n", ( unsigned long int )bli_mem_buf_type( pack_mem ) );
	FPRINTF1( file, " - size          %lu\n", ( unsigned long int )bli_mem_size( pack_mem ) );
	FPRINTF1( file, " m_padded        %lu\n", ( unsigned long int )bli_obj_padded_length( *obj ) );
	FPRINTF1( file, " n_padded        %lu\n", ( unsigned long int )bli_obj_padded_width( *obj ) );
	FPRINTF1( file, " ps              %lu\n", ( unsigned long int )bli_obj_panel_stride( *obj ) );
	FPRINTF0( file, "\n" );

	FPRINTF1( file, " info            %lX\n", ( unsigned long int )(*obj).info );
	FPRINTF1( file, " - is complex    %lu\n", ( unsigned long int )bli_obj_is_complex( *obj ) );
	FPRINTF1( file, " - is d. prec    %lu\n", ( unsigned long int )bli_obj_is_double_precision( *obj ) );
	FPRINTF1( file, " - has trans     %lu\n", ( unsigned long int )bli_obj_has_trans( *obj ) );
	FPRINTF1( file, " - has conj      %lu\n", ( unsigned long int )bli_obj_has_conj( *obj ) );
	FPRINTF1( file, " - struc type    %lu\n", ( unsigned long int )bli_obj_struc( *obj ) );
	FPRINTF1( file, " - uplo type     %lu\n", ( unsigned long int )bli_obj_uplo( *obj ) );
	FPRINTF1( file, "   - is upper    %lu\n", ( unsigned long int )bli_obj_is_upper( *obj ) );
	FPRINTF1( file, "   - is lower    %lu\n", ( unsigned long int )bli_obj_is_lower( *obj ) );
	FPRINTF1( file, "   - is dense    %lu\n", ( unsigned long int )bli_obj_is_dense( *obj ) );
	FPRINTF1( file, " - datatype      %lu\n", ( unsigned long int )bli_obj_datatype( *obj ) );
	FPRINTF1( file, " - target dt     %lu\n", ( unsigned long int )bli_obj_target_datatype( *obj ) );
	FPRINTF1( file, " - exec dt       %lu\n", ( unsigned long int )bli_obj_execution_datatype( *obj ) );
	FPRINTF0( file, "\n" );
}
