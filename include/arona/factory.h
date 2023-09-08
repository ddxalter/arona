#ifndef ARONA_FACTORY_H_
#define ARONA_FACTORY_H_

#include<string>
#include<unordered_map>
#include<stdexcept>

namespace arona {

// usage:
//  1. specialize factory for Base class.
//    using MyFactory = arona::Factory<MyBase, MyBaseConstructorArg1, MyBaseConstructorArg2>;
//  2. register derived to the factory.
//    MyFactory::Register<MyDerived> myderived_reg("myderived_name_to_create");
//  3. create instance.
//    MyBase* foo = MyFactory::create("myderived_name_to_create");

template<class Base, class ... Args>
class Factory
{
  using key_type = std::string;
  using creator_type = Base*(*)(Args ...);
  using registry_type = std::unordered_map<key_type, creator_type>;
public:
  
  template<class Derived>
  struct Register
  {
    Register(const key_type& key)
    {
      if(registry().find(key) != registry().end())
      {
        throw std::logic_error("arona::Factory::registration: key '" +key + "' is duplicated." );
      }
      registry()[key] = [](Args ... args){ return static_cast<Base*>(new Derived(args ...)); };
    }
  };

  static Base* create(const key_type& key, Args ... args)
  {
    if(registry().find(key) == registry().end())
    {
      std::runtime_error("arona::Factory::create: key '" + key + "' does not exist.");
    }
    return registry()[key](std::forward<Args>(args) ...);
  }

private:
  static registry_type& registry()
  {
    static registry_type registry_;
    return registry_;
  }
};

} // namespace arona

#endif // ARONA_FACTORY_H_

