/* See LICENSE file for copyright and license details. */
#pragma once

/*
 * appearance
 *
 * font: see https://freedesktop.org/software/fontconfig/fontconfig-user.html
 */
static char *font = "monospace:size=13:antialias=true:autohint=true";
static int borderpx = 2;

/*
 * What program is execed by st depends of these precedence rules:
 * 1: program passed with -e
 * 2: scroll and/or utmp
 * 3: SHELL environment variable
 * 4: value of shell in /etc/passwd
 * 5: value of shell in config.h
 */
static char *shell = "/bin/sh";
char *utmp = NULL;
/* scroll program: to enable use a string like "scroll" */
char *scroll = NULL;
char *stty_args = "stty raw pass8 nl -echo -iexten -cstopb 38400";

/* identification sequence returned in DA and DECID */
char *vtiden = "\033[?6c";

/* Kerning / character bounding-box multipliers */
static float cwscale = 1.0;
static float chscale = 1.0;

/*
 * word delimiter string
 *
 * More advanced example: L" `'\"()[]{}"
 */
wchar_t *worddelimiters = L" `'\"()[]{}:";

/* selection timeouts (in milliseconds) */
static unsigned int doubleclicktimeout = 300;
static unsigned int tripleclicktimeout = 600;

/* alt screens */
int allowaltscreen = 1;

/* allow certain non-interactive (insecure) window operations such as:
   setting the clipboard text */
int allowwindowops = 1;

/*
 * draw latency range in ms - from new content/keypress/etc until drawing.
 * within this range, st draws when content stops arriving (idle). mostly it's
 * near minlatency, but it waits longer for slow updates to avoid partial draw.
 * low minlatency will tear/flicker more, as it can "detect" idle too early.
 */
static double minlatency = 8;
static double maxlatency = 33;

/*
 * blinking timeout (set to 0 to disable blinking) for the terminal blinking
 * attribute.
 */
static unsigned int blinktimeout = 800;

/*
 * thickness of underline and bar cursors
 */
static unsigned int cursorthickness = 2;

/*
 * bell volume. It must be a value between -100 and 100. Use 0 for disabling
 * it
 */
static int bellvolume = 0;

/* default TERM value */
char *termname = "st-256color";

/*
 * spaces per tab
 *
 * When you are changing this value, don't forget to adapt the »it« value in
 * the st.info and appropriately install the st.info in the environment where
 * you use this st version.
 *
 *	it#$tabspaces,
 *
 * Secondly make sure your kernel is not expanding tabs. When running `stty
 * -a` »tab0« should appear. You can tell the terminal to not expand tabs by
 *  running following command:
 *
 *	stty tabs
 */
unsigned int tabspaces = 8;

/* Terminal colors (16 first used in escape sequence) */
static const char *colorname[] = {
	/* 8 normal colors */
	"#1c1b19",
	"#ef2f27",
	"#519f50",
	"#fbb829",
	"#2c78bf",
	"#e02c6d",
	"#0aaeb3",
	"#baa67f",

	/* 8 bright colors */
	"#918175",
	"#f75341",
	"#98bc37",
	"#fed06e",
	"#68a8e4",
	"#ff5c8f",
	"#2be4d0",
	"#fce8c3",

	[255] = 0,

	/* more colors can be added after 255 to use with defaultXX */
	"#fce8c3", /* foreground */
	"#1c1b19", /* background */
	"#fbb829", /* cursor */
	"#cccccc",
	"#555555",
	"gray90", /* default foreground colour */
	"black", /* default background colour */
};

/*
 * Default colors (colorname index)
 * foreground, background, cursor, reverse cursor
 */
unsigned int defaultfg = 256;
unsigned int defaultbg = 257;
unsigned int defaultcs = 258;
static unsigned int defaultrcs = 257;

/*
 * https://invisible-island.net/xterm/ctlseqs/ctlseqs.html#h4-Functions-using-CSI-_-ordered-by-the-final-character-lparen-s-rparen:CSI-Ps-SP-q.1D81
 * Default style of cursor
 * 0: blinking block
 * 1: blinking block (default)
 * 2: steady block ("█")
 * 3: blinking underline
 * 4: steady underline ("_")
 * 5: blinking bar
 * 6: steady bar ("|")
 * 7: blinking st cursor
 * 8: steady st cursor
 */
