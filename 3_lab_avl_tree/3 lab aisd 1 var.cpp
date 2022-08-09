#include "Interface.h";

int main()
{
	setlocale(LC_ALL, "RU");

	try
	{
		Interface<int, int> I;

		I.menu();

	}
	catch (const std::exception& exc)
	{
		cout << "FATAL EXCEPTION: " << exc.what() << endl;
	}
	return 0;
}