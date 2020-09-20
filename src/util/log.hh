#ifndef TCPSERVER_UTIL_LOG_HH
#define TCPSERVER_UTIL_LOG_HH

#include "fmt/core.h"
#include "fmt/format.h"
#include <ctime>
#include <iostream>
#include <string>
#include <string_view>

namespace ec::util {
  namespace colors {
    /** @brief Black ANSI code */
    constexpr auto code_black = "\u001b[30m";

    /** @brief Red ANSI code */
    constexpr auto code_red = "\u001b[31m";

    /** @brief Green ANSI code */
    constexpr auto code_green = "\u001b[32m";

    /** @brief Yellow ANSI code */
    constexpr auto code_yellow = "\u001b[33m";

    /** @brief Blue ANSI code */
    constexpr auto code_blue = "\u001b[34m";

    /** @brief Magenta ANSI code */
    constexpr auto code_magenta = "\u001b[35m";

    /** @brief Cyan ANSI code */
    constexpr auto code_cyan = "\u001b[36m";

    /** @brief White ANSI code */
    constexpr auto code_white = "\u001b[37m";

    /** @brief Reset ANSI code */
    constexpr auto code_reset = "\u001b[0m";

    /** @brief Bright Black ANSI code */
    constexpr auto code_bold_black = "\u001b[30;1m";

    /** @brief Bright Red ANSI code */
    constexpr auto code_bold_red = "\u001b[31;1m";

    /** @brief Bright Green ANSI code */
    constexpr auto code_bold_green = "\u001b[32;1m";

    /** @brief Bright Yellow ANSI code */
    constexpr auto code_bold_yellow = "\u001b[33;1m";

    /** @brief Bright Blue ANSI code */
    constexpr auto code_bold_blue = "\u001b[34;1m";

    /** @brief Bright Magenta ANSI code */
    constexpr auto code_bold_magenta = "\u001b[35;1m";

    /** @brief Bright Cyan ANSI code */
    constexpr auto code_bold_cyan = "\u001b[36;1m";

    /** @brief Bright White ANSI code */
    constexpr auto code_bold_white = "\u001b[37;1m";

#define COLOR_FUNC(color)                                                                          \
  inline std::string color(std::string message) { return code_##color + message + code_reset; }    \
  inline std::string bold_##color(std::string message) {                                           \
    return code_bold_##color + message + code_reset;                                               \
  }

    COLOR_FUNC(black)
    COLOR_FUNC(red)
    COLOR_FUNC(green)
    COLOR_FUNC(yellow)
    COLOR_FUNC(blue)
    COLOR_FUNC(magenta)
    COLOR_FUNC(cyan)
    COLOR_FUNC(white)

#undef COLOR_FUNC
  } // namespace colors

  namespace detail {
    std::string datetime() {
      std::time_t now = std::time(0);
      std::tm *time = std::localtime(&now);

      return fmt::format("{}{}/{:02d}/{:02d} {:02d}:{:02d}:{:02d}{}",
          colors::bold_black("["),
          time->tm_year + 1900,
          time->tm_mon + 1,
          time->tm_mday,
          time->tm_hour,
          time->tm_min,
          time->tm_sec,
          colors::bold_black("]"));
    }

    std::string add_brackets(std::string tag) {
      return fmt::format("{}{}{}", colors::bold_black("["), tag, colors::bold_black("]"));
    }
  } // namespace detail

  template <class... Args> void fail(std::string_view format, Args... args) {
    auto message = fmt::format(format, args...);

    fmt::print(stderr,
        "{} {} {}\n",
        detail::datetime(),
        detail::add_brackets(colors::bold_red("fail!")),
        message);
  }

  template <class... Args> void warning(std::string_view format, Args... args) {
    auto message = fmt::format(format, args...);

    fmt::print(stderr,
        "{} {} {}\n",
        detail::datetime(),
        detail::add_brackets(colors::bold_yellow("warn!")),
        message);
  }

  template <class... Args> void info(std::string_view format, Args... args) {
    auto message = fmt::format(format, args...);

    fmt::print(stderr,
        "{} {} {}\n",
        detail::datetime(),
        detail::add_brackets(colors::bold_cyan("info!")),
        message);
  }

  template <class... Args> void ok(std::string_view format, Args... args) {
    auto message = fmt::format(format, args...);

    fmt::print(stderr,
        "{} {} {}\n",
        detail::datetime(),
        detail::add_brackets(colors::bold_green(" ok! ")),
        message);
  }

  template <class... Args> void trace(std::string_view format, Args... args) {
    auto message = fmt::format(format, args...);

    fmt::print(stderr,
        "{} {} [line {}, file {}] {}\n",
        detail::datetime(),
        detail::add_brackets(colors::bold_white("trace")),
        __LINE__,
        __FILE__,
        message);
  }

  template <class... Args> void open(std::string_view format, Args... args) {
    auto message = fmt::format(format, args...);

    fmt::print(stderr,
        "{} {} {}\n",
        detail::datetime(),
        detail::add_brackets(colors::bold_blue("open!")),
        message);
  }

  template <class... Args> void done(std::string_view format, Args... args) {
    auto message = fmt::format(format, args...);

    fmt::print(stderr,
        "{} {} {}\n",
        detail::datetime(),
        detail::add_brackets(colors::bold_magenta("done!")),
        message);
  }
} // namespace ec::util

#endif