static unsigned int cursorstyle = 2;
static Rune stcursor = 0x2603; /* snowman ("☃") */

/*
 * Default columns and rows numbers
 */
static unsigned int cols = 80;
static unsigned int rows = 24;

/*
 * Default color and shape of the mouse cursor
 */
static unsigned int mouseshape = XC_xterm;
static unsigned int mousefg = 7;
static unsigned int mousebg = 0;

/*
 * Force mouse select/shortcuts while mask is active (when MODE_MOUSE is set).
 * Note that if you want to use ShiftMask with selmasks, set this to an other
 * modifier, set to 0 to not use it.
 */
static uint forcemousemod = ShiftMask;

/*
 * Internal mouse shortcuts.
 * Beware that overloading Button1 will disable the selection.
 */
static MouseShortcut mshortcuts[] = {
	/* mask        button    function   argument               release */
	{ XK_ANY_MOD , Button2 , selpaste , { .i = 0           } , 1 } ,
	{ ShiftMask  , Button4 , ttysend  , { .s = "\033[5;2~" } , 0 } ,
	{ XK_ANY_MOD , Button4 , ttysend  , { .s = "\031"      } , 0 } ,
	{ ShiftMask  , Button5 , ttysend  , { .s = "\033[6;2~" } , 0 } ,
	{ XK_ANY_MOD , Button5 , ttysend  , { .s = "\005"      } , 0 } ,
};

/* Internal keyboard shortcuts. */
#define C_M1_Mask (ControlMask|Mod1Mask)
#define S_C_M1_Mask (ShiftMask|ControlMask|Mod1Mask)
#define S_C_Mask (ShiftMask|ControlMask)
#define S_M1_Mask (ShiftMask|Mod1Mask)

static Shortcut shortcuts[] = {
	/* mask         keysym        function        argument */
	{ XK_ANY_MOD  , XK_Break    , sendbreak     , { .i =  0 } } ,
	{ ControlMask , XK_Print    , toggleprinter , { .i =  0 } } ,
	{ ShiftMask   , XK_Print    , printscreen   , { .i =  0 } } ,
	{ XK_ANY_MOD  , XK_Print    , printsel      , { .i =  0 } } ,
	{ S_C_Mask    , XK_N        , newterm       , { .i =  0 } } ,
	{ S_C_Mask    , XK_Prior    , zoom          , { .f = +1 } } ,
	{ S_C_Mask    , XK_Next     , zoom          , { .f = -1 } } ,
	{ S_C_Mask    , XK_Home     , zoomreset     , { .f =  0 } } ,
	{ S_C_Mask    , XK_C        , clipcopy      , { .i =  0 } } ,
	{ S_C_Mask    , XK_V        , clippaste     , { .i =  0 } } ,
	{ S_C_Mask    , XK_Y        , selpaste      , { .i =  0 } } ,
	{ ShiftMask   , XK_Insert   , selpaste      , { .i =  0 } } ,
	{ S_C_Mask    , XK_Num_Lock , numlock       , { .i =  0 } } ,
};

/*
 * Special keys (change & recompile st.info accordingly)
 *
 * Mask value:
 * * Use XK_ANY_MOD to match the key no matter modifiers state
 * * Use XK_NO_MOD to match the key alone (no modifiers)
 * appkey value:
 * * 0: no value
 * * > 0: keypad application mode enabled
 * *   = 2: term.numlock = 1
 * * < 0: keypad application mode disabled
 * appcursor value:
 * * 0: no value
 * * > 0: cursor application mode enabled
 * * < 0: cursor application mode disabled
 *
 * Be careful with the order of the definitions because st searches in
 * this table sequentially, so any XK_ANY_MOD must be in the last
 * position for a key.
 */

/*
 * If you want keys other than the X11 function keys (0xFD00 - 0xFFFF)
 * to be mapped below, add them to this array.
 */
static KeySym mappedkeys[] = { -1 };

/*
 * State bits to ignore when matching key or button events.  By default,
 * numlock (Mod2Mask) and keyboard layout (XK_SWITCH_MOD) are ignored.
 */
