///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-05-19
// Updated : 2009-05-19
// Licence : This source is under MIT License
// File    : glm/gtx/simd_mat4.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace detail
{
	GLM_FUNC_QUALIFIER fmat4x4SIMD::size_type fmat4x4SIMD::value_size()
	{
		return sizeof(value_type);
	}

	GLM_FUNC_QUALIFIER fmat4x4SIMD::size_type fmat4x4SIMD::col_size()
	{
		return 4;
	}

	GLM_FUNC_QUALIFIER fmat4x4SIMD::size_type fmat4x4SIMD::row_size()
	{
		return 4;
	}

    GLM_FUNC_QUALIFIER fmat4x4SIMD::fmat4x4SIMD()
    {}

    GLM_FUNC_QUALIFIER fmat4x4SIMD::fmat4x4SIMD(float const & s)
    {
		this->Data[0] = fvec4SIMD(s, 0, 0, 0);
		this->Data[1] = fvec4SIMD(0, s, 0, 0);
		this->Data[2] = fvec4SIMD(0, 0, s, 0);
		this->Data[3] = fvec4SIMD(0, 0, 0, s);
    }

	GLM_FUNC_QUALIFIER fmat4x4SIMD::fmat4x4SIMD
	(
		float const & x0, float const & y0, float const & z0, float const & w0,
		float const & x1, float const & y1, float const & z1, float const & w1,
		float const & x2, float const & y2, float const & z2, float const & w2,
		float const & x3, float const & y3, float const & z3, float const & w3
	)
	{
		this->Data[0] = fvec4SIMD(x0, y0, z0, w0);
		this->Data[1] = fvec4SIMD(x1, y1, z1, w1);
		this->Data[2] = fvec4SIMD(x2, y2, z2, w2);
		this->Data[3] = fvec4SIMD(x3, y3, z3, w3);
	}

	GLM_FUNC_QUALIFIER fmat4x4SIMD::fmat4x4SIMD
	(
		fvec4SIMD const & v0,
		fvec4SIMD const & v1,
		fvec4SIMD const & v2,
		fvec4SIMD const & v3
	)
	{
		this->Data[0] = v0;
		this->Data[1] = v1;
		this->Data[2] = v2;
		this->Data[3] = v3;
	}

	GLM_FUNC_QUALIFIER fmat4x4SIMD::fmat4x4SIMD
	(
		tmat4x4<float> const & m
	)
	{
		this->Data[0] = fvec4SIMD(m[0]);
		this->Data[1] = fvec4SIMD(m[1]);
		this->Data[2] = fvec4SIMD(m[2]);
		this->Data[3] = fvec4SIMD(m[3]);
	}

	//////////////////////////////////////
	// Accesses

	GLM_FUNC_QUALIFIER fvec4SIMD & fmat4x4SIMD::operator[]
	(
		fmat4x4SIMD::size_type i
	)
	{
		assert(
			i >= fmat4x4SIMD::size_type(0) &&
			i < fmat4x4SIMD::col_size());

		return this->Data[i];
	}

	GLM_FUNC_QUALIFIER fvec4SIMD const & fmat4x4SIMD::operator[]
	(
		fmat4x4SIMD::size_type i
	) const
	{
		assert(
			i >= fmat4x4SIMD::size_type(0) &&
			i < fmat4x4SIMD::col_size());

		return this->Data[i];
	}

    //////////////////////////////////////////////////////////////
    // mat4 operators

    GLM_FUNC_QUALIFIER fmat4x4SIMD& fmat4x4SIMD::operator= 
	(
		fmat4x4SIMD const & m
	)
    {
		this->Data[0] = m[0];
		this->Data[1] = m[1];
		this->Data[2] = m[2];
		this->Data[3] = m[3];
        return *this;
    }

    GLM_FUNC_QUALIFIER fmat4x4SIMD & fmat4x4SIMD::operator+= 
	(
		fmat4x4SIMD const & m
	)
    {
		this->Data[0].Data = _mm_add_ps(this->Data[0].Data, m[0].Data);
		this->Data[1].Data = _mm_add_ps(this->Data[1].Data, m[1].Data);
		this->Data[2].Data = _mm_add_ps(this->Data[2].Data, m[2].Data);
		this->Data[3].Data = _mm_add_ps(this->Data[3].Data, m[3].Data);
        return *this;
    }

    GLM_FUNC_QUALIFIER fmat4x4SIMD & fmat4x4SIMD::operator-= 
	(
		fmat4x4SIMD const & m
	)
    {
		this->Data[0].Data = _mm_sub_ps(this->Data[0].Data, m[0].Data);
		this->Data[1].Data = _mm_sub_ps(this->Data[1].Data, m[1].Data);
		this->Data[2].Data = _mm_sub_ps(this->Data[2].Data, m[2].Data);
		this->Data[3].Data = _mm_sub_ps(this->Data[3].Data, m[3].Data);

        return *this;
    }

    GLM_FUNC_QUALIFIER fmat4x4SIMD & fmat4x4SIMD::operator*= 
	(
		fmat4x4SIMD const & m
	)
    {
		sse_mul_ps(&this->Data[0].Data, &m.Data[0].Data, &this->Data[0].Data);
        return *this;
    }

    GLM_FUNC_QUALIFIER fmat4x4SIMD & fmat4x4SIMD::operator/= 
	(
		fmat4x4SIMD const & m
	)
    {
		__m128 Inv[4];
		sse_inverse_ps(&m.Data[0].Data, Inv);
		sse_mul_ps(&this->Data[0].Data, Inv, &this->Data[0].Data);
        return *this;
    }

    GLM_FUNC_QUALIFIER fmat4x4SIMD & fmat4x4SIMD::operator+= 
	(
		float const & s
	)
    {
		__m128 Operand = _mm_set_ps1(s);
		this->Data[0].Data = _mm_add_ps(this->Data[0].Data, Operand);
		this->Data[1].Data = _mm_add_ps(this->Data[1].Data, Operand);
		this->Data[2].Data = _mm_add_ps(this->Data[2].Data, Operand);
		this->Data[3].Data = _mm_add_ps(this->Data[3].Data, Operand);
        return *this;
    }

    GLM_FUNC_QUALIFIER fmat4x4SIMD & fmat4x4SIMD::operator-= 
	(
		float const & s
	)
    {
		__m128 Operand = _mm_set_ps1(s);
		this->Data[0].Data = _mm_sub_ps(this->Data[0].Data, Operand);
		this->Data[1].Data = _mm_sub_ps(this->Data[1].Data, Operand);
		this->Data[2].Data = _mm_sub_ps(this->Data[2].Data, Operand);
		this->Data[3].Data = _mm_sub_ps(this->Data[3].Data, Operand);
        return *this;
    }

    GLM_FUNC_QUALIFIER fmat4x4SIMD & fmat4x4SIMD::operator*= 
	(
		float const & s
	)
    {
		__m128 Operand = _mm_set_ps1(s);
		this->Data[0].Data = _mm_mul_ps(this->Data[0].Data, Operand);
		this->Data[1].Data = _mm_mul_ps(this->Data[1].Data, Operand);
		this->Data[2].Data = _mm_mul_ps(this->Data[2].Data, Operand);
		this->Data[3].Data = _mm_mul_ps(this->Data[3].Data, Operand);
        return *this;
    }

    GLM_FUNC_QUALIFIER fmat4x4SIMD & fmat4x4SIMD::operator/= 
	(
		float const & s
	)
    {
		__m128 Operand = _mm_div_ps(one, _mm_set_ps1(s));
		this->Data[0].Data = _mm_mul_ps(this->Data[0].Data, Operand);
		this->Data[1].Data = _mm_mul_ps(this->Data[1].Data, Operand);
		this->Data[2].Data = _mm_mul_ps(this->Data[2].Data, Operand);
		this->Data[3].Data = _mm_mul_ps(this->Data[3].Data, Operand);
        return *this;
    }

    GLM_FUNC_QUALIFIER fmat4x4SIMD & fmat4x4SIMD::operator++ ()
    {
		this->Data[0].Data = _mm_add_ps(this->Data[0].Data, one);
		this->Data[1].Data = _mm_add_ps(this->Data[1].Data, one);
		this->Data[2].Data = _mm_add_ps(this->Data[2].Data, one);
		this->Data[3].Data = _mm_add_ps(this->Data[3].Data, one);
        return *this;
    }

    GLM_FUNC_QUALIFIER fmat4x4SIMD & fmat4x4SIMD::operator-- ()
    {
		this->Data[0].Data = _mm_sub_ps(this->Data[0].Data, one);
		this->Data[1].Data = _mm_sub_ps(this->Data[1].Data, one);
		this->Data[2].Data = _mm_sub_ps(this->Data[2].Data, one);
		this->Data[3].Data = _mm_sub_ps(this->Data[3].Data, one);
        return *this;
    }

}//namespace detail

