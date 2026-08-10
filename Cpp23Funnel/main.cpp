#include <iostream>
#include <variant>
#include <print>
#include <type_traits>
#include <sstream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <iterator>

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

template <typename T>

concept Streamable = requires(std::ostream & os, T t)
{
	os << t;
};


template <typename _Iter>
	requires Streamable<std::iter_value_t<_Iter>>
void print_iterable(_Iter beg, _Iter end);

int main(int argc, char** argv)
{
	std::cout << std::boolalpha;
	std::variant<A, B> variant = b;
	


	A* a_mutato = new A;
	B* b_mutato = new B;

	std::variant<A*, B*> mutato_variant = a_mutato;
		
	std::visit([](auto&& v) { v.f(); }, variant);
	std::visit([](auto v) {v->f(); }, mutato_variant);


	/*std::cout << "\n" << std::is_signed<char>();

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
	std::cout << rnd;*/

	std::cout << std::endl;

	std::vector<int> vec{ 1,2,3,4,5 };
	auto vec1 = vec | std::views::filter([](int n) {return n % 2 == 0;});
	std::vector<std::string> words = { "hello", "world", "c++", "ranges" };
	std::ranges::transform(
		words, words.begin(), [](std::string s) {
			transform(s.begin(), s.end(), s.begin(),
				[](unsigned char c) {
					return toupper(c);
				});
			return s;
		});

	print_iterable(vec1.begin(), vec1.end());
	print_iterable(words.begin(), words.end());

	return 0;
}

template <typename _Iter>
	requires Streamable<std::iter_value_t<_Iter>>
void print_iterable(_Iter beg, _Iter end)
{
	while(beg != end)
	{
		std::cout << *beg << " ";
		++beg;
	}
	std::cout << '\n';
}