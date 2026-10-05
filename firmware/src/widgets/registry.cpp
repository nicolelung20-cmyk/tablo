// Реестр виджетов — таблица указателей на Spec.
#include "widget.h"

#include <cstring>

namespace widgets {

extern const Spec kMarketsSpec;
extern const Spec kLimitsSpec;
extern const Spec kAirSpec;
extern const Spec kLimitsAirSpec;
extern const Spec kMailSpec;
extern const Spec kTodaySpec;
extern const Spec kMetricSpec;
extern const Spec kTextSpec;
extern const Spec kElevatSpec;

namespace {

const Spec* const kRegistry[] = {
    &kMarketsSpec, &kLimitsSpec, &kAirSpec, &kLimitsAirSpec,
    &kMailSpec, &kTodaySpec, &kMetricSpec, &kTextSpec, &kElevatSpec,
};
const size_t kRegistryCount = sizeof(kRegistry) / sizeof(kRegistry[0]);

}  // namespace

const Spec* find(const char* type) {
    if (type == nullptr) return nullptr;
    for (const Spec* s : kRegistry) {
        if (std::strcmp(s->type, type) == 0) return s;
    }
    return nullptr;
}

const Spec* const* all(size_t* count) {
    if (count) *count = kRegistryCount;
    return kRegistry;
}

void required_slots(const Instance& instance, std::vector<String>& out) {
    const Spec* spec = find(instance.type.c_str());
    if (spec == nullptr) return;

    if (std::strcmp(spec->type, "metric") == 0) {
        if (instance.slot.length() > 0) out.push_back(instance.slot);
        return;
    }

    for (const char* const* p = spec->slots; p != nullptr && *p != nullptr; ++p) {
        out.push_back(String(*p));
    }
}

}  // namespace widgets
