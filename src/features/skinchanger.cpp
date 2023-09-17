#include "skinchanger.h"
#include "../hack.h"
#include "../memory/memory.h"
#include <iostream>
#include <vector>
#include <array>

extern Hack* hack;

bool skinchanger::ValidSkin(SKIN skin) {
	if (GetSkinName(skin.paint) == "ERROR") {
		return false;
	}
	for (SKIN &otherskin : inventory) {
		if (skin.weaponID == otherskin.weaponID) {
			return false;
		}

		
	}
	

	return true;
}


std::vector<int> SKINSID = { 651, 573, 389, 1156, 644, 905, 445, 204, 792, 658, 290, 1000, 1155, 279, 452, 1012, 1005, 965, 963, 785, 776, 545, 76, 326, 436, 166, 277, 351, 262, 746, 266, 995, 754,
10037, 1060, 945, 803, 361, 624, 1098, 458, 908, 614, 346, 946, 441, 10059, 10070, 10047, 657, 430, 75, 1051, 889, 801, 1007, 84, 208, 300, 10060, 629, 419, 732, 491, 310, 10036, 546, 484, 203, 10056,
571, 10033, 283, 514, 862, 1105, 409, 225, 1113, 828, 10051, 582, 479, 647, 822, 1101, 147, 997, 174, 378, 258, 236, 74, 177, 631, 1139, 273, 759, 478, 469, 1126, 955, 313, 711, 1016, 674,
1084, 884, 891, 398, 157, 693, 978, 135, 111, 10043, 600, 429, 394, 635, 322, 275, 1019, 570, 898, 215, 10030, 493, 10016, 786, 10013, 947, 840, 706, 555, 692, 486, 281, 659, 917, 391, 672,
10077, 328, 1125, 1157, 666, 497, 846, 356, 708, 566, 788, 707, 395, 617, 694, 534, 594, 503, 381, 101, 291, 641, 10055, 525, 1052, 784, 1034, 541, 10076, 608, 906, 567, 227, 366, 1061, 812
, 10063, 575, 902, 196, 10015, 816, 998, 844, 95, 896, 558, 885, 349, 780, 198, 100, 449, 640, 289, 197, 98, 274, 213, 734, 10067, 1106, 977, 536, 1024, 606, 221, 992, 10049, 156, 723, 512,
380, 10007, 637, 1014, 498, 17, 724, 428, 959, 796, 10006, 254, 30, 10038, 550, 932, 396, 332, 62, 825, 312, 372, 934, 34, 490, 523, 420, 742, 187, 1081, 979, 256, 10062, 894, 245, 411, 1063,
778, 597, 362, 350, 143, 299, 92, 32, 1153, 399, 1055, 721, 684, 364, 820, 383, 435, 51, 952, 634, 230, 1074, 448, 500, 317, 437, 43, 789, 442, 345, 960, 819, 857, 46, 470, 363, 755, 1036,
589, 996, 969, 677, 1030, 976, 712, 621, 466, 314, 650, 502, 343, 750, 726, 646, 238, 464, 915, 1134, 826, 206, 10054, 360, 515, 628, 48, 863, 989, 302, 949, 856, 71, 10082, 304, 591, 670,
987, 579, 480, 1003, 845, 293, 986, 301, 10018, 167, 1020, 615, 584, 10034, 907, 620, 687, 551, 10039, 375, 581, 667, 376, 333, 387, 382, 220, 1018, 920, 542, 1013, 443, 393, 599, 488, 308,
432, 10042, 994, 1138, 861, 727, 232, 787, 676, 26, 15, 922, 83, 890, 1096, 1108, 561, 519, 638, 702, 367, 104, 1059, 267, 22, 402, 212, 926, 37, 311, 307, 858, 489, 176, 516, 384, 1072, 964,
481, 252, 806, 325, 736, 1151, 530, 563, 1048, 722, 14, 583, 354, 42, 590, 1083, 205, 1066, 795, 738, 201, 386, 1158, 1008, 499, 556, 1097, 340, 622, 869, 251, 1002, 543, 607, 781, 601, 855,
260, 999, 961, 47, 807, 413, 668, 1136, 253, 194, 444, 341, 777, 880, 10065, 403, 669, 821, 782, 505, 280, 843, 348, 1104, 504, 329, 153, 678, 446, 370, 725, 528, 518, 853, 1031, 850, 595,
1092, 681, 532, 10027, 10, 10078, 2, 249, 1145, 1053, 691, 10072, 190, 347, 888, 549, 405, 613, 835, 886, 244, 1091, 935, 811, 686, 261, 648, 800, 240, 852, 836, 697, 1050, 1039, 699, 320,
219, 749, 1128, 10044, 909, 747, 182, 10066, 897, 970, 330, 1042, 941, 282, 214, 10086, 739, 10021, 633, 993, 982, 125, 255, 864, 951, 649, 228, 1037, 619, 10069, 524, 1056, 189, 61, 973,
1120, 11, 713, 719, 10061, 539, 38, 223, 1144, 1017, 688, 808, 10040, 954, 1154, 272, 321, 229, 660, 10058, 209, 842, 1026, 916, 854, 585, 985, 603, 1044, 1140, 460, 971, 745, 710, 10080,
334, 1075, 887, 1085, 231, 653, 10073, 495, 752, 10041, 191, 10084, 233, 797, 642, 195, 226, 943, 611, 695, 809, 485, 188, 918, 141, 373, 246, 410, 285, 1025, 859, 656, 554, 1103, 698, 763,
467, 431, 388, 28, 737, 680, 645, 748, 1058, 974, 1116, 804, 10048, 609, 371, 16, 1004, 10053, 463, 1148, 823, 1132, 815, 5, 802, 473, 873, 1070, 975, 1112, 110, 910, 286, 586, 284, 576, 73,
1022, 1079, 319, 39, 867, 355, 929, 122, 414, 904, 757, 10075, 598, 895, 610, 564, 171, 1152, 10081, 756, 818, 616, 400, 3, 475, 243, 10071, 180, 438, 1094, 335, 183, 899, 421, 829, 1118, 654,
21, 99, 447, 10085, 753, 169, 454, 263, 632, 921, 553, 107, 306, 568, 344, 501, 327, 966, 661, 720, 10024, 758, 385, 1142, 984, 604, 468, 827, 794, 679, 1131, 1130, 288, 1029, 944, 439, 983,
593, 9, 740, 496, 865, 316, 10009, 671, 186, 559, 1033, 716, 729, 401, 892, 77, 1121, 814, 179, 1090, 872, 1150, 216, 193, 1021, 357, 242, 535, 526, 1115, 10019, 379, 790, 988, 353, 10057,
813, 1082, 602, 701, 838, 70, 1093, 1006, 596, 1127, 1067, 181, 1107, 760, 715, 124, 779, 612, 980, 733, 36, 1095, 682, 1088, 1080, 577, 474, 805, 359, 1010, 851, 580, 459, 511, 165, 453, 927
, 10046, 1129, 913, 652, 1137, 540, 817, 704, 517, 508, 1065, 278, 265, 900, 427, 336, 175, 544, 709, 455, 588, 548, 1135, 1123, 1046, 119, 417, 690, 643, 625, 250, 685, 338, 492, 78, 1041,
911, 665, 476, 791, 440, 271, 10079, 662, 352, 663, 1047, 866, 1147, 968, 10088, 426, 623, 506, 202, 20, 1071, 1015, 1146, 538, 1001, 664, 744, 247, 848, 12, 1119, 1078, 1073, 487, 1122, 562,
237, 477, 162, 93, 303, 102, 578, 1149, 870, 700, 155, 10068, 1102, 369, 67, 494, 1045, 639, 841, 241, 520, 268, 972, 168, 471, 991, 1049, 207, 116, 217, 199, 224, 170, 618, 1077, 605, 318,
297, 893, 149, 159, 1009, 626, 164, 1100, 200, 728, 574, 743, 860, 424, 407, 339, 210, 1099, 689, 222, 521, 718, 374, 482, 510, 879, 919, 1111, 25, 868, 533, 148, 627, 10045, 507, 90, 903,
673, 192, 10083, 1133, 1035, 451, 234, 962, 837, 1043, 1028, 565, 264, 1087, 178, 956, 27, 761, 683, 933, 527, 377, 1038, 298, 276, 72, 705, 44, 40, 948, 33, 547, 529, 270, 1109, 552, 703,
184, 10052, 557, 928, 696, 1032, 871, 59, 730, 358, 953, 924, 923, 416, 731, 10064, 1064, 839, 714, 323, 636, 1141, 457, 96, 423, 342, 824, 522, 296, 450, 456, 151, 1117, 930, 368, 315, 465,
1023, 765, 1011, 762, 422, 392, 1089, 849, 655, 990, 10050, 154, 1086, 675, 433, 10074, 294, 10008, 957, 287, 741, 483, 365, 1110, 1076, 735, 257, 10087, 847, 537, 248, 925, 717, 10010, 295,
1114, 305, 218, 783, 799, 10035, 942, 259, 397, 211, 587, 13, 914, 798, 751, 592, 764, 235, 10026, 967, 958, 569, 60, 509, 309, 418, 390, 337, 434, 572, 472, 269, 425, 172, 8, 1143, 793, 775,
462, 981, 810, 560, 630, 1040, 931, 415, 158, 41, 6, 950, 136, 406, 404, 185, 1027 };

