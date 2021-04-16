/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const char *fonts[] = {"FiraCode Nerd Font:size=12"};
static const char dmenufont[] = {"FiraCode Nerd Font:size=12"};
static const char col_gray1[] = "#222222";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#ffffff";
static const char col_cyan[] = "#37474F";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
    [SchemeSel] = {col_gray4, col_cyan, col_cyan},
};

/* tagging */
static const char *tags[] = {"\uf120", "\uf7ae", "\uf121", "\uf04b", "\ue62e",
                             "\uf251", "\ue727", "\uf537", "\uf684"};
// static const char *tags[] = { "\uf120", "\uf7ae", "\uf121", "\uf04b",
// "\ue62e", "\uf251", "\ue727", "\uf537", "\uf684" }; ☕"\u+2516"

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Gimp", NULL, NULL, 0, 1, -1},
    {"Firefox", NULL, NULL, 1 << 8, 0, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     col_gray1,
    "-nf",       col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL};
static const char *termcmd[]        = {"st", NULL};
static const char *alacrittycmd[]   = {"alacritty", NULL};
static const char *fcitx5cmd[]      = {"fcitx5", NULL};
static const char *thunderbirdcmd[] = {"thunderbird", NULL};
static const char *clipmenucmd[]    = {"/usr/bin/clipmenu", NULL};
static const char *qutebroswercmd[] = {"qutebroswer", NULL};
static const char *browsercmd[] = {
    "google-chrome-stable", "--proxy-server=http://127.0.0.1:7890", NULL};

static const char *upvol[]         = {"/home/omega/.local/bin/vol-up.sh", NULL};
static const char *downvol[]       = {"/home/omega/.local/bin/vol-down.sh", NULL};
static const char *mutevol[]       = {"/home/omega/.local/bin/vol-toggle.sh", NULL};

static const char *suspendcmd[]    = {"/home/omega/.local/bin/suspend.sh", NULL};
static const char *hibernatecmd[]  = {"/home/omega/.local/bin/hibernate.sh", NULL};

static const char *screenkeycmd[]  = {"/home/omega/.local/bin/sck-tog.sh", NULL};
static const char *screenshotcmd[] = {"/home/omega/.local/bin/screenshot.sh", NULL};

// static const char *monbrightnessup[] = {
// "/home/omega/.local/bin/monbrightnessup.sh", NULL }; static const char
// *monbrightnessdown[] = { "/home/omega/.local/bin/monbrightnessdown.sh", NULL
// };

static Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY             , XK_z                    , spawn          , {.v = dmenucmd}}       ,
    {MODKEY             , XK_Return               , spawn          , {.v = termcmd}}        ,
    {MODKEY             , XK_y                    , spawn          , {.v = alacrittycmd}}   ,
    {MODKEY             , XK_c                    , spawn          , {.v = fcitx5cmd}}      ,
    {MODKEY             , XK_v                    , spawn          , {.v = clipmenucmd}}    ,
    {MODKEY             , XK_g                    , spawn          , {.v = browsercmd}}     ,
    {MODKEY | ShiftMask , XK_g                    , spawn          , {.v = qutebroswercmd}} ,
    {MODKEY             , XK_e                    , spawn          , {.v = thunderbirdcmd}} ,
    {MODKEY | ShiftMask , XK_p                    , spawn          , {.v = hibernatecmd}}   ,
    {0                  , XF86XK_PowerOff         , spawn          , {.v = suspendcmd}}     ,
    {0                  , XF86XK_AudioLowerVolume , spawn          , {.v = downvol}}        ,
    //{ 0               , XF86XK_AudioMute        , spawn          , {.v = mutevol } }      ,
    {0                  , XF86XK_AudioRaiseVolume , spawn          , {.v = upvol}}          ,
    {MODKEY             , XK_bracketleft          , spawn          , {.v = downvol}}        ,
    {MODKEY             , XK_backslash            , spawn          , {.v = mutevol}}        ,
    {MODKEY             , XK_bracketright         , spawn          , {.v = upvol}}          ,
    {0                  , XK_Print                , spawn          , {.v = screenshotcmd}}  ,
    {MODKEY | ShiftMask , XK_y                    , spawn          , {.v = screenkeycmd}}   ,
    {MODKEY             , XK_b                    , togglebar      , {0}}                   ,
    {MODKEY             , XK_j                    , focusstack     , {.i = +1}}             ,
    {MODKEY             , XK_k                    , focusstack     , {.i = -1}}             ,
    {MODKEY             , XK_i                    , incnmaster     , {.i = +1}}             ,
    {MODKEY             , XK_d                    , incnmaster     , {.i = -1}}             ,
    {MODKEY             , XK_h                    , setmfact       , {.f = -0.05}}          ,
    {MODKEY             , XK_l                    , setmfact       , {.f = +0.05}}          ,
    {MODKEY | ShiftMask , XK_Return               , zoom           , {0}}                   ,
    {MODKEY             , XK_Tab                  , view           , {0}}                   ,
    {MODKEY | ShiftMask , XK_c                    , killclient     , {0}}                   ,
    {MODKEY             , XK_t                    , setlayout      , {.v = &layouts[0]}}    ,
    {MODKEY             , XK_f                    , setlayout      , {.v = &layouts[1]}}    ,
    {MODKEY             , XK_m                    , setlayout      , {.v = &layouts[2]}}    ,
    {MODKEY | ShiftMask , XK_f                    , fullscreen     , {0}}                   ,
    {MODKEY             , XK_space                , setlayout      , {0}}                   ,
    {MODKEY | ShiftMask , XK_f                    , togglefullscr  , {0}}                   ,
    {MODKEY | ShiftMask , XK_space                , togglefloating , {0}}                   ,
    {MODKEY             , XK_s                    , togglesticky   , {0}}                   ,
    {MODKEY             , XK_0                    , view           , {.ui = ~0}}            ,
    {MODKEY | ShiftMask , XK_0                    , tag            , {.ui = ~0}}            ,
    {MODKEY             , XK_comma                , focusmon       , {.i = -1}}             ,
    {MODKEY             , XK_period               , focusmon       , {.i = +1}}             ,
    {MODKEY | ShiftMask , XK_comma                , tagmon         , {.i = -1}}             ,
    {MODKEY | ShiftMask , XK_period               , tagmon         , {.i = +1}}             ,
    //{ 0,           XF86XK_MonBrightnessDown,   spawn,          {.v =
    // monbrightnessdown} }, { 0,           XF86XK_MonBrightnessUp,     spawn,
    //{.v = monbrightnessup } }, { MODKEY|ShiftMask,         XK_space,
    // togglealwaysontop,   {0} },
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument
     */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
