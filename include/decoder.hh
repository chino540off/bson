#ifndef DECODER_HH_
# define DECODER_HH_

# include <vector>
# include <string>
# include <cstring>

# include <types.hh>

template <typename T>
class Decoder
{
	public:
		Decoder(std::vector<std::uint8_t> const &	buffer,
				unsigned int &						offset)
		{
			std::memcpy(&_value, &buffer[offset], sizeof (T));
			offset += sizeof (T);
		}

	public:
		T const &									value() const
		{
			return _value;
		}

	private:
		T											_value;
};

template <>
class Decoder<t_empty>
{
	public:
		Decoder(std::vector<std::uint8_t> const &	buffer,
				unsigned int &						offset)
		{
		}

	public:
		t_empty const &							value() const
		{
			return _value;
		}

	private:
		t_empty									_value;
};

template <>
class Decoder<bool>
{
	public:
		Decoder(std::vector<std::uint8_t> const &	buffer,
				unsigned int &						offset)
		{
			_value = static_cast<bool>(buffer[offset]);
			++offset;
		}

	public:
		bool const &							value() const
		{
			return _value;
		}

	private:
		bool									_value;
};

template <>
class Decoder<t_cstring>
{
	public:
		Decoder(std::vector<std::uint8_t> const &	buffer,
				unsigned int &						offset)
		{
			while (buffer[offset] != 0x00)
			{
				_value += buffer[offset];
				++offset;
			}
			++offset;
		}

	public:
		t_cstring const &							value() const
		{
			return _value;
		}

	private:
		t_cstring									_value;
};

template <>
class Decoder<t_string>
{
	public:
		Decoder(std::vector<std::uint8_t> const &	buffer,
				unsigned int &						offset)
		{
			_value.len = Decoder<std::int32_t>(buffer, offset).value();
			_value.str = Decoder<t_cstring>(buffer, offset).value();
		}

	public:
		t_string const &							value() const
		{
			return _value;
		}

	private:
		t_string									_value;
};

template <>
class Decoder<t_oid>
{
	public:
		Decoder(std::vector<std::uint8_t> const &	buffer,
				unsigned int &						offset)
		{
			std::memcpy(&_value.buffer, &buffer[offset], t_oid::size);
			offset += t_oid::size;
		}

	public:
		t_oid const &								value() const
		{
			return _value;
		}

	private:
		t_oid										_value;
};

template <>
class Decoder<t_regex>
{
	public:
		Decoder(std::vector<std::uint8_t> const &	buffer,
				unsigned int &						offset)
		{
			_value.pattern = Decoder<t_cstring>(buffer, offset).value();
			_value.regex = Decoder<t_cstring>(buffer, offset).value();
		}

	public:
		t_regex const &							value() const
		{
			return _value;
		}

	private:
		t_regex									_value;
};

template <>
class Decoder<t_dbpointer>
{
	public:
		Decoder(std::vector<std::uint8_t> const &	buffer,
				unsigned int &						offset)
		{
			_value.str = Decoder<t_string>(buffer, offset).value();
			std::memcpy(&_value.buffer, &buffer[offset], t_dbpointer::size);
			offset += t_dbpointer::size;
		}

	public:
		t_dbpointer const &							value() const
		{
			return _value;
		}

	private:
		t_dbpointer									_value;
};

#endif /** !DECODER_HH_  */

