/*
================================================================================
██╗      ██████╗  ██████╗  ██████╗ ███████╗██████╗     ██████╗ ██████╗  ██████╗ 
██║     ██╔═══██╗██╔════╝ ██╔════╝ ██╔════╝██╔══██╗    ██╔══██╗██╔══██╗██╔═══██╗
██║     ██║   ██║██║  ███╗██║  ███╗█████╗  ██████╔╝    ██████╔╝██████╔╝██║   ██║
██║     ██║   ██║██║   ██║██║   ██║██╔══╝  ██╔══██╗    ██╔═══╝ ██╔══██╗██║   ██║
███████╗╚██████╔╝╚██████╔╝╚██████╔╝███████╗██║  ██║    ██║     ██║  ██║╚██████╔╝
╚══════╝ ╚═════╝  ╚═════╝  ╚═════╝ ╚══════╝╚═╝  ╚═╝    ╚═╝     ╚═╝  ╚═╝ ╚═════╝ 
--------------------------------------------------------------------------------
  LoggerPro - Lightweight C++ Logging Library
  © 2025 ItzFalco | https://github.com/ItzFalco08/LoggerPro
================================================================================
*/

#pragma once
#include <iostream>
#include <string>
#include <sstream>

namespace Color {
    // Reset
    constexpr const char* RESET = "\033[0m";

    // ---------- COLORS ----------
    namespace FG { // Foreground colors
        constexpr const char* BLACK   = "\033[30m";
        constexpr const char* RED     = "\033[31m";
        constexpr const char* GREEN   = "\033[32m";
        constexpr const char* YELLOW  = "\033[33m";
        constexpr const char* BLUE    = "\033[34m";
        constexpr const char* MAGENTA = "\033[35m";
        constexpr const char* CYAN    = "\033[36m";
        constexpr const char* WHITE   = "\033[37m";
        constexpr const char* GRAY    = "\033[90m";

        // Bright (bold/bright colors)
        constexpr const char* BRIGHT_BLACK   = "\033[90m";
        constexpr const char* BRIGHT_RED     = "\033[91m";
        constexpr const char* BRIGHT_GREEN   = "\033[92m";
        constexpr const char* BRIGHT_YELLOW  = "\033[93m";
        constexpr const char* BRIGHT_BLUE    = "\033[94m";
        constexpr const char* BRIGHT_MAGENTA = "\033[95m";
        constexpr const char* BRIGHT_CYAN    = "\033[96m";
        constexpr const char* BRIGHT_WHITE   = "\033[97m";
    }

    // ---------- BACKGROUNDS ----------
    namespace BG {
        constexpr const char* BLACK   = "\033[40m";
        constexpr const char* RED     = "\033[41m";
        constexpr const char* GREEN   = "\033[42m";
        constexpr const char* YELLOW  = "\033[43m";
        constexpr const char* BLUE    = "\033[44m";
        constexpr const char* MAGENTA = "\033[45m";
        constexpr const char* CYAN    = "\033[46m";
        constexpr const char* WHITE   = "\033[47m";
        constexpr const char* GRAY    = "\033[100m";

        constexpr const char* BRIGHT_RED     = "\033[101m";
        constexpr const char* BRIGHT_GREEN   = "\033[102m";
        constexpr const char* BRIGHT_YELLOW  = "\033[103m";
        constexpr const char* BRIGHT_BLUE    = "\033[104m";
        constexpr const char* BRIGHT_MAGENTA = "\033[105m";
        constexpr const char* BRIGHT_CYAN    = "\033[106m";
        constexpr const char* BRIGHT_WHITE   = "\033[107m";
    }

    // ---------- TEXT STYLES ----------
    namespace Style {
        constexpr const char* BOLD       = "\033[1m";
        constexpr const char* DIM        = "\033[2m";
        constexpr const char* ITALIC     = "\033[3m";
        constexpr const char* UNDERLINE  = "\033[4m";
        constexpr const char* BLINK      = "\033[5m";
        constexpr const char* INVERT     = "\033[7m";  // Swap fg/bg
        constexpr const char* HIDDEN     = "\033[8m";
        constexpr const char* STRIKETHRU = "\033[9m";
    }
}
namespace LOG {
    // ANSI color codes for terminal output

    // Log level prefixes
    enum class Level {
        INFO,
        SUCCESS,
        WARNING,
        ERROR,
        FATAL,
        DEBUG
    };

    // Internal helper for formatting
    inline std::string getLevelPrefix(Level level) {
        switch (level) {
            case Level::INFO:    return std::string(Color::Style::BOLD) + Color::FG::CYAN + "[INFO] " + Color::RESET;
            case Level::SUCCESS: return std::string(Color::Style::BOLD) + Color::FG::GREEN + "[SUCCESS] " + Color::RESET;
            case Level::WARNING: return std::string(Color::Style::BOLD) + Color::FG::YELLOW + "[WARNING] " + Color::RESET;
            case Level::ERROR:   return std::string(Color::Style::BOLD) + Color::FG::RED + "[ERROR] " + Color::RESET;
            case Level::FATAL:   return std::string(Color::Style::BOLD) + Color::FG::RED + "[FATAL] " + Color::RESET;
            case Level::DEBUG:   return std::string(Color::Style::BOLD) + Color::FG::GRAY + "[DEBUG] " + Color::RESET;
            default:             return "[LOG]     ";
        }
    }

    // Variadic template for any number of arguments
    template<typename... Args>
    inline void log(Level level, Args&&... args) {
        std::cout << getLevelPrefix(level);
        (std::cout << ... << args);
        std::cout << std::endl;
    }

    // Convenience functions
    template<typename... Args>
    inline void Info(Args&&... args) {
        log(Level::INFO, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void Success(Args&&... args) {
        log(Level::SUCCESS, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void Warning(Args&&... args) {
        log(Level::WARNING, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void Error(Args&&... args) {
        log(Level::ERROR, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void Fatal(Args&&... args) {
        log(Level::FATAL, std::forward<Args>(args)...);
        std::exit(EXIT_FAILURE);
    }

    template<typename... Args>
    inline void Debug(Args&&... args) {
        #ifdef _DEBUG
        log(Level::DEBUG, std::forward<Args>(args)...);
        #endif
    }
}
