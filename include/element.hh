#ifndef ELEMENT_HH_
# define ELEMENT_HH_

# include <vector>

# include <decoder.hh>
# include <visitor.hh>

template <typename TKey>
class Element
{
	public:
		Element():
			_key_offset(0),
			_val_offset(0)
		{
		}

	public:
		Element(std::vector<std::uint8_t> const &	buffer,
				unsigned int &						offset):
			_key_offset(offset)

		{
			_key		= Decoder<TKey>(buffer,	offset).value();
			_val_offset	= offset;
		}

	public:
		TKey const &								key() const
		{
			return _key;
		}

	public:
		virtual void								accept(Visitor &) = 0;
		virtual void								accept(ConstVisitor &) const = 0;

	protected:
		TKey										_key;
		unsigned int								_key_offset;
		unsigned int								_val_offset;
};

template <typename TKey, std::uint8_t _id, typename TValue>
class _TElement<TKey, _id, TValue>:
	public Element<TKey>
{
	public:
		static constexpr std::uint8_t				id = _id;

	public:
		_TElement(std::vector<std::uint8_t> const &	buffer,
				  unsigned int &					offset):
			Element<TKey>(buffer, offset)
		{
			std::cout << "start: " << Element<TKey>::_key_offset << " "
					  << std::endl;

			_value = Decoder<TValue>(buffer, offset).value();
		}

	public:
		virtual void								accept(Visitor &		v)
		{
			v.visit(*this);
		}

		virtual void								accept(ConstVisitor &	v) const
		{
			v.visit(*this);
		}

	public:
		TValue const &								value() const
		{
			return _value;
		}

	protected:
		TValue										_value;
};

template <typename TKey, std::uint8_t _id>
class _TElement<TKey, _id>:
	public Element<TKey>
{
	public:
		static constexpr std::uint8_t				id = _id;

	public:
		_TElement(std::vector<std::uint8_t> const &	buffer,
				  unsigned int &					offset):
			Element<TKey>(buffer, offset)
		{
		}

	public:
		virtual void								accept(Visitor &		v)
		{
			v.visit(*this);
		}

		virtual void								accept(ConstVisitor &	v) const
		{
			v.visit(*this);
		}
};

#endif /** !ELEMENT_HH_  */

