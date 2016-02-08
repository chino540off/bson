#ifndef PRINTER_HH_
# define PRINTER_HH_

# include <element.hh>

class Printer:
	public ConstVisitor
{
	public:
		Printer():
			Printer(std::cout)
		{
		}

		Printer(std::ostream &			os):
			_os(os)
		{
		}

	public:
		/** 
		 * @brief RootDocument printer
		 * 
		 * @param e a RootDocument
		 */
		virtual void visit(RootDocument	const & e)
		{
			bool notfirst = false;

			_os << "{ ";

			for (auto & i : e.elements())
			{
				if (notfirst)
					_os << ", ";

				i->accept(*this);

				notfirst = true;
			}
			_os << " }";
		}
		/** 
		 * @brief Double printer
		 * 
		 * @param e a Double
		 */
		virtual void visit(Double		const & e)
		{
			_os << "\""<< e.key() << "\" : " << e.value();
		}
		/** 
		 * @brief String printer
		 * 
		 * @param e a String
		 */
		virtual void visit(String		const & e)
		{
			_os << "\"" << e.key() << "\" : " << e.value();
		}
		/** 
		 * @brief Document printer
		 * 
		 * @param e a Document
		 */
		virtual void visit(Document		const & e)
		{
			bool notfirst = false;

			_os << "\"" << e.key() << "\" : { ";

			for (auto & i : e.elements())
			{
				if (notfirst)
					_os << ", ";

				i->accept(*this);

				notfirst = true;
			}
			_os << " }";
		}
		/** 
		 * @brief Array printer
		 * 
		 * @param e a Array
		 */
		virtual void visit(Array		const & e)
		{
			bool notfirst = false;

			_os << "\"" << e.key() << "\" : [ ";

			for (auto & i : e.elements())
			{
				if (notfirst)
					_os << ", ";

				i->accept(*this);

				notfirst = true;
			}
			_os << " ]";
		}
		/** 
		 * @brief Binary printer
		 * 
		 * @param e a Binary
		 */
		virtual void visit(Binary		const & e)
		{
			_os << "\"" << e.key() << "\" : " << e.value();
		}
		/** 
		 * @brief Undefined printer
		 * 
		 * @param e a Undefined
		 */
		virtual void visit(Undefined	const & e)
		{
			_os << "\"" << e.key() << "\"";
		}
		/** 
		 * @brief ObjectId printer
		 * 
		 * @param e a ObjectId
		 */
		virtual void visit(ObjectId		const & e)
		{
			_os << "\"" << e.key() << "\" : " << e.value();
		}
		/** 
		 * @brief Boolean printer
		 * 
		 * @param e a Boolean
		 */
		virtual void visit(Boolean		const & e)
		{
			_os << "\"" << e.key() << "\" : "<< std::boolalpha << e.value() << std::noboolalpha;
		}
		/** 
		 * @brief DateTime printer
		 * 
		 * @param e a DateTime
		 */
		virtual void visit(DateTime		const & e)
		{
			_os << "\"" << e.key() << "\" : Date( " << e.value() << " )";
		}
		/** 
		 * @brief Null printer
		 * 
		 * @param e a Null
		 */
		virtual void visit(Null			const & e)
		{
			_os << "\"" << e.key() << "\" : null";
		}
		/** 
		 * @brief Regex printer
		 * 
		 * @param e a Regex
		 */
		virtual void visit(Regex		const & e)
		{
			_os << "\"" << e.key() << "\" : " << e.value();;
		}
		/** 
		 * @brief DBPointer printer
		 * 
		 * @param e a DBPointer
		 */
		virtual void visit(DBPointer	const & e)
		{
			_os << "\"" << e.key() << "\" : " << e.value();
		}
		/** 
		 * @brief JSCode printer
		 * 
		 * @param e a JSCode
		 */
		virtual void visit(JSCode		const & e)
		{
			_os << "\"" << e.key() << "\" : " << e.value();
		}
		/** 
		 * @brief Deprecated printer
		 * 
		 * @param e a Deprecated
		 */
		virtual void visit(Deprecated	const & e)
		{
			_os << "\"" << e.key() << "\" : " << e.value();
		}
		/** 
		 * @brief JSCodeWS printer
		 * 
		 * @param e a JSCodeWS
		 */
		virtual void visit(JSCodeWS		const & e)
		{
			_os << "\"" << e.key() << "\" : ";// << e.value();
			_os << "{ \"$code\" : " << e.value().code;
			_os << " , \"$scope\" : ";
			e.value().doc->accept(*this);
			_os << " }";
		}
		/** 
		 * @brief Integer32 printer
		 * 
		 * @param e a Integer32
		 */
		virtual void visit(Integer32	const & e)
		{
			_os << "\"" << e.key() << "\" : " << e.value();
		}
		/** 
		 * @brief Timestamp printer
		 * 
		 * @param e a Timestamp
		 */
		virtual void visit(Timestamp	const & e)
		{
			_os << "\"" << e.key() << "\" : " << e.value();
		}
		/** 
		 * @brief Integer64 printer
		 * 
		 * @param e a Integer64 
		 */
		virtual void visit(Integer64	const & e)
		{
			_os << "\"" << e.key() << "\" : NumberLong(" << e.value() << ")";
		}
		/** 
		 * @brief MinKey printer
		 * 
		 * @param e a MinKey
		 */
		virtual void visit(MinKey		const & e)
		{
			_os << "\"" << e.key() << "\"";
		}
		/** 
		 * @brief MaxKey printer
		 * 
		 * @param e a MaxKey
		 */
		virtual void visit(MaxKey		const & e)
		{
			_os << "\"" << e.key() << "\"";
		}

	private:
		std::ostream &					_os;
};

#endif /** !PRINTER_HH_  */

