#ifndef DOCUMENT_HH_
# define DOCUMENT_HH_

# include <memory>

# include <decoder.hh>
# include <element.hh>
# include <factory.hh>
# include <visitor.hh>

template <typename TKey, std::uint8_t _id>
class _TDocument:
	public Element<TKey>
{
	public:
		static constexpr std::uint8_t							id = _id;

	public:
		_TDocument(std::vector<std::uint8_t> const &			buffer)
		{
			unsigned int										offset = 0;

			init(buffer, offset);
		}

	public:
		_TDocument(std::vector<std::uint8_t> const &			buffer,
				   unsigned int &								offset):
			Element<TKey>(buffer, offset)
		{
			init(buffer, offset);
		}

	private:
		void
		init(std::vector<std::uint8_t> const &					buffer,
			 unsigned int &										offset)
		{
			// get size from buffer
			_size = Decoder<std::int32_t>(buffer, offset).value();

			std::cout << "start: " << Element<TKey>::_key_offset << " "
					  << "size: " << _size
					  << std::endl;

			if (Element<TKey>::_key_offset + _size > buffer.size())
			{
				std::cerr << "Error: overflow " << Element<TKey>::_key_offset + _size <<  " > " << buffer.size() << std::endl;
				return;
			}

			if (buffer[Element<TKey>::_val_offset + _size] != 0x00)
			{
				std::cerr << "Error: Unterminated buffer[" << Element<TKey>::_val_offset + _size <<  "] == "
						  << std::hex << static_cast<int>(buffer[Element<TKey>::_val_offset + _size])
						  << std::dec << std::endl;
				return;
			}

			while (offset < _size)
			{
				if (buffer[offset] == 0x00)
					break;

				unsigned int	type_offset = offset;

				++offset;

				auto e = std::shared_ptr<Element<TKey>>(GenericFactory<Element<TKey>, std::uint8_t>::instance().Create(buffer[type_offset], buffer, offset));

				if (e != nullptr)
					_elements.push_back(e);
				else
				{
					std::cerr << "Unknown Type " << std::hex << static_cast<int>(buffer[type_offset]) << std::dec << std::endl;;
				}
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

