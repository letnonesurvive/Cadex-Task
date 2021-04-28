#pragma once
#include <iostream>
#include <string>

const double PI = 3.141592653589793;
const double r_min = 0.01;
const double r_max = 100;


class Point3D
{
private:
	double x;
	double y;
	double z;
public:
	Point3D()
	{
		x = y = z = 0;
	}
	Point3D(double _x, double _y, double _z)
	{
		x = _x; y = _y; z = _z;
	}
	Point3D GetPoint()
	{
		return *this;
	}
	friend std::ostream& operator<<(std::ostream& os, const Point3D& p)
	{
		os << '{' << p.x << ',' << ' ' << p.y << ',' << ' ' << p.z << '}';
		return os;
	};
};

class Curve
{
protected:
	
public:
	Curve() {}
	virtual std::string GetName()const noexcept = 0;
	virtual Point3D GetPoint(double t) = 0;
	virtual Point3D Derivative(double t) = 0;
	virtual ~Curve() {} 
};

class Circle :public Curve
{
private:
	double radius;
public:
	Circle()
	{
		radius = 0;
	}
	Circle(double _radius)
	{
		if (_radius < r_min)
			throw std::invalid_argument("The parameters must be a positive value");
		else if (_radius > r_max)
			throw std::invalid_argument("Parameters too large");
		radius = _radius;
	}
	static std::string name()noexcept
	{
		return "Circle";
	}
	std::string GetName() const noexcept 
	{
		return name();
	}
	double GetRadius() const
	{
		return radius;
	}
	Point3D GetPoint(double t) override
	{
		Point3D point(radius * cos(t), radius * sin(t), 0);
		return point;
	}
	Point3D Derivative(double t) override
	{
		Point3D deriv_point(-radius * sin(t), radius * cos(t), 0);
		return deriv_point;
	}
	friend bool operator < (Circle const& c1, Circle const& c2) // оператор перегружен для для сортировки
	{
		return (c1.GetRadius() < c2.GetRadius());
	}
};

class Elips : public Curve
{
private:
	double a, b;
public:
	Elips()
	{
		a = b = 0;
	}
	Elips(double _a, double _b)
	{
		if (_a < 0 || _b < 0)
			throw std::invalid_argument("The parameters must be a positive value");
		else if (a > r_max || b > r_max)
			throw std::invalid_argument("Parameters too large");
		a = _a;
		b = _b;
	}
	static std::string name()noexcept
	{
		return "Elips";
	}
	virtual std::string GetName() const noexcept
	{
		return name();
	}
	double GetOxRadius() const
	{
		return a;
	}
	double GetOyRadius() const
	{
		return b;
	}
	Point3D GetPoint(double t) override
	{
		Point3D point(a * cos(t), b * sin(t), 0);
		return point;
	}
	Point3D Derivative(double t) override
	{
		Point3D deriv_point(-a * sin(t), b * cos(t), 0);
		return deriv_point;
	}
};

class Helix : public Curve
{
private:
	double radius;
	double step;
public:
	Helix()
	{
		radius = 0;
		step = 0;
		
	}
	Helix(double _radius, double _step)
	{
		if (_radius < 0 || _step < 0)
			throw std::invalid_argument("The parameters must be a positive value");
		else if (radius > r_max || step > r_max)
			throw std::invalid_argument("Parameters too large");
		radius = _radius;
		step = _step;
	}
	static std::string name()noexcept
	{
		return "Helix";
	}
	virtual std::string GetName()const noexcept
	{
		return name();
	}
	Point3D GetPoint(double t) override
	{
		Point3D point(radius * cos(t), radius * sin(t), t / (2 * PI) * step);
		return point;
	}
	double GetRadius() const
	{
		return radius;
	}
	double GetStep() const
	{
		return step;
	}
	Point3D Derivative(double t) override
	{
		Point3D deriv_point(-radius * sin(t), radius * cos(t), step / (2 * PI));
		return deriv_point;
	}
};