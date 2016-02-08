#ifndef ELEMENT_HH_
# define ELEMENT_HH_

# include <vector>

# include <decoder.hh>
# include <visitor.hh>

/**
** Element Interface, every field derive from it
*/
template <typename TKey>
class Element
{
	/**
	** Ctor with no key
	*/
	public:
		Element():
			_key_offset(0),
			_val_offset(0)
		{
		}

	/**
	** Ctor with a key
	*/
	public:
		Element(std::vector<std::uint8_t>::const_iterator &		it,
				std::vector<std::uint8_t>::const_iterator const &	end,
				unsigned int &									offset):
			_key_offset(offset)

		{
			_key		= Decoder<TKey>(it, end, offset).value();
			_val_offset	= offset;
		}

	public:
		TKey const &											key() const
		{
			return _key;
		}

	public:
		virtual std::uint8_t									type() const = 0;

	public:
		/// Accept a NonConst Visitor
		virtual void											accept(Visitor &) = 0;
		/// Accept a Const Visitor
		virtual void											accept(ConstVisitor &) const = 0;

	public:
		virtual bool											has_key(TKey const &) const = 0;

		virtual Element<TKey> const &							operator[](TKey const &) const = 0;

	protected:
		TKey													_key;
		unsigned int											_key_offset;
		unsigned int											_val_offset;
};

/**
** Basic Element with a value, derive from Element
** Every Fields with value are built from this meta class
*/
template <typename TKey, std::uint8_t _id, typename TValue>
class _TElement<TKey, _id, TValue>:
	public Element<TKey>
{
	public:
		static constexpr std::uint8_t							id = _id;

	public:
		_TElement(std::vector<std::uint8_t>::const_iterator &	it,
				  std::vector<std::uint8_t>::const_iterator const &	end,
				  unsigned int &								offset):
			Element<TKey>(it, end, offset)
		{
			_value = Decoder<TValue>(it, end, offset).value();
		}

	public:
		virtual std::uint8_t									type() const
		{
			return id;
		}

	public:
		/// Accept a NonConst Visitor
		virtual void											accept(Visitor &		v)
		{
			v.visit(*this);
		}

		/// Accept a Const Visitor
		virtual void											accept(ConstVisitor &	v) const
		{
			v.visit(*this);
		}

	public:
		virtual bool											has_key(TKey const &) const
		{
			return false;
		}

		virtual Element<TKey> const &							operator[](TKey const &) const
		{
			throw std::exception();
		}

	public:
		TValue const &											value() const
		{
			return _value;
		}

	protected:
		TValue													_value;
};

/**
** Basic Element with no value, derive from Element
** Every Fields with no value are built from this meta class
*/
template <typename TKey, std::uint8_t _id>
class _TElement<TKey, _id>:
	public Element<TKey>
{
	public:
		static constexpr std::uint8_t							id = _id;

	public:
		_TElement(std::vector<std::uint8_t>::const_iterator &	it,
				  std::vector<std::uint8_t>::const_iterator const &	end,
				  unsigned int &								offset):
			Element<TKey>(it, end, offset)
		{
		}

	public:
		virtual std::uint8_t									type() const
		{
			return id;
		}

	public:
		/// Accept a NonConst Visitor
		virtual void											accept(Visitor &		v)
		{
			v.visit(*this);
		}

		/// Accept a Const Visitor
		virtual void											accept(ConstVisitor &	v) const
		{
			v.visit(*this);
		}

	public:
		virtual bool											has_key(TKey const &) const
		{
			return false;
		}

		virtual Element<TKey> const &							operator[](TKey const &) const
		{
			throw std::exception();
		}
};

#endif /** !ELEMENT_HH_  */

