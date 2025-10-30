# LoggerPro

A tiny, header-only C++ logger with colorful, readable prefixes. Drop in `loggerpro.hpp`, include it, and start logging.

## Features

- Single-header, header-only (no build system or libs)
- Simple API with levels: Info, Success, Warning, Error, Fatal, Debug
- Colorful, bold prefixes
- `Debug` only logs when `_DEBUG` is defined

## Quick start

1) Copy `loggerpro.hpp` into your project (somewhere in your include path).

2) Include it and use the convenience functions:

```cpp
#include "loggerpro.hpp"

int main() {
	LOG::Info("Starting app v", 1.2);
	LOG::Success("Connected in ", 42, " ms");
	LOG::Warning("Low disk: ", 5, "% remaining");

	std::string filename = "config.json";
	LOG::Error("Couldn't open file: ", filename);

	int x = 10, y = 20;
	LOG::Debug("x=", x, " y=", y); // Visible only if _DEBUG is defined

	// LOG::Fatal("Unrecoverable error — shutting down"); // Logs and exits
}

```
## Custom colors

If you want to decorate parts of your message, the header exposes a simple `Color` namespace:

```cpp
// examples
LOG::Info(Color::Style::UNDERLINE, Color::Style::BOLD, "underlined", Color::RESET, " normal text");

LOG::Info(Color::Style::ITALIC, "italic", Color::RESET, " normal text");

```

### Available color constants

- Reset
	- `Color::RESET`

- Text styles `Color::Style`
	- `BOLD`, `DIM`, `ITALIC`, `UNDERLINE`, `BLINK`, `INVERT`, `HIDDEN`, `STRIKETHRU`

- Foreground colors `Color::FG`
	- Normal: `BLACK`, `RED`, `GREEN`, `YELLOW`, `BLUE`, `MAGENTA`, `CYAN`, `WHITE`, `GRAY`
	- Bright: `BRIGHT_BLACK`, `BRIGHT_RED`, `BRIGHT_GREEN`, `BRIGHT_YELLOW`, `BRIGHT_BLUE`, `BRIGHT_MAGENTA`, `BRIGHT_CYAN`, `BRIGHT_WHITE`

- Background colors `Color::BG`
	- Normal: `BLACK`, `RED`, `GREEN`, `YELLOW`, `BLUE`, `MAGENTA`, `CYAN`, `WHITE`, `GRAY`
	- Bright: `BRIGHT_RED`, `BRIGHT_GREEN`, `BRIGHT_YELLOW`, `BRIGHT_BLUE`, `BRIGHT_MAGENTA`, `BRIGHT_CYAN`, `BRIGHT_WHITE`

### Compile (C++17)

LoggerPro uses C++17 fold expressions, so compile with C++17 or newer.

- g++ (MinGW/MSYS or Linux/macOS):

```powershell
g++ -std=c++17 -O2 .\demo.cpp -o demo
```

## API overview

- `LOG::Info(args...)`
- `LOG::Success(args...)`
- `LOG::Warning(args...)`
- `LOG::Error(args...)`
- `LOG::Fatal(args...)`  // logs, then calls `std::exit(EXIT_FAILURE)`
- `LOG::Debug(args...)`  // only prints when `_DEBUG` is defined


## Colors on Windows

- Modern terminals (Windows Terminal, recent PowerShell, VS Code integrated terminal) support ANSI colors out of the box on Windows 10+.
- Legacy consoles may need ANSI support enabled. If colors don’t appear or you see `\x1b[...m` sequences, enable “Virtual Terminal” processing once at startup:

```cpp
#if defined(_WIN32)
#include <windows.h>
inline void enableANSIColors() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (h == INVALID_HANDLE_VALUE) return;
	DWORD mode = 0;
	if (!GetConsoleMode(h, &mode)) return;
	SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
#endif

int main() {
#if defined(_WIN32)
	enableANSIColors();
#endif
	// ... your code
}
```

## Tips

- `LOG::Fatal(...)` exits the program after logging — use for unrecoverable errors only.
- `LOG::Debug(...)` is compiled-in but only prints when `_DEBUG` is defined (MSVC Debug configs define this automatically; otherwise pass `-D_DEBUG`).
- Messages themselves print without colors; if you add your own `Color::...` sequences in messages, remember to end with `Color::RESET` to avoid “color bleed”.
- Not thread-safe by default. If logging from multiple threads, guard calls with a mutex.


## License

See `LICENSE` in this repository.