namespace gtx{
namespace simd_mat4
{
	GLM_FUNC_QUALIFIER detail::tmat4x4<float> mat4_cast
	(
		detail::fmat4x4SIMD const & x
	)
	{
		GLM_ALIGN(16) detail::tmat4x4<float> Result;
		_mm_store_ps(&Result[0][0], x.Data[0].Data);
		_mm_store_ps(&Result[1][0], x.Data[1].Data);
		_mm_store_ps(&Result[2][0], x.Data[2].Data);
		_mm_store_ps(&Result[3][0], x.Data[3].Data);
		return Result;
	}

	GLM_FUNC_QUALIFIER detail::fmat4x4SIMD matrixCompMult
	(
		detail::fmat4x4SIMD const & x,
		detail::fmat4x4SIMD const & y
	)
	{
		detail::fmat4x4SIMD result;
		result[0] = x[0] * y[0];
		result[1] = x[1] * y[1];
		result[2] = x[2] * y[2];
		result[3] = x[3] * y[3];
		return result;
	}

	GLM_FUNC_QUALIFIER detail::fmat4x4SIMD outerProduct
	(
		detail::fvec4SIMD const & c,
		detail::fvec4SIMD const & r
	)
	{
		__m128 Shu0 = _mm_shuffle_ps(r.Data, r.Data, _MM_SHUFFLE(0, 0, 0, 0));
		__m128 Shu1 = _mm_shuffle_ps(r.Data, r.Data, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 Shu2 = _mm_shuffle_ps(r.Data, r.Data, _MM_SHUFFLE(2, 2, 2, 2));
		__m128 Shu3 = _mm_shuffle_ps(r.Data, r.Data, _MM_SHUFFLE(3, 3, 3, 3));

		detail::fmat4x4SIMD result(detail::fmat4x4SIMD::null);
		result[0].Data = _mm_mul_ps(c.Data, Shu0);
		result[1].Data = _mm_mul_ps(c.Data, Shu1);
		result[2].Data = _mm_mul_ps(c.Data, Shu2);
		result[3].Data = _mm_mul_ps(c.Data, Shu3);
		return result;
	}

	GLM_FUNC_QUALIFIER detail::fmat4x4SIMD transpose(detail::fmat4x4SIMD const & m)
	{
		detail::fmat4x4SIMD result;
		detail::sse_transpose_ps(&m[0].Data, &result[0].Data);
		return result;
	}

	GLM_FUNC_QUALIFIER float determinant(detail::fmat4x4SIMD const & m)
	{
		float Result;
		_mm_store_ss(&Result, detail::sse_det_ps(&m[0].Data));
		return Result;
	}

	GLM_FUNC_QUALIFIER detail::fmat4x4SIMD inverse(detail::fmat4x4SIMD const & m)
	{
		detail::fmat4x4SIMD result;
		detail::sse_inverse_ps(&m[0].Data, &result[0].Data);
		return result;
	}
}//namespace simd_mat4
}//namespace gtx

}//namespace glm
