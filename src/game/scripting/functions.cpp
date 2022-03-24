#include <std_include.hpp>
#include "functions.hpp"

namespace game::scripting
{
	std::map<std::string, int> instance_function_map =
	{
		{"getviewmodel", 33457},
		{"fragbuttonpressed", 33458},
		{"secondaryoffhandbuttonpressed", 33459},
		{"getcurrentweaponclipammo", 33460},
		{"setvelocity", 33461},
		{"getplayerviewheight", 33462},
		{"enablemousesteer", 33545},
		{"getnormalizedmovement", 33463},
		{"getnormalizedcameramovement", 33486},
		{"giveweapon", 33487},
		{"takeweapon", 33488},
		{"takeallweapons", 33489},
		{"getcurrentweapon", 33490},
		{"getcurrentprimaryweapon", 33491},
		{"getcurrentoffhand", 33492},
		{"hasweapon", 33493},
		{"switchtoweapon", 33494},
		{"switchtoweaponimmediate", 33495},
		{"switchtooffhand", 33496},
		{"givestartammo", 33522},
		{"givemaxammo", 33523},
		{"getfractionstartammo", 33524},
		{"getfractionmaxammo", 33525},
		{"isdualwielding", 33526},
		{"isreloading", 33527},
		{"isswitchingweapon", 33528},
		{"setorigin", 33529},
		{"getvelocity", 33530},
		{"setplayerangles", 33531},
		{"getplayerangles", 33532},
		{"usebuttonpressed", 33533},
		{"attackbuttonpressed", 33534},
		{"adsbuttonpressed", 33535},
		{"meleebuttonpressed", 33536},
		{"playerads", 33537},
		{"isonground", 33538},
		{"isusingturret", 33539},
		{"setviewmodel", 33540},
		{"setoffhandprimaryclass", 33541},
		{"getoffhandprimaryclass", 33542},
		{"setoffhandsecondaryclass", 33497},
		{"getoffhandsecondaryclass", 33498},
		{"beginlocationselection", 33499},
		{"endlocationselection", 33500},
		{"disableweapons", 33501},
		{"enableweapons", 33502},
		{"disableoffhandweapons", 33503},
		{"enableoffhandweapons", 33504},
		{"disableweaponswitch", 33505},
		{"enableweaponswitch", 33506},
		{"openpopupmenu", 33507},
		{"openpopupmenunomouse", 33508},
		{"closepopupmenu", 33509},
		{"openmenu", 33510},
		{"closemenu", 33511},
		{"freezecontrols", 33513},
		{"disableusability", 33514},
		{"enableusability", 33515},
		{"setwhizbyspreads", 33516},
		{"setwhizbyradii", 33517},
		{"setreverb", 33518},
		{"deactivatereverb", 33519},
		{"setvolmod", 33520},
		{"setchannelvolume", 33521},
		{"setchannelvolumes", 33464},
		{"deactivatechannelvolumes", 33465},
		{"playlocalsound", 33466},
		{"stoplocalsound", 33467},
		{"setweaponammoclip", 33468},
		{"setweaponammostock", 33469},
		{"getweaponammoclip", 33470},
		{"getweaponammostock", 33471},
		{"anyammoforweaponmodes", 33472},
		{"setclientdvar", 33473},
		{"setclientdvars", 33474},
		{"allowads", 33475},
		{"allowjump", 33476},
		{"allowsprint", 33477},
		{"setspreadoverride", 33478},
		{"resetspreadoverride", 33479},
		{"setaimspreadmovementscale", 33480},
		{"setactionslot", 33481},
		{"setviewkickscale", 33482},
		{"getviewkickscale", 33483},
		{"getweaponslistall", 33484},
		{"getweaponslistprimaries", 33485},
		{"getweaponslistoffhands", 33430},
		{"getweaponslistitems", 33431},
		{"getweaponslistexclusives", 33432},
		{"getweaponslist", 33433},
		{"canplayerplacesentry", 33434},
		{"canplayerplacetank", 33435},
		{"visionsetnakedforplayer", 33436},
		{"visionsetnightforplayer", 33437},
		{"visionsetmissilecamforplayer", 33438},
		{"visionsetthermalforplayer", 33439},
		{"visionsetpainforplayer", 33440},
		{"setblurforplayer", 33441},
		{"getplayerweaponmodel", 33442},
		{"getplayerknifemodel", 33443},
		{"updateplayermodelwithweapons", 33444},
		{"notifyonplayercommand", 33445},
		{"canmantle", 33446},
		{"forcemantle", 33447},
		{"ismantling", 33448},
		{"playfx", 33449},
		{"recoilscaleon", 33450},
		{"recoilscaleoff", 33451},
		{"weaponlockstart", 33452},
		{"weaponlockfinalize", 33453},
		{"weaponlockfree", 33454},
		{"weaponlocktargettooclose", 33455},
		{"weaponlocknoclearance", 33390},
		{"visionsyncwithplayer", 33391},
		{"showhudsplash", 33392},
		{"setperk", 33393},
		{"hasperk", 33394},
		{"clearperks", 33395},
		{"unsetperk", 33396},
		{"noclip", 33397},
		{"ufo", 33398},

		// playercmd #2
		{"pingplayer", 33308},
		{"buttonpressed", 33309},
		{"sayall", 33310},
		{"sayteam", 33311},
		{"showscoreboard", 33312},
		{"setspawnweapon", 33313},
		{"dropitem", 33314},
		{"dropscavengerbag", 33315},
		{"finishplayerdamage", 33340},
		{"suicide", 33341},
		{"closeingamemenu", 33342},
		{"iprintln", 33343},
		{"iprintlnbold", 33344},
		{"spawn", 33345},
		{"setentertime", 33346},
		{"cloneplayer", 33347},
		{"istalking", 33348},
		{"allowspectateteam", 33349},
		{"getguid", 33350},
		{"getxuid", 33382},
		{"ishost", 33383},
		{"getspectatingplayer", 33384},
		{"predictstreampos", 33385},
		{"updatescores", 33386},
		{"updatedmscores", 33387},
		{"setrank", 33388},
		{"setcardtitle", 33389},
		{"setcardicon", 33420},
		{"setcardnameplate", 33421},
		{"setcarddisplayslot", 33422},
		{"regweaponforfxremoval", 33423},
		{"laststandrevive", 33424},
		{"setspectatedefaults", 33425},
		{"getthirdpersoncrosshairoffset", 33426},
		{"disableweaponpickup", 33427},
		{"enableweaponpickup", 33428},

		// HECmd
		{"settext", 32950},
		{"clearalltextafterhudelem", 32951},
		{"setshader", 32952},
		{"settargetent", 32953},
		{"cleartargetent", 32954},
		{"settimer", 32955},
		{"settimerup", 32956},
		{"settimerstatic", 32957},
		{"settenthstimer", 32958},
		{"settenthstimerup", 32959},
		{"settenthstimerstatic", 32960},
		{"setclock", 32961},
		{"setclockup", 32962},
		{"setvalue", 32963},
		{"setwaypoint", 32964},
		{"rotatingicon", 32965},
		{"secondaryarrow", 32891},
		{"setwaypointiconoffscreenonly", 32892},
		{"fadeovertime", 32893},
		{"scaleovertime", 32894},
		{"moveovertime", 32895},
		{"reset", 32896},
		{"destroy", 32897},
		{"setpulsefx", 32898},
		{"setplayernamestring", 32899},
		{"fadeovertime2", 33547},
		{"scaleovertime2", 33548},
		{"changefontscaleovertime", 32900},

		// ScrCmd
		{"attach", 32791},
		{"attachshieldmodel", 32792},
		{"detach", 32804},
		{"detachshieldmodel", 32805},
		{"moveshieldmodel", 32806},
		{"detachall", 32807},
		{"getattachsize", 32808},
		{"getattachmodelname", 32809},
		{"getattachtagname", 32810},
		{"getattachignorecollision", 32835},
		{"hidepart", 32836},
		{"allinstances", 32837},
		{"hideallparts", 32838},
		{"showpart", 32839},
		{"showallparts", 32840},
		{"linkto", 32841},
		{"linktoblendtotag", 32842},
		{"unlink", 32843},
		{"islinked", 32867},
		{"enablelinkto", 32868},
		{"playerlinkto", 32885},
		{"playerlinktodelta", 32886},
		{"playerlinkweaponviewtodelta", 32887},
		{"playerlinktoabsolute", 32888},
		{"playerlinktoblend", 32889},
		{"playerlinkedoffsetenable", 32890},
		{"playerlinkedoffsetdisable", 32916},
		{"playerlinkedsetviewznear", 32917},
		{"playerlinkedsetusebaseangleforviewclamp", 32918},
		{"lerpviewangleclamp", 32919},
		{"setviewangleresistance", 32920},
		{"geteye", 32921},
		{"istouching", 32922},
		{"stoploopsound", 32923},
		{"stopsounds", 32924},
		{"playrumbleonentity", 32925},
		{"playrumblelooponentity", 32926},
		{"stoprumble", 32927},
		{"delete", 32928},
		{"setmodel", 32929},
		{"laseron", 32930},
		{"laseroff", 32931},
		{"laseraltviewon", 32932},
		{"laseraltviewoff", 32933},
		{"thermalvisionon", 32934},
		{"thermalvisionoff", 32935},
		{"thermaldrawenable", 32803},
		{"thermaldrawdisable", 32768},
		{"thermalvisionfofoverlayon", 32936},
		{"thermalvisionfofoverlayoff", 32937},
		{"autospotoverlayon", 32938},
		{"autospotoverlayoff", 32939},
		{"setcontents", 32940},
		{"makeusable", 32941},
		{"makeunusable", 32942},
		{"setcursorhint", 32966},
		{"sethintstring", 32967},
		{"forceusehinton", 32968},
		{"forceusehintoff", 32969},
		{"makesoft", 32970},
		{"makehard", 32971},
		{"willneverchange", 32972},
		{"startfiring", 32973},
		{"stopfiring", 32974},
		{"isfiringturret", 32975},
		{"startbarrelspin", 32976},
		{"stopbarrelspin", 32977},
		{"getbarrelspinrate", 32978},
		{"remotecontrolturret", 32979},
		{"remotecontrolturretoff", 32980},
		{"shootturret", 32981},
		{"getturretowner", 32982},
		{"setsentryowner", 33006},
		{"setsentrycarrier", 33007},
		{"setturretminimapvisible", 33008},
		{"settargetentity", 33009},
		{"snaptotargetentity", 33010},
		{"cleartargetentity", 33011},
		{"getturrettarget", 33012},
		{"setplayerspread", 33013},
		{"setaispread", 33014},
		{"setsuppressiontime", 33015},
		{"setconvergencetime", 33049},
		{"setconvergenceheightpercent", 33050},
		{"setturretteam", 33051},
		{"maketurretsolid", 33052},
		{"maketurretoperable", 33053},
		{"maketurretinoperable", 33054},
		{"setturretaccuracy", 33082},
		{"setrightarc", 33083},
		{"setleftarc", 33084},
		{"settoparc", 33085},
		{"setbottomarc", 33086},
		{"setautorotationdelay", 33087},
		{"setdefaultdroppitch", 33088},
		{"restoredefaultdroppitch", 33089},
		{"turretfiredisable", 33090},
		{"turretfireenable", 33121},
		{"setturretmodechangewait", 33122},
		{"usetriggerrequirelookat", 33123},
		{"getstance", 33124},
		{"setstance", 33125},
		{"itemweaponsetammo", 33126},
		{"getammocount", 33127},
		{"gettagorigin", 33128},
		{"gettagangles", 33129},
		{"shellshock", 33130},
		{"stunplayer", 33131},
		{"stopshellshock", 33132},
		{"fadeoutshellshock", 33133},
		{"setdepthoffield", 33134},
		{"setviewmodeldepthoffield", 33135},
		{"setmotionblurmovescale", 33136},
		{"setmotionblurturnscale", 33168},
		{"setmotionblurzoomscale", 33169},
		{"viewkick", 33170},
		{"localtoworldcoords", 33171},
		{"getentitynumber", 33172},
		{"getentityvelocity", 33173},
		{"enablegrenadetouchdamage", 33174},
		{"disablegrenadetouchdamage", 33175},
		{"enableaimassist", 33176},
		{"disableaimassist", 33207},
		{"radiusdamage", 33208},
		{"detonate", 33209},
		{"damageconetrace", 33210},
		{"sightconetrace", 33211},
		{"settargetent", 33212},
		{"settargetpos", 33213},
		{"cleartarget", 33214},
		{"setflightmodedirect", 33215},
		{"setflightmodetop", 33216},
		{"getlightintensity", 33217},
		{"setlightintensity", 33218},
		{"isragdoll", 33219},
		{"setmovespeedscale", 33220},
		{"cameralinkto", 33221},
		{"cameraunlink", 33222},
		{"controlslinkto", 33251},
		{"controlsunlink", 33252},
		{"makevehiclesolidcapsule", 33253},
		{"makevehiclesolidsphere", 33254},
		{"remotecontrolvehicle", 33256},
		{"remotecontrolvehicleoff", 33257},
		{"isfiringvehicleturret", 33258},
		{"drivevehicleandcontrolturret", 33259},
		{"drivevehicleandcontrolturretoff", 33260},
		{"getplayersetting", 33261},
		{"getlocalplayerprofiledata", 33262},
		{"setlocalplayerprofiledata", 33263},
		{"remotecamerasoundscapeon", 33264},
		{"remotecamerasoundscapeoff", 33265},
		{"radarjamon", 33266},
		{"radarjamoff", 33267},
		{"setmotiontrackervisible", 33268},
		{"getmotiontrackervisible", 33269},
		{"circle", 33270},
		{"getpointinbounds", 33271},
		{"transfermarkstonewscriptmodel", 33272},
		{"setwatersheeting", 33273},
		{"setweaponhudiconoverride", 33274},
		{"getweaponhudiconoverride", 33275},
		{"setempjammed", 33276},
		{"playersetexpfog", 33277},
		{"isitemunlocked", 33278},
		{"getplayerdata", 33279},
		{"setplayerdata", 33306},

		// Vehicle stuff
		{"teleport", 0x824C},
		{"attachpath", 0x824D},
		{"getattachpos", 0x824E},
		{"startpath", 0x824F},
		{"setswitchnode", 0x8250},
		{"setwaitspeed", 0x8251},
		{"finishdamage", 0x8252},
		{"setspeed", 0x8253},
		{"setspeedimmediate", 0x8254},
		{"setwaitspeed", 0x8251},

		{"setlookatent", 0x8237},
		{"clearlookatent", 0x8238},

		{"setvehgoalpos", 33325},
		{"setturningability", 33381},

		// some entity (script_model) stuff
		{"moveto", 33399},
		{"movex", 33400},
		{"movey", 33401},
		{"movez", 33402},
		{"movegravity", 33403},
		{"moveslide", 33404},
		{"stopmoveslide", 33405},
		{"rotateto", 33406},
		{"rotatepitch", 33407},
		{"rotateyaw", 33408},
		{"rotateroll", 33409},
		{"addpitch", 33410},
		{"addyaw", 33411},
		{"addroll", 33412},
		{"vibrate", 33413},
		{"rotatevelocity", 33414},
		{"solid", 33415},
		{"notsolid", 33416},
		{"setcandamage", 33417},
		{"setcanradiusdamage", 33418},
		{"physicslaunchclient", 33419},
		{"physicslaunchserver", 33351},
		{"physicslaunchserveritem", 33352},
		{"clonebrushmodeltoscriptmodel", 33353},
		{"scriptmodelplayanim", 33354},
		{"scriptmodelclearanim", 33355},

		// varied ent/player script commands
		{"getorigin", 32910},
		{"useby", 32914},
		{"playsound", 32915},
		{"playsoundasmaster", 32878},
		{"playsoundtoteam", 32771},
		{"playsoundtoplayer", 32772},
		{"playloopsound", 32879},
		{"getnormalhealth", 32884},
		{"setnormalhealth", 32844},
		{"show", 32847},
		{"hide", 32848},
		{"playerhide", 32773},
		{"showtoplayer", 32774},
		{"enableplayeruse", 32775},
		{"disableplayeruse", 32776},
		{"setscriptmoverkillcam", 33546},
		{"makescrambler", 32777},
		{"makeportableradar", 32778},
		{"maketrophysystem", 32779},
		{"setmode", 32864},
		{"getmode", 32865},
		{"placespawnpoint", 32780},
		{"setteamfortrigger", 32781},
		{"clientclaimtrigger", 32782},
		{"clientreleasetrigger", 32783},
		{"releaseclaimedtrigger", 32784},
		{"isusingonlinedataoffline", 32785},
		{"getrestedtime", 32786},
		{"sendleaderboards", 32787},
		{"logstring", 32800},
		{"isonladder", 32788},
		{"startragdoll", 32798},
		{"getcorpseanim", 32789},
		{"playerforcedeathanim", 32790},
		{"startac130", 33543},
		{"stopac130", 33544},
	};

