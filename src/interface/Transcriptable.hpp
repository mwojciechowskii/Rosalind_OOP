#pragma once

#include <memory>
#include "../RNA.hpp"

class Transcriptable {
public:
    virtual ~Transcriptable() = default;
	virtual std::unique_ptr<RNA> transcribe() const = 0;
};
