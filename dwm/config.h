/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12" };
static const char dmenufont[]       = "monospace:size=12";
// par defaut
// static const char col_gray1[]       = "#222222";
// static const char col_gray2[]       = "#444444";
// static const char col_gray3[]       = "#bbbbbb";
// static const char col_gray4[]       = "#eeeeee";
// static const char col_cyan[]        = "#005577";
// rouge
// static const char col_gray1[]       = "#BE3144";
// static const char col_gray2[]       = "#F05941";
// static const char col_gray3[]       = "#22092C";
// static const char col_gray4[]       = "#F05941";
// static const char col_cyan[]        = "#872341";
// vert
static const char col_gray1[]       = "#A0E418";
static const char col_gray2[]       = "#E5F9BD";
static const char col_gray3[]       = "#505250";
static const char col_gray4[]       = "#E5F9BD";
static const char col_cyan[]        = "#7FB414";
// bleu
// static const char col_gray1[]       = "#9AD0C2"; //F1FADA
// static const char col_gray2[]       = "#F1FADA"; //265073
// static const char col_gray3[]       = "#265073"; //2D9596
// static const char col_gray4[]       = "#F1FADA"; //265073
// static const char col_cyan[]        = "#2D9596"; //9AD0C2
// gay
// static const char col_gray1[]       = "#F7418F";
// static const char col_gray2[]       = "#FFF3C7";
// static const char col_gray3[]       = "#FEC7B4";
// static const char col_gray4[]       = "#FFF3C7";
// static const char col_cyan[]        = "#FC819E";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	// { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
 	{ "HHH",      grid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/bash", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "xfce4-terminal", "--hide-menubar", NULL };
static const char *firefox[]  = { "firefox", NULL };
static const char *cacalendar[]  = { "cacalendar", NULL };
static const char *pcmanfm[]  = { "pcmanfm", NULL };
static const char *thunderbird[]  = { "thunderbird", NULL };
static const char *mineur[]  = { "mineur", NULL };

#define PrintScreenDWM 0x0000ff61

static const Key keys[] = {
    /* custom */
	{ 0,    XF86XK_PowerOff,            spawn,  SHCMD("power") },
    { 0,    XF86XK_AudioRaiseVolume,    spawn,  SHCMD("volume add") },
	{ 0,    XF86XK_AudioLowerVolume,    spawn,  SHCMD("volume min") },
    { 0,    XF86XK_AudioMute,           spawn,  SHCMD("volume set 0") },
    { 0,    XF86XK_AudioPlay,           spawn,  SHCMD("volume set 100") },
    { 0,    XF86XK_MonBrightnessUp,     spawn,  SHCMD("luminosity add") },
    { 0,    XF86XK_MonBrightnessDown,   spawn,  SHCMD("luminosity min") },
    { 0,    PrintScreenDWM,             spawn,  SHCMD("screenshot") },
    { ShiftMask,        XF86XK_AudioRaiseVolume,    spawn,  SHCMD("set-sound-card next") },
	{ ShiftMask,        XF86XK_AudioLowerVolume,    spawn,  SHCMD("set-sound-card prev") },
    { ShiftMask,        XF86XK_AudioMute,           spawn,  SHCMD("set-sound-card") },
    { ShiftMask,        PrintScreenDWM, spawn,  SHCMD("screenrecorder") },
    { MODKEY|ShiftMask, XK_l,           spawn,  SHCMD("lockscreen") },
    { MODKEY,           XK_w,           spawn,  SHCMD("randwallpaper") },
    { MODKEY|ShiftMask, XK_w,           spawn,  SHCMD("wallpaper") },
    { MODKEY|Mod1Mask,  XK_f,           spawn,  {.v = firefox} },
    { MODKEY|Mod1Mask,  XK_c,           spawn,  {.v = cacalendar} },
    { MODKEY|Mod1Mask,  XK_p,           spawn,  {.v = pcmanfm} },
    { MODKEY|Mod1Mask,  XK_t,           spawn,  {.v = thunderbird} },
    { MODKEY|Mod1Mask,  XK_m,           spawn,  {.v = mineur} },
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,   			XK_s,	   spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_agrave, view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_agrave, tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_semicolon, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_semicolon, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_ampersand,              0)
	TAGKEYS(                        XK_eacute,                 1)
	TAGKEYS(                        XK_quotedbl,               2)
	TAGKEYS(                        XK_apostrophe,             3)
	TAGKEYS(                        XK_parenleft,              4)
	TAGKEYS(                        XK_minus,                  5)
	TAGKEYS(                        XK_egrave,                 6)
	TAGKEYS(                        XK_underscore,             7)
	TAGKEYS(                        XK_ccedilla,               8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

