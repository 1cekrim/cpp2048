#ifndef SCREEN_H
#define SCREEN_H

#include <iosfwd>
#include <string>
#include <vector>

namespace Screen
{
void ClearScreen();
void PauseGameUntilPressEnter();
int GetKey();
}  // namespace Screen

namespace Screen::Color
{
enum class Code
{
    RESET = 0,
    BOLD_ON = 1,
    UNDERLINE_ON = 4,
    INVERSE_ON = 7,
    BOLD_OFF = 21,
    UNDERLINE_OFF = 24,
    INVERSE_OFF = 27,
    FG_BLACK = 30,
    FG_RED = 31,
    FG_GREEN = 32,
    FG_YELLOW = 33,
    FG_BLUE = 34,
    FG_MAGENTA = 35,
    FG_CYAN = 36,
    FG_WHITE = 37,
    BG_BLACK = 40,
    BG_RED = 41,
    BG_GREEN = 42,
    BG_YELLOW = 43,
    BG_BLUE = 44,
    BG_MAGENTA = 45,
    BG_CYAN = 46,
    BG_WHITE = 47,
    BG_BRIGHT_RED = 101,
    BG_BRIGHT_GREEN = 102,
    BG_BRIGHT_YELLOW = 103,
    BG_BRIGHT_BLUE = 104,
    BG_BRIGHT_MAGENTA = 105,
    BG_BRIGHT_CYAN = 106,
    BG_BRIGHT_WHITE = 107,
    BG_BRIGHT_BLACK = 100,
};

class Modifier
{
 private:
    Code code;

 public:
    Modifier(Code pCode);
    friend std::ostream& operator<<(std::ostream& os, const Modifier& mod);
};

static Modifier gmReset(Code::RESET);
static Modifier gmBoldOn(Code::BOLD_ON);
static Modifier gmBoldOff(Code::BOLD_OFF);

static Modifier fgBlack(Code::FG_BLACK);
static Modifier fgRed(Code::FG_RED);
static Modifier fgGreen(Code::FG_GREEN);
static Modifier fgYellow(Code::FG_YELLOW);
static Modifier fgBlue(Code::FG_BLUE);
static Modifier fgMagenta(Code::FG_MAGENTA);
static Modifier fgCyan(Code::FG_CYAN);
static Modifier fgWhite(Code::FG_WHITE);

static Modifier bgBlack(Code::BG_BLACK);
static Modifier bgRed(Code::BG_RED);
static Modifier bgGreen(Code::BG_GREEN);
static Modifier bgYellow(Code::BG_YELLOW);
static Modifier bgBlue(Code::BG_BLUE);
static Modifier bgMagenta(Code::BG_MAGENTA);
static Modifier bgCyan(Code::BG_CYAN);
static Modifier bgWhite(Code::BG_WHITE);

static Modifier bgBrightBlack(Code::BG_BRIGHT_BLACK);
static Modifier bgBrightRed(Code::BG_BRIGHT_RED);
static Modifier bgBrightGreen(Code::BG_BRIGHT_GREEN);
static Modifier bgBrightYellow(Code::BG_BRIGHT_YELLOW);
static Modifier bgBrightBlue(Code::BG_BRIGHT_BLUE);
static Modifier bgBrightMagenta(Code::BG_BRIGHT_MAGENTA);
static Modifier bgBrightCyan(Code::BG_BRIGHT_CYAN);
static Modifier bgBrightWhite(Code::BG_BRIGHT_WHITE);

}  // namespace Screen::Color

namespace Screen::Image
{
using ImageVector = std::vector<std::string>;

std::string LogoImage();
std::string ImageToString(const ImageVector& image);
}  // namespace Screen::Image

#endif