static uint ignoremod = Mod2Mask|XK_SWITCH_MOD;

/*
 * This is the huge key array which defines all compatibility to the Linux
 * world. Please decide about changes wisely.
 */
static Key key[] = {
	/* keysym           string         mask          appkey appcursor */
	{ XK_KP_Home      , "\033[2J"    , ShiftMask   , 0  , -1 } ,
	{ XK_KP_Home      , "\033[1;2H"  , ShiftMask   , 0  , +1 } ,
	{ XK_KP_Home      , "\033[H"     , XK_ANY_MOD  , 0  , -1 } ,
	{ XK_KP_Home      , "\033[1~"    , XK_ANY_MOD  , 0  , +1 } ,
	{ XK_KP_Up        , "\033Ox"     , XK_ANY_MOD  , +1 , 0  } ,
	{ XK_KP_Up        , "\033[A"     , XK_ANY_MOD  , 0  , -1 } ,
	{ XK_KP_Up        , "\033OA"     , XK_ANY_MOD  , 0  , +1 } ,
	{ XK_KP_Down      , "\033Or"     , XK_ANY_MOD  , +1 , 0  } ,
	{ XK_KP_Down      , "\033[B"     , XK_ANY_MOD  , 0  , -1 } ,
	{ XK_KP_Down      , "\033OB"     , XK_ANY_MOD  , 0  , +1 } ,
	{ XK_KP_Left      , "\033Ot"     , XK_ANY_MOD  , +1 , 0  } ,
	{ XK_KP_Left      , "\033[D"     , XK_ANY_MOD  , 0  , -1 } ,
	{ XK_KP_Left      , "\033OD"     , XK_ANY_MOD  , 0  , +1 } ,
	{ XK_KP_Right     , "\033Ov"     , XK_ANY_MOD  , +1 , 0  } ,
	{ XK_KP_Right     , "\033[C"     , XK_ANY_MOD  , 0  , -1 } ,
	{ XK_KP_Right     , "\033OC"     , XK_ANY_MOD  , 0  , +1 } ,
	{ XK_KP_Prior     , "\033[5;2~"  , ShiftMask   , 0  , 0  } ,
	{ XK_KP_Prior     , "\033[5~"    , XK_ANY_MOD  , 0  , 0  } ,
	{ XK_KP_Begin     , "\033[E"     , XK_ANY_MOD  , 0  , 0  } ,
	{ XK_KP_End       , "\033[J"     , ControlMask , -1 , 0  } ,
	{ XK_KP_End       , "\033[1;5F"  , ControlMask , +1 , 0  } ,
	{ XK_KP_End       , "\033[K"     , ShiftMask   , -1 , 0  } ,
	{ XK_KP_End       , "\033[1;2F"  , ShiftMask   , +1 , 0  } ,
	{ XK_KP_End       , "\033[4~"    , XK_ANY_MOD  , 0  , 0  } ,
	{ XK_KP_Next      , "\033[6;2~"  , ShiftMask   , 0  , 0  } ,
	{ XK_KP_Next      , "\033[6~"    , XK_ANY_MOD  , 0  , 0  } ,
	{ XK_KP_Insert    , "\033[2;2~"  , ShiftMask   , +1 , 0  } ,
	{ XK_KP_Insert    , "\033[4l"    , ShiftMask   , -1 , 0  } ,
	{ XK_KP_Insert    , "\033[L"     , ControlMask , -1 , 0  } ,
	{ XK_KP_Insert    , "\033[2;5~"  , ControlMask , +1 , 0  } ,
	{ XK_KP_Insert    , "\033[4h"    , XK_ANY_MOD  , -1 , 0  } ,
	{ XK_KP_Insert    , "\033[2~"    , XK_ANY_MOD  , +1 , 0  } ,
	{ XK_KP_Delete    , "\033[M"     , ControlMask , -1 , 0  } ,
	{ XK_KP_Delete    , "\033[3;5~"  , ControlMask , +1 , 0  } ,
	{ XK_KP_Delete    , "\033[2K"    , ShiftMask   , -1 , 0  } ,
	{ XK_KP_Delete    , "\033[3;2~"  , ShiftMask   , +1 , 0  } ,
	{ XK_KP_Delete    , "\033[P"     , XK_ANY_MOD  , -1 , 0  } ,
	{ XK_KP_Delete    , "\033[3~"    , XK_ANY_MOD  , +1 , 0  } ,
	{ XK_KP_Multiply  , "\033Oj"     , XK_ANY_MOD  , +2 , 0  } ,
	{ XK_KP_Add       , "\033Ok"     , XK_ANY_MOD  , +2 , 0  } ,
	{ XK_KP_Enter     , "\033OM"     , XK_ANY_MOD  , +2 , 0  } ,
	{ XK_KP_Enter     , "\r"         , XK_ANY_MOD  , -1 , 0  } ,
	{ XK_KP_Subtract  , "\033Om"     , XK_ANY_MOD  , +2 , 0  } ,
	{ XK_KP_Decimal   , "\033On"     , XK_ANY_MOD  , +2 , 0  } ,
	{ XK_KP_Divide    , "\033Oo"     , XK_ANY_MOD  , +2 , 0  } ,
	{ XK_KP_0         , "\033Op"     , XK_ANY_MOD  , +2 , 0  } ,
	{ XK_KP_1         , "\033Oq"     , XK_ANY_MOD  , +2 , 0  } ,
	{ XK_KP_2         , "\033Or"     , XK_ANY_MOD  , +2 , 0  } ,
	{ XK_KP_3         , "\033Os"     , XK_ANY_MOD  , +2 , 0  } ,
	{ XK_KP_4         , "\033Ot"     , XK_ANY_MOD  , +2 , 0  } ,
	{ XK_KP_5         , "\033Ou"     , XK_ANY_MOD  , +2 , 0  } ,
	{ XK_KP_6         , "\033Ov"     , XK_ANY_MOD  , +2 , 0  } ,
	{ XK_KP_7         , "\033Ow"     , XK_ANY_MOD  , +2 , 0  } ,
	{ XK_KP_8         , "\033Ox"     , XK_ANY_MOD  , +2 , 0  } ,
	{ XK_KP_9         , "\033Oy"     , XK_ANY_MOD  , +2 , 0  } ,
	{ XK_Up           , "\033[1;2A"  , ShiftMask   , 0  , 0  } ,
	{ XK_Up           , "\033[1;3A"  , Mod1Mask    , 0  , 0  } ,
	{ XK_Up           , "\033[1;4A"  , S_M1_Mask   , 0  , 0  } ,
	{ XK_Up           , "\033[1;5A"  , ControlMask , 0  , 0  } ,
	{ XK_Up           , "\033[1;6A"  , S_C_Mask    , 0  , 0  } ,
	{ XK_Up           , "\033[1;7A"  , C_M1_Mask   , 0  , 0  } ,
	{ XK_Up           , "\033[1;8A"  , S_C_M1_Mask , 0  , 0  } ,
	{ XK_Up           , "\033[A"     , XK_ANY_MOD  , 0  , -1 } ,
	{ XK_Up           , "\033OA"     , XK_ANY_MOD  , 0  , +1 } ,
	{ XK_Down         , "\033[1;2B"  , ShiftMask   , 0  , 0  } ,
	{ XK_Down         , "\033[1;3B"  , Mod1Mask    , 0  , 0  } ,
	{ XK_Down         , "\033[1;4B"  , S_M1_Mask   , 0  , 0  } ,
	{ XK_Down         , "\033[1;5B"  , ControlMask , 0  , 0  } ,
	{ XK_Down         , "\033[1;6B"  , S_C_Mask    , 0  , 0  } ,
	{ XK_Down         , "\033[1;7B"  , C_M1_Mask   , 0  , 0  } ,
	{ XK_Down         , "\033[1;8B"  , S_C_M1_Mask , 0  , 0  } ,
	{ XK_Down         , "\033[B"     , XK_ANY_MOD  , 0  , -1 } ,
	{ XK_Down         , "\033OB"     , XK_ANY_MOD  , 0  , +1 } ,
	{ XK_Left         , "\033[1;2D"  , ShiftMask   , 0  , 0  } ,
	{ XK_Left         , "\033[1;3D"  , Mod1Mask    , 0  , 0  } ,
	{ XK_Left         , "\033[1;4D"  , S_M1_Mask   , 0  , 0  } ,
	{ XK_Left         , "\033[1;5D"  , ControlMask , 0  , 0  } ,
	{ XK_Left         , "\033[1;6D"  , S_C_Mask    , 0  , 0  } ,
	{ XK_Left         , "\033[1;7D"  , C_M1_Mask   , 0  , 0  } ,
	{ XK_Left         , "\033[1;8D"  , S_C_M1_Mask , 0  , 0  } ,
	{ XK_Left         , "\033[D"     , XK_ANY_MOD  , 0  , -1 } ,
	{ XK_Left         , "\033OD"     , XK_ANY_MOD  , 0  , +1 } ,
	{ XK_Right        , "\033[1;2C"  , ShiftMask   , 0  , 0  } ,
	{ XK_Right        , "\033[1;3C"  , Mod1Mask    , 0  , 0  } ,
	{ XK_Right        , "\033[1;4C"  , S_M1_Mask   , 0  , 0  } ,
	{ XK_Right        , "\033[1;5C"  , ControlMask , 0  , 0  } ,
	{ XK_Right        , "\033[1;6C"  , S_C_Mask    , 0  , 0  } ,
	{ XK_Right        , "\033[1;7C"  , C_M1_Mask   , 0  , 0  } ,
	{ XK_Right        , "\033[1;8C"  , S_C_M1_Mask , 0  , 0  } ,
	{ XK_Right        , "\033[C"     , XK_ANY_MOD  , 0  , -1 } ,
	{ XK_Right        , "\033OC"     , XK_ANY_MOD  , 0  , +1 } ,
	{ XK_ISO_Left_Tab , "\033[Z"     , ShiftMask   , 0  , 0  } ,
	{ XK_Return       , "\033\r"     , Mod1Mask    , 0  , 0  } ,
	{ XK_Return       , "\r"         , XK_ANY_MOD  , 0  , 0  } ,
	{ XK_Insert       , "\033[4l"    , ShiftMask   , -1 , 0  } ,
	{ XK_Insert       , "\033[2;2~"  , ShiftMask   , +1 , 0  } ,
	{ XK_Insert       , "\033[L"     , ControlMask , -1 , 0  } ,
	{ XK_Insert       , "\033[2;5~"  , ControlMask , +1 , 0  } ,
	{ XK_Insert       , "\033[4h"    , XK_ANY_MOD  , -1 , 0  } ,
	{ XK_Insert       , "\033[2~"    , XK_ANY_MOD  , +1 , 0  } ,
	{ XK_Delete       , "\033[M"     , ControlMask , -1 , 0  } ,
	{ XK_Delete       , "\033[3;5~"  , ControlMask , +1 , 0  } ,
	{ XK_Delete       , "\033[2K"    , ShiftMask   , -1 , 0  } ,
	{ XK_Delete       , "\033[3;2~"  , ShiftMask   , +1 , 0  } ,
	{ XK_Delete       , "\033[P"     , XK_ANY_MOD  , -1 , 0  } ,
	{ XK_Delete       , "\033[3~"    , XK_ANY_MOD  , +1 , 0  } ,
	{ XK_BackSpace    , "\177"       , XK_NO_MOD   , 0  , 0  } ,
	{ XK_BackSpace    , "\033\177"   , Mod1Mask    , 0  , 0  } ,
	{ XK_Home         , "\033[2J"    , ShiftMask   , 0  , -1 } ,
	{ XK_Home         , "\033[1;2H"  , ShiftMask   , 0  , +1 } ,
	{ XK_Home         , "\033[H"     , XK_ANY_MOD  , 0  , -1 } ,
	{ XK_Home         , "\033[1~"    , XK_ANY_MOD  , 0  , +1 } ,
	{ XK_End          , "\033[J"     , ControlMask , -1 , 0  } ,
	{ XK_End          , "\033[1;5F"  , ControlMask , +1 , 0  } ,
	{ XK_End          , "\033[K"     , ShiftMask   , -1 , 0  } ,
	{ XK_End          , "\033[1;2F"  , ShiftMask   , +1 , 0  } ,
	{ XK_End          , "\033[4~"    , XK_ANY_MOD  , 0  , 0  } ,
	{ XK_Prior        , "\033[5;5~"  , ControlMask , 0  , 0  } ,
	{ XK_Prior        , "\033[5;2~"  , ShiftMask   , 0  , 0  } ,
	{ XK_Prior        , "\033[5~"    , XK_ANY_MOD  , 0  , 0  } ,
	{ XK_Next         , "\033[6;5~"  , ControlMask , 0  , 0  } ,
	{ XK_Next         , "\033[6;2~"  , ShiftMask   , 0  , 0  } ,
	{ XK_Next         , "\033[6~"    , XK_ANY_MOD  , 0  , 0  } ,
	{ XK_F1           , "\033OP"     , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F1           , "\033[1;2P"  , ShiftMask   , 0  , 0  } , /* F13 */
	{ XK_F1           , "\033[1;5P"  , ControlMask , 0  , 0  } , /* F25 */
	{ XK_F1           , "\033[1;6P"  , Mod4Mask    , 0  , 0  } , /* F37 */
	{ XK_F1           , "\033[1;3P"  , Mod1Mask    , 0  , 0  } , /* F49 */
	{ XK_F1           , "\033[1;4P"  , Mod3Mask    , 0  , 0  } , /* F61 */
	{ XK_F2           , "\033OQ"     , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F2           , "\033[1;2Q"  , ShiftMask   , 0  , 0  } , /* F14 */
	{ XK_F2           , "\033[1;5Q"  , ControlMask , 0  , 0  } , /* F26 */
	{ XK_F2           , "\033[1;6Q"  , Mod4Mask    , 0  , 0  } , /* F38 */
	{ XK_F2           , "\033[1;3Q"  , Mod1Mask    , 0  , 0  } , /* F50 */
	{ XK_F2           , "\033[1;4Q"  , Mod3Mask    , 0  , 0  } , /* F62 */
	{ XK_F3           , "\033OR"     , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F3           , "\033[1;2R"  , ShiftMask   , 0  , 0  } , /* F15 */
	{ XK_F3           , "\033[1;5R"  , ControlMask , 0  , 0  } , /* F27 */
	{ XK_F3           , "\033[1;6R"  , Mod4Mask    , 0  , 0  } , /* F39 */
	{ XK_F3           , "\033[1;3R"  , Mod1Mask    , 0  , 0  } , /* F51 */
	{ XK_F3           , "\033[1;4R"  , Mod3Mask    , 0  , 0  } , /* F63 */
	{ XK_F4           , "\033OS"     , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F4           , "\033[1;2S"  , ShiftMask   , 0  , 0  } , /* F16 */
	{ XK_F4           , "\033[1;5S"  , ControlMask , 0  , 0  } , /* F28 */
	{ XK_F4           , "\033[1;6S"  , Mod4Mask    , 0  , 0  } , /* F40 */
	{ XK_F4           , "\033[1;3S"  , Mod1Mask    , 0  , 0  } , /* F52 */
	{ XK_F5           , "\033[15~"   , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F5           , "\033[15;2~" , ShiftMask   , 0  , 0  } , /* F17 */
	{ XK_F5           , "\033[15;5~" , ControlMask , 0  , 0  } , /* F29 */
	{ XK_F5           , "\033[15;6~" , Mod4Mask    , 0  , 0  } , /* F41 */
	{ XK_F5           , "\033[15;3~" , Mod1Mask    , 0  , 0  } , /* F53 */
	{ XK_F6           , "\033[17~"   , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F6           , "\033[17;2~" , ShiftMask   , 0  , 0  } , /* F18 */
	{ XK_F6           , "\033[17;5~" , ControlMask , 0  , 0  } , /* F30 */
	{ XK_F6           , "\033[17;6~" , Mod4Mask    , 0  , 0  } , /* F42 */
	{ XK_F6           , "\033[17;3~" , Mod1Mask    , 0  , 0  } , /* F54 */
	{ XK_F7           , "\033[18~"   , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F7           , "\033[18;2~" , ShiftMask   , 0  , 0  } , /* F19 */
	{ XK_F7           , "\033[18;5~" , ControlMask , 0  , 0  } , /* F31 */
	{ XK_F7           , "\033[18;6~" , Mod4Mask    , 0  , 0  } , /* F43 */
	{ XK_F7           , "\033[18;3~" , Mod1Mask    , 0  , 0  } , /* F55 */
	{ XK_F8           , "\033[19~"   , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F8           , "\033[19;2~" , ShiftMask   , 0  , 0  } , /* F20 */
	{ XK_F8           , "\033[19;5~" , ControlMask , 0  , 0  } , /* F32 */
	{ XK_F8           , "\033[19;6~" , Mod4Mask    , 0  , 0  } , /* F44 */
	{ XK_F8           , "\033[19;3~" , Mod1Mask    , 0  , 0  } , /* F56 */
	{ XK_F9           , "\033[20~"   , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F9           , "\033[20;2~" , ShiftMask   , 0  , 0  } , /* F21 */
	{ XK_F9           , "\033[20;5~" , ControlMask , 0  , 0  } , /* F33 */
	{ XK_F9           , "\033[20;6~" , Mod4Mask    , 0  , 0  } , /* F45 */
	{ XK_F9           , "\033[20;3~" , Mod1Mask    , 0  , 0  } , /* F57 */
	{ XK_F10          , "\033[21~"   , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F10          , "\033[21;2~" , ShiftMask   , 0  , 0  } , /* F22 */
	{ XK_F10          , "\033[21;5~" , ControlMask , 0  , 0  } , /* F34 */
	{ XK_F10          , "\033[21;6~" , Mod4Mask    , 0  , 0  } , /* F46 */
	{ XK_F10          , "\033[21;3~" , Mod1Mask    , 0  , 0  } , /* F58 */
	{ XK_F11          , "\033[23~"   , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F11          , "\033[23;2~" , ShiftMask   , 0  , 0  } , /* F23 */
	{ XK_F11          , "\033[23;5~" , ControlMask , 0  , 0  } , /* F35 */
	{ XK_F11          , "\033[23;6~" , Mod4Mask    , 0  , 0  } , /* F47 */
	{ XK_F11          , "\033[23;3~" , Mod1Mask    , 0  , 0  } , /* F59 */
	{ XK_F12          , "\033[24~"   , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F12          , "\033[24;2~" , ShiftMask   , 0  , 0  } , /* F24 */
	{ XK_F12          , "\033[24;5~" , ControlMask , 0  , 0  } , /* F36 */
	{ XK_F12          , "\033[24;6~" , Mod4Mask    , 0  , 0  } , /* F48 */
	{ XK_F12          , "\033[24;3~" , Mod1Mask    , 0  , 0  } , /* F60 */
	{ XK_F13          , "\033[1;2P"  , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F14          , "\033[1;2Q"  , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F15          , "\033[1;2R"  , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F16          , "\033[1;2S"  , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F17          , "\033[15;2~" , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F18          , "\033[17;2~" , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F19          , "\033[18;2~" , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F20          , "\033[19;2~" , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F21          , "\033[20;2~" , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F22          , "\033[21;2~" , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F23          , "\033[23;2~" , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F24          , "\033[24;2~" , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F25          , "\033[1;5P"  , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F26          , "\033[1;5Q"  , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F27          , "\033[1;5R"  , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F28          , "\033[1;5S"  , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F29          , "\033[15;5~" , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F30          , "\033[17;5~" , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F31          , "\033[18;5~" , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F32          , "\033[19;5~" , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F33          , "\033[20;5~" , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F34          , "\033[21;5~" , XK_NO_MOD   , 0  , 0  } ,
	{ XK_F35          , "\033[23;5~" , XK_NO_MOD   , 0  , 0  } ,
};

/*
 * Selection types' masks.
 * Use the same masks as usual.
 * Button1Mask is always unset, to make masks match between ButtonPress.
 * ButtonRelease and MotionNotify.
 * If no match is found, regular selection is used.
 */
static uint selmasks[] = {
	[SEL_RECTANGULAR] = Mod1Mask,
};
