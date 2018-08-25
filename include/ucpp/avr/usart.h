#ifndef UCPP_AVR_USART_H
#define UCPP_AVR_USART_H

#include <avr/io.h>

namespace ucpp
{
namespace avr
{

template<unsigned int Baud>
struct usart
{
    void init()
    {
        constexpr unsigned int ubrr = F_CPU / 16 / Baud - 1;

        UBRR0H = (unsigned char)(ubrr>>8);
        UBRR0L = (unsigned char)ubrr;
        UCSR0B = (1<<RXEN0)|(1<<TXEN0);
        UCSR0C = (1<<USBS0)|(3<<UCSZ00);
    }

    void write_byte(unsigned char data)
    {
        while ( !( UCSR0A & (1<<UDRE0)) )
            ;

        UDR0 = data;
    }
};

} // namespace avr
} // namespace ucpp

#endif