	std::map<std::string, int> global_function_map =
	{
		// global stuff #1
		{"iprintln", 362},
		{"iprintlnbold", 363},
		{"logstring", 364},
		{"getent", 365},
		{"getentarray", 366},
		{"spawnplane", 367},
		{"spawnstruct", 368},
		{"spawnhelicopter", 369},
		{"isalive", 370},
		{"isspawner", 371},
		{"createattractorent", 372},
		{"createattractororigin", 373},
		{"createrepulsorent", 374},
		{"createrepulsororigin", 375},
		{"deleteattractor", 376},
		{"playsoundatpos", 377},
		{"newhudelem", 378},
		{"newclienthudelem", 379},
		{"newteamhudelem", 380},
		{"resettimeout", 381},
		{"precachefxteamthermal", 382},
		{"isplayer", 383},
		{"isplayernumber", 384},
		{"setsunlight", 57},
		{"resetsunlight", 58},
		{"setwinningplayer", 385},
		{"setwinningteam", 311},
		{"announcement", 312},
		{"clientannouncement", 313},
		{"getteamscore", 314},
		{"setteamscore", 315},
		{"setclientnamemode", 316},
		{"updateclientnames", 317},
		{"getteamplayersalive", 318},
		{"logprint", 319},
		{"worldentnumber", 320},
		{"obituary", 321},
		{"positionwouldtelefrag", 322},
		{"canspawn", 323},
		{"getstarttime", 324},
		{"precachestatusicon", 325},
		{"precacheminimapicon", 327},
		{"precachempanim", 328},
		{"restart", 329},
		{"exitlevel", 330},
		{"addtestclient", 331},
		{"makedvarserverinfo", 332},
		{"setarchive", 333},
		{"allclientsprint", 334},
		{"clientprint", 335},
		{"mapexists", 336},
		{"isvalidgametype", 337},
		{"matchend", 338},
		{"setplayerteamrank", 339},
		{"endparty", 340},
		{"setteamradar", 341},
		{"getteamradar", 342},
		{"setteamradarstrength", 343},
		{"getteamradarstrength", 344},
		{"getuavstrengthmin", 345},
		{"getuavstrengthmax", 262},
		{"getuavstrengthlevelneutral", 263},
		{"getuavstrengthlevelshowenemyfastsweep", 264},
		{"getuavstrengthlevelshowenemydirectional", 265},
		{"blockteamradar", 266},
		{"unblockteamradar", 267},
		{"isteamradarblocked", 268},
		{"getassignedteam", 269},
		{"setmatchdata", 270},
		{"getmatchdata", 271},
		{"sendmatchdata", 272},
		{"clearmatchdata", 273},
		{"setmatchdatadef", 274},
		{"setmatchclientip", 275},
		{"setmatchdataid", 276},
		{"setclientmatchdata", 277},
		{"getclientmatchdata", 278},
		{"setclientmatchdatadef", 279},
		{"sendclientmatchdata", 280},
		{"getbuildversion", 281},
		{"getbuildnumber", 282},
		{"getsystemtime", 283},
		{"getmatchrulesdata", 284},
		{"isusingmatchrulesdata", 285},
		{"kick", 286},
		{"issplitscreen", 287},
		{"setmapcenter", 288},
		{"setgameendtime", 289},
		{"visionsetnaked", 290},
		{"visionsetnight", 291},
		{"visionsetmissilecam", 292},
		{"visionsetthermal", 217},
		{"visionsetpain", 218},
		{"endlobby", 219},
		{"ambience", 220},
		{"getmapcustom", 221},
		{"updateskill", 222},
		{"spawnsighttrace", 223},

		// global stuff #2
		{"setprintchannel", 14},
		{"print", 15},
		{"println", 16},
		{"print3d", 17},
		{"line", 18},
		{"spawnturret", 19},
		{"canspawnturret", 20},
		{"assert", 21},
		{"assertex", 38},
		{"assertmsg", 39},
		{"isdefined", 40},
		{"isstring", 41},
		{"setdvar", 42},
		{"setdynamicdvar", 43},
		{"setdvarifuninitialized", 44},
		{"setdevdvar", 45},
		{"setdevdvarifuninitialized", 46},
		{"getdvar", 47},
		{"getdvarint", 48},
		{"getdvarfloat", 49},
		{"getdvarvector", 50},
		{"gettime", 51},
		{"getentbynum", 52},
		{"getweaponmodel", 53},
		{"getweaponhidetags", 81},
		{"getanimlength", 82},
		{"animhasnotetrack", 83},
		{"getnotetracktimes", 84},
		{"spawn", 85},
		{"spawnloopsound", 86},
		{"bullettrace", 87},
		{"bullettracepassed", 88},
		{"sighttracepassed", 116},
		{"physicstrace", 117},
		{"physicstracenormal", 118},
		{"playerphysicstrace", 119},
		{"getgroundposition", 120},
		{"getmovedelta", 121},
		{"getangledelta", 122},
		{"getnorthyaw", 123},
		{"setnorthyaw", 150},
		{"setslowmotion", 151},
		{"randomint", 152},
		{"randomfloat", 153},
		{"randomintrange", 154},
		{"randomfloatrange", 155},
		{"sin", 156},
		{"cos", 157},
		{"tan", 158},
		{"asin", 159},
		{"acos", 160},
		{"atan", 161},
		{"int", 162},
		{"float", 163},
		{"abs", 164},
		{"min", 165},
		{"max", 198},
		{"floor", 199},
		{"ceil", 200},
		{"exp", 201},
		{"log", 202},
		{"sqrt", 203},
		{"squared", 204},
		{"clamp", 205},
		{"angleclamp", 206},
		{"angleclamp180", 207},
		{"vectorfromlinetopoint", 208},
		{"pointonsegmentnearesttopoint", 209},
		{"distance", 210},
		{"distance2d", 211},
		{"distancesquared", 212},
		{"length", 213},
		{"lengthsquared", 214},
		{"closer", 215},
		{"vectordot", 216},
		{"vectornormalize", 246},
		{"vectortoangles", 247},
		{"vectortoyaw", 248},
		{"vectorlerp", 249},
		{"anglestoup", 250},
		{"anglestoright", 251},
		{"anglestoforward", 252},
		{"combineangles", 253},
		{"transformmove", 254},
		{"issubstr", 255},
		{"isendstr", 256},
		{"getsubstr", 257},
		{"tolower", 258},
		{"strtok", 259},
		{"stricmp", 260},
		{"ambientplay", 261},
		{"ambientstop", 293},
		{"precachemodel", 294},
		{"precacheshellshock", 295},
		{"precacheitem", 296},
		{"precacheshader", 297},
		{"precachestring", 298},
		{"precachemenu", 299},
		{"precacherumble", 300},
		{"precachelocationselector", 301},
		{"precacheleaderboards", 302},
		{"precacheheadicon", 326},
		{"loadfx", 303},
		{"playfx", 304},
		{"playfxontag", 305},
		{"stopfxontag", 306},
		{"playloopedfx", 307},
		{"spawnfx", 308},
		{"triggerfx", 309},
		{"playfxontagforclients", 310},
		{"physicsexplosionsphere", 346},
		{"physicsexplosioncylinder", 347},
		{"physicsjolt", 348},
		{"physicsjitter", 349},
		{"setexpfog", 350},
		{"isexplosivedamagemod", 351},
		{"radiusdamage", 352},
		{"setplayerignoreradiusdamage", 353},
		{"glassradiusdamage", 354},
		{"earthquake", 355},
		{"getnumparts", 356},
		{"getpartname", 386},
		{"weaponfiretime", 387},
		{"weaponclipsize", 388},
		{"weaponisauto", 389},
		{"weaponissemiauto", 390},
		{"weaponisboltaction", 391},
		{"weaponinheritsperks", 392},
		{"weaponburstcount", 393},
		{"weapontype", 394},
		{"weaponclass", 395},
		{"weaponinventorytype", 437},
		{"weaponstartammo", 438},
		{"weaponmaxammo", 439},
		{"weaponaltweaponname", 440},
		{"isweaponcliponly", 441},
		{"isweapondetonationtimed", 442},
		{"weaponhasthermalscope", 443},
		{"getvehiclenode", 444},
		{"getvehiclenodearray", 445},
		{"getallvehiclenodes", 446},
		{"getnumvehicles", 447},
		{"precachevehicle", 448},
		{"spawnvehicle", 449},
		{"getarray", 450},
		{"getspawnerarray", 408},
		{"playrumbleonposition", 409},
		{"playrumblelooponposition", 410},
		{"stopallrumbles", 411},
		{"soundexists", 412},
		{"openfile", 413},
		{"closefile", 414},
		{"fprintln", 415},
		{"fprintfields", 416},
		{"freadln", 417},
		{"fgetarg", 418},
		{"setminimap", 419},
		{"setthermalbodymaterial", 420},
		{"getarraykeys", 421},
		{"getfirstarraykey", 422},
		{"getnextarraykey", 396},
		{"sortbydistance", 397},
		{"tablelookup", 398},
		{"tablelookupbyrow", 399},
		{"tablelookupistring", 400},
		{"tablelookupistringbyrow", 401},
		{"tablelookuprownum", 402},
		{"getmissileowner", 403},
		{"magicbullet", 404},
		{"getweaponflashtagname", 405},
		{"averagepoint", 406},
		{"averagenormal", 407},
		{"getglass", 423},
		{"getglassarray", 424},
		{"getglassorigin", 425},
		{"isglassdestroyed", 426},
		{"destroyglass", 427},
		{"deleteglass", 428},
		{"getentchannelscount", 429},

		// objective
		{"objective_add", 431},
		{"objective_delete", 432},
		{"objective_state", 433},
		{"objective_icon", 434},
		{"objective_position", 435},
		{"objective_current", 436},
		{"objective_onentity", 357},
		{"objective_team", 358},
		{"objective_player", 359},
		{"objective_playerteam", 360},
		{"objective_playerenemyteam", 361},
	};
}
