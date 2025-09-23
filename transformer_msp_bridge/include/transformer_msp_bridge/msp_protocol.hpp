// Deprecated monolithic header. Prefer including:
//  - "transformer_msp_bridge/msp_parser.hpp" for parser types/classes
//  - "transformer_msp_bridge/msp_builders.hpp" for frame builder helpers
// This header is kept as a compatibility shim and will be removed in a future cleanup.
#pragma once

#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/msp_builders.hpp"

#ifdef __GNUC__
#pragma message ("Warning: msp_protocol.hpp is deprecated; include msp_parser.hpp or msp_builders.hpp directly.")
#endif
