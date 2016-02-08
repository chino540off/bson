#include <cassert>
#include <iostream>

#include <bson.hh>

int
main(void)
{
	/// String tests
	{
		{
			unsigned int				offset = 1;
			std::vector<std::uint8_t>	vec = {0x02, 'a', 0x00, 0x00};

			auto it = vec.cbegin();
			String						elt(it, vec.cend(), offset);
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

			auto it = vec.cbegin();
			Boolean						elt(it, vec.cend(), offset);
			assert(elt.id == vec[0]);
			assert(elt.key() == "a");
			assert(elt.value() == false);
		}
		{
			unsigned int				offset = 1;
			std::vector<std::uint8_t>	vec = {0x08, 'a', 0x00, 0x01};

			auto it = vec.cbegin();
			Boolean						elt(it, vec.cend(), offset);
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

			auto it = vec.cbegin();
			Regex						elt(it, vec.cend(), offset);
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

			auto it = vec.cbegin();
			MaxKey						elt(it, vec.cend(), offset);
			assert(elt.id == vec[0]);
			assert(elt.key() == "a");
		}
	}

	/// MinKey
	{
		{
			unsigned int				offset = 1;
			std::vector<std::uint8_t>	vec = {0xFF, 'a', 0x00};

			auto it = vec.cbegin();
			MinKey						elt(it, vec.cend(), offset);
			assert(elt.id == vec[0]);
			assert(elt.key() == "a");
		}
	}

	/// JavaScript Code WS
	{
		{
			unsigned int				offset = 1;
			std::vector<std::uint8_t>	vec = {0xf, 0x63, 0x6f, 0x64, 0x65, 0x0, 0x26, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0x76, 0x61, 0x72, 0x20, 0x61, 0x20, 0x3d, 0x20, 0x7b, 0x7d, 0x3b, 0x0, 0x12, 0x0, 0x0, 0x0, 0x2, 0x66, 0x6f, 0x6f, 0x0, 0x4, 0x0, 0x0, 0x0, 0x62, 0x61, 0x72, 0x0, 0x0, 0x0};

			auto it = vec.cbegin();
			JSCodeWS					elt(it, vec.cend(), offset);
			assert(elt.id == vec[0]);
			assert(elt.key() == "code");
		}
	}

	return 0;
}
