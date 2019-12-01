#pragma once

// Macro for develop. TODO: Delete if after
#define unused(x) do {(void)(x);} while(0)

// I need to support C++11 but constexpr in C++11 is bad
#ifdef constexpr_14
# error "constexpr_14 is already defined"
#endif

#if __cplusplus >= 201300
# define constexpr_14 constexpr
#else
# define constexpr_14
#endif

// C++17 needed for support of std::string_view
#if __cplusplus >= 201700
# define placebo_cpp17
#endif
