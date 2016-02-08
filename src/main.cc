#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

#include <bson.hh>

int
main(int								argc,
	 char**								argv)
{
	int									pos = 0;
	if (argc != 2)
	{
		return 1;
	}

    std::ifstream						input(argv[1], std::ios::binary);
	std::vector<std::uint8_t>			vec;

	std::copy(std::istream_iterator<std::uint8_t>(input), std::istream_iterator<std::uint8_t>(), std::back_inserter(vec));
	for (auto & i : vec)
		std::cout << std::hex << static_cast<int>(i) << " ";

	std::cout << std::dec << std::endl;

	auto bson = BSON(vec);

	bson.Dump();

	return 0;
}
