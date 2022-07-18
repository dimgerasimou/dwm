/*  ____   ____                                          */
/* |  _ \ / ___|    Dimitris Gerasimou (dimgerasimou)    */
/* | | | | |  _     <https://github.com/dimgerasimou>    */
/* | |_| | |_| |                                         */
/* |____/ \____|                                         */
/*                                                       */
/* My dwm configuration file                             */

#define STATUSBAR "dwmblocks"

/* appearance */
static unsigned int borderpx  = 1;              /* border pixel of windows */
static unsigned int snap      = 32;             /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static int showbar            = 1;              /* 0 means no bar */
static int topbar             = 1;              /* 0 means bottom bar */
static char font[]            = "monospace:size=10";
static char dmenufont[]       = "monospace:size=10";
static const char *fonts[]    = { font };
static char normbgcolor[]     = "#222222";
static char normbordercolor[] = "#444444";
static char normfgcolor[]     = "#bbbbbb";
static char selfgcolor[]      = "#eeeeee";
static char selbordercolor[]  = "#005577";
static char selbgcolor[]      = "#005577";
static char *colors[][3]      = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* audio control */
static const char *volumeup[]   = { "/home/dimgerasimou/.local/bin/dwm/dwm/volumecontrol",    "--volume",        "--raise",    NULL };
static const char *volumedown[] = { "/home/dimgerasimou/.local/bin/dwm/dwm/volumecontrol",    "--volume",        "--lower",    NULL };
static const char *volumemute[] = { "/home/dimgerasimou/.local/bin/dwm/dwm/volumecontrol",    "--volume",        "--mute",     NULL };
static const char *mutemic[]    = { "/home/dimgerasimou/.local/bin/dwm/dwm/volumecontrol",    "--microphone",    "--mute",     NULL };

/* brightness control */
static const char *brightnessup[]   = { "/usr/bin/brightnessctl",    "--class=backlight",    "set",    "+5%",    NULL };
static const char *brightnessdown[] = { "/usr/bin/brightnessctl",    "--class=backlight",    "set",    "5%-",    NULL };

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title            tags mask    iscentered    isfloating    isterminal    noswallow    monitor */
	{ "Gimp",     NULL,       NULL,            0,           0,            1,            0,            0,           -1 },
	{ "firefox",  NULL,       NULL,            1 << 8,      0,            0,            0,            0,           -1 },
	{ "dolphin",  NULL,       NULL,            0,           0,            1,            0,            0,           -1 },
	{ "alacritty",NULL,       NULL,            0,           0,            0,            1,            0,           -1 },
	{ NULL,       NULL,       "Event Tester",  0,           0,            0,            0,            1,           -1 },
};

/* layout(s) */
static float mfact     = 0.55;       /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;          /* number of clients in master area */
static int resizehints = 1;          /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 1;    /* 1 means respect decoration hints */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      grid },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *emailcmd[] = { "thunderbird", NULL};
static const char *filecmd[]  = { "dolphin", NULL };
static const char *browsercmd[] = { "firefox", NULL };

/* xresources preferences to load at startup */
ResourcePref resources[] = {
		{ "font",               STRING,  &font },
		{ "dmenufont",          STRING,  &dmenufont },
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};

static Key keys[] = {
	/* modifier                     key            function        argument */

	/* application spawning */
	{ MODKEY,                       XK_p,          spawn,          {.v = dmenucmd }   },
	{ MODKEY|ShiftMask,             XK_Return,     spawn,          {.v = termcmd }    },
	{ MODKEY,                       XK_w,          spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_e,          spawn,          {.v = emailcmd }   },
	{ MODKEY,                       XK_r,          spawn,          {.v = filecmd }    },

	/* dwm control */
	{ MODKEY,                       XK_b,          togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,          rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,          rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,          focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,          focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,          incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,          incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,          setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,          setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,     zoom,           {0} },
	{ MODKEY,                       XK_Tab,        view,           {0} },
	{ MODKEY|ShiftMask,             XK_BackSpace,  killclient,     {0} },
	
	/* layouts */
	{ MODKEY,                       XK_t,          setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,          setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,          setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,           XK_comma,      cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period,     cyclelayout,    {.i = +1 } },	
	{ MODKEY,                       XK_g,          setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,      setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,      togglefloating, {0} },
	{ MODKEY,                       XK_0,          view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,          tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,      focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,     focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,     tagmon,         {.i = +1 } },
	{ MODKEY|ControlMask,           XK_space,      focusmaster,    {0} },
	
	/* vainty gaps */
	{ MODKEY|Mod1Mask,              XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },

	
	/* fn keys utilities */
	{ 0,                            XF86XK_AudioMute,          spawn,    {.v = volumemute}     },
	{ 0,                            XF86XK_AudioRaiseVolume,   spawn,    {.v = volumeup}       },
	{ 0,                            XF86XK_AudioLowerVolume,   spawn,    {.v = volumedown}     },
	{ 0,                            XF86XK_AudioMicMute,       spawn,    {.v = mutemic}        },
	{ 0,                            XF86XK_MonBrightnessUp,    spawn,    {.v = brightnessup}   },
	{ 0,                            XF86XK_MonBrightnessDown,  spawn,    {.v = brightnessdown} },

	/* tagkeys */
	TAGKEYS(                        XK_1,                          0)
	TAGKEYS(                        XK_2,                          1)
	TAGKEYS(                        XK_3,                          2)
	TAGKEYS(                        XK_4,                          3)
	TAGKEYS(                        XK_5,                          4)
	TAGKEYS(                        XK_6,                          5)
	TAGKEYS(                        XK_7,                          6)
	TAGKEYS(                        XK_8,                          7)
	TAGKEYS(                        XK_9,                          8)
	{ MODKEY|ShiftMask,             XK_q,          quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,          quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

