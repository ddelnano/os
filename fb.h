#ifndef INCLUDE_FB_H
#define INCLUDE_FB_H

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos);

int fb_write(char *text, unsigned int len);

#endif /* INCLUDE_FB_H */
