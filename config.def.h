/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 3;   /* border pixel of windows */
static unsigned int snap      = 32;  /* snap pixel */
static unsigned int gappx     = 5;   /* gaps between windows */

/* bar */
static unsigned int showbar        = 1;  /* 0 means no bar */
static unsigned int topbar         = 1;  /* 0 means bottom bar */
static unsigned int vertpad        = 0;  /* vertical padding of bar */
static unsigned int sidepad        = 0;  /* horizontal padding of bar */
static unsigned int drawvacanttags = 1;  /* 0 means no vacant tags drawn*/
static unsigned int centertitle    = 1;  /* center window title */
static unsigned int showtitle      = 1;  /* show window title */
static unsigned int showltsymbol   = 1;  /* show layout symbol */

/* systray */
static       unsigned int showsystray             = 1;  /* 0 means no systray */
static const unsigned int systraypinning          = 0;  /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static       unsigned int systrayonleft           = 0;  /* 0: systray in the right corner, >0: systray on left of status text */
static       unsigned int systrayspacing          = 5;  /* systray spacing */
static       unsigned int systraypadding          = 0;  /* systray pading (detach from bar) */
static const unsigned int systraypinningfailfirst = 1;  /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/

/* fonts */
static char font[256]      = "monspace:size=11";
static char *fonts[]       = { font, "monspace:size=11" };
static char dmenufont[256] = "monospace:size=10";

/* colors & alphas */
static char hexFg[16]      = "#bbbbbb";
static char hexBg[16]      = "#222222";
static char hexSelFg[16]   = "#eeeeee";
static char hexSelBg[16]   = "#005577";
static char hexTitleFg[16] = "#eeeeee";
static char hexTitleBg[16] = "#222222";
static char hexTrayBg[16]  = "#222222";
static char hexBSel[16]    = "#005577";
static char hexBUnsel[16]  = "#444444";

static char *colors[][2] = {
	/*                   fg          bg         */
	[SchemeNorm]     = { hexFg,      hexBg      },
	[SchemeSel]      = { hexSelFg,   hexSelBg   },
	[SchemeSelTitle] = { hexTitleFg, hexTitleBg },
	[SchemeSystray]  = { hexFg,      hexTrayBg  }, /* fg is currently not used anywhere */
	[SchemeBorder]   = { hexBSel,    hexBUnsel  }, /* fg is sel border color and bg is norm border color */
};

static unsigned int alphas[][2] = {
	/*                   fg      bg     */
	[SchemeNorm]     = { OPAQUE, 0xd0   },
	[SchemeSel]      = { OPAQUE, 0xd0   },
	[SchemeSelTitle] = { OPAQUE, 0xd0   },
	[SchemeSystray]  = { OPAQUE, 0xd0   }, /* fg is currently not used anywhere */
	[SchemeBorder]   = { OPAQUE, OPAQUE }, /* transparent borders are broken on most apps, recommend to be set on OPAQUE */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact         = 0.55;         /* factor of master area size [0.05..0.95] */
static const int nmaster         = 1;            /* number of clients in master area */
static const int nobrodersingle  = 1;            /* 1 means no window border when only a single window is on the screen */
static const int resizehints     = 1;            /* 1 means respect size hints in tiled resizals */
static const int decorhints      = 1;            /* 1 means respect decoration hints */
static const int lockfullscreen  = 1;            /* 1 will force focus on the fullscreen window */
static const int refreshrate     = 120;          /* refresh rate (per second) for client move/resize */
static const int attachwhichside = AttachAside;  /* valid values: AttachDefault, AttachAbove, AttachAside, AttachBelow, AttachBottom, AttachTop */
static const int swallowfloating = 0;            /* 1 means swallow floating windows by default */
static const int focusonwheel    = 1;            /* 1 means focus on scroll as well, not only on click */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2]            = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]      = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", hexBg, "-nf", hexFg, "-sb", hexSelBg, "-sf", hexSelFg, NULL };
static const char *termcmd[]       = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

/* Xresources preferences to load at startup */
ResourcePref resources[] = {
	{ "borderpx",       INTEGER, &borderpx                      },
	{ "snap",           INTEGER, &snap                          },
	{ "gappx",          INTEGER, &gappx                         },
	{ "showbar",        INTEGER, &showbar                       },
	{ "topbar",         INTEGER, &topbar                        },
	{ "vertpad",        INTEGER, &vertpad                       },
	{ "sidepad",        INTEGER, &sidepad                       },
	{ "drawvacanttags", INTEGER, &drawvacanttags                },
	{ "centertitle",    INTEGER, &centertitle                   },
	{ "showtitle",      INTEGER, &showtitle                     },
	{ "showltsymbol",   INTEGER, &showltsymbol                  },
	{ "showsystray",    INTEGER, &showsystray                   },
	{ "systrayonleft",  INTEGER, &systrayonleft                 },
	{ "systrayspacing", INTEGER, &systrayspacing                },
	{ "systraypadding", INTEGER, &systraypadding                },
	{ "font",           STRING,  &font                          },
	{ "dmenufont",      STRING,  &dmenufont                     },
	{ "hexFg",          STRING,  &hexFg                         },
	{ "hexBg",          STRING,  &hexBg                         },
	{ "hexSelFg",       STRING,  &hexSelFg                      },
	{ "hexSelBg",       STRING,  &hexSelBg                      },
	{ "hexTitleFg",     STRING,  &hexTitleFg                    },
	{ "hexTitleBg",     STRING,  &hexTitleBg                    },
	{ "hexTrayBg",      STRING,  &hexTrayBg                     },
	{ "hexBSel",        STRING,  &hexBSel                       },
	{ "hexBUnsel",      STRING,  &hexBUnsel                     },
	{ "alphaBg",        INTEGER, &alphas[SchemeNorm][ColBg]     },
	{ "alphaSelBg",     INTEGER, &alphas[SchemeSel][ColBg]      },
	{ "alphaTitleBg",   INTEGER, &alphas[SchemeSelTitle][ColBg] },
	{ "alphaTrayBg",    INTEGER, &alphas[SchemeSystray][ColBg]  },
};


static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

