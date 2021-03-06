#ifndef DECODER_HH_
# define DECODER_HH_

# include <vector>
# include <string>
# include <cstring>

# include <types.hh>
# include <document.hh>
# include <factory.hh>

/// Basic Decoder from bytes
template <typename T>
class Decoder
{
	public:
		Decoder(std::vector<std::uint8_t>::const_iterator &	it,
				std::vector<std::uint8_t>::const_iterator const &	/* end */,
				unsigned int &								offset)
		{
			std::memcpy(&_value, &it[offset], sizeof (T));
			offset += sizeof (T);
		}

	public:
		T const &											value() const
		{
			return _value;
		}

	private:
		T													_value;
};

/// Boolean Decoder from bytes
template <>
class Decoder<bool>
{
	public:
		Decoder(std::vector<std::uint8_t>::const_iterator &	it,
				std::vector<std::uint8_t>::const_iterator const &	/* end */,
				unsigned int &								offset)
		{
			_value = static_cast<bool>(it[offset]);
			++offset;
		}

	public:
		bool const &										value() const
		{
			return _value;
		}

	private:
		bool												_value;
};

/// CString Decoder from bytes
template <>
class Decoder<t_cstring>
{
	public:
		Decoder(std::vector<std::uint8_t>::const_iterator &	it,
				std::vector<std::uint8_t>::const_iterator const &	/* end */,
				unsigned int &								offset)
		{
			while (it[offset] != 0x00)
			{
				_value += it[offset];
				++offset;
			}
			++offset;
		}

	public:
		t_cstring const &									value() const
		{
			return _value;
		}

	private:
		t_cstring											_value;
};

/// String Decoder from bytes
template <>
class Decoder<t_string>
{
	public:
		Decoder(std::vector<std::uint8_t>::const_iterator &	it,
				std::vector<std::uint8_t>::const_iterator const &	end,
				unsigned int &								offset)
		{
			_value.len = Decoder<std::int32_t>(it, end, offset).value();
			_value.str = Decoder<t_cstring>(it, end, offset).value();
		}

	public:
		t_string const &									value() const
		{
			return _value;
		}

	private:
		t_string											_value;
};

/// ObjectId Decoder from bytes
template <>
class Decoder<t_oid>
{
	public:
		Decoder(std::vector<std::uint8_t>::const_iterator &	it,
				std::vector<std::uint8_t>::const_iterator const &	/* end */,
				unsigned int &								offset)
		{
			std::memcpy(&_value.buffer, &it[offset], t_oid::size);
			offset += t_oid::size;
		}

	public:
		t_oid const &										value() const
		{
			return _value;
		}

	private:
		t_oid												_value;
};

/// Regex Decoder from bytes
template <>
class Decoder<t_regex>
{
	public:
		Decoder(std::vector<std::uint8_t>::const_iterator &	it,
				std::vector<std::uint8_t>::const_iterator const &	end,
				unsigned int &								offset)
		{
			_value.pattern = Decoder<t_cstring>(it, end, offset).value();
			_value.regex = Decoder<t_cstring>(it, end, offset).value();
		}

	public:
		t_regex const &										value() const
		{
			return _value;
		}

	private:
		t_regex												_value;
};

/// DBPointer Decoder from bytes
template <>
class Decoder<t_dbpointer>
{
	public:
		Decoder(std::vector<std::uint8_t>::const_iterator &	it,
				std::vector<std::uint8_t>::const_iterator const &	end,
				unsigned int &								offset)
		{
			_value.str = Decoder<t_string>(it, end, offset).value();
			std::memcpy(&_value.buffer, &it[offset], t_dbpointer::size);
			offset += t_dbpointer::size;
		}

	public:
		t_dbpointer const &									value() const
		{
			return _value;
		}

	private:
		t_dbpointer											_value;
};

/// Binary Decoder from bytes
template <>
class Decoder<t_binary>
{
	public:
		Decoder(std::vector<std::uint8_t>::const_iterator &	it,
				std::vector<std::uint8_t>::const_iterator const &	end,
				unsigned int &								offset)
		{
			_value.size = Decoder<std::int32_t>(it, end, offset).value();
			_value.subtype = Decoder<std::uint8_t>(it, end, offset).value();

			//if (_value.size + offset > it.size())
			if (_value.size < 0)
			{
				// FIXME: throw exception
				return;
			}

			for (auto i = 0; i < _value.size; ++i)
				_value.buffer.push_back(it[offset + i]);

			offset += _value.size;
		}


	public:
		t_binary const &									value() const
		{
			return _value;
		}

	private:
		t_binary											_value;
};

/// JavaScript Code WS Decoder from bytes
template <>
class Decoder<t_code_w_s>
{
	public:
		Decoder(std::vector<std::uint8_t>::const_iterator &	it,
				std::vector<std::uint8_t>::const_iterator const &	end,
				unsigned int &								offset)
		{
			_value.size = Decoder<std::int32_t>(it, end, offset).value();
			_value.code = Decoder<t_string>(it, end, offset).value();
			std::vector<std::uint8_t>::const_iterator tmp = it + offset;
			_value.doc = std::make_shared<RootDocument>(tmp, end);

			// 8 == t_code_w_s(sizeof(std::int32_t)) +
			//		doc(sizeof(std::int32_t))
			offset += _value.size - _value.code.len - 8;
		}

	public:
		t_code_w_s const &									value() const
		{
			return _value;
		}

	private:
		t_code_w_s											_value;
};

#endif /** !DECODER_HH_  */

