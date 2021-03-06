#include <wchar.h>
#include "constants.h"
wchar_t pwup[]=L"◀▶";
wchar_t pwup_safe[]=L"<>";
wchar_t tickbox[]=L"☐☒";
wchar_t speed_icon[num_speedset]=L"♺☂☺⚡☠";
wchar_t explo[]=L"><";
wchar_t icon_portale[2][3]={L"❨❩",L"❨❩"};
wchar_t icon_portale_safe[2][3]={L"()",L"()"};
wchar_t wall=L'▓'; // formaggio per il mouse
wchar_t wall_safe=L'▒';
wchar_t snakebody[4][4]={L"║╝║╚",L"╔═╚═",L"║╗║╔",L"╗═╝═"};
wchar_t snakebody2x[4][4][2]={{L"││",L"╧╛",L"││",L"╘╧"},{L"╒╤",L"══",L"╘╧",L"══"},{L"││",L"╤╕",L"││",L"╒╤"},{L"╤╕",L"══",L"╧╛",L"══"}};
wchar_t snakebody2x_safe[4][4][2]={{L"||",L"-/",L"||",L"\\-"},{L"/-",L"==",L"\\-",L"=="},{L"||",L"-\\",L"||",L"/-"},{L"-\\",L"==",L"-/",L"=="}};
//wchar_t snakebody2x[4][4][2]={{L"▐▌",L"╧╛",L"││",L"╘╧"},{L"╒╤",L"══",L"╘╧",L"══"},{L"││",L"╤╕",L"││",L"╒╤"},{L"╤╕",L"══",L"╧╛",L"══"}};
wchar_t head[2][4]={L"▲▶▼◀",L"△▷▽◁"};
wchar_t head2x[2][4][2]={{L"◢◣",L"▮►",L"◥◤",L"◄▮"},{L"◿◺",L"▯▻",L"◹◸",L"◅▯"}};
wchar_t head2x_safe[2][4][2]={{L"db",L"0-",L"qp",L"-0"},{L"db",L"0-",L"qp",L"-0"}};
wchar_t tail[4]=L"│─│─";
wchar_t tail2x[4][2]={L"▕▏",L"──",L"▕▏",L"──"};
wchar_t tail2x_safe[4][2]={L"| ",L"--",L" |",L"--"};
char scritta_pausa[5][50]={
    "    ____  _____  _  _  _____    ____    ___  \0",
    "   /__ / /___ / // // / ___/   /___/_  /__ \\ \0",
    "  / __/ //__// // //  \\ \\     / ____/ //  \\ \\\0",
    " / /   //  // //_// ___\\ \\   / /__   //___/ /\0",
    "/_/   //  // /___/  \\____/  /____/  /______/ \0"
};
char scritta_gameover[5][85]={
    "    ____    _____  ___     ____  ____         ______ __    __  ____    ___\0",
    "   / __/   /___ / / _/_  _/_  / /___/_       / __  / | |  / / /___/_  / _ \\\0",
    "  / /  _  //__// / / //_// / / / ____/      / / / /  | | / / / ____/ / _  /\0",
    " / /__// //  // / /  \\__/ / / / /__        / /_/ /   | |/ / / /__   / / \\ \\\0",
    "/_____/ //  // /_/       /_/ /____/       /_____/    |___/ /____/  /_/   \\_\\\0"
};
char scritta_titolo[5][70]={
    "   _____    __    __      __        __  __    ____    __\0",
    "  / ___/   /  \\  / /    _/ /_      / /_/ /   /___/_  / /\0",
    "  \\ \\     / /\\ \\/ /   _/ __ /_    /    _/   / ____/ /_/\0",
    "___\\ \\   / /  \\  /  _/ _/ /_ /_  /  /\\ \\   /  /__  __\0",
    "\\____/  /_/   /_/  /__/    /__/ /__/  \\_\\ /_____/ /_/\0"
};
char scritta_congrats[5][90]={
    "    ______  ______  __    __  ____    ___       _____  _______  ____    __\0",
    "   / ____/ / __  / /  \\  / / / __/   / _ \\     /___ / /__  __/ / __/   / /\0",
    "  / /     / / / / / /\\ \\/ / / /  _  / _  /    //__//    / /    \\ \\    /_/\0",
    " / /___  / /_/ / / /  \\  / / /__// / / \\ \\   //  //    / /   ___\\ \\  __\0",
    "/_____/ /_____/ /_/   /_/ /_____/ /_/   \\_\\ //  //    /_/    \\____/ /_/\0"
};
