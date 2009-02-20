#include "../freeband.h"
#include "../audio/audio.h"
#include "../graphics/graphics.h"
#include "../graphics/text.h"
#include "../io/prefs.h"
#include "game.h"
#include "main.h"
#include "pause.h"

bool songRunning = false;
bool songEnded = false;

GLfloat bringDownAngle = 90.0f;
GLfloat NE_coord_neg = 0.0f;
GLfloat NE_coord_pos = 1.0f;

texture_p buttonT[] = "GameData/themes/default/screenGame/button.png";
texture_p string[] = "GameData/themes/default/screenGame/string.png";
texture_p stringEndG[] = "GameData/themes/default/screenGame/button_top.png"; /* Green string */
texture_p trackloop_a[] = "GameData/themes/default/screenGame/loop_a.png";

uint combo = 0;
float life = 50.0f; /* From 0 to 100 */
uint score = 0;

/* Order of corners: top-left, bottom-left, bottom-right, top-right */
GLcoordsX button_sizeX[] = { 0.0f, 0.0f, 0.11f, 0.11f };
GLcoordsY button_sizeY[] = { 0.0f, 0.11f, 0.11f, 0.0f };
GLfloat button_rotationX = -0.055f;

GLcoordsX score_digit1X[] = { 0.0f, 0.0f, 0.05f, 0.05f };
GLcoordsY score_digit1Y[] = { 0.0f, 0.1f, 0.1f, 0.0f };

GLcoordsX stringGreenX[] = { 0.0f, 0.2f, 0.2f, 0.0f };
GLcoordsY stringGreenY[] = { -3.5f, -3.5f, 2.0f, 2.0f };
GLcoordsZ stringVertexZ[] = { -1.6f, 0.6f, 0.6f, -1.6f };

GLcoordsX stringEndG_X[] = { 0.0f, 1.0f, 1.0f, 0.0f };
GLcoordsX stringEndG_Y[] = { 1.0f, -0.2f, -0.2f, -1.0f };
GLcoordsZ stringEndG_Z[] = { -1.6f, 0.6f, 0.6f, -1.6f };

text_i combo0, combo1, combo2, combo3, combo4, combo5, combo6, combo7, combo8, combo9; /* Combo numbers */
text_i score0, score1, score2, score3, score4, score5, score6, score7, score8, score9; /* Score numbers */
texture_i trackloop_a_T, button_T, string_T, stringEndG_t;

button_s screenGame_button;

timing_window_s timing_window[NOTE_BUFFER];

GLvoid screenGame_buffer() {
  ushort i;
  
  gamePaused = false;
  screenPause_buffer(); /* Buffer the pause screen in advance */
  
  for (i = 0; i < NOTE_BUFFER; i++) {
    timing_window[i].note = 0;
    timing_window[i].speed = 0;
    timing_window[i].hit = COMPLETE_MISS;
  }
  
  SDL_EnableKeyRepeat(0, 0); /* Disable key repeat */
  
  if ((trackloop_a_T = graphics_loadTexture(trackloop_a, 0)) == -1)
    fprintf(stderr, "Unable to load texture: %s.\n", trackloop_a);
  
  if ((button_T = graphics_loadTexture(buttonT, 1)) == -1)
    fprintf(stderr, "Unable to load texture: %s.\n", buttonT);
  
  if ((stringEndG_t = graphics_loadTexture(stringEndG, 2)) == -1)
    fprintf(stderr, "Unable to load texture: %s.\n", stringEndG);
  /*u_width = graphics_getTextureWidth(stringEndG);
  u_height = graphics_getTextureHeight(stringEndG);
  f_width = graphics_scaleTextureWidth(u_width, u_height, 0.2f);
  for ( i = 0; i < 2; i++ ) stringEndG_X[i] = graphics_centreAtX(0.2, f_width);
  for ( i = 2; i < 4; i++ ) stringEndG_X[i] = stringEndG_X[i-2] + f_width;*/
  
  if ((string_T = graphics_loadTexture(string, 3)) == -1)
    fprintf(stderr, "Unable to load texture: %s.\n", string);

  /* Combo numbers */
  TTF_Font *bitstreamMonoBold;
  bitstreamMonoBold = TTF_OpenFont(path_bold_bitstreamVeraSansMono, DEFAULT_TEXT_PT);
  combo0 = text_load("0", bitstreamMonoBold, white);
  combo1 = text_load("1", bitstreamMonoBold, white);
  combo2 = text_load("2", bitstreamMonoBold, white);
  combo3 = text_load("3", bitstreamMonoBold, white);
  combo4 = text_load("4", bitstreamMonoBold, white);
  combo5 = text_load("5", bitstreamMonoBold, white);
  combo6 = text_load("6", bitstreamMonoBold, white);
  combo7 = text_load("7", bitstreamMonoBold, white);
  combo8 = text_load("8", bitstreamMonoBold, white);
  combo9 = text_load("9", bitstreamMonoBold, white);
  if (bitstreamMonoBold)
    TTF_CloseFont(bitstreamMonoBold);
  
  /* Prepare score numbers */
  TTF_Font *freeSansBold;
  freeSansBold = TTF_OpenFont(path_bold_freeSans, DEFAULT_TEXT_PT);
  score0 = text_load("0", freeSansBold, white);
  score1 = text_load("1", freeSansBold, white);
  score2 = text_load("2", freeSansBold, white);
  score3 = text_load("3", freeSansBold, white);
  score4 = text_load("4", freeSansBold, white);
  score5 = text_load("5", freeSansBold, white);
  score6 = text_load("6", freeSansBold, white);
  score7 = text_load("7", freeSansBold, white);
  score8 = text_load("8", freeSansBold, white);
  score9 = text_load("9", freeSansBold, white);
  if (freeSansBold)
    TTF_CloseFont(freeSansBold);

  return;
}

