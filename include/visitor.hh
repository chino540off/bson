#ifndef VISITOR_HH_
# define VISITOR_HH_

# include <types.hh>

/**
** Non Const Visitor, not used in challenge.
*/
class Visitor
{
	public:
		virtual void visit(RootDocument	&) = 0;
		virtual void visit(Double		&) = 0;
		virtual void visit(String		&) = 0;
		virtual void visit(Document		&) = 0;
		virtual void visit(Array		&) = 0;
		virtual void visit(Binary		&) = 0;
		virtual void visit(Undefined	&) = 0;
		virtual void visit(ObjectId		&) = 0;
		virtual void visit(Boolean		&) = 0;
		virtual void visit(DateTime		&) = 0;
		virtual void visit(Null			&) = 0;
		virtual void visit(Regex		&) = 0;
		virtual void visit(DBPointer	&) = 0;
		virtual void visit(JSCode		&) = 0;
		virtual void visit(Deprecated	&) = 0;
		virtual void visit(JSCodeWS		&) = 0;
		virtual void visit(Integer32	&) = 0;
		virtual void visit(Timestamp	&) = 0;
		virtual void visit(Integer64	&) = 0;
		virtual void visit(MinKey		&) = 0;
		virtual void visit(MaxKey		&) = 0;
};

/**
** Const Visitor, used for the printer.
*/
class ConstVisitor
{
	public:
		virtual void visit(RootDocument	const &) = 0;
		virtual void visit(Double		const &) = 0;
		virtual void visit(String		const &) = 0;
		virtual void visit(Document		const &) = 0;
		virtual void visit(Array		const &) = 0;
		virtual void visit(Binary		const &) = 0;
		virtual void visit(Undefined	const &) = 0;
		virtual void visit(ObjectId		const &) = 0;
		virtual void visit(Boolean		const &) = 0;
		virtual void visit(DateTime		const &) = 0;
		virtual void visit(Null			const &) = 0;
		virtual void visit(Regex		const &) = 0;
		virtual void visit(DBPointer	const &) = 0;
		virtual void visit(JSCode		const &) = 0;
		virtual void visit(Deprecated	const &) = 0;
		virtual void visit(JSCodeWS		const &) = 0;
		virtual void visit(Integer32	const &) = 0;
		virtual void visit(Timestamp	const &) = 0;
		virtual void visit(Integer64	const &) = 0;
		virtual void visit(MinKey		const &) = 0;
		virtual void visit(MaxKey		const &) = 0;
};

#endif /** !VISITOR_HH_  */

