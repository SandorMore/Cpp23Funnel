#include <iostream>
#include <variant>
#include <print>
#include <type_traits>
#include <sstream>

struct A {
	virtual void f() 
	{
		std::cout << 1;
	}
}a;

struct B : public A{
	void f() override 
	{
		std::cout << 2;
	}
}b;

volatile int c;

int main(int argc, char** argv)
{
	std::cout << std::boolalpha;
	std::variant<A, B> variant = b;
	


	A* a_mutato = new A;
	B* b_mutato = new B;

	std::variant<A*, B*> mutato_variant = a_mutato;
		
	std::visit([](auto&& v) { v.f(); }, variant);
	std::visit([](auto v) {v->f(); }, mutato_variant);


	std::cout << "\n" << std::is_signed<char>();

	std::cout << "\n" << std::is_same_v<void(int), void(const int)>;
	std::cout << "\n" << std::is_same_v<void(int*), void(const int*)>;

	int n = sizeof [](){};
	std::cout << "\n" << n;

	std::stringstream ss("a");
	std::cout << ss.str();
	ss << "b";
	std::cout << ss.str() << "\n";



	int i, &j = i;
	[=]
	{
		std::cout << std::is_same<decltype    ((j)), int>::value
			<< std::is_same<decltype   (((j))), int& >::value
			<< std::is_same<decltype  ((((j)))), int const& >::value
			<< std::is_same<decltype (((((j))))), int&&>::value
			<< std::is_same<decltype((((((j)))))), int const&&>::value;
	}();

	std::cout << "\n" << (c + c) << "\n";

	int rnd = '3' - '2';
	std::cout << rnd;
	return 0;
}