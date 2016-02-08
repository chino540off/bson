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

	public:
		_TDocument(std::vector<std::uint8_t>::const_iterator &			it,
				   std::vector<std::uint8_t>::const_iterator const &	end)
		{
			unsigned int												offset = 0;

			init(it, end, offset);

			it += offset;
		}

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
			// get size from it
			_size = Decoder<std::int32_t>(it, end, offset).value();

			//std::cout << this << " start: " << Element<TKey>::_key << " " << Element<TKey>::_key_offset << " "
			//		  << "size: " << _size
			//		  << std::endl;

			//for (auto i = 0; i < _size; ++i)
			//	std::cout << std::hex << static_cast<int>(it[Element<TKey>::_val_offset + i]) << "(" << std::dec << Element<TKey>::_val_offset + i << ") ";

			//std::cout << std::dec << std::endl << std::endl;

			// FIXME
			if (it + Element<TKey>::_key_offset + _size > end)
			{
				std::cerr << this << " Error: overflow " << std::endl;//<< Element<TKey>::_key_offset + _size <<  " > " << end << std::endl;
				throw std::exception();
			}

			if (it[Element<TKey>::_val_offset + _size - 1] != 0x00)
			{
				std::cerr << this << " Error: Unterminated it[" << Element<TKey>::_val_offset + _size - 1 <<  "] == "
						  << std::hex << static_cast<int>(it[Element<TKey>::_val_offset + _size - 1])
						  << std::dec << std::endl;
				throw std::exception();
			}

			while (offset < Element<TKey>::_val_offset + _size - 1)
			{
				unsigned int	type_offset = offset;

				++offset;

				auto e = std::shared_ptr<Element<TKey>>(GenericFactory<Element<TKey>, std::uint8_t>::instance().Create(it[type_offset], it, end, offset));

				if (e != nullptr)
				{
					_elements.push_back(e);
				}
				else
				{
					std::cerr << this << " Unknown Type " << std::hex << static_cast<int>(it[type_offset]) << std::dec << " at " << type_offset << std::endl;;
					throw std::exception();
				}
			}

			if (it[offset] == 0x00)
			{
				++offset;
			}
			else
			{
				std::cerr << this << " Error: Unterminated it[" << offset <<  "] == "
						  << std::hex << static_cast<int>(it[offset])
						  << std::dec << std::endl;
				throw std::exception();
			}
		}

	public:
		virtual void		accept(Visitor &					v)
		{
			v.visit(*this);
		}

		virtual void		accept(ConstVisitor &				v) const
		{
			v.visit(*this);
		}

	public:
		std::vector<std::shared_ptr<Element<TKey>>> const &		elements() const
		{
			return _elements;
		}

	private:
		unsigned int											_size;
		std::vector<std::shared_ptr<Element<TKey>>>				_elements;
};

#endif /** !DOCUMENT_HH_  */

