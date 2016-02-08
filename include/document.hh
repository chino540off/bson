#ifndef DOCUMENT_HH_
# define DOCUMENT_HH_

# include <memory>
# include <exception>

# include <decoder.hh>
# include <element.hh>
# include <factory.hh>
# include <visitor.hh>

template <typename TKey, std::uint8_t _id>
class _TDocument:
	public Element<TKey>
{
	public:
		static constexpr std::uint8_t									id = _id;

	/**
	** Ctor for RootDocument (no Key Document)
	*/
	public:
		_TDocument(std::vector<std::uint8_t>::const_iterator &			it,
				   std::vector<std::uint8_t>::const_iterator const &	end)
		{
			unsigned int												offset = 0;

			init(it, end, offset);

			it += offset;
		}

	/**
	** Ctor for embedded documents/arrays
	*/
	public:
		_TDocument(std::vector<std::uint8_t>::const_iterator &			it,
				   std::vector<std::uint8_t>::const_iterator const &	end,
				   unsigned int &										offset):
			Element<TKey>(it, end, offset)
		{
			init(it, end, offset);
		}

	private:
		void
		init(std::vector<std::uint8_t>::const_iterator &				it,
			 std::vector<std::uint8_t>::const_iterator const &			end,
			 unsigned int &												offset)
		{
			/// get size from it
			_size = Decoder<std::int32_t>(it, end, offset).value();

			/// Overflow error, throw exception
			if (it + Element<TKey>::_key_offset + _size > end)
			{
				std::cerr << this << " Error: overflow" << std::endl;
				throw std::exception();
			}

			/// Non Terminal Document, throw exception
			if (it[Element<TKey>::_val_offset + _size - 1] != 0x00)
			{
				std::cerr << this << " Error: Unterminated it[" << Element<TKey>::_val_offset + _size - 1 <<  "] == "
						  << std::hex << static_cast<int>(it[Element<TKey>::_val_offset + _size - 1])
						  << std::dec << std::endl;
				throw std::exception();
			}

			while (offset < Element<TKey>::_val_offset + _size - 1)
			{
				/// What is the type of the document field
				unsigned int	type_offset = offset;

				++offset;

				/// Create it from factory
				auto e = std::shared_ptr<Element<TKey>>(GenericFactory<Element<TKey>, std::uint8_t>::instance().Create(it[type_offset], it, end, offset));

				if (e != nullptr)
				{
					_elements.insert(std::make_pair(e->key(), e));
				}
				else /// Unknown Type, throw exception
				{
					std::cerr << this << " Unknown Type " << std::hex << static_cast<int>(it[type_offset]) << std::dec << " at " << type_offset << std::endl;;
					throw std::exception();
				}
			}

			/// Pass on the 0x00 terminal
			if (it[offset] == 0x00)
			{
				++offset;
			}
			else /// Missing 0x00 terminal, throw exception
			{
				std::cerr << this << " Error: Unterminated it[" << offset <<  "] == "
						  << std::hex << static_cast<int>(it[offset])
						  << std::dec << std::endl;
				throw std::exception();
			}
		}

	public:
		virtual std::uint8_t									type() const
		{
			return id;
		}

	public:
		/// Accept a NonConst Visitor
		virtual void		accept(Visitor &					v)
		{
			v.visit(*this);
		}

		/// Accept a Const Visitor
		virtual void		accept(ConstVisitor &				v) const
		{
			v.visit(*this);
		}

	public:
		virtual bool		has_key(TKey const &				k) const
		{
			return _elements.find(k) != _elements.end();
		}

		virtual Element<TKey> const &							operator[](TKey const & k) const
		{
			auto e = _elements.find(k);

			if (e != _elements.end())
				return *(e->second);

			throw std::exception();
		}

	public:
		std::map<TKey, std::shared_ptr<Element<TKey>>> const &	elements() const
		{
			return _elements;
		}

	private:
		unsigned int											_size;
		std::map<TKey, std::shared_ptr<Element<TKey>>>			_elements;
};

#endif /** !DOCUMENT_HH_  */

