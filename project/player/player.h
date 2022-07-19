#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "type.h"

#define SONG_ACCOUNT 10
#define SONG_LENGTH 256

/*歌曲结构*/
typedef struct song {
    uint8 music[SONG_LENGTH]; // 音符
    uint8 rhythm[SONG_LENGTH]; // 节奏
    uint16 length; // 音乐长度
}MUSIC;

/*歌单结构*/
typedef struct {
    MUSIC list[SONG_ACCOUNT]; // 歌单
    uint16 length; // 歌单的数目
}SONG;

#endif