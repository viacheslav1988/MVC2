// MVC2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <vector>

class Observer
{
public:
	virtual void update() = 0;
};

class Observable
{
public:
	void addObserver(Observer *observer)
	{
		_observers.push_back(observer);
	}
	void notifyUpdate()
	{
		int size = _observers.size();
		for (int i = 0; i < size; i++)
		{
			_observers[i]->update();
		}
	}
private:
	std::vector<Observer*> _observers;
};

class TemperatureModel : public Observable
{
private:
	double _temperatureF = 0;
public:
	TemperatureModel(double tempF)
	{
		_temperatureF = tempF;
	}
	double getF()
	{
		return _temperatureF;
	}
	double getC()
	{
		return (_temperatureF - 32.0) * 5.0 / 9.0;
	}
	void setF(double tempF)
	{
		_temperatureF = tempF;
		notifyUpdate();
	}
	void setC(double tempC)
	{
		_temperatureF = tempC * 9.0 / 5.0 + 32.0;
		notifyUpdate();
	}
};

class ConsoleView : public Observer
{
public:
	ConsoleView(TemperatureModel *model)
	{
		_model = model;
		_model->addObserver(this);
	}
	virtual void update()
	{
		system("cls");
		printf("Temperature in Celsius: %.2f\n", _model->getC());
		printf("Temperature in Farenheit: %.2f\n", _model->getF());
		printf("Input temperature in Celsius: ");
	}
private:
	TemperatureModel *_model;
};

class Controller
{
public:
	Controller(TemperatureModel *model)
	{
		_model = model;
	}
	void start()
	{
		_model->setC(0);

		double temp;
		do
		{
			std::cin >> temp;
			_model->setC(temp);
		} while (temp != 0);
	}
private:
	TemperatureModel *_model;
};

int main()
{
	TemperatureModel model(0.0);
	ConsoleView view(&model);
	Controller controller(&model);
	controller.start();
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
