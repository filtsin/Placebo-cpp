#pragma once

// Macro for develop. TODO: Delete if after
#define unused(x) do {(void)(x);} while(0)

#ifdef constexpr_14
# error "constexpr_14 already defined"
#endif

// I need to support C++11 but constexpr in C++11 is bad
#if __cplusplus >= 201300
# define constexpr_14 constexpr
#else
# define constexpr_14
#endif

