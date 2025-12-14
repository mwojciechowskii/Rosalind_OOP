#pragma once

#include "AaSequence.hpp"
#include <memory>

class Translatable {
public:
    virtual ~Translatable() = default; 
	virtual std::unique_ptr<aaSequence> translate() const = 0;
};
