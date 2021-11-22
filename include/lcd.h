#ifndef LCD_H
#define LCD_H

enum lcd_states
{
    L_STARTUP,
    L_INFO,
    L_INFO_SNEEZE,
    L_MENU //Future
};

void init_lcd(int rs, int en, int d4, int d5, int d6, int d7);
void tick_lcd(void);


#endif // LCD_H