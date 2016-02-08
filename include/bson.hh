#ifndef BSON_HH_
# define BSON_HH_

# include <types.hh>
# include <document.hh>
# include <factory.hh>
# include <printer.hh>

RegisterInFactory<Element<t_cstring>, Double,		std::uint8_t>	_register_elt_double(0x01);
RegisterInFactory<Element<t_cstring>, String,		std::uint8_t>	_register_elt_string(0x02);
RegisterInFactory<Element<t_cstring>, Document,		std::uint8_t>	_register_elt_document(0x03);
RegisterInFactory<Element<t_cstring>, Array,		std::uint8_t>	_register_elt_array(0x04);
RegisterInFactory<Element<t_cstring>, Binary,		std::uint8_t>	_register_elt_binary(0x05);
RegisterInFactory<Element<t_cstring>, Undefined,	std::uint8_t>	_register_elt_undefined(0x06);
RegisterInFactory<Element<t_cstring>, ObjectId,		std::uint8_t>	_register_elt_objectid(0x07);
RegisterInFactory<Element<t_cstring>, Boolean,		std::uint8_t>	_register_elt_boolean(0x08);
RegisterInFactory<Element<t_cstring>, DateTime,		std::uint8_t>	_register_elt_datetime(0x09);
RegisterInFactory<Element<t_cstring>, Null,			std::uint8_t>	_register_elt_null(0x0A);
RegisterInFactory<Element<t_cstring>, Regex,		std::uint8_t>	_register_elt_regex(0x0B);
RegisterInFactory<Element<t_cstring>, DBPointer,	std::uint8_t>	_register_elt_dbpointer(0x0C);
RegisterInFactory<Element<t_cstring>, JSCode,		std::uint8_t>	_register_elt_jscode(0x0D);
RegisterInFactory<Element<t_cstring>, Deprecated,	std::uint8_t>	_register_elt_deprecated(0x0E);
//RegisterInFactory<Element<t_cstring>, Null,			std::uint8_t>	_register_elt_null(0x0F);
RegisterInFactory<Element<t_cstring>, Integer32,	std::uint8_t>	_register_elt_int32(0x10);
RegisterInFactory<Element<t_cstring>, Timestamp,	std::uint8_t>	_register_elt_timestamp(0x11);
RegisterInFactory<Element<t_cstring>, Integer64,	std::uint8_t>	_register_elt_int64(0x12);
RegisterInFactory<Element<t_cstring>, MinKey,		std::uint8_t>	_register_elt_minkey(0xFF);
RegisterInFactory<Element<t_cstring>, MaxKey,		std::uint8_t>	_register_elt_maxkey(0x7F);

class BSON
{
	public:
		BSON(std::vector<std::uint8_t> const &		buffer)
		{
			unsigned int							offset = 0;

			_rds.push_back(std::make_shared<RootDocument>(buffer));
		}

	public:
		void Dump() const
		{
			Printer			p(std::cout);

			for (auto & rd: _rds)
				rd->accept(p);

			std::cout << _rds.size() << " objects found" << std::endl;
		}

	private:
		std::vector<std::shared_ptr<RootDocument>>	_rds;
};

#endif /** !BSON_HH_  */

