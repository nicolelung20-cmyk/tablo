#include "widget.h"

#include "../assets/plexmono_14.h"
#include "../assets/terminus_14.h"
#include "prims.h"

namespace widgets {

namespace {

using canvas::Canvas;
using canvas::Color;
using fonts::draw_text;
using layout::DeviceInfo;
using layout::Rect;
using slots::Store;

const char* const kElevatSlots[] = {
    "elevat.system",
    "elevat.hermes",
    "elevat.revenue",
    "elevat.paper",
    "elevat.alerts",
    "elevat.deploy",
    nullptr,
};

bool elevat_visible(const Store& store, const Instance&) {
    for (const char* const* p = kElevatSlots; *p != nullptr; ++p) {
        if (layout::has_data(store.find(*p))) return true;
    }
    return false;
}

void draw_status(Canvas& c, const Store& store, const char* label, const char* slot,
                 int16_t x, int16_t y, int16_t w) {
    const auto* s = store.find(slot);
    if (!layout::has_data(s)) return;

    draw_text(c, fonts::Terminus14, x, y, label, Color::Black, 1, /*bold=*/true);
    String value = prims::truncate_to_width(fonts::PlexMono14, s->text.c_str(),
                                            static_cast<int16_t>(w - 70));
    draw_text(c, fonts::PlexMono14, static_cast<int16_t>(x + 70), y, value.c_str(),
              Color::Black);
}

void elevat_draw(Canvas& c, const Store& store, const DeviceInfo&, Rect r, const Instance&) {
    prims::draw_eyebrow(c, r, "ELEVAT");
    int16_t y = static_cast<int16_t>(r.y + prims::kEyebrowTextOffset + 20);
    const int16_t gap = 18;

    draw_status(c, store, "SYSTEM", "elevat.system", r.x, y, r.w);
    draw_status(c, store, "HERMES", "elevat.hermes", r.x, y + gap, r.w);
    draw_status(c, store, "REVENUE", "elevat.revenue", r.x, y + gap * 2, r.w);
    draw_status(c, store, "PAPER", "elevat.paper", r.x, y + gap * 3, r.w);
    draw_status(c, store, "ALERTS", "elevat.alerts", r.x, y + gap * 4, r.w);
    draw_status(c, store, "DEPLOY", "elevat.deploy", r.x, y + gap * 5, r.w);
}

}  // namespace

extern const Spec kElevatSpec = {
    "elevat", "Elevat", Size::kS, 202, kElevatSlots, 120,
    &elevat_visible, &elevat_draw,
};

}  // namespace widgets