std::string SKINSNAMES[] = { "Last Dive", "Autotronic", "Fire Elemental", "Flora Carnivora", "Decimator", "Flash Out", "Hot Rod", "Mosaico", "Control Panel", "Cobra Strike", "Guardian", "Run and Hide", "Kiss Love",
"Asiimov", "Shipping Forecast", "Phoenix Stencil", "Heist", "Allure", "Vogue", "Mandrel", "Facility Negative", "Orange Crash", "Winter Forest", "Knight", "Grand Prix", "Blaze Orange",
"Stainless", "Conspiracy", "Rose Iron", "Baroque Orange", "Magma", "Surveillance", "Rust Coat", "Pandoras Box", "Spring Twilly", "Blue Ply", "Neo - Noir", "Abyss", "Dragonfire",
"Toybox", "Bamboo Shadow", "Classic Crate", "Fuel Injector", "Coach Class", "Player Two", "Minotaurs Labyrinth", "Rattler", "Snow Leopard", "Omega", "Blueprint", "Hyper Beast",
"Blizzard Marbleized", "Windblown", "Decimator", "Asiimov", "Vault Heist", "Pink DDPAT", "Sand Dune", "Emerald Pinstripe", "Case Hardened", "Black Sand", "Doppler", "Synth Leaf",
"Dualing Dragons", "Curse", "Badlands", "Firefight", "Ranger", "Rust Coat", "Arboreal", "Gamma Doppler Phase 3", "Crimson Kimono", "Trigon", "Power Loader", "Moss Quartz", "Lore",
"Tiger Tooth", "Ghost Camo", "Black Laminate", "Verdant Growth", "Transport", "Freehand", "Bunsen Burner", "Crimson Tsunami", "Navy Sheen", "Turbo Peek", "Jungle Dashed", "Dispatch",
"BOOM", "Fallout Warning", "Mehndi", "Night Ops", "Polar Camo", "Memento", "Flashback", "Poultrygeist", "Heirloom", "Astral Jormungandr", "Rocket Pop", "Sunset Storm _", "Melondrama",
"Darkwing", "Orion", "Code Red", "Franklin", "Triqua", "Hazard Pay", "Embargo", "Black Sand", "Chatterbox", "Palm", "Flame Test", "Dezastre", "Urban Perforated", "Glacier Mesh", "Overtake",
"Neon Revolution", "Djinn", "Cartel", "Turf", "Nitro", "Red FragCam", "Panther Camo", "Gamma Doppler Phase 2", "Stalker", "X-Ray", "Forest DDPAT", "Flux", "Crimson Weave", "Exchanger",
"Lunar Weave", "Disco Tech", "Whitefish", "Oxide Blaze", "Re-Entry", "Night Riot", "Elite Build", "Corporal", "Macabre", "Wildfire", "Cardiac", "Metal Flowers", "Finish Line", "Hand Cannon",
"Space Cat", "Roadblock", "Hard Water", "Golden Coil", "Gauss", "Koi", "Amber Slipstream", "Black Laminate", "Acheron", "Neon Rider", "Man-o", "Doppler", "Moonrise", "Lapis Gator",
"Harvester", "Big Iron", "Grinder", "Tornado", "Heaven Guard", "Jungle Slipstream", "Duct Tape", "Elite Build", "Death Strike", "Coolant", "Ancient Ritual",
"Fleet Flock", "Nocts", "Petroglyph", "Buddy", "Black Laminate", "Electric Hive", "Green Plaid", "Autumn Twilly", "Pipe Down", "Fade", "Autotronic", "Aztec",
"Emerald", "Convoy", "Fubar", "Switch Board", "The Emperor", "Grassland", "Torn", "Lore", "Rat Rod", "Osiris", "Mainframe", "Hazard", "Storm", "Poseidon", "Fever Dream",
"Sandstorm", "Anodized Navy", "Ultraviolet", "Copper Galaxy", "Ocean Foam", "Wild Lily", "Tiger Strike", "Lore", "Cocoa Rampage", "Impire", "Blast From the Past", "Ventilator",
"Serum", "The Bronze", "POW!", "Death by Kitty", "Eye of Athena", "Royal Paladin", "Wasteland Rebel", "Snakebite", "Cyrex", "Clay Ambush", "Rangeen", "Urban DDPAT", "Wild Lotus",
"Eco", "Legion of Anubis", "Check Engine", "Charred", "Nitro", "Snake Camo", "Hedge Maze", "Oceanic", "Withered Vine", "Urban Shock", "Royal Blue", "Bloomstick", "Drought", "Cyrex",
"Nuclear Garden", "Bleached", "Metallic DDPAT", "Frontside Misty", "Amber Fade", "Doppler", "Red Filigree", "Zirka", "Digital Architect", "Fairy Tale", "The Kraken", "Buckshot",
"Obsidian", "Army Recon", "Damascus Steel", "The Coalition", "Facility Dark", "Bloodsport", "Labyrinth", "Tigris", "Urban Masked", "Caged Steel", "Cyanospatter", "Silver", "Visions",
"Catacombs", "Space Race", "Survivalist", "Cracked Opal", "Business Class", "Music Box", "Basilisk", "Pole Position", "Lightning Strike", "Bone Forged", "Gila", "Steel Disruption",
"Schematic", "Pandoras Box", "Special Delivery", "Bratatat", "Twilight Galaxy", "Stained", "Nuclear Garden", "Asterion", "First Class", "Gnarled", "Desert Hydra", "Damascus Steel",
"Contractor", "Sunset Storm _", "Traveler", "Slide", "Circaetus", "Carnivore", "Threat Detected", "Freight", "Hunter", "Bengal Tiger", "Vendetta", "High Seas", "Ultraviolet",
"Crimson Kimono", "Heaven Guard", "Ripple", "Green Marine", "Commuter", "Integrale", "Sunset Lily", "Capillary", "VariCamo Blue", "Neon Kimono", "Agent", "Starlight Protector",
"Sienna Damask", "Tornado", "Overprint", "Cyrex", "Imperial", "Stinger", "Dragon Tattoo", "Night Borre", "Parallax", "Vulcan", "Desert Strike", "Marble Fade", "Scorpion", "Giraffe",
"Slashed", "Imperial Dragon", "Deaths Head", "Clear Polymer", "Bright Water", "Evil Daimyo", "Crime Scene", "Momentum", "Death Rattle", "Condition Zero", "Atomic Alloy", "Superconductor",
"Radiation Hazard", "Ancient Earth", "Briefing", "Phobos", "Emerald Web", "Inferno", "Ultraviolet", "Tacticat", "Asiimov", "Guerrilla", "Radiation Hazard", "Freehand", "Woodsman",
"Chemical Green", "Indigo", "Urban Hazard", "Murky", "Hemoglobin", "Panthera onca", "Boroque Sand", "Judgement of Anubis", "Phoenix Blacklight", "Pathfinder", "Tranquility",
"Ice Cap", "Riot", "Kami", "Man war", "Imperial Plaid", "Charter", "Lifted Spirits", "Barricade", "Midnight Lily", "Crimson Web", "Core Breach", "High Roller", "Lichen Dashed",
"Gunsmoke", "Orange Anolis", "Orange DDPAT", "Plume", "Guerrilla", "Lore", "Lore", "Tiger Moth", "Wasteland Princess", "Aloha", "Reactor", "Grassland Leaves", "Fizzy POP", "Cobalt Halftone",
"Contrast Spray", "Malachite", "Graphite", "Red DDPAT", "Blaze", "Desert Warfare", "Retribution", "Damascus Steel", "Torque", "Faded Zebra", "Shapewood", "Griffin", "Prism Terrace", "Brother",
"Nemesis", "Silver Quartz", "Scavenger", "Chalice", "The Prince", "Dragon Tech", "Triumvirate", "Black Laminate", "Heavy Metal", "Snek-9", "Red Laminate", "Aristocrat", "Urban Hazard",
"Blue Steel", "Exo", "Breaker Box", "Jungle", "Faulty Wiring", "Safety Net", "Orange Murano", "Palm", "Dart", "Winterized", "Houndstooth", "Cobalt Core", "Primal Saber", "Spider Lily",
"Jet Set", "Polymer", "Sundown", "Pit Viper", "Berries And Cherries", "Red Astor", "Weasel", "Co-Processor", "Syd Mead", "Doppler", "Pulse", "Prime Conspiracy", "Monster Call", "Colony",
"Signal", "Marble Fade", "Red Rock", "Ticket to Hell", "Acid Fade", "Spitfire", "Daedalus", "First Class", "Facility Draft", "Parched", "Marble Fade", "Deadly Poison", "Death Grip",
"Elegant Vines", "Motherboard", "Scumbria", "Chameleon", "Skull Crusher", "Red Leather", "Lore", "Kill Confirmed", "Dark Age", "Demolition", "See Ya Later", "Medusa", "Bone Machine",
"Day Lily", "Cartel", "Outbreak", "Doppler", "Ancient Visions", "Incinegator", "Reboot", "ZX Spectron", "Leaded Glass", "Royal Legion", "Boom!", "Copperhead", "Smoke Out", "Groundwater",
"Cobalt Quartz", "Crazy 8", "Meltdown", "Mortis", "Black Tie", "Black Limba", "Pilot", "Acid Wash", "Bioleak", "Serenity", "Triarch", "Crypsis", "Arctic Wolf", "Teardown", "Tread", "Prey",
"Magnesium", "Phantom", "Marina", "Emerald Poison Dart", "Lab Rats", "CaliCamo", "Doppler", "Uncharted", "Black Sand", "Trigger Discipline", "Clear Polymer", "Wild Six", "Red Python", "Hive",
"Vino Primo", "Scrawl", "Racing Green", "Popdog", "Twin Turbo", "Emerald Dragon", "Lt. Commander", "Colony IV", "Entombed", "Briar", "O.S.I.P.R.", "Phantom Disruptor", "Redline", "Graphite",
"Yellow-banded", "Violet Murano", "Slaughter", "Sonar", "Global Offensive", "Contaminant", "X-Ray", "Asiimov", "Candy Apple", "Acid Etched", "Akoben", "Blind Spot", "Food Chain", "Doppler",
"Rezan the Red", "Fuel Injector", "Sputnik", "Bright Water", "Hypnotic", "Runic", "Gamma Doppler", "Skulls", "Warhawk", "Powercore", "Crimson Web", "Jambiya", "Fade", "Nightshade",
"Chromatic Aberration", "Blue Phosphor", "Exposure", "Oxide Blaze", "Diamondback", "Enforcer", "Vent Rush", "Titanium Bit", "Master Piece", "Azure Zebra", "Hyper Beast", "Mangrove",
"Groundwater", "Akoben", "Fade", "Plastique", "Doppler", "Violent Daimyo", "Cyber Security", "Directive", "Cyber Shell", "Spirit Board", "Aqua Terrace", "Tooth Fairy", "Baroque Purple",
"Shred", "3rd Commando Company", "Twist", "Strats", "Containment Breach", "Mechanism", "Cobalt Disruption", "Neo-Noir", "Slingshot", "Wraiths", "Fade", "King Snake", "Tempest", "CAUTION!",
"Tropical Storm", "Brake Light", "Blueprint", "Demeter", "Blue Laminate", "Capillary", "Grim", "Neo-Noir", "Wood Fired", "Handgun", "Graven", "Sacrifice", "Orange Peel", "Contamination",
"Amber Fade", "Damascus Steel", "Terrain", "Gold Brick", "Emerald Quartz", "Orbit Mk01", "Ghost Crusader", "Watchdog", "Lionfish", "Mjolnir", "Mint Kimono", "Heat", "Cartel", "Anodized Navy",
"Cinquedea", "Off World", "Oxide Blaze", "Calf Skin", "POP AWP", "Kitbash", "Autotronic", "Modest Threat", "Vice", "Airlock", "Styx", "Jungle Tiger", "X-Ray", "Cobalt Skulls", "Terrace",
"Downtown", "Sand Storm", "Foresight", "Danger Close", "Forest DDPAT", "Momentum", "Seabird", "Seabird", "Green Laminate", "Exoskeleton", "Black Laminate", "Condemned", "Hydra", "Antique"
, "Wasteland Rebel", "Heat", "Autotronic", "Wings", "Lush Ruins", "Red Tire", "Detour", "Bulldozer", "Stained Glass", "Desert-Strike", "Quick Sand", "Jungle Spray", "Rust Coat",
"Decommissioned", "Emerald Jormungandr", "Scarlet Shamagh", "Aerial", "Balance", "Dazzle", "Black Laminate", "Irradiated Alert", "Drop Me", "Desert Shamagh", "Gungnir", "Purple DDPAT",
"Slipstream", "__ (Dragon King)", "Candy Apple", "Hyper Beast", "Gator Mesh", "Queen Jaguar", "Fire Serpent", "Chronos", "Mount Fuji", "Module", "Overgrowth", "Bloodshot", "Doppler",
"Anolis", "Autotronic", "Seasons", "Granite Marbleized", "Sand Dune", "Duelist", "Jade", "Dirt Drop", "Fallout Warning", "Para Green", "Rising Skull", "Buzz Kill", "Gold Arabesque",
"Atlas", "Polar Mesh", "Antique", "Gamma Doppler Emerald Marble", "Dragon Lore", "Wingshot", "Chainmail", "Ol Rusty", "Sugar Rush", "Devourer", "Eclipse", "Flame Jormungandr",
"Firestarter", "Printstream", "Printstream", "Roll Cage", "Midnight Storm", "Humidor", "Sweeper", "Goo", "Ensnared", "Night Terror", "Sergeant", "Silk Tiger", "Distressed", "Hades",
"Deep Relief", "Chopper", "Bengal Tiger", "Navy Murano", "Nebula Crusader", "Stone Mosaico", "Jaguar", "Leather", "Cut Out", "Wave Spray", "Lore", "Carved Jade", "Toy Soldier",
"Crimson Blossom", "System Lock", "Memento", "Boreal Forest", "Gamma Doppler", "Black Sand", "Nuclear Threat", "Ocean Drive", "Bamboo Garden", "Monkeyflage", "Blue Titanium",
"Bone Pile", "Ancient Lore", "Ivory", "Army Mesh", "Praetorian", "Photic Zone", "Autotronic", "Arid", "Cerberus", "Cold Fusion", "Neo - Noir", "Water Elemental", "Emerald",
"Nevermore", "Fall Hazard", "Imprint", "Grip", "Atheris", "Carbon Fiber", "Boost Protocol", "Night Heist", "Limelight", "Rapid Eye Movement", "Propaganda", "Corticera", "Lore",
"Frost Borre", "Capillary", "Sand Spray", "Random Access", "Powercore", "Digital Mesh", "Rust Leaf", "Ossified", "Keeping Tabs", "Oceanic", "Plague", "Infrastructure", "Autotronic",
"Aquamarine Revenge", "Mecha Industries", "Asiimov", "Phoenix Chalk", "Moonrise", "Freehand", "Bamboo Forest", "The Executioner", "Splash Jam", "Emerald", "Spalted Wood",
"Bronze Morph", "Dream Glade", "Death by Puppy", "Scaffold", "Necro Jr.", "Lead Conduit", "Flashback", "Arctic Wolf", "Yorick", "Fuel Rod", "Whiteout", "Blue Fissure", "Kami",
"Warbird", "Monkey Business", "Desert - Strike", "Scorched", "Ventilators", "Eco", "Akihabara Accept", "Desolate Space", "Chanticos Fire", "Zombie Offensive", "Gamma Doppler",
"XOXO", "Sage Spray", "Doppler", "Stymphalian", "Xiangliu", "Royal Consorts", "Full Stop", "Jungle Slipstream", "Pulse", "Survivor Z", "Forest Night", "In Living Color",
"Nostalgia", "Aloha", "Yellow Jacket", "Remote Control", "Icarus Fell", "Undertow", "Blood Pressure", "Oni Taiji", "Fowl Play", "Briefing", "Junk Yard", "Canal Spray",
"Destroyer", "Cassette", "Unhinged", "Valence", "Ironwork", "Point Disarray", "Jungle DDPAT", "Virus", "CAUTION!", "Tiger Pit", "Meow 36", "Necropos", "Welcome to the Jungle",
"Hellfire", "Baroque Red", "Damascus Steel", "Verdigris", "Crimson Web", "Gamma Doppler", "Blue Tire", "Imminent Danger", "Cyrex", "Gamma Doppler", "Lore", "Urban Rubble",
"Neural Net", "Splash", "Caramel", "Isaac", "Whiteout", "Bright Water", "Poly Mag", "Jungle Thicket", "Urban Hazard", "Bullet Rain", "Field Agent", "Black Lotus", "Nuclear Waste",
"Cold Blooded", "Stone Cold", "Button Masher", "Bloodsport", "Light Rail", "Hunting Blind", "Avalanche", "Tread Plate", "Connexion", "Nuclear Threat", "Daybreak", "Monster Mashup",
"Oscillator", "Facets", "Sand Mesh", "Blood Tiger", "Dry Season", "Water Sigil", "Predator", "Doppler", "Interlock", "Scumbria", "Road Rash", "Tuxedo", "Neon Ply", "Urban Dashed",
"Brass", "Hot Snakes", "Mecha Industries", "Modern Hunter", "Snack Attack", "Mayan Dreams", "Teal Blossom", "Autotronic", "Orange Filigree", "Pyre", "Worm God", "Quicksilver", "Caiman",
"Anodized Gunmetal", "Lumen", "Ziggy", "Blood in the Water", "Teclu Burner", "PAW", "Toxic", "Ruby Poison Dart", "Retrobution", "Fade", "Commemoration", "Black Laminate", "Forest Leaves",
"Sea Calico", "The Battlestar", "Sand Dashed", "Cirrus", "Amphibious", "Ricochet", "Mudder", "Elite 1.6", "Morris", "Shattered", "Constrictor", "Abyssal Apparition", "Slate", "Sun in Leo",
"Ash Wood", "Printstream", "Angry Mob", "dev_texture", "Magna Carta", "Black Laminate", "Sandstorm", "Leet Museo", "Doomkitty", "Fever Dream", "Bone Mask", "Copper Borre", "Llama Cannon",
"Midnight Palm", "Kumicho Dragon", "Hot Shot", "Chromatic Aberration", "Army Sheen", "Panther", "Safari Mesh", "Cortex", "Case Hardened", "Night", "Justice", "Hot Rod", "Spectre", "Valence",
"Victoria", "Black Laminate", "Fubar", "SWAG-7", "Corticera", "Polygon", "Black Tie", "Black & Tan", "Bloodsport", "Dusk Ruins", "Surfwood", "Slaughter", "Dark Blossom", "Supernova",
"Apocalypto", "Desert Brush", "Oxide Oasis", "Doppler", "Banana Leaf", "Mogul", "Syndicate", "Bamboozle", "Nightmare", "Rust Coat", "Shallow Grave", "Nightwish", "Bamboo Print",
"Blue Spruce", "Armor Core", "Leather", "Drift Wood", "Fade", "Meteorite", "Moon in Libra", "Hydroponic", "Jungle", "Autotronic", "New Roots", "Setting Sun", "Poison Dart", "Orange Kimono",
"Tall Grass", "Desert Blossom", "Phoenix Marker", "Red Stone", "Elite Build", "Delusion", "BI83 Spectrum", "Off World", "Zander", "Gold Bismuth", "Turtle", "Afterimage", "Oil Change",
"The Empress", "Neon Rider", "Big Game", "Green Apple", "Bronzed", "Bullet Queen", "Pulse", "Dark Filigree", "Loudmouth", "Olive Plaid", "Black Laminate", "Framework", "Night Stripe",
"Guardian", "Needle Point", "Mischief", "Hyper Beast", "Red Quartz", "Desert DDPAT", "Traction", "Spruce DDPAT", "Franklin", "Autotronic", "Torque", "Hexane", "Bulkhead", "High Beam",
"Foundation", "Tom Cat", "Redline", "Naga", "Ocean Foam", "Mecha Industries", "Blue Streak", "Assault", "Nitro", "Hand Brake", "Iron Clad", "Fennec Fox", "VariCamo", "Spearmint",
"Mainframe 001", "Ultralight", "Gamma Doppler Phase 1", "Dark Water", "Corinthian", "Howl", "Doppler", "Highwayman", "Tatter", "Origami", "Gamma Doppler Phase 4", "Impact Drill",
"The Fuschia Is Now", "Bronze Deco", "Black Laminate", "Desert Storm", "Ice Coaled", "Converter", "Facility Sketch", "Counter Terrace", "Vandal", "Phosphor", "Lore", "Sand Scale",
"The Traitor", "Old Roots", "Doppler", "Walnut", "Copper", "Arctic Camo", "Prototype", "Waves Perforated", "Grotto", "Muertos", "Golden Koi", "Target Acquired", "Cool Mint" };

