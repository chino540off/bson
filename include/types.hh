#ifndef TYPES_HH_
# define TYPES_HH_

# include <string>
# include <vector>
# include <iomanip>
# include <memory>

/// CString Declaration
typedef std::string									t_cstring;

/**
** Forward Declarations
*/
template <typename TKey, std::uint8_t _id, typename ...Args>
class _TElement;

template <typename TKey, std::uint8_t _id>
class _TDocument;

struct t_string;
struct t_binary;
struct t_oid;
struct t_regex;
struct t_dbpointer;
struct t_code_w_s;

/**
** Fields Construction
*/
typedef _TDocument<t_cstring, 0x00>					RootDocument;

/// element	::=	"\x01" e_name double				64-bit binary floating point
typedef _TElement<t_cstring, 0x01, double>			Double;
/// |			"\x02" e_name string				UTF-8 string
typedef _TElement<t_cstring, 0x02, t_string>		String;
/// |			"\x03" e_name document				Embedded document
typedef _TDocument<t_cstring, 0x03>					Document;
/// |			"\x04" e_name document				Array
typedef _TDocument<t_cstring, 0x04>					Array;
/// |			"\x05" e_name binary				Binary data
typedef _TElement<t_cstring, 0x05, t_binary>		Binary;
/// |			"\x06" e_name						Undefined (value) — Deprecated
typedef _TElement<t_cstring, 0x06>					Undefined;
/// |			"\x07" e_name (byte*12)				ObjectId
typedef _TElement<t_cstring, 0x07, t_oid>			ObjectId;
/// |			"\x08" e_name "\x00"				Boolean "false"
/// |			"\x08" e_name "\x01"				Boolean "true"
typedef _TElement<t_cstring, 0x08, bool>			Boolean;
/// |			"\x09" e_name int64					UTC datetime
typedef _TElement<t_cstring, 0x09, std::int64_t>	DateTime;
/// |			"\x0A" e_name						Null value
typedef _TElement<t_cstring, 0x0A>					Null;
/// |			"\x0B" e_name cstring cstring		Regular expression - The first cstring is the regex pattern, the second is the regex options string. Options are identified by characters, which must be stored in alphabetical order. Valid options are 'i' for case insensitive matching, 'm' for multiline matching, 'x' for verbose mode, 'l' to make \w, \W, etc. locale dependent, 's' for dotall mode ('.' matches everything), and 'u' to make \w, \W, etc. match unicode.
typedef _TElement<t_cstring, 0x0B, t_regex>			Regex;
/// |			"\x0C" e_name string (byte*12)		DBPointer — Deprecated
typedef _TElement<t_cstring, 0x0C, t_dbpointer>		DBPointer;
/// |			"\x0D" e_name string				JavaScript code
typedef _TElement<t_cstring, 0x0D, t_string>		JSCode;
/// |			"\x0E" e_name string				Deprecated
typedef _TElement<t_cstring, 0x0E, t_string>		Deprecated;
/// |			"\x0F" e_name code_w_s				JavaScript code w/ scope
typedef _TElement<t_cstring, 0x0F, t_code_w_s>		JSCodeWS;
/// |			"\x10" e_name int32					32-bit integer
typedef _TElement<t_cstring, 0x10, std::int32_t>	Integer32;
/// |			"\x11" e_name int64					Timestamp
typedef _TElement<t_cstring, 0x11, std::int64_t>	Timestamp;
/// |			"\x12" e_name int64					64-bit integer
typedef _TElement<t_cstring, 0x12, std::int64_t>	Integer64;
/// |			"\xFF" e_name						Min key
typedef _TElement<t_cstring, 0xFF>					MinKey;
/// |			"\x7F" e_name						Max key
typedef _TElement<t_cstring, 0x7F>					MaxKey;


/// String Declaration
struct t_string
{
	std::int32_t									len;
	t_cstring										str;
};

/// String Print method
std::ostream &
operator<<(std::ostream &							os,
		   t_string const &							e)
{
	return os << "\"" << e.str << "\"";
}

/// ObjectId Declaration
# define T_OID_BUFFER_SIZE							12

struct t_oid
{
	static constexpr unsigned int					size = T_OID_BUFFER_SIZE;

	std::uint8_t									buffer[T_OID_BUFFER_SIZE];
};

/// ObjectId Print method
std::ostream &
operator<<(std::ostream &							os,
		   t_oid const &							e)
{
	os << "ObjectId( \"";
	os << std::hex;

	for (unsigned int i = 0; i < t_oid::size; ++i)
		os << std::setw(2) << std::setfill('0') << static_cast<int>(e.buffer[i]);

	os << std::dec;
	os << "\" )";

	return os;
}

/// Regex Declaration
struct t_regex
{
	t_cstring										pattern;
	t_cstring										regex;
};

/// Regex Print method
std::ostream &
operator<<(std::ostream &							os,
		   t_regex const &							e)
{
	return os << "/" << e.pattern << "/" << e.regex;
}

/// DBPointer Declaration
# define T_DBPTR_BUFFER_SIZE						12

struct t_dbpointer
{
	static constexpr unsigned int					size = T_DBPTR_BUFFER_SIZE;

	t_string										str;
	std::uint8_t									buffer[T_DBPTR_BUFFER_SIZE];
};

/// DBPointer Print method
std::ostream &
operator<<(std::ostream &							os,
		   t_dbpointer const &						e)
{
	os << "Dbref( " << e.str << ", \"";
	os << std::hex;

	for (unsigned int i = 0; i < t_dbpointer::size; ++i)
		os << std::setw(2) << std::setfill('0') << static_cast<int>(e.buffer[i]);

	os << std::dec;
	os << "\" )";
	return os;
}

/// Binary Declaration
struct t_binary
{
	std::int32_t									size;
	std::uint8_t									subtype;
	std::vector<std::uint8_t>						buffer;
};

/// Binary Print method
std::ostream &
operator<<(std::ostream &							os,
		   t_binary const &							e)
{
	bool											notfirst = false;

	os << "{";
	os << " \"$size\" : " << e.size << ",";
	os << " \"$binary\" : \"";
	for (auto & i: e.buffer)
	{
		if (notfirst)
			os << ", ";

		os << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i);

		notfirst = true;
	}
	os << "\", \"$type\" : \"";
	os << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(e.subtype) << std::dec;
	os << "\"}";
	return os;
}

/// JavaScript Code WS Declaration
struct t_code_w_s
{
	std::int32_t									size;
	t_string										code;
	std::shared_ptr<RootDocument>					doc;
};

/// JavaScript Code WS Print method
/// It exists, but implemented in printerVisitor
std::ostream &
operator<<(std::ostream &							os,
		   t_code_w_s const &						/* e */)
{
	return os;
}

#endif /** !TYPES_HH_  */