ushort screenGame_pollKey(ushort note) {
  (void)note;
  ushort hit = NOTE_HIT;
  return hit;
}

void screenGame_loop() {
  bool songFailed;
  ushort i;
  
  /* As of now this is in part pseudo code; still need a way to align incoming notes properly based upon timing data etc */
  
  while (songRunning) {
    
    if (timing_window[0].note != DEAD_NOTE || timing_window[0].note != SONG_END) { /* If the note is not a 'dead' note, where no buttons are hit, process */
      timing_window[0].hit = screenGame_pollKey(timing_window[0].note);
      
      switch (timing_window[0].hit) {
        case NOTE_HIT:
          ++combo;
          if (!songFailed)
            score += SCORE_ADD; /* This value may be dynamic based upon song difficulty */
          else
            score += SCORE_ADD_FAILED;
          life += LIFE_ADD;
          break;
          
        case NOTE_HIT_WITH_EXTRA:
          combo = 0; /* Reset the combo */
          if (!songFailed)
            life -= LIFE_ADD; /* Minus life value to increase chances of failure */
          /* audio_lowerTrackVolume();
          audio_sfxMissed(instrument); */
          break;
          
        case ALL_NOTES_HIT:
          combo = 0;
          if (!songFailed)
            life -= (LIFE_ADD * 5.0f); /* We give a greater penalty here */
          /* audio_lowerTrackVolume();
          audio_sfxMissed(instrument);
          audio_sfxAudienceBoo(); */
          break;
          
        case COMPLETE_MISS:
          combo = 0;
          if (!songFailed)
            life -= LIFE_ADD;
          /* audio_lowerTrackVolume(); */
          break;
          
        case FREEZE_BARELY_OFF:
          ++combo; /* Yes, we do keep counting the combo */
          if (!songFailed)
            score += SCORE_ADD / 2.0f;
          else
            score += SCORE_ADD_FAILED / 2.0f;
          /* screenGame_greyFreeze(timing_window.note);
          audio_lowerTrackVolume(); */
          break;
          
        case FREEZE_HIT_AND_RELEASED:
          /* screenGame_greyFreeze(timing_window.note);
          audio_lowerTrackVolume(); */
          break;
          
        default:
          break;
      }
      
    }
    
    if (life < 0.5f /* && !prefs_Songs.fail_to_end */) /* Song failed */
      break;
    else
      songFailed = true;
    
    for (i = 0; i < NOTE_BUFFER; i++) timing_window[i].note = timing_window[i+1].note; /* Shift all notes up 1 */
    /* timing_window[NOTE_BUFFER-1].note = screenGame_getNextNote();
   screenGame_alignNotes();*/
  }
  
  return;
}

float screenGame_failed() {
  float percent = 0.0f;
  return percent;
}

GLvoid screenGame_completed() {
  return;
}

