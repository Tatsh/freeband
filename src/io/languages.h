#ifndef LANGUAGES_H
#define LANGUAGES_H

/* Add more here, we can go up to 0xFF (255); use ISO 639-1 for 2-character language names */
#define en_GB     0x00 /* English-UK */
#define en_US     0x01 /* English-USA */
#define zh_CN     0x02 /* Chinese-China (Standard Mandarin) (simplified Chinese) */
#define hi_IN     0x03 /* Hindi-India */
#define ur_IN     0x04 /* Urdu-India */
#define es_ES     0x05 /* Spanish-Spain */
#define ar_SA     0x06 /* Arabic-Saudi Arabia */
#define pt_PT     0x07 /* Portuguese-Portugal */
#define pt_BR     0x08 /* Portuguese-Brazil */
#define bn_BD     0x09 /* Bengali-Bangladesh */
#define bn_IN     0x0A /* Bengali-India */
#define ru_RU     0x0B /* Russian-Russia */
#define ru_BY     0x0C /* Russian-Belarus */
#define ru_KZ     0x0D /* Russian-Kazakhstan */
#define ru_KG     0x0E /* Russian-Kyrgyzstan */
#define ru_MD     0x0F /* Russian-Moldova */
#define ru_RO     0x10 /* Russian-Romania */
#define ru_TM     0x11 /* Russian-Turkmenistan */
#define ja_JP     0x12 /* Japanese-Japan */
#define de_DE     0x13 /* German-Germany */
#define sv_SV     0x14 /* Swedish-Sweden */
#define nb_NO     0x15 /* Norwegian Bokmal-Norway */
#define nn_NO     0x16 /* Norwegian Nynnorsk-Norway */
#define pa_IN     0x19 /* Punjabi-India */
#define fr_FR     0x1A /* French-France */
#define fr_BE     0x1B /* French-Belgium */
#define fr_CH     0x1C /* French-Switzerland */
#define fr_LU     0x1D /* French-Luxembourg */
#define fr_MC     0x1E /* French-Monaco */
#define fr_CA     0x1F /* French-Canada */
#define fr_HT     0x20 /* French-Haiti */
#define zh_CN_PY  0x21 /* Standard Mandarin written in Pinyin */
#define id_ID     0x22 /* Indonesian-Indonesia */
#define el_GR     0x23 /* Greek-Greece */
#define zh_HK     0x24 /* Cantonese-Hong Kong (traditional Chinese) */
#define es_PR     0x25 /* Spanish-Puerto Rico */
#define ja_JP_HK  0x26 /* Japanese-Japan (Hiragana and Katakana ONLY) */
#define pl_PL     0x27 /* Polish-Poland */

typedef char langINI_path;

typedef struct {
  char *single_player;
  char *multiplayer;
  char *online;
  char *options;
  char *quit;
}  languageStrings_screenMain_s;

typedef struct {
  char *select;
  char *back;
  char *up_down;
} languageStrings_screenFooter_s;

typedef struct {
  char *header;
  char *header_multiplayer;
  char *guitar;
  char *bass;
  char *drums;
  char *vocals;
} languageStrings_screenInstruments_s;

typedef struct {
  char *header;
  char *sort_by_tier;
  char *sort_title_AZ;
  char *sort_artist_AZ;
  char *sort_bpm;
} languageStrings_screenSongs_s;

typedef struct {
  char *header;
  char *header_multiplayer;
  char *easy;
  char *medium;
  char *hard;
  char *expert;
} languageStrings_screenDifficulty_s;

typedef struct {
  char *header;
  char *player_1;
  char *player_2;
  char *player_3;
  char *player_4;
  char *resume;
  char *resume_timer;
  char *restart;
  char *lefty_mode;
  char *change_difficulty;
  char *adjust_microphone_volume;
  char *quit;
  char *new_song;
  char *main_menu;
} languageStrings_screenPause_s;

extern dictionary *lang_d;

extern languageStrings_screenMain_s languageStrings_screenMain;
extern languageStrings_screenFooter_s languageStrings_screenFooter;
extern languageStrings_screenInstruments_s languageStrings_screenInstruments;
extern languageStrings_screenSongs_s languageStrings_screenSongs;
extern languageStrings_screenDifficulty_s languageStrings_screenDifficulty;
extern languageStrings_screenPause_s languageStrings_screenPause;

bool languages_loadLanguage(ushort lang);
void getStrings_screenMain();
void languages_checkForINIs();

#endif
