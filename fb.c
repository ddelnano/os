#include "fb.h"
#include "io.h"

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

#define FB_ROW_LENGTH 80
#define FB_TOTAL_CHARS 2000

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
}

static unsigned int fb_pos = 0;

// TODO: Cursor does not persit after scrolling
/**
 * fb_scroll
 *
 * Scrolls the framebuffer video buffer.  This is implemented by copying
 * row 1 to row 0, row 2 to row 1, etc.  Row 25 is nulled out and the
 * background color is set back to black.
 *
 * @param fb Pointer to the framebuffer memory location
 */
int fb_scroll(char *fb)
{
    for (unsigned int i = 0; i < 2000; i++) {
        // Copy each row to the one before it, with the exception
        // of the last row.  The last row will be 'nulled' out.
        if (i < FB_TOTAL_CHARS - FB_ROW_LENGTH) {
            fb[i*2] = fb[i*2+FB_ROW_LENGTH];
        } else {
            // null out character byte
            fb[i*2] = 0x00;
            // Set bg back to black
            fb[i*2+1] = 0x00;
        }
    }
    fb_pos -= FB_ROW_LENGTH;
    return 0;
}

int fb_write(char *text, unsigned int len)
{
    // 0x000b87d0
    char *fb = (char *) 0x000B8000;
    for (unsigned int i = 0; i < len; i++)
    {
        if (fb_pos == 2000) {
            fb_scroll(fb);
        }
        fb[(fb_pos)*2] = text[i];
        fb[(fb_pos)*2+1] = 0x28;
        fb_pos++;
    }
    fb_move_cursor(fb_pos);
    return 0;
}