std::string skinchanger::GetSkinName(int id) {


	auto it = std::find(SKINSID.begin(), SKINSID.end(), id);
	if (it != SKINSID.end()) {
		int nameindex = it - SKINSID.begin();
		return SKINSNAMES[nameindex];
	}

	return "ERROR";
}



void skinchanger::Run() {


	std::array<uintptr_t, 8> weapons;
	uintptr_t adr;

	memory::Read<uintptr_t>((uintptr_t)hack->LocalPlayer, &adr);
	memory::Read<std::array<uintptr_t, 8>>(adr + offsets::hMyWeapons, &weapons);

	for (const auto& handle : weapons) {
		uintptr_t weapon;
		uintptr_t toread = uintptr_t(hack->GetEntity((handle & 0xFFF) - 1));
		//uintptr_t toread = (hack->client + offsets::dwEntityList + (handle & 0xFFF) * 0x10) - 0x10;
		memory::Read<uintptr_t>(toread, &weapon);

		if (!weapon) {
			continue;
		}

		short id;
		memory::Read<short>(weapon + offsets::iItemDefinitionIndex, &id);

		bool shouldupdate = false;
		bool shouldFORCEUPDATE = false;
		std::int32_t a = -1;

		for (SKIN& skin : inventory) {
			if (skin.weaponID == id) {

				std::int32_t paint = 0;
				memory::Read<std::int32_t>(weapon + offsets::nFallbackPaintKit, &paint);
				shouldupdate = paint != skin.paint;

				
				if (shouldupdate) {

					std::int32_t desiredpaint = skin.paint;
					
					float desiredfloat = skin.wear;
					memory::Write<std::int32_t>(weapon + offsets::iItemIDHigh, &a);

					memory::Write<std::int32_t>(weapon + offsets::nFallbackPaintKit, &desiredpaint);
					memory::Write<float>(weapon + offsets::flFallbackWear, &desiredfloat);

					std::int32_t deltaticksadr;
					memory::Read<std::int32_t>(hack->engine + offsets::dwClientState, &deltaticksadr);
					memory::Write<std::int32_t>(deltaticksadr + 0x174, &a);

					
				}
				
			}
		}



		
	}
}