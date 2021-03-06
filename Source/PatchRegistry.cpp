#include "PatchRegistry.h"

#include "Patches/GainPatch.hpp"
#include "Patches/TemplatePatch.hpp"
#include "Patches/StupidDelayPatch.hpp"
#include "Patches/SimpleDelayPatch.hpp"
#include "Patches/ParametricEqPatch.hpp"

#define REGISTER_PATCH(T, STR) registerPatch(STR, Register<T>::construct)

PatchRegistry::PatchRegistry(){
  REGISTER_PATCH(GainPatch, "Gain");
  REGISTER_PATCH(TemplatePatch, "Template");
  REGISTER_PATCH(Delay1, "Delay 1");
  REGISTER_PATCH(SimpleDelayPatch, "Simple Delay");
  REGISTER_PATCH(ParametricEqPatch, "Parametric EQ");
}

StringArray PatchRegistry::getNames(){
  Creators::iterator iterator = getCreators().begin();
  Creators::iterator last = getCreators().end();
  StringArray result;
  for(; iterator != last; ++iterator){
    result.add((const char*)(iterator->first).c_str());
  }
  return result;
}

Patch* PatchRegistry::create(const std::string& name) {
  // creates an object from a string
  const Creators::const_iterator iter = getCreators().find(name);
  return iter == getCreators().end() ? NULL : (*iter->second)();
  // if found, execute the creator function pointer
}

void PatchRegistry::registerPatch(const std::string& name, PatchCreator creator){
  getCreators()[name] = creator;
}
