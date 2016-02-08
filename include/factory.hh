#ifndef FACTORY_HH_
# define FACTORY_HH_

# include <map>
# include <memory>

template <class ManufacturedType, typename ClassIDKey>
class GenericFactory
{
	private:
		typedef ManufacturedType* (*BaseCreateFn)(std::vector<std::uint8_t>::const_iterator &, unsigned int &);
		typedef std::map<ClassIDKey, BaseCreateFn> FnRegistry;

		FnRegistry registry;

		GenericFactory()
		{
		}

		GenericFactory(GenericFactory const &); // Not implemented
		GenericFactory &			operator=(GenericFactory const &); // Not implemented

	public:
		static GenericFactory &		instance()
		{
			static GenericFactory _instance;

			return _instance;
		}

		void						RegCreateFn(ClassIDKey const &								className,
												BaseCreateFn									fn)
		{
			registry[className] = fn;
		}

		ManufacturedType *			Create(ClassIDKey const &									className,
										   std::vector<std::uint8_t>::const_iterator &			it,
										   unsigned int &										pos) const
		{
			auto reg = registry.find(className);

			if (reg != registry.end())
				return registry.at(className)(it, pos);
			else
				return nullptr;
		}
};

template <class AncestorType, class ManufacturedType, typename ClassIDKey>
class RegisterInFactory
{
	public:
		static AncestorType *		CreateInstance(std::vector<std::uint8_t>::const_iterator &	it,
												   unsigned int &								pos)
		{
			return new ManufacturedType(it, pos);
		}

		RegisterInFactory(ClassIDKey const & id)
		{
			GenericFactory<AncestorType, ClassIDKey>::instance().RegCreateFn(id, CreateInstance);
		}
};

#endif /** !FACTORY_HH_  */

