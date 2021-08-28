#include <gsl/gsl_poly.h>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <functional>
#include <vector>
#include <span>
#include <cassert>
#include <numbers>
#include <cmath>

namespace glm
{
    template <typename T, qualifier Q>
    GLM_FUNC_QUALIFIER T l2Norm(vec<2, T, Q> const &a)
    {
        return length(a);
    }
}

template <typename VectorType>
class QuadraticBezier
{
public:
    using value_type = typename VectorType::value_type;

private:
    VectorType _x, _y, _z;

public:
    QuadraticBezier() = default;
    QuadraticBezier(const VectorType &x, const VectorType &y, const VectorType &z) : _x{x}, _y{y}, _z{z}
    {
    }

    VectorType operator()(value_type t) const
    {
        return (1 - t) * (1 - t) * _x + 2 * (1 - t) * t * _y + t * t * _z;
    }
};

template <typename VectorType>
class QuadraticBezierInterpolation
{
public:
    using value_type = typename VectorType::value_type;

private:
    QuadraticBezier<VectorType> _bezier;

public:
    QuadraticBezierInterpolation() = default;
    QuadraticBezierInterpolation(const VectorType &p0, const VectorType &p1, const VectorType &p2)
    {
        static auto square = [](value_type x)
        { return x * x; };
        value_type ti = 0.5;

        auto p20 = p2 - p0, p01 = p0 - p1, p12 = p1 - p2;
        value_type a = square(glm::l2Norm(p20));
        value_type b = static_cast<value_type>(3.0) * glm::dot(p20, p01);
        value_type c = glm::dot(static_cast<value_type>(3.0) * p01 + p12, p01);
        value_type d = -square(glm::l2Norm(p01));
        double x[3];
        int n_res = gsl_poly_solve_cubic(b / a, c / a, d / a, x, x + 1, x + 2);
        switch (n_res)
        {
        case 1:
            ti = static_cast<value_type>(x[0]);
            break;
        case 2:
            for (int i = 0; i < 2; i++)
                if (0 < x[i] && x[i] < 1)
                {
                    ti = static_cast<value_type>(x[i]);
                    break;
                }
            break;
        default:
            gsl_complex complex[3];
            gsl_poly_complex_solve_cubic(b / a, c / a, d / a, complex, complex + 1, complex + 2);
            for (int i = 0; i < 3; i++)
            {
                if (complex[i].dat[0] < 1 && complex[i].dat[0] > 0 && complex[i].dat[1] < 0.01)
                {
                    ti = static_cast<value_type>(complex[i].dat[0]);
                    break;
                }
            }
            break;
        }

        VectorType b1 = (p1 - square(1 - ti) * p0 - square(ti) * p2) / (2 * (1 - ti) * ti);
        _bezier = QuadraticBezier<VectorType>(p0, b1, p2);
    }

    VectorType operator()(value_type t)
    {
        return _bezier(t);
    }
};

template <typename VectorType, typename InterpF>
class YukselC2Interpolation
{
public:
    using value_type = typename VectorType::value_type;
    using interp_function = std::function<VectorType(value_type)>;

private:
    std::vector<interp_function> _interp_f;
    int _num_points;

    VectorType scaled_call(int n, value_type theta)
    {
        assert(n >= 0 && n < _num_points - 2);
        return _interp_f[n](theta / std::numbers::pi_v<value_type>);
    }
    VectorType blend(int n1, int n2, value_type theta)
    {
        return std::cos(theta) * std::cos(theta) * scaled_call(n1, theta + std::numbers::pi_v<value_type> / 2) +
               std::sin(theta) * std::sin(theta) * scaled_call(n2, theta);
    }

public:
    YukselC2Interpolation(std::span<VectorType> points) : _num_points(points.size())
    {
        for (int i = 0; i < points.size() - 2; i++)
            _interp_f.push_back(InterpF(points[i], points[i + 1], points[i + 2]));
    }

    // 0<t<pi/2
    VectorType operator()(int n, value_type theta)
    {
        assert(n >= 0 && n < _num_points - 1);
        if (n == 0)
            return scaled_call(0, theta);
        if (n == _num_points - 2)
            return scaled_call(n - 1, theta + std::numbers::pi_v<value_type> / 2);
        else
            return blend(n - 1, n, theta);
    }
};