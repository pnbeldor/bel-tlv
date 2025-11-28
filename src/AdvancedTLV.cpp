/* --- AdvancedTLV.cpp --- */

/* ------------------------------------------
author: Pnbeldor
date: 11/20/2025
------------------------------------------ */

#include "AdvancedTLV.h"

    AdvancedTLV::AdvancedTLV(Type type) : type_(type) {}
    AdvancedTLV::AdvancedTLV(Type type, const std::vector<uint8_t>& value) : type_(type), value_(value) {}
