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
			_os << " }" << std::endl;
		}
		virtual void visit(Double		const & e)
		{
			_os << "\""<< e.key() << "\" : " << e.value();
		}
		virtual void visit(String		const & e)
		{
			_os << "\"" << e.key() << "\" : " << e.value();
		}
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
		virtual void visit(Binary		const & e)
		{
			_os << "\"" << e.key() << "\" : " << e.value();
		}
		virtual void visit(Undefined	const & e)
		{
			_os << "\"" << e.key() << "\"";
		}
		virtual void visit(ObjectId		const & e)
		{
			_os << "\"" << e.key() << "\" : " << e.value();
		}
		virtual void visit(Boolean		const & e)
		{
			_os << "\"" << e.key() << "\" : "<< std::boolalpha << e.value() << std::noboolalpha;
		}
		virtual void visit(DateTime		const & e)
		{
			_os << "\"" << e.key() << "\" : Date( " << e.value() << " )";
		}
		virtual void visit(Null			const & e)
		{
			_os << "\"" << e.key() << "\" : null";
		}
		virtual void visit(Regex		const & e)
		{
			_os << "\"" << e.key() << "\" : " << e.value();;
		}
		virtual void visit(DBPointer	const & e)
		{
			_os << "\"" << e.key() << "\" : " << e.value();
		}
		virtual void visit(JSCode		const & e)
		{
			_os << "\"" << e.key() << "\" : " << e.value();
		}
		virtual void visit(Deprecated	const & e)
		{
			_os << "\"" << e.key() << "\" : " << e.value();
		}
		virtual void visit(Integer32	const & e)
		{
			_os << "\"" << e.key() << "\" : " << e.value();
		}
		virtual void visit(Timestamp	const & e)
		{
			_os << "\"" << e.key() << "\" : " << e.value();
		}
		virtual void visit(Integer64	const & e)
		{
			_os << "\"" << e.key() << "\" : NumberLong(" << e.value() << ")";
		}
		virtual void visit(MinKey		const & e)
		{
			_os << "\"" << e.key() << "\"";
		}
		virtual void visit(MaxKey		const & e)
		{
			_os << "\"" << e.key() << "\"";
		}

	private:
		std::ostream &					_os;
};

#endif /** !PRINTER_HH_  */

