/*  ____   ____                                           */
/* |  _ \ / ___|    Dimitris Gerasimou (dimgerasimou)     */
/* | | | | |  _     <https://github.com/dimgerasimou>     */
/* | |_| | |_| |                                          */
/* |____/ \____|                                          */
/*                                                        */
/* My dwm configuration file.                             */

/* Header definitions ------------------------------------*/
#define CONFIGPATH(script) "/home/dimgerasimou/.local/bin/" #script

/* Appearance --------------------------------------------*/

/* borders */
static const unsigned int borderpx  = 2;                        /* border pixel of windows */
static const unsigned int snap      = 32;                       /* snap pixel */

/* vanity gaps */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */

/* bar */
static const int showbar            = 1;                        /* 0 means no bar */
static const int topbar             = 1;                        /* 0 means bottom bar */

/* fonts */
static const char *fonts[]          = { "monospace:size=10", "FiraCode Nerd Font:size=10", "JoyPixels:size=10:antialias=true:autohint=true" };
static const char dmenufont[]       = "monospace:size=10";

/* colors */
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* alpha */
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* Functionality -----------------------------------------*/

/* tags */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* rules */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance    title       tags mask     isfloating   monitor */
	{ "Gimp",        NULL,       NULL,       0,            1,           -1 },
	{ "firefox",     NULL,       NULL,       1 << 8,       0,           -1 },
	{ "thunderbird", NULL,       NULL,       1 << 7,       0,           -1 },
	{ "dolphin",     NULL,       NULL,       0,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55;                           /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;                              /* number of clients in master area */
static const int resizehints = 1;                              /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;                           /* 1 will force focus on the fullscreen window */
static const int decorhints  = 1;                              /* 1 means respect decoration hints */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },                                      /* first entry is default */
	{ "><>",      NULL },                                      /* no layout function means floating behavior */
	{ "[M]",      monocle },
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

/* Commands ----------------------------------------------*/

/* application launchers */
static char dmenumon[2] = "0";                                 /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]    = { "alacritty", NULL };
static const char *browsercmd[] = { "firefox", NULL };
static const char *emailcmd[]   = { "thunderbird", NULL };
static const char *fmgercmd[]   = { "dolphin", NULL };

/* Volume control */
static const char *volumeup[]   = { CONFIGPATH(volumecontrol), "--volume",     "--raise", NULL };
static const char *volumedown[] = { CONFIGPATH(volumecontrol), "--volume",     "--lower", NULL };
static const char *volumemute[] = { CONFIGPATH(volumecontrol), "--volume",     "--mute",  NULL };
static const char *micmute[]    = { CONFIGPATH(volumecontrol), "--microphone", "--mute",  NULL };

/* Brightness control */
static const char *brightup[]   = { "brightnessctl", "--class=backlight", "set", "+5%", NULL };
static const char *brightdown[] = { "brightnessctl", "--class=backlight", "set", "5%-", NULL };

/* Keyboard language */
static const char *switchlang[] = { CONFIGPATH(swaplanguage), NULL };

/* Keybinds ----------------------------------------------*/

static Key keys[] = {
	/* modifier                     key            function        argument */

	/* application control */
	{ MODKEY,                       XK_p,          spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,     spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,          spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_e,          spawn,          {.v = emailcmd } },
	{ MODKEY,                       XK_r,          spawn,          {.v = fmgercmd } },
	{ MODKEY|ShiftMask,             XK_BackSpace,  killclient,     {0} },
	{ MODKEY,                       XK_space,      spawn,          {.v = switchlang } },


	{ MODKEY,                       XK_b,          togglebar,      {0} },

	/* window controls */
	{ MODKEY,                       XK_j,          focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,          focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,          rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,          rotatestack,    {.i = -1 } },	
	{ MODKEY,                       XK_i,          incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,          incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,          setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,          setmfact,       {.f = +0.05} },
	/*{ MODKEY,                       XK_Return,     zoom,           {0} },*/
	{ MODKEY,                       XK_Tab,        view,           {0} },
	{ MODKEY,                       XK_t,          setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,          setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,          setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,           XK_space,      setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,      togglefloating, {0} },
	{ MODKEY,                       XK_0,          view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,          tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,      focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,     focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,     tagmon,         {.i = +1 } },

	/* vanity gaps */
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
    
	/* FN keys */
	{ 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = volumeup } },
	{ 0,                            XF86XK_AudioLowerVolume, spawn, {.v = volumedown } },
	{ 0,                            XF86XK_AudioMute,        spawn, {.v = volumemute } },
	{ 0,                            XF86XK_AudioMicMute,     spawn, {.v = micmute } },

	{ 0,                            XF86XK_MonBrightnessUp,  spawn, {.v = brightup } },
	{ 0,                            XF86XK_MonBrightnessDown,spawn, {.v = brightdown } },

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

	/* login */
	{ MODKEY|ShiftMask,             XK_q,          quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,          quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

