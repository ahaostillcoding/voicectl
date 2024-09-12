#ifndef _CONTROL_H_
#define _CONTROL_H_


#define LED7 "/sys/kernel/gec_ctrl/led_d7"
#define LED8 "/sys/kernel/gec_ctrl/led_d8"
#define LED9 "/sys/kernel/gec_ctrl/led_d9"
#define LED10 "/sys/kernel/gec_ctrl/led_d10"
#define LEDall "/sys/kernel/gec_ctrl/led_all"
#define beep "/sys/kernel/gec_ctrl/beep"

int led_beep_ctrl(char *filename, int state);

#endif