GLvoid screenGame() {
  if (!gamePaused) { 
    /* Generate track */
    glPushMatrix(); {
      glTranslatef( 0.0f, 0.0f, -2.0f );
      glRotatef( 90.0f, 0.0f, 0.5f, 0.0f );
      if (bringDownAngle > 0.0f)
        glRotatef( bringDownAngle, 0.0, 0.0f, -1.0f );
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
      glBindTexture( GL_TEXTURE_2D, trackloop_a_T );
      glBegin( GL_QUADS ); {
        glNormal3f( 0.0f, 0.5f, 0.0f );
        glTexCoord2f( NE_coord_pos, 1.0 ); glColor4f( 1.0f, 1.0f, 1.0f, 1.0f ); glVertex3f( -3.5f, 0.5f, -TRACKWIDTH );
        glTexCoord2f( NE_coord_pos, 0.0 ); glColor4f( 1.0f, 1.0f, 1.0f, 1.0f ); glVertex3f( -3.5f, 0.5f,  TRACKWIDTH );
        glTexCoord2f( NE_coord_neg, 0.0 ); glColor4f( 1.0f, 1.0f, 1.0f, 0.0f ); glVertex3f(  2.0f, 0.5f,  TRACKWIDTH );
        glTexCoord2f( NE_coord_neg, 1.0 ); glColor4f( 1.0f, 1.0f, 1.0f, 0.0f ); glVertex3f(  2.0f, 0.5f, -TRACKWIDTH );
      } glEnd();
    } glPopMatrix();

    glPushMatrix(); { /* Left bumper */
      if (bringDownAngle > 0.0f)
        glRotatef( bringDownAngle, -1.0, 0.0f, 0.0f );
      glTranslatef( -TRACKWIDTH - 0.012f, 0.5f, -4.0f );
      glColor4f( 0.5f, 0.5f, 0.5f, 1.0f );
      glBindTexture( GL_TEXTURE_2D, 0 );
      gluCylinder( quadratic, 0.01f, 0.01f, 6.0f, 32, 32 );
    } glPopMatrix();

    glPushMatrix(); /* Right bumper */
    if (bringDownAngle > 0.0f)
      glRotatef( bringDownAngle, -1.0, 0.0f, 0.0f );
    glTranslatef( TRACKWIDTH + 0.012f, 0.5f, -4.0f );
    glColor4f( 0.5f, 0.5f, 0.5f, 1.0f );
    gluCylinder( quadratic, 0.01f, 0.01f, 6.0f, 32, 32 );
    glPopMatrix();
  
    /* Strings */
    glPushMatrix(); /* 1 */
    if (bringDownAngle > 0.0f)
      glRotatef( bringDownAngle, -1.0, 0.0f, 0.0f );
    glBindTexture( GL_TEXTURE_2D, string_T );
    glTranslatef( 0.0f, 0.0f, STRINGSTRANS);
    glBegin(GL_QUADS); {
      glTexCoord2f( 1.0f, 1.0f );
      glColor4f( 1.0f, 1.0f, 1.0f, 0.0f );
      glVertex3f( GREENSTRCOORD, 0.5f, STRINGLENGTH );
  
      glTexCoord2f( 1.0f, 0.0f );
      glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
      glVertex3f( GREENSTRCOORD, 0.5f, STRINGOFFSET );
  
      glTexCoord2f( 0.0f, 0.0f );
      glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
      glVertex3f( GREENSTRCOORD + STRINGWIDTH, 0.5f, STRINGOFFSET );
  
      glTexCoord2f( 0.0f, 1.0f );
      glColor4f( 1.0f, 1.0f, 1.0f, 0.0f );
      glVertex3f( GREENSTRCOORD + STRINGWIDTH, 0.5f, STRINGLENGTH );
    } glEnd();
    glPopMatrix();
  
    glPushMatrix(); /* 2 */
    if (bringDownAngle > 0.0f)
      glRotatef( bringDownAngle, -1.0, 0.0f, 0.0f );
    glTranslatef( 0.0f, 0.0f, STRINGSTRANS);
    glBegin(GL_QUADS); {
      glTexCoord2f( 1.0f, 1.0f );
      glColor4f( 1.0f, 1.0f, 1.0f, 0.0f );
      glVertex3f( GREENSTRCOORD + STRINGSPACE, 0.5f, STRINGLENGTH );
    
      glTexCoord2f( 1.0f, 0.0f );
      glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
      glVertex3f( GREENSTRCOORD + STRINGSPACE, 0.5f, STRINGOFFSET );
    
      glTexCoord2f( 0.0f, 0.0f );
      glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
      glVertex3f( (GREENSTRCOORD + STRINGSPACE) + STRINGWIDTH, 0.5f, STRINGOFFSET );
    
      glTexCoord2f( 0.0f, 1.0f );
      glColor4f( 1.0f, 1.0f, 1.0f, 0.0f );
      glVertex3f( (GREENSTRCOORD + STRINGSPACE) + STRINGWIDTH, 0.5f, STRINGLENGTH );
    } glEnd();
    glPopMatrix();
  
    glPushMatrix(); /* 3 */
    if (bringDownAngle > 0.0f)
      glRotatef( bringDownAngle, -1.0, 0.0f, 0.0f );
    glTranslatef( 0.0f, 0.0f, STRINGSTRANS);
    glBegin(GL_QUADS); {
      glTexCoord2f( 1.0f, 1.0f );
      glColor4f( 1.0f, 1.0f, 1.0f, 0.0f );
      glVertex3f( (GREENSTRCOORD + (2.0f * STRINGSPACE)), 0.5f, -4.5f ); /* For appearance reasons */
    
      glTexCoord2f( 1.0f, 0.0f );
      glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
      glVertex3f( (GREENSTRCOORD + (2.0f * STRINGSPACE)), 0.5f, STRINGOFFSET );
    
      glTexCoord2f( 0.0f, 0.0f );
      glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
      glVertex3f( (GREENSTRCOORD + (2.0f * STRINGSPACE)) + STRINGWIDTH, 0.5f, STRINGOFFSET );
    
      glTexCoord2f( 0.0f, 1.0f );
      glColor4f( 1.0f, 1.0f, 1.0f, 0.0f );
      glVertex3f( (GREENSTRCOORD + (2.0f * STRINGSPACE)) + STRINGWIDTH, 0.5f, -4.5f );
    } glEnd();
    glPopMatrix();
  
    glPushMatrix(); /* 4 */
    if (bringDownAngle > 0.0f)
      glRotatef( bringDownAngle, -1.0, 0.0f, 0.0f );
    glTranslatef( 0.0f, 0.0f, STRINGSTRANS);
    glBegin(GL_QUADS); {
      glTexCoord2f( 1.0f, 1.0f );
      glColor4f( 1.0f, 1.0f, 1.0f, 0.0f );
      glVertex3f( (GREENSTRCOORD + (3.0f * STRINGSPACE)), 0.5f, STRINGLENGTH );
    
      glTexCoord2f( 1.0f, 0.0f );
      glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
      glVertex3f( (GREENSTRCOORD + (3.0f * STRINGSPACE)), 0.5f, STRINGOFFSET );
    
      glTexCoord2f( 0.0f, 0.0f );
      glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
      glVertex3f( (GREENSTRCOORD + (3.0f * STRINGSPACE)) + STRINGWIDTH, 0.5f, STRINGOFFSET );
    
      glTexCoord2f( 0.0f, 1.0f );
      glColor4f( 1.0f, 1.0f, 1.0f, 0.0f );
      glVertex3f( (GREENSTRCOORD + (3.0f * STRINGSPACE)) + STRINGWIDTH, 0.5f, STRINGLENGTH );
    } glEnd();
    glPopMatrix();
  
    glPushMatrix(); /* 5 */
    if (bringDownAngle > 0.0f)
      glRotatef( bringDownAngle, -1.0, 0.0f, 0.0f );
    glTranslatef( 0.0f, 0.0f, STRINGSTRANS);
    glBegin(GL_QUADS); {
      glTexCoord2f( 1.0f, 1.0f );
      glColor4f( 1.0f, 1.0f, 1.0f, 0.0f );
      glVertex3f( (GREENSTRCOORD + (4.0f * STRINGSPACE)), 0.5f, STRINGLENGTH );
    
      glTexCoord2f( 1.0f, 0.0f );
      glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
      glVertex3f( (GREENSTRCOORD + (4.0f * STRINGSPACE)), 0.5f, STRINGOFFSET );
    
      glTexCoord2f( 0.0f, 0.0f );
      glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
      glVertex3f( (GREENSTRCOORD + (4.0f * STRINGSPACE)) + STRINGWIDTH, 0.5f, STRINGOFFSET );
    
      glTexCoord2f( 0.0f, 1.0f );
      glColor4f( 1.0f, 1.0f, 1.0f, 0.0f );
      glVertex3f( (GREENSTRCOORD + (4.0f * STRINGSPACE)) + STRINGWIDTH, 0.5f, STRINGLENGTH );
    } glEnd();
    glPopMatrix();
  
    if (bringDownAngle < 0.0f) { /* Only load buttons, etc after has been placed down entirely */
      /* Buttons */
      glPushMatrix(); /* Green */
      glTranslatef( GREENNOTE, 0.35f, 1.64f );
      glRotatef( 90.0f, button_rotationX, 0.0f, 0.0 ); /* Flatten against track */
      if (screenGame_button.g)
        glColor4f( 0.373f, 1.0f, 0.35f, 1.0f);
      else
        glColor4f( buttonColour_green[0], buttonColour_green[1], buttonColour_green[2], buttonColour_green[3] );
      glBindTexture(GL_TEXTURE_2D, texture[1]);
      graphics_positionTexture(button_sizeX, button_sizeY, defVertexZ);
      glPopMatrix();
    
      glPushMatrix(); /* Red */
      glTranslatef( GREENNOTE + NOTEDIFF, 0.35f, 1.64f );
      glRotatef( 90.0f, button_rotationX, 0.0f, 0.0 ); /* Flatten against track */
      if (screenGame_button.r)
        glColor4f( 1.0f, 0.541f, 0.541f, 1.0f);
      else
        glColor4f( buttonColour_red[0], buttonColour_red[1], buttonColour_red[2], buttonColour_red[3] );
      graphics_positionTexture(button_sizeX, button_sizeY, defVertexZ);
      glPopMatrix();
    
      glPushMatrix(); /* Yellow */
      glTranslatef( GREENNOTE + (2.0f * NOTEDIFF), 0.35f, 1.64f );
      glRotatef( 90.0f, button_rotationX, 0.0f, 0.0 ); /* Flatten against track */
      if (screenGame_button.y)
        glColor4f( 1.0f, 1.0f, 1.0f, 1.0f);
      else
        glColor4f( buttonColour_yellow[0], buttonColour_yellow[1], buttonColour_yellow[2], buttonColour_yellow[3] );
      graphics_positionTexture(button_sizeX, button_sizeY, defVertexZ);
      glPopMatrix();
    
      glPushMatrix(); /* Blue */
      glTranslatef( GREENNOTE + (3.0f * NOTEDIFF), 0.35f, 1.64f );
      glRotatef( 90.0f, button_rotationX, 0.0f, 0.0 ); /* Flatten against track */
      if (screenGame_button.b)
        glColor4f( 0.282f, 0.918, 1.0f, 1.0f );
      else
        glColor4f( buttonColour_blue[0], buttonColour_blue[1], buttonColour_blue[2], buttonColour_blue[3] );
      graphics_positionTexture(button_sizeX, button_sizeY, defVertexZ);
      glPopMatrix();
    
      glPushMatrix(); /* Orange */
      glTranslatef( GREENNOTE + (4.0f * NOTEDIFF), 0.35f, 1.64f );
      glRotatef( 90.0f, button_rotationX, 0.0f, 0.0 ); /* Flatten against track */
      if (screenGame_button.o)
        glColor4f( 1.0f, 0.867f, 0.506f, 1.0f );
      else
        glColor4f( buttonColour_orange[0], buttonColour_orange[1], buttonColour_orange[2], buttonColour_orange[3] );
      graphics_positionTexture(button_sizeX, button_sizeY, defVertexZ);
      glPopMatrix();
    
      /* Score */
      glPushMatrix();
      glTranslatef( 0.5f, 0.0f, 0.0f );
      glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
      glBindTexture( GL_TEXTURE_2D, score0 );
      graphics_positionTexture(score_digit1X, score_digit1Y, defVertexZ);
      glPopMatrix();
    
      NE_coord_neg -= 0.005f;
      NE_coord_pos -= 0.005f;
    }
  
    if (bringDownAngle > 0.0f)
      bringDownAngle -= 0.2f;
  }
  else
    screenPause();
  
  return;
}
