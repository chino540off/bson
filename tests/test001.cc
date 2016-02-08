#include <cassert>
#include <iostream>

#include "element.hh"

int
main(void)
{
	/// String tests
	{
		{
			unsigned int				offset = 1;
			std::vector<std::uint8_t>	vec = {0x02, 'a', 0x00, 0x00};

			String						elt(vec, offset);
			assert(elt.id == vec[0]);
			assert(elt.key() == "a");
			assert(elt.value().len == 0);
			assert(elt.value().str == "");
		}
	}

	/// Boolean tests
	{
		{
			unsigned int				offset = 1;
			std::vector<std::uint8_t>	vec = {0x08, 'a', 0x00, 0x00};

			Boolean						elt(vec, offset);
			assert(elt.id == vec[0]);
			assert(elt.key() == "a");
			assert(elt.value() == false);
		}
		{
			unsigned int				offset = 1;
			std::vector<std::uint8_t>	vec = {0x08, 'a', 0x00, 0x01};

			Boolean						elt(vec, offset);
			assert(elt.id == vec[0]);
			assert(elt.key() == "a");
			assert(elt.value() == true);
		}
	}

	/// Regex
	{
		{
			unsigned int				offset = 1;
			std::vector<std::uint8_t>	vec = {0x0B, 'a', 0x00, 'l', 'o', 'l', 0x00, '.', '*', 0x00};

			Regex						elt(vec, offset);
			assert(elt.id == vec[0]);
			assert(elt.key() == "a");
			assert(elt.value().pattern == "lol");
			assert(elt.value().regex == ".*");
		}
	}

	/// MaxKey
	{
		{
			unsigned int				offset = 1;
			std::vector<std::uint8_t>	vec = {0x7F, 'a', 0x00};

			MaxKey						elt(vec, offset);
			assert(elt.id == vec[0]);
			assert(elt.key() == "a");
		}
	}

	/// MinKey
	{
		{
			unsigned int				offset = 1;
			std::vector<std::uint8_t>	vec = {0xFF, 'a', 0x00};

			MinKey						elt(vec, offset);
			assert(elt.id == vec[0]);
			assert(elt.key() == "a");
		}
	}

	return 0;
}
