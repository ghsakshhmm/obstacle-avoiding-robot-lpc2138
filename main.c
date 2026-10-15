#include <LPC213x.H>

/* L293D mapping (schematic ke hisaab se):
   P0.4 -> IN1, P0.5 -> IN2  (Motor 1)
   P0.6 -> IN3, P0.7 -> IN4  (Motor 2)
   P0.1 -> IR OUT
*/

#define IR_PIN   (1 << 1)
#define M_MASK   ((1 << 4) | (1 << 5) | (1 << 6) | (1 << 7))

/* IR module: obstacle par OUT = LOW (zyadatar modules).
   Simulation mein ulta chale to 0 ko 1 kar do. */
#define OBSTACLE_LEVEL  0

void delay_ms(unsigned int ms)
{
    volatile unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 1000; j++);
}

void motors_stop(void)
{
    IOCLR0 = M_MASK;
}

void motors_forward(void)
{
    IOCLR0 = (1 << 5) | (1 << 7);
    IOSET0 = (1 << 4) | (1 << 6);
}

void motors_reverse(void)
{
    IOCLR0 = (1 << 4) | (1 << 6);
    IOSET0 = (1 << 5) | (1 << 7);
}

/* Left turn: Motor 1 stop, Motor 2 forward */
void motors_left(void)
{
    IOCLR0 = (1 << 4) | (1 << 5) | (1 << 7);
    IOSET0 = (1 << 6);
}

/* Right turn: Motor 2 stop, Motor 1 forward */
void motors_right(void)
{
    IOCLR0 = (1 << 5) | (1 << 6) | (1 << 7);
    IOSET0 = (1 << 4);
}

int obstacle_detected(void)
{
    return ((IOPIN0 & IR_PIN) ? 1 : 0) == OBSTACLE_LEVEL;
}

int main(void)
{
    unsigned char turn_left = 1;

    PINSEL0 = 0x00000000;          /* P0.0-P0.15 GPIO */
    IODIR0 |= M_MASK;              /* motor pins output */
    IODIR0 &= ~IR_PIN;             /* IR pin input */

    motors_stop();
    delay_ms(200);

    while(1)
    {
        if(!obstacle_detected())
        {
            motors_forward();
        }
        else
        {
            motors_stop();
            delay_ms(200);

            motors_reverse();      /* thoda peeche */
            delay_ms(400);

            motors_stop();
            delay_ms(100);

            if(turn_left)
                motors_left();
            else
                motors_right();

            delay_ms(600);
            turn_left = !turn_left; /* agli baar opposite side */

            motors_stop();
            delay_ms(100);
        }
    }
}

