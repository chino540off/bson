#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

#include <bson.hh>

int
main(int								argc,
	 char**								argv)
{
	if (argc != 2)
	{
		return 1;
	}

	// open the file:
    std::ifstream						file(argv[1], std::ios::binary);

    // Stop eating new lines in binary mode!!!
    file.unsetf(std::ios::skipws);

    // get its size:
    std::streampos						fileSize;

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // reserve capacity
    std::vector<std::uint8_t> vec;
    vec.reserve(fileSize);

	std::copy(std::istream_iterator<std::uint8_t>(file), std::istream_iterator<std::uint8_t>(), std::back_inserter(vec));

	auto bson = BSON(vec);

	bson.Dump();

	std::cout << bson[0].has_key("a") << std::endl;
	std::cout << bson[0]["a"]["lol"].key() << std::endl;

	return 0;
}
