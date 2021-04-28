// CadEx Task.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <math.h>
#include <vector>
#include <ctime>
#include <random>
#include <typeinfo>
#include <algorithm>
#include <omp.h>
#include "CadExLib.h"
#include <memory>


enum Figures
{
	circle,
	elips,
	helix
};

int main()
{
	std::vector<std::shared_ptr<Curve>> curves;
	uint8_t var;
	srand(time(0));

	std::random_device genSource;
	std::uniform_real_distribution<> generator(r_min, r_max); //Генерация случайного  вещественного положительного числа в заданном дапазоне

	double a, b, step;
	for (int i = 0; i < 100; i++) // инициализируем контейнер различными кривыми 
	{
		var = rand() % 3;//здесь достаточно классической функции rand()
		switch (var)
		{
		case circle:
			a = static_cast<double>(generator(genSource));
			curves.push_back(std::make_shared<Circle>(a));
			break;
		case elips:
			a = static_cast<double>(generator(genSource));
			b = static_cast<double>(generator(genSource));
			curves.push_back(std::make_shared<Elips>(a, b));
			break;

		case helix:
			a = static_cast<double>(generator(genSource));
			step = static_cast<double>(generator(genSource));
			curves.push_back(std::make_shared<Helix>(a, step));
			break;
		}
	}

	const double t1 = PI / 4;

	for (size_t i = 0; i < curves.size(); i++) //подсчет в точке PI/4
	{
		std::cout << curves[i]->GetName() << " ";
		std::cout << curves[i]->GetPoint(t1) << std::endl;
	}

	std::vector<std::shared_ptr<Circle>> circles;//новый контейнер для окружностей

	for (size_t i = 0; i < curves.size(); i++)//выделяем из всего вектора только окружности
	{
		if (curves[i]->GetName() == "Circle")//так же можно просто использовать метод getName()
			circles.push_back(std::dynamic_pointer_cast<Circle>(curves[i]));
	}

	std::sort(circles.begin(), circles.end(), [](std::shared_ptr<Circle> c1, std::shared_ptr<Circle> c2) { // сортируем по возрастанию
		return *c1 < *c2;
		});

	std::cout << "Sorted circles" << std::endl;
	for (size_t i = 0; i < circles.size(); i++)
	{
		std::cout << circles[i]->GetName() << " radius=" << circles[i]->GetRadius() << std::endl;
	}

	double sum = 0;
#pragma omp parallel reduction(+:sum) //многопоточное вычисление
	{
#pragma omp for 
		for (int i = 0; i < circles.size(); i++)
		{
			sum += circles[i]->GetRadius();
		}
	}
	std::cout << "sum2=" << sum << std::endl;

	return 0;
}

