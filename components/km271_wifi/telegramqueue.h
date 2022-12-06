#ifndef TELEGRAMQUEUE_H
#define TELEGRAMQUEUE_H

#include <stdint.h>

static const int QUEUE_SIZE = 256;

namespace esphome {
namespace KM271 {


class TelegramQueue
{
public:
    TelegramQueue();
    bool enqueueTelegram(const uint8_t *data, uint8_t length);
    bool isEmpty() const;
    uint16_t remainingCapacity() const;
    uint8_t popTelegram(uint8_t *dest, uint8_t maxSize);

protected:
    void compact();

private:
    uint8_t queue[QUEUE_SIZE];
    uint16_t currentQueueLength;
    uint16_t currentQueueOffset;

};

}
}

#endif // TELEGRAMQUEUE_H
