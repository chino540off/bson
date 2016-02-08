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
			_indent(0),
			_os(os)
		{
		}

	public:
		virtual void visit(RootDocument	const & e)
		{
			_os << "{" << std::endl;
			++_indent;
			for (auto & i : e.elements())
			{
				i->accept(*this);
				_os << std::endl;
			}
			--_indent;
			_os << "}" << std::endl;
		}
		virtual void visit(Double		const & e)
		{
			indent(); _os << "(Double) " << e.key() << ": " << e.value();
		}
		virtual void visit(String		const & e)
		{
			indent(); _os << "(String) " << e.key() << ": " << e.value();
		}
		virtual void visit(Document		const & e)
		{
			indent(); _os << "(Document) " << e.key() << ": {" << std::endl;
			++_indent;
			for (auto & i : e.elements())
			{
				i->accept(*this);
				_os << std::endl;
			}
			--_indent;
			indent(); _os << "}";
		}
		virtual void visit(Array		const & e)
		{
			indent(); _os << "(Array) " << e.key() << ": [" << std::endl;
			++_indent;
			for (auto & i : e.elements())
			{
				i->accept(*this);
				_os << std::endl;
			}
			--_indent;
			indent(); _os << "]";
		}
		virtual void visit(Undefined	const & e)
		{
			indent(); _os << "(Undefined) " << e.key();
		}
		virtual void visit(ObjectId		const & e)
		{
			indent(); _os << "(ObjectId) " << e.key() << ": " << e.value();
		}
		virtual void visit(Boolean		const & e)
		{
			indent(); _os << "(Bool) " << e.key() << ": " << e.value();
		}
		virtual void visit(DateTime		const & e)
		{
			indent(); _os << "(DateTime) " << e.key() << ": " << e.value();
		}
		virtual void visit(Null			const & e)
		{
			indent(); _os << "(Null) " << e.key() << ": null";
		}
		virtual void visit(Regex		const & e)
		{
			indent(); _os << "(Regex) " << e.key() << ": " << e.value();;
		}
		virtual void visit(DBPointer	const & e)
		{
			indent(); _os << "(DBPointer) " << e.key() << ": " << e.value();
		}
		virtual void visit(JSCode		const & e)
		{
			indent(); _os << "(JSCode) " << e.key() << ": " << e.value();
		}
		virtual void visit(Deprecated	const & e)
		{
			indent(); _os << "(Deprecated) " << e.key() << ": " << e.value();
		}
		virtual void visit(Integer32	const & e)
		{
			indent(); _os << "(Integer32) " << e.key() << ": " << e.value();
		}
		virtual void visit(Timestamp	const & e)
		{
			indent(); _os << "(Timestamp) " << e.key() << ": " << e.value();
		}
		virtual void visit(Integer64	const & e)
		{
			indent(); _os << "(Integer64) " << e.key() << ": " << e.value();
		}
		virtual void visit(MinKey		const & e)
		{
			indent(); _os << "(MinKey) " << e.key();
		}
		virtual void visit(MaxKey		const & e)
		{
			indent(); _os << "(MaxKey) " << e.key();
		}

	private:
		void							indent()
		{
			for (unsigned int i = 0; i < _indent; ++i)
				_os << "  ";
		}

	private:
		unsigned int					_indent;
		std::ostream &					_os;
};

#endif /** !PRINTER_HH_